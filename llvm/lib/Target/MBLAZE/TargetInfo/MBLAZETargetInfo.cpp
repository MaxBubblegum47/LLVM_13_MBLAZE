//===- MBLAZETargetInfo.cpp - MBLAZE Target Implementation ----------- *- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/MBLAZETargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheMBLAZETarget() {
  static Target TheMBLAZETarget;
  return TheMBLAZETarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMBLAZETargetInfo() {
    RegisterTarget<Triple::mblaze> X(getTheMBLAZETarget(), "mblaze", "mblaze 32 bit", "MBLAZE");
}
