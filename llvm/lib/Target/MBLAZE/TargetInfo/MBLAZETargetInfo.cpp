//===-- MBLAZETargetInfo.cpp - MBLAZE Target Implementation -------------------===//
//
//
//                  The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "MBLAZE.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
#include "TargetInfo/MBLAZETargetInfo.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheMBLAZETarget() {
  static Target TheMBLAZETarget;
  return TheMBLAZETarget;
}


extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMBLAZETargetInfo() {
  RegisterTarget<Triple::mblaze> X(getTheMBLAZETarget(), "mblaze",
                                    "32-bit MBLAZE", "MBLAZE");
}