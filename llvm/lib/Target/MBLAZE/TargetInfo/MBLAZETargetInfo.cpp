//===-- MBLAZETargetInfo.cpp - MBLAZE Target Implementation -------------------===//
//
//
//                  The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "TargetInfo/MBLAZETargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;


//Target llvm::TheMBLAZETarget, llvm::TheMBLAZEelTarget;

Target &llvm::getTheMBLAZETarget() {
  static Target TheMBLAZETarget;
  return TheMBLAZETarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMBLAZETargetInfo() {
    RegisterTarget<Triple::mblaze> X(getTheMBLAZETarget(), "mblaze", "mblaze (32-bit big endian)", "MBLAZE");
}