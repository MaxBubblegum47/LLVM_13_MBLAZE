//===- MBLAZEMachineFunctionInfo.h - MBLAZE machine function info -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares MBLAZE-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZEMACHINEFUNCTIONINFO_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZEMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFunction.h"
#include <vector>

namespace llvm {

/// MBLAZEFunctionInfo - This class is derived from MachineFunction private
/// MBLAZE target-specific information for each MachineFunction.
class MBLAZEFunctionInfo : public MachineFunctionInfo {
  virtual void anchor();
  bool ReturnStackOffsetSet;
  int VarArgsFrameIndex;
  unsigned ReturnStackOffset;

public:
  MBLAZEFunctionInfo()
      : ReturnStackOffsetSet(false), VarArgsFrameIndex(0),
        ReturnStackOffset(-1U), MaxCallStackReq(0) {}

  explicit MBLAZEFunctionInfo(MachineFunction &MF)
      : ReturnStackOffsetSet(false), VarArgsFrameIndex(0),
        ReturnStackOffset(-1U), MaxCallStackReq(0) {}

  ~MBLAZEFunctionInfo() {}

  void setVarArgsFrameIndex(int off) { VarArgsFrameIndex = off; }
  int getVarArgsFrameIndex() const { return VarArgsFrameIndex; }

  void setReturnStackOffset(unsigned value) {
    assert(!ReturnStackOffsetSet && "Return stack offset set twice");
    ReturnStackOffset = value;
    ReturnStackOffsetSet = true;
  }

  unsigned getReturnStackOffset() const {
    assert(ReturnStackOffsetSet && "Return stack offset not set");
    return ReturnStackOffset;
  }

  unsigned MaxCallStackReq;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_MBLAZE_MBLAZEMACHINEFUNCTIONINFO_H
