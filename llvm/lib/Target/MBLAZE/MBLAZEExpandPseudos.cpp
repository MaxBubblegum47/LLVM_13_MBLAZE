//===- MBLAZEExpandPseudosPass - MBLAZE expand pseudo loads -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This pass expands stores with large offsets into an appropriate sequence.
//===----------------------------------------------------------------------===//

#include "MBLAZE.h"
#include "MBLAZEInstrInfo.h"
#include "MBLAZERegisterInfo.h"
#include "MBLAZESubtarget.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

#define DEBUG_TYPE "MBLAZE-expand-pseudos"

namespace {

class MBLAZEExpandPseudos : public MachineFunctionPass {
public:
  static char ID;
  MBLAZEExpandPseudos() : MachineFunctionPass(ID) {}

  bool runOnMachineFunction(MachineFunction &Fn) override;

  StringRef getPassName() const override { return "MBLAZE Expand Pseudos"; }

private:
  void ExpandStore(MachineFunction &, MachineBasicBlock::iterator);

  const MBLAZEInstrInfo *TII;
};

char MBLAZEExpandPseudos::ID = 0;

} // end anonymous namespace

static unsigned getMappedOp(unsigned PseudoOp) {
  switch (PseudoOp) {
  case MBLAZE::ST_FAR:
    return MBLAZE::ST_rs9;
  case MBLAZE::STH_FAR:
    return MBLAZE::STH_rs9;
  case MBLAZE::STB_FAR:
    return MBLAZE::STB_rs9;
  default:
    llvm_unreachable("Unhandled pseudo op.");
  }
}

void MBLAZEExpandPseudos::ExpandStore(MachineFunction &MF,
                                   MachineBasicBlock::iterator SII) {
  MachineInstr &SI = *SII;
  unsigned AddrReg = MF.getRegInfo().createVirtualRegister(&MBLAZE::GPR32RegClass);
  unsigned AddOpc =
      isUInt<6>(SI.getOperand(2).getImm()) ? MBLAZE::ADD_rru6 : MBLAZE::ADD_rrlimm;
  BuildMI(*SI.getParent(), SI, SI.getDebugLoc(), TII->get(AddOpc), AddrReg)
      .addReg(SI.getOperand(1).getReg())
      .addImm(SI.getOperand(2).getImm());
  BuildMI(*SI.getParent(), SI, SI.getDebugLoc(),
          TII->get(getMappedOp(SI.getOpcode())))
      .addReg(SI.getOperand(0).getReg())
      .addReg(AddrReg)
      .addImm(0);
  SI.eraseFromParent();
}

bool MBLAZEExpandPseudos::runOnMachineFunction(MachineFunction &MF) {
  const MBLAZESubtarget *STI = &MF.getSubtarget<MBLAZESubtarget>();
  TII = STI->getInstrInfo();
  bool ExpandedStore = false;
  for (auto &MBB : MF) {
    MachineBasicBlock::iterator MBBI = MBB.begin(), E = MBB.end();
    while (MBBI != E) {
      MachineBasicBlock::iterator NMBBI = std::next(MBBI);
      switch (MBBI->getOpcode()) {
      case MBLAZE::ST_FAR:
      case MBLAZE::STH_FAR:
      case MBLAZE::STB_FAR:
        ExpandStore(MF, MBBI);
        ExpandedStore = true;
        break;
      default:
        break;
      }
      MBBI = NMBBI;
    }
  }
  return ExpandedStore;
}

FunctionPass *llvm::createMBLAZEExpandPseudosPass() {
  return new MBLAZEExpandPseudos();
}
