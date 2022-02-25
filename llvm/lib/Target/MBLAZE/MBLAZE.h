//===-- MBlaze.h - Top-level interface for MBlaze representation ----*- C++ -*-===//
//
//
//                      The LLVM Compiler Infrastructure
//

//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM MBlaze back-end.
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_LIB_TARGET_MBlaze_MBlaze_H
#define LLVM_LIB_TARGET_MBlaze_MBlaze_H
#include "MBlazeConfig.h"
#include "MCTargetDesc/MBlazeMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
    class MBlazeTargetMachine;
    class FunctionPass;
} // end namespace llvm;
#endif