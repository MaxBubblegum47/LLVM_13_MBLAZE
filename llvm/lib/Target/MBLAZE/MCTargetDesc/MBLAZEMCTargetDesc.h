//===-- MBLAZEMCTargetDesc.h - MBLAZE Target Descriptions -----------*- C++ -*-===//
//
//
//                  The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides MBLAZE specific target descriptions.
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCTARGETDESC_H
#define LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCTARGETDESC_H


//#include "MBLAZEConfig.h"
#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
    class Target;
    class Triple;

    extern Target TheMBLAZETarget;
    extern Target TheMBLAZEelTarget;
} // End llvm namespace


// Defines symbolic names for MBLAZE registers. This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "MBLAZEGenRegisterInfo.inc"

// Defines symbolic names for the MBLAZE instructions.
#define GET_INSTRINFO_ENUM
#include "MBLAZEGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "MBLAZEGenSubtargetInfo.inc"

#endif