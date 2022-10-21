//===- MBLAZE.h - Top-level interface for MBLAZE representation -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// MBLAZE back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZE_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZE_H

#include "MCTargetDesc/MBLAZEMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class FunctionPass;
class MBLAZETargetMachine;

FunctionPass *createMBLAZEISelDag(MBLAZETargetMachine &TM,
                               CodeGenOpt::Level OptLevel);
FunctionPass *createMBLAZEExpandPseudosPass();
FunctionPass *createMBLAZEOptAddrMode();
FunctionPass *createMBLAZEBranchFinalizePass();

} // end namespace llvm

#endif // LLVM_LIB_TARGET_MBLAZE_MBLAZE_H
