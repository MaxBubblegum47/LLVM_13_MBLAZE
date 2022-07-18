//===-- MBLAZEMCAsmInfo.cpp - MBLAZE Asm properties ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the MBLAZEMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "MBLAZEMCAsmInfo.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/MC/MCStreamer.h"

using namespace llvm;

void MBLAZEMCAsmInfo::anchor() {}

MBLAZEMCAsmInfo::MBLAZEMCAsmInfo(const Triple &TargetTriple) {
  IsLittleEndian              = false;
  StackGrowsUp                = false;
  SupportsDebugInformation    = true;
  AlignmentIsInBytes          = false;
  PrivateGlobalPrefix         = "$";
  GPRel32Directive            = "\t.gpword\t";
}
