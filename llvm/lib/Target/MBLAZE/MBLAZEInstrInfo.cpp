//===- MBLAZEInstrInfo.cpp - MBLAZE Instruction Information -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the MBLAZE implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "MBLAZEInstrInfo.h"
#include "MBLAZE.h"
#include "MBLAZEMachineFunctionInfo.h"
#include "MBLAZESubtarget.h"
#include "MCTargetDesc/MBLAZEInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "MBLAZEGenInstrInfo.inc"

#define DEBUG_TYPE "MBLAZE-inst-info"

enum AddrIncType {
    NoAddInc = 0,
    PreInc   = 1,
    PostInc  = 2,
    Scaled   = 3
};

enum TSFlagsConstants {
    TSF_AddrModeOff = 0,
    TSF_AddModeMask = 3
};

// Pin the vtable to this file.
void MBLAZEInstrInfo::anchor() {}

MBLAZEInstrInfo::MBLAZEInstrInfo()
    : MBLAZEGenInstrInfo(MBLAZE::ADJCALLSTACKDOWN, MBLAZE::ADJCALLSTACKUP), RI() {}

static bool isZeroImm(const MachineOperand &Op) {
  return Op.isImm() && Op.getImm() == 0;
}

static bool isLoad(int Opcode) {
  return Opcode == MBLAZE::LD_rs9 || Opcode == MBLAZE::LDH_rs9 ||
         Opcode == MBLAZE::LDB_rs9;
}

static bool isStore(int Opcode) {
  return Opcode == MBLAZE::ST_rs9 || Opcode == MBLAZE::STH_rs9 ||
         Opcode == MBLAZE::STB_rs9;
}

/// If the specified machine instruction is a direct
/// load from a stack slot, return the virtual or physical register number of
/// the destination along with the FrameIndex of the loaded stack slot.  If
/// not, return 0.  This predicate must return 0 if the instruction has
/// any side effects other than loading from the stack slot.
unsigned MBLAZEInstrInfo::isLoadFromStackSlot(const MachineInstr &MI,
                                           int &FrameIndex) const {
  int Opcode = MI.getOpcode();
  if (isLoad(Opcode)) {
    if ((MI.getOperand(1).isFI()) &&  // is a stack slot
        (MI.getOperand(2).isImm()) && // the imm is zero
        (isZeroImm(MI.getOperand(2)))) {
      FrameIndex = MI.getOperand(1).getIndex();
      return MI.getOperand(0).getReg();
    }
  }
  return 0;
}

/// If the specified machine instruction is a direct
/// store to a stack slot, return the virtual or physical register number of
/// the source reg along with the FrameIndex of the loaded stack slot.  If
/// not, return 0.  This predicate must return 0 if the instruction has
/// any side effects other than storing to the stack slot.
unsigned MBLAZEInstrInfo::isStoreToStackSlot(const MachineInstr &MI,
                                          int &FrameIndex) const {
  int Opcode = MI.getOpcode();
  if (isStore(Opcode)) {
    if ((MI.getOperand(1).isFI()) &&  // is a stack slot
        (MI.getOperand(2).isImm()) && // the imm is zero
        (isZeroImm(MI.getOperand(2)))) {
      FrameIndex = MI.getOperand(1).getIndex();
      return MI.getOperand(0).getReg();
    }
  }
  return 0;
}

/// Return the inverse of passed condition, i.e. turning COND_E to COND_NE.
static MBLAZECC::CondCode GetOppositeBranchCondition(MBLAZECC::CondCode CC) {
  switch (CC) {
  default:
    llvm_unreachable("Illegal condition code!");
  case MBLAZECC::EQ:
    return MBLAZECC::NE;
  case MBLAZECC::NE:
    return MBLAZECC::EQ;
  case MBLAZECC::LO:
    return MBLAZECC::HS;
  case MBLAZECC::HS:
    return MBLAZECC::LO;
  case MBLAZECC::GT:
    return MBLAZECC::LE;
  case MBLAZECC::GE:
    return MBLAZECC::LT;
  case MBLAZECC::VS:
    return MBLAZECC::VC;
  case MBLAZECC::VC:
    return MBLAZECC::VS;
  case MBLAZECC::LT:
    return MBLAZECC::GE;
  case MBLAZECC::LE:
    return MBLAZECC::GT;
  case MBLAZECC::HI:
    return MBLAZECC::LS;
  case MBLAZECC::LS:
    return MBLAZECC::HI;
  case MBLAZECC::NZ:
    return MBLAZECC::Z;
  case MBLAZECC::Z:
    return MBLAZECC::NZ;
  }
}

static bool isUncondBranchOpcode(int Opc) { return Opc == MBLAZE::BR; }

static bool isCondBranchOpcode(int Opc) {
  return Opc == MBLAZE::BRcc_rr_p || Opc == MBLAZE::BRcc_ru6_p;
}

static bool isJumpOpcode(int Opc) { return Opc == MBLAZE::J; }

/// Analyze the branching code at the end of MBB, returning
/// true if it cannot be understood (e.g. it's a switch dispatch or isn't
/// implemented for a target).  Upon success, this returns false and returns
/// with the following information in various cases:
///
/// 1. If this block ends with no branches (it just falls through to its succ)
///    just return false, leaving TBB/FBB null.
/// 2. If this block ends with only an unconditional branch, it sets TBB to be
///    the destination block.
/// 3. If this block ends with a conditional branch and it falls through to a
///    successor block, it sets TBB to be the branch destination block and a
///    list of operands that evaluate the condition. These operands can be
///    passed to other TargetInstrInfo methods to create new branches.
/// 4. If this block ends with a conditional branch followed by an
///    unconditional branch, it returns the 'true' destination in TBB, the
///    'false' destination in FBB, and a list of operands that evaluate the
///    condition.  These operands can be passed to other TargetInstrInfo
///    methods to create new branches.
///
/// Note that RemoveBranch and insertBranch must be implemented to support
/// cases where this method returns success.
///
/// If AllowModify is true, then this routine is allowed to modify the basic
/// block (e.g. delete instructions after the unconditional branch).

bool MBLAZEInstrInfo::analyzeBranch(MachineBasicBlock &MBB,
                                 MachineBasicBlock *&TBB,
                                 MachineBasicBlock *&FBB,
                                 SmallVectorImpl<MachineOperand> &Cond,
                                 bool AllowModify) const {
  TBB = FBB = nullptr;
  MachineBasicBlock::iterator I = MBB.end();
  if (I == MBB.begin())
    return false;
  --I;

  while (isPredicated(*I) || I->isTerminator() || I->isDebugValue()) {
    // Flag to be raised on unanalyzeable instructions. This is useful in cases
    // where we want to clean up on the end of the basic block before we bail
    // out.
    bool CantAnalyze = false;

    // Skip over DEBUG values and predicated nonterminators.
    while (I->isDebugInstr() || !I->isTerminator()) {
      if (I == MBB.begin())
        return false;
      --I;
    }

    if (isJumpOpcode(I->getOpcode())) {
      // Indirect branches and jump tables can't be analyzed, but we still want
      // to clean up any instructions at the tail of the basic block.
      CantAnalyze = true;
    } else if (isUncondBranchOpcode(I->getOpcode())) {
      TBB = I->getOperand(0).getMBB();
    } else if (isCondBranchOpcode(I->getOpcode())) {
      // Bail out if we encounter multiple conditional branches.
      if (!Cond.empty())
        return true;

      assert(!FBB && "FBB should have been null.");
      FBB = TBB;
      TBB = I->getOperand(0).getMBB();
      Cond.push_back(I->getOperand(1));
      Cond.push_back(I->getOperand(2));
      Cond.push_back(I->getOperand(3));
    } else if (I->isReturn()) {
      // Returns can't be analyzed, but we should run cleanup.
      CantAnalyze = !isPredicated(*I);
    } else {
      // We encountered other unrecognized terminator. Bail out immediately.
      return true;
    }

    // Cleanup code - to be run for unpredicated unconditional branches and
    //                returns.
    if (!isPredicated(*I) && (isUncondBranchOpcode(I->getOpcode()) ||
                              isJumpOpcode(I->getOpcode()) || I->isReturn())) {
      // Forget any previous condition branch information - it no longer
      // applies.
      Cond.clear();
      FBB = nullptr;

      // If we can modify the function, delete everything below this
      // unconditional branch.
      if (AllowModify) {
        MachineBasicBlock::iterator DI = std::next(I);
        while (DI != MBB.end()) {
          MachineInstr &InstToDelete = *DI;
          ++DI;
          InstToDelete.eraseFromParent();
        }
      }
    }

    if (CantAnalyze)
      return true;

    if (I == MBB.begin())
      return false;

    --I;
  }

  // We made it past the terminators without bailing out - we must have
  // analyzed this branch successfully.
  return false;
}

unsigned MBLAZEInstrInfo::removeBranch(MachineBasicBlock &MBB,
                                    int *BytesRemoved) const {
  assert(!BytesRemoved && "Code size not handled");
  MachineBasicBlock::iterator I = MBB.getLastNonDebugInstr();
  if (I == MBB.end())
    return 0;

  if (!isUncondBranchOpcode(I->getOpcode()) &&
      !isCondBranchOpcode(I->getOpcode()))
    return 0;

  // Remove the branch.
  I->eraseFromParent();

  I = MBB.end();

  if (I == MBB.begin())
    return 1;
  --I;
  if (!isCondBranchOpcode(I->getOpcode()))
    return 1;

  // Remove the branch.
  I->eraseFromParent();
  return 2;
}

void MBLAZEInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                               MachineBasicBlock::iterator I,
                               const DebugLoc &dl, MCRegister DestReg,
                               MCRegister SrcReg, bool KillSrc) const {
  assert(MBLAZE::GPR32RegClass.contains(SrcReg) &&
         "Only GPR32 src copy supported.");
  assert(MBLAZE::GPR32RegClass.contains(DestReg) &&
         "Only GPR32 dest copy supported.");
  BuildMI(MBB, I, dl, get(MBLAZE::MOV_rr), DestReg)
      .addReg(SrcReg, getKillRegState(KillSrc));
}

void MBLAZEInstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                       MachineBasicBlock::iterator I,
                                       Register SrcReg, bool isKill,
                                       int FrameIndex,
                                       const TargetRegisterClass *RC,
                                       const TargetRegisterInfo *TRI) const {
  DebugLoc dl = MBB.findDebugLoc(I);
  MachineFunction &MF = *MBB.getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();

  MachineMemOperand *MMO = MF.getMachineMemOperand(
      MachinePointerInfo::getFixedStack(MF, FrameIndex),
      MachineMemOperand::MOStore, MFI.getObjectSize(FrameIndex),
      MFI.getObjectAlign(FrameIndex));

  assert(MMO && "Couldn't get MachineMemOperand for store to stack.");
  assert(TRI->getSpillSize(*RC) == 4 &&
         "Only support 4-byte stores to stack now.");
  assert(MBLAZE::GPR32RegClass.hasSubClassEq(RC) &&
         "Only support GPR32 stores to stack now.");
  LLVM_DEBUG(dbgs() << "Created store reg=" << printReg(SrcReg, TRI)
                    << " to FrameIndex=" << FrameIndex << "\n");
  BuildMI(MBB, I, dl, get(MBLAZE::ST_rs9))
      .addReg(SrcReg, getKillRegState(isKill))
      .addFrameIndex(FrameIndex)
      .addImm(0)
      .addMemOperand(MMO);
}

void MBLAZEInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                        MachineBasicBlock::iterator I,
                                        Register DestReg, int FrameIndex,
                                        const TargetRegisterClass *RC,
                                        const TargetRegisterInfo *TRI) const {
  DebugLoc dl = MBB.findDebugLoc(I);
  MachineFunction &MF = *MBB.getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  MachineMemOperand *MMO = MF.getMachineMemOperand(
      MachinePointerInfo::getFixedStack(MF, FrameIndex),
      MachineMemOperand::MOLoad, MFI.getObjectSize(FrameIndex),
      MFI.getObjectAlign(FrameIndex));

  assert(MMO && "Couldn't get MachineMemOperand for store to stack.");
  assert(TRI->getSpillSize(*RC) == 4 &&
         "Only support 4-byte loads from stack now.");
  assert(MBLAZE::GPR32RegClass.hasSubClassEq(RC) &&
         "Only support GPR32 stores to stack now.");
  LLVM_DEBUG(dbgs() << "Created load reg=" << printReg(DestReg, TRI)
                    << " from FrameIndex=" << FrameIndex << "\n");
  BuildMI(MBB, I, dl, get(MBLAZE::LD_rs9))
      .addReg(DestReg, RegState::Define)
      .addFrameIndex(FrameIndex)
      .addImm(0)
      .addMemOperand(MMO);
}

/// Return the inverse opcode of the specified Branch instruction.
bool MBLAZEInstrInfo::reverseBranchCondition(
    SmallVectorImpl<MachineOperand> &Cond) const {
  assert((Cond.size() == 3) && "Invalid MBLAZE branch condition!");
  Cond[2].setImm(GetOppositeBranchCondition((MBLAZECC::CondCode)Cond[2].getImm()));
  return false;
}

MachineBasicBlock::iterator
MBLAZEInstrInfo::loadImmediate(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator MI, unsigned Reg,
                            uint64_t Value) const {
  DebugLoc dl = MBB.findDebugLoc(MI);
  if (isInt<12>(Value)) {
    return BuildMI(MBB, MI, dl, get(MBLAZE::MOV_rs12), Reg)
        .addImm(Value)
        .getInstr();
  }
  llvm_unreachable("Need MBLAZE long immediate instructions.");
}

unsigned MBLAZEInstrInfo::insertBranch(MachineBasicBlock &MBB,
                                    MachineBasicBlock *TBB,
                                    MachineBasicBlock *FBB,
                                    ArrayRef<MachineOperand> Cond,
                                    const DebugLoc &dl, int *BytesAdded) const {
  assert(!BytesAdded && "Code size not handled.");

  // Shouldn't be a fall through.
  assert(TBB && "insertBranch must not be told to insert a fallthrough");
  assert((Cond.size() == 3 || Cond.size() == 0) &&
         "MBLAZE branch conditions have two components!");

  if (Cond.empty()) {
    BuildMI(&MBB, dl, get(MBLAZE::BR)).addMBB(TBB);
    return 1;
  }
  int BccOpc = Cond[1].isImm() ? MBLAZE::BRcc_ru6_p : MBLAZE::BRcc_rr_p;
  MachineInstrBuilder MIB = BuildMI(&MBB, dl, get(BccOpc));
  MIB.addMBB(TBB);
  for (unsigned i = 0; i < 3; i++) {
    MIB.add(Cond[i]);
  }

  // One-way conditional branch.
  if (!FBB) {
    return 1;
  }

  // Two-way conditional branch.
  BuildMI(&MBB, dl, get(MBLAZE::BR)).addMBB(FBB);
  return 2;
}

unsigned MBLAZEInstrInfo::getInstSizeInBytes(const MachineInstr &MI) const {
  if (MI.isInlineAsm()) {
    const MachineFunction *MF = MI.getParent()->getParent();
    const char *AsmStr = MI.getOperand(0).getSymbolName();
    return getInlineAsmLength(AsmStr, *MF->getTarget().getMCAsmInfo());
  }
  return MI.getDesc().getSize();
}

bool MBLAZEInstrInfo::isPostIncrement(const MachineInstr &MI) const {
  const MCInstrDesc &MID = MI.getDesc();
  const uint64_t F = MID.TSFlags;
  return ((F >> TSF_AddrModeOff) & TSF_AddModeMask) == PostInc;
}

bool MBLAZEInstrInfo::isPreIncrement(const MachineInstr &MI) const {
  const MCInstrDesc &MID = MI.getDesc();
  const uint64_t F = MID.TSFlags;
  return ((F >> TSF_AddrModeOff) & TSF_AddModeMask) == PreInc;
}

bool MBLAZEInstrInfo::getBaseAndOffsetPosition(const MachineInstr &MI,
                                        unsigned &BasePos,
                                        unsigned &OffsetPos) const {
  if (!MI.mayLoad() && !MI.mayStore())
    return false;

  BasePos = 1;
  OffsetPos = 2;

  if (isPostIncrement(MI) || isPreIncrement(MI)) {
    BasePos++;
    OffsetPos++;
  }

  if (!MI.getOperand(BasePos).isReg() || !MI.getOperand(OffsetPos).isImm())
    return false;

  return true;
}
