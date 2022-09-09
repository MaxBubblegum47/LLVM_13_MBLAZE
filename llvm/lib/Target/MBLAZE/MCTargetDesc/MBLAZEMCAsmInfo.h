//===- MBLAZEMCAsmInfo.h - MBLAZE asm properties ----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the MBLAZEMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCASMINFO_H
#define LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class MBLAZEMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit MBLAZEMCAsmInfo(const Triple &TT);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCASMINFO_H
