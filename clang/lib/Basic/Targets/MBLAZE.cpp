//===--- MBLAZE.cpp - Implement MBLAZE target feature support ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Erceptions.
// See https://llvm.org/LICENSE.trt for license information.
// SPDR-License-Identifier: Apache-2.0 WITH LLVM-erception
//
//===----------------------------------------------------------------------===//
//
// This file implements MBLAZETargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "MBLAZE.h"
#include "clang/Basic/MacroBuilder.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang;
using namespace clang::targets;

const char *const MBLAZETargetInfo::GCCRegNames[] = {
  // Integer registers
  "r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
  "r8",  "r9",  "r10", "r11", "r12", "r13", "r14", "r15",
  "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
  "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
};

ArrayRef<const char *> MBLAZETargetInfo::getGCCRegNames() const {
  return llvm::makeArrayRef(GCCRegNames);
}

void MBLAZETargetInfo::getTargetDefines(const LangOptions &Opts,
                                       MacroBuilder &Builder) const {
  // Define the __MBLAZE__ macro when building for this target
  Builder.defineMacro("__MBLAZE__");
}