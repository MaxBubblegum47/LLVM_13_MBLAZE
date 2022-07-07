//===-- MBLAZESubtarget.h - Define Subtarget for the MBLAZE -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the MBLAZE specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZESUBTARGET_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZESUBTARGET_H


#include "llvm/ADT/Triple.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include <string>

#define GET_SUBTARGETINFO_HEADER
#include "MBLAZEGenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class MBLAZESubtarget : public MBLAZEGenSubtargetInfo {
  Triple TargetTriple;
  virtual void anchor();

public:
  MBLAZESubtarget(const Triple &TT, const std::string &CPU,
                 const std::string &FS);

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);
  MBLAZESubtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS);

};

} // end namespace llvm

#endif
