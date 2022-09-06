//===--- MBLAZE.h - Declare MBLAZE target feature support ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares MBLAZETargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_MBLAZE_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_MBLAZE_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Compiler.h"

namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY MBLAZETargetInfo : public TargetInfo {
  static const char *const GCCRegNames[];

public:
  MBLAZETargetInfo(const llvm::Triple &Triple, const TargetOptions &)
    : TargetInfo(Triple) {
    // Description string has to be kept in sync with backend string at
    // llvm/lib/Target/MBLAZE/MBLAZETargetMachine.cpp
    resetDataLayout("e"
                    // ELF name mangling
                    "-m:e"
                    // 32-bit pointers, 32-bit aligned
                    "-p:32:32"

    );
    SuitableAlign = 128;
    WCharType = SignedInt;
    WIntType = UnsignedInt;
    IntPtrType = SignedInt;
    PtrDiffType = SignedInt;
    SizeType = UnsignedInt;
  }

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  ArrayRef<const char *> getGCCRegNames() const override;

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override;

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  ArrayRef<Builtin::Info> getTargetBuiltins() const override {
    return None;
  }

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &info) const override {
    return false;
  }

  const char *getClobbers() const override {
    return "";
  }
};

} // namespace targets
} // namespace clang

#endif // LLVM_CLANG_LIB_BASIC_TARGETS_MBLAZE_H