//===- MBLAZEOptAddrMode.cpp ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
/// \file
/// This pass folds LD/ST + ADD pairs into Pre/Post-increment form  of
/// load/store instructions.
//===----------------------------------------------------------------------===//

#include "MBLAZE.h"
#define GET_INSTRMAP_INFO
#include "MBLAZEInstrInfo.h"
#include "MBLAZETargetMachine.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineDominators.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/InitializePasses.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define OPTADDRMODE_DESC "MBLAZE load/store address mode"
#define OPTADDRMODE_NAME "MBLAZE-addr-mode"
#define DEBUG_TYPE "MBLAZE-addr-mode"

namespace llvm {
FunctionPass *createMBLAZEOptAddrMode();
void initializeMBLAZEOptAddrModePass(PassRegistry &);
} // end namespace llvm

namespace {
class MBLAZEOptAddrMode : public MachineFunctionPass {
public:
  static char ID;

  MBLAZEOptAddrMode() : MachineFunctionPass(ID) {}

  StringRef getPassName() const override { return OPTADDRMODE_DESC; }

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesCFG();
    MachineFunctionPass::getAnalysisUsage(AU);
    AU.addRequired<MachineDominatorTree>();
    AU.addPreserved<MachineDominatorTree>();
  }

  bool runOnMachineFunction(MachineFunction &MF) override;

private:
  const MBLAZESubtarget *AST = nullptr;
  const MBLAZEInstrInfo *AII = nullptr;
  MachineRegisterInfo *MRI = nullptr;
  MachineDominatorTree *MDT = nullptr;

  // Tries to combine \p Ldst with increment of its base register to form
  // single post-increment instruction.
  MachineInstr *tryToCombine(MachineInstr &Ldst);

  // Returns true if result of \p Add is not used before \p Ldst
  bool noUseOfAddBeforeLoadOrStore(const MachineInstr *Add,
                                   const MachineInstr *Ldst);

  // Returns true if load/store instruction \p Ldst can be hoisted up to
  // instruction \p To
  bool canHoistLoadStoreTo(MachineInstr *Ldst, MachineInstr *To);

  // Returns true if load/store instruction \p Ldst can be sunk down
  // to instruction \p To
  bool canSinkLoadStoreTo(MachineInstr *Ldst, MachineInstr *To);

  // Check if instructions \p Ldst and \p Add can be moved to become adjacent
  // If they can return instruction which need not to move.
  // If \p Uses is not null, fill it with instructions after \p Ldst which use
  // \p Ldst's base register
  MachineInstr *canJoinInstructions(MachineInstr *Ldst, MachineInstr *Add,
                                    SmallVectorImpl<MachineInstr *> *Uses);

  // Returns true if all instruction in \p Uses array can be adjusted
  // to accomodate increment of register \p BaseReg by \p Incr
  bool canFixPastUses(const ArrayRef<MachineInstr *> &Uses,
                      MachineOperand &Incr, unsigned BaseReg);

  // Update all instructions in \p Uses to accomodate increment
  // of \p BaseReg by \p Offset
  void fixPastUses(ArrayRef<MachineInstr *> Uses, unsigned BaseReg,
                   int64_t Offset);

  // Change instruction \p Ldst to postincrement form.
  // \p NewBase is register to hold update base value
  // \p NewOffset is instruction's new offset
  void changeToAddrMode(MachineInstr &Ldst, unsigned NewOpcode,
                        unsigned NewBase, MachineOperand &NewOffset);

  bool processBasicBlock(MachineBasicBlock &MBB);
};

} // end anonymous namespace

char MBLAZEOptAddrMode::ID = 0;
INITIALIZE_PASS_BEGIN(MBLAZEOptAddrMode, OPTADDRMODE_NAME, OPTADDRMODE_DESC, false,
                      false)
INITIALIZE_PASS_DEPENDENCY(MachineDominatorTree)
INITIALIZE_PASS_END(MBLAZEOptAddrMode, OPTADDRMODE_NAME, OPTADDRMODE_DESC, false,
                    false)

// Return true if \p Off can be used as immediate offset
// operand of load/store instruction (S9 literal)
static bool isValidLoadStoreOffset(int64_t Off) { return isInt<9>(Off); }

// Return true if \p Off can be used as immediate operand of
// ADD/SUB instruction (U6 literal)
static bool isValidIncrementOffset(int64_t Off) { return isUInt<6>(Off); }

static bool isAddConstantOp(const MachineInstr &MI, int64_t &Amount) {
  int64_t Sign = 1;
  switch (MI.getOpcode()) {
  case MBLAZE::SUB_rru6:
    Sign = -1;
    LLVM_FALLTHROUGH;
  case MBLAZE::ADD_rru6:
    assert(MI.getOperand(2).isImm() && "Expected immediate operand");
    Amount = Sign * MI.getOperand(2).getImm();
    return true;
  default:
    return false;
  }
}

// Return true if \p MI dominates of uses of virtual register \p VReg
static bool dominatesAllUsesOf(const MachineInstr *MI, unsigned VReg,
                               MachineDominatorTree *MDT,
                               MachineRegisterInfo *MRI) {

  assert(Register::isVirtualRegister(VReg) && "Expected virtual register!");

  for (auto it = MRI->use_nodbg_begin(VReg), end = MRI->use_nodbg_end();
       it != end; ++it) {
    MachineInstr *User = it->getParent();
    if (User->isPHI()) {
      unsigned BBOperandIdx = User->getOperandNo(&*it) + 1;
      MachineBasicBlock *MBB = User->getOperand(BBOperandIdx).getMBB();
      if (MBB->empty()) {
        const MachineBasicBlock *InstBB = MI->getParent();
        assert(InstBB != MBB && "Instruction found in empty MBB");
        if (!MDT->dominates(InstBB, MBB))
          return false;
        continue;
      }
      User = &*MBB->rbegin();
    }

    if (!MDT->dominates(MI, User))
      return false;
  }
  return true;
}

// Return true if \p MI is load/store instruction with immediate offset
// which can be adjusted by \p Disp
static bool isLoadStoreThatCanHandleDisplacement(const TargetInstrInfo *TII,
                                                 const MachineInstr &MI,
                                                 int64_t Disp) {
  unsigned BasePos, OffPos;
  if (!TII->getBaseAndOffsetPosition(MI, BasePos, OffPos))
    return false;
  const MachineOperand &MO = MI.getOperand(OffPos);
  if (!MO.isImm())
    return false;
  int64_t Offset = MO.getImm() + Disp;
  return isValidLoadStoreOffset(Offset);
}

bool MBLAZEOptAddrMode::noUseOfAddBeforeLoadOrStore(const MachineInstr *Add,
                                                 const MachineInstr *Ldst) {
  Register R = Add->getOperand(0).getReg();
  return dominatesAllUsesOf(Ldst, R, MDT, MRI);
}

MachineInstr *MBLAZEOptAddrMode::tryToCombine(MachineInstr &Ldst) {
  assert(Ldst.mayLoadOrStore() && "LD/ST instruction expected");

  unsigned BasePos, OffsetPos;

  LLVM_DEBUG(dbgs() << "[ABAW] tryToCombine " << Ldst);
  if (!AII->getBaseAndOffsetPosition(Ldst, BasePos, OffsetPos)) {
    LLVM_DEBUG(dbgs() << "[ABAW] Not a recognized load/store\n");
    return nullptr;
  }

  MachineOperand &Base = Ldst.getOperand(BasePos);
  MachineOperand &Offset = Ldst.getOperand(OffsetPos);

  assert(Base.isReg() && "Base operand must be register");
  if (!Offset.isImm()) {
    LLVM_DEBUG(dbgs() << "[ABAW] Offset is not immediate\n");
    return nullptr;
  }

  Register B = Base.getReg();
  if (Register::isStackSlot(B) || !Register::isVirtualRegister(B)) {
    LLVM_DEBUG(dbgs() << "[ABAW] Base is not VReg\n");
    return nullptr;
  }

  // TODO: try to generate address preincrement
  if (Offset.getImm() != 0) {
    LLVM_DEBUG(dbgs() << "[ABAW] Non-zero offset\n");
    return nullptr;
  }

  for (auto &Add : MRI->use_nodbg_instructions(B)) {
    int64_t Incr;
    if (!isAddConstantOp(Add, Incr))
      continue;
    if (!isValidLoadStoreOffset(Incr))
      continue;

    SmallVector<MachineInstr *, 8> Uses;
    MachineInstr *MoveTo = canJoinInstructions(&Ldst, &Add, &Uses);

    if (!MoveTo)
      continue;

    if (!canFixPastUses(Uses, Add.getOperand(2), B))
      continue;

    LLVM_DEBUG(MachineInstr *First = &Ldst; MachineInstr *Last = &Add;
               if (MDT->dominates(Last, First)) std::swap(First, Last);
               dbgs() << "[ABAW] Instructions " << *First << " and " << *Last
                      << " combined\n";

    );

    MachineInstr *Result = Ldst.getNextNode();
    if (MoveTo == &Add) {
      Ldst.removeFromParent();
      Add.getParent()->insertAfter(Add.getIterator(), &Ldst);
    }
    if (Result == &Add)
      Result = Result->getNextNode();

    fixPastUses(Uses, B, Incr);

    int NewOpcode = MBLAZE::getPostIncOpcode(Ldst.getOpcode());
    assert(NewOpcode > 0 && "No postincrement form found");
    unsigned NewBaseReg = Add.getOperand(0).getReg();
    changeToAddrMode(Ldst, NewOpcode, NewBaseReg, Add.getOperand(2));
    Add.eraseFromParent();

    return Result;
  }
  return nullptr;
}

MachineInstr *
MBLAZEOptAddrMode::canJoinInstructions(MachineInstr *Ldst, MachineInstr *Add,
                                    SmallVectorImpl<MachineInstr *> *Uses) {
  assert(Ldst && Add && "NULL instruction passed");

  MachineInstr *First = Add;
  MachineInstr *Last = Ldst;
  if (MDT->dominates(Ldst, Add))
    std::swap(First, Last);
  else if (!MDT->dominates(Add, Ldst))
    return nullptr;

  LLVM_DEBUG(dbgs() << "canJoinInstructions: " << *First << *Last);

  unsigned BasePos, OffPos;

  if (!AII->getBaseAndOffsetPosition(*Ldst, BasePos, OffPos)) {
    LLVM_DEBUG(
        dbgs()
        << "[canJoinInstructions] Cannot determine base/offset position\n");
    return nullptr;
  }

  Register BaseReg = Ldst->getOperand(BasePos).getReg();

  // prohibit this:
  //   v1 = add v0, c
  //   st v1, [v0, 0]
  // and this
  //   st v0, [v0, 0]
  //   v1 = add v0, c
  if (Ldst->mayStore() && Ldst->getOperand(0).isReg()) {
    Register StReg = Ldst->getOperand(0).getReg();
    if (Add->getOperand(0).getReg() == StReg || BaseReg == StReg) {
      LLVM_DEBUG(dbgs() << "[canJoinInstructions] Store uses result of Add\n");
      return nullptr;
    }
  }

  SmallVector<MachineInstr *, 4> UsesAfterLdst;
  SmallVector<MachineInstr *, 4> UsesAfterAdd;
  for (MachineInstr &MI : MRI->use_nodbg_instructions(BaseReg)) {
    if (&MI == Ldst || &MI == Add)
      continue;
    if (&MI != Add && MDT->dominates(Ldst, &MI))
      UsesAfterLdst.push_back(&MI);
    else if (!MDT->dominates(&MI, Ldst))
      return nullptr;
    if (MDT->dominates(Add, &MI))
      UsesAfterAdd.push_back(&MI);
  }

  MachineInstr *Result = nullptr;

  if (First == Add) {
    //  n = add b, i
    //  ...
    //  x = ld [b, o] or x = ld [n, o]

    if (noUseOfAddBeforeLoadOrStore(First, Last)) {
      Result = Last;
      LLVM_DEBUG(dbgs() << "[canJoinInstructions] Can sink Add down to Ldst\n");
    } else if (canHoistLoadStoreTo(Ldst, Add)) {
      Result = First;
      LLVM_DEBUG(dbgs() << "[canJoinInstructions] Can hoist Ldst to Add\n");
    }
  } else {
    // x = ld [b, o]
    // ...
    // n = add b, i
    Result = First;
    LLVM_DEBUG(dbgs() << "[canJoinInstructions] Can hoist Add to Ldst\n");
  }
  if (Result && Uses)
    *Uses = (Result == Ldst) ? UsesAfterLdst : UsesAfterAdd;
  return Result;
}

bool MBLAZEOptAddrMode::canFixPastUses(const ArrayRef<MachineInstr *> &Uses,
                                    MachineOperand &Incr, unsigned BaseReg) {

  assert(Incr.isImm() && "Expected immediate increment");
  int64_t NewOffset = Incr.getImm();
  for (MachineInstr *MI : Uses) {
    int64_t Dummy;
    if (isAddConstantOp(*MI, Dummy)) {
      if (isValidIncrementOffset(Dummy + NewOffset))
        continue;
      return false;
    }
    if (isLoadStoreThatCanHandleDisplacement(AII, *MI, -NewOffset))
      continue;
    LLVM_DEBUG(dbgs() << "Instruction cannot handle displacement " << -NewOffset
                      << ": " << *MI);
    return false;
  }
  return true;
}

void MBLAZEOptAddrMode::fixPastUses(ArrayRef<MachineInstr *> Uses,
                                 unsigned NewBase, int64_t NewOffset) {

  for (MachineInstr *MI : Uses) {
    int64_t Amount;
    unsigned BasePos, OffPos;
    if (isAddConstantOp(*MI, Amount)) {
      NewOffset += Amount;
      assert(isValidIncrementOffset(NewOffset) &&
             "New offset won't fit into ADD instr");
      BasePos = 1;
      OffPos = 2;
    } else if (AII->getBaseAndOffsetPosition(*MI, BasePos, OffPos)) {
      MachineOperand &MO = MI->getOperand(OffPos);
      assert(MO.isImm() && "expected immediate operand");
      NewOffset += MO.getImm();
      assert(isValidLoadStoreOffset(NewOffset) &&
             "New offset won't fit into LD/ST");
    } else
      llvm_unreachable("unexpected instruction");

    MI->getOperand(BasePos).setReg(NewBase);
    MI->getOperand(OffPos).setImm(NewOffset);
  }
}

bool MBLAZEOptAddrMode::canHoistLoadStoreTo(MachineInstr *Ldst, MachineInstr *To) {
  if (Ldst->getParent() != To->getParent())
    return false;
  MachineBasicBlock::const_iterator MI(To), ME(Ldst),
      End(Ldst->getParent()->end());

  bool IsStore = Ldst->mayStore();
  for (; MI != ME && MI != End; ++MI) {
    if (MI->isDebugValue())
      continue;
    if (MI->mayStore() || MI->isCall() || MI->isInlineAsm() ||
        MI->hasUnmodeledSideEffects())
      return false;
    if (IsStore && MI->mayLoad())
      return false;
  }

  for (auto &O : Ldst->explicit_operands()) {
    if (!O.isReg() || !O.isUse())
      continue;
    MachineInstr *OpDef = MRI->getVRegDef(O.getReg());
    if (!OpDef || !MDT->dominates(OpDef, To))
      return false;
  }
  return true;
}

bool MBLAZEOptAddrMode::canSinkLoadStoreTo(MachineInstr *Ldst, MachineInstr *To) {
  // Can only sink load/store within same BB
  if (Ldst->getParent() != To->getParent())
    return false;
  MachineBasicBlock::const_iterator MI(Ldst), ME(To),
      End(Ldst->getParent()->end());

  bool IsStore = Ldst->mayStore();
  bool IsLoad = Ldst->mayLoad();

  Register ValReg = IsLoad ? Ldst->getOperand(0).getReg() : Register();
  for (; MI != ME && MI != End; ++MI) {
    if (MI->isDebugValue())
      continue;
    if (MI->mayStore() || MI->isCall() || MI->isInlineAsm() ||
        MI->hasUnmodeledSideEffects())
      return false;
    if (IsStore && MI->mayLoad())
      return false;
    if (ValReg && MI->readsVirtualRegister(ValReg))
      return false;
  }
  return true;
}

void MBLAZEOptAddrMode::changeToAddrMode(MachineInstr &Ldst, unsigned NewOpcode,
                                      unsigned NewBase,
                                      MachineOperand &NewOffset) {
  bool IsStore = Ldst.mayStore();
  unsigned BasePos, OffPos;
  MachineOperand Src = MachineOperand::CreateImm(0xDEADBEEF);
  AII->getBaseAndOffsetPosition(Ldst, BasePos, OffPos);

  Register BaseReg = Ldst.getOperand(BasePos).getReg();

  Ldst.RemoveOperand(OffPos);
  Ldst.RemoveOperand(BasePos);

  if (IsStore) {
    Src = Ldst.getOperand(BasePos - 1);
    Ldst.RemoveOperand(BasePos - 1);
  }

  Ldst.setDesc(AST->getInstrInfo()->get(NewOpcode));
  Ldst.addOperand(MachineOperand::CreateReg(NewBase, true));
  if (IsStore)
    Ldst.addOperand(Src);
  Ldst.addOperand(MachineOperand::CreateReg(BaseReg, false));
  Ldst.addOperand(NewOffset);
  LLVM_DEBUG(dbgs() << "[ABAW] New Ldst: " << Ldst);
}

bool MBLAZEOptAddrMode::processBasicBlock(MachineBasicBlock &MBB) {
  bool Changed = false;
  for (auto MI = MBB.begin(), ME = MBB.end(); MI != ME; ++MI) {
    if (MI->isDebugValue())
      continue;
    if (!MI->mayLoad() && !MI->mayStore())
      continue;
    if (MBLAZE::getPostIncOpcode(MI->getOpcode()) < 0)
      continue;
    MachineInstr *Res = tryToCombine(*MI);
    if (Res) {
      Changed = true;
      // Res points to the next instruction. Rewind to process it
      MI = std::prev(Res->getIterator());
    }
  }
  return Changed;
}

bool MBLAZEOptAddrMode::runOnMachineFunction(MachineFunction &MF) {
  if (skipFunction(MF.getFunction()))
    return false;

  AST = &MF.getSubtarget<MBLAZESubtarget>();
  AII = AST->getInstrInfo();
  MRI = &MF.getRegInfo();
  MDT = &getAnalysis<MachineDominatorTree>();

  bool Changed = false;
  for (auto &MBB : MF)
    Changed |= processBasicBlock(MBB);
  return Changed;
}

//===----------------------------------------------------------------------===//
//                         Public Constructor Functions
//===----------------------------------------------------------------------===//

FunctionPass *llvm::createMBLAZEOptAddrMode() { return new MBLAZEOptAddrMode(); }
