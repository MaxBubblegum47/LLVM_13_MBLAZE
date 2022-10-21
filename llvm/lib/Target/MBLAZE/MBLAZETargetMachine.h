//===- MBLAZETargetMachine.h - Define TargetMachine for MBLAZE --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the MBLAZE specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZETARGETMACHINE_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZETARGETMACHINE_H

#include "MBLAZESubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class TargetPassConfig;

class MBLAZETargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  MBLAZESubtarget Subtarget;

public:
  MBLAZETargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                   CodeGenOpt::Level OL, bool JIT);
  ~MBLAZETargetMachine() override;

  const MBLAZESubtarget *getSubtargetImpl() const { return &Subtarget; }
  const MBLAZESubtarget *getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetTransformInfo getTargetTransformInfo(const Function &F) override;
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_MBLAZE_MBLAZETARGETMACHINE_H
