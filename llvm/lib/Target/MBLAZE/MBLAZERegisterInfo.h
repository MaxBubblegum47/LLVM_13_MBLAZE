//===- MBLAZERegisterInfo.h - MBLAZE Register Information Impl --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the MBLAZE implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZEREGISTERINFO_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZEREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "MBLAZEGenRegisterInfo.inc"

namespace llvm {

class TargetInstrInfo;

struct MBLAZERegisterInfo : public MBLAZEGenRegisterInfo {
public:
  MBLAZERegisterInfo();

  /// Code Generation virtual methods...

  //done
  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;

  // done
  BitVector getReservedRegs(const MachineFunction &MF) const override;

  // done
  bool requiresRegisterScavenging(const MachineFunction &MF) const override;

  // done
  bool useFPForScavengingIndex(const MachineFunction &MF) const override;

  // done
  void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;

  // done
  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const override;

  // Debug information queries. done
  Register getFrameRegister(const MachineFunction &MF) const override;

  //! Return whether to emit frame moves
  static bool needsFrameMoves(const MachineFunction &MF);
};



} // end namespace llvm

#endif // LLVM_LIB_TARGET_MBLAZE_MBLAZEREGISTERINFO_H
