//===- MBLAZEMCTargetDesc.h - MBLAZE Target Descriptions --------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides MBLAZE specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCTARGETDESC_H
#define LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {

class Target;

} // end namespace llvm

// Defines symbolic names for MBLAZE registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "MBLAZEGenRegisterInfo.inc"

// Defines symbolic names for the MBLAZE instructions.
#define GET_INSTRINFO_ENUM
#include "MBLAZEGenInstrInfo.inc"

// #define GET_SUBTARGETINFO_ENUM
#include "MBLAZEGenSubtargetInfo.inc"

#endif // LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCTARGETDESC_H
