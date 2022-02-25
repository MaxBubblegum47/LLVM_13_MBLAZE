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
using namespace llvm;
Target llvm::TheMBLAZETarget, llvm::TheMBLAZEelTarget;
extern "C" void LLVMInitializeMBLAZETargetInfo() {
RegisterTarget<Triple::mblaze,
/*HasJIT=*/true> X(TheMBLAZETarget, "mblaze", "mblaze (32-bit big endian)", "MBLAZE");
//RegisterTarget<Triple::MBLAZEel,
//*HasJIT=*/true> Y(TheMBLAZEelTarget, "MBLAZEel", "MBLAZE (32-bit little endian)","MBLAZE");
}