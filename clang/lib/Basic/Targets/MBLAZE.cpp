//===--- MBLAZE.cpp - Implement MBLAZE target feature support ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
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
  "x0",  "x1",  "x2",  "x3",  "x4",  "x5",  "x6",  "x7",
  "x8",  "x9",  "x10", "x11", "x12", "x13", "x14", "x15",
  "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23",
  "x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31",
};

// pag. 195 Xilinx MBLAZE documentation for more inforamtions
const TargetInfo::GCCRegAlias GCCRegAliases[] = {
  {{"zero"}, "x0"}, {{"sp"}, "x1"},   {{"ro"}, "x2"},    {{"rt"}, "x3"},
  {{"rt"}, "x4"},   {{"t0"}, "x5"},   {{"t1"}, "x6"},    {{"t2"}, "x7"},
  {{"t3"}, "x8"},   {{"t4"}, "x9"},   {{"t5"}, "x10"},   {{"t6"}, "x11"},
  {{"t7"}, "x12"},  {{"rw"}, "x13"},  {{"ri"}, "x14"},   {{"ras"}, "x15"},
  {{"rat"}, "x16"},  {{"rte"}, "x17"},  {{"cmp"}, "x18"},   {{"cls"}, "x19"},
  {{"gp"}, "x20"},  {{"s1"}, "x21"},  {{"s2"}, "x22"},   {{"s3"}, "x23"},
  {{"s4"}, "x24"},  {{"s5"}, "x25"},  {{"s6"}, "x26"},  {{"s7"}, "x27"},
  {{"s8"}, "x28"},  {{"s9"}, "x29"},  {{"s10"}, "x30"},   {{"s11"}, "x31"}};

ArrayRef<const char *> MBLAZETargetInfo::getGCCRegNames() const {
  return llvm::makeArrayRef(GCCRegNames);
}

ArrayRef<TargetInfo::GCCRegAlias> MBLAZETargetInfo::getGCCRegAliases() const {
  return llvm::makeArrayRef(GCCRegAliases);
}

void MBLAZETargetInfo::getTargetDefines(const LangOptions &Opts,
                                       MacroBuilder &Builder) const {
  // Define the __MBLAZE__ macro when building for this target
  Builder.defineMacro("__MBLAZE__");
}