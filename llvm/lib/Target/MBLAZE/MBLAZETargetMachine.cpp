//===- MBLAZETargetMachine.cpp - Define TargetMachine for MBLAZE ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "MBLAZETargetMachine.h"
#include "MBLAZE.h"
#include "MBLAZETargetTransformInfo.h"
#include "TargetInfo/MBLAZETargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

static Reloc::Model getRelocModel(Optional<Reloc::Model> RM) {
  return RM.getValueOr(Reloc::Static);
}

/// MBLAZETargetMachine ctor - Create an ILP32 MBLAZEhitecture model
MBLAZETargetMachine::MBLAZETargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   Optional<Reloc::Model> RM,
                                   Optional<CodeModel::Model> CM,
                                   CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T,
                        "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i32:32:32-"
                        "f32:32:32-i64:32-f64:32-a:0:32-n32",
                        TT, CPU, FS, Options, getRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

MBLAZETargetMachine::~MBLAZETargetMachine() = default;

namespace {

/// MBLAZE Code Generator Pass Configuration Options.
class MBLAZEPassConfig : public TargetPassConfig {
public:
  MBLAZEPassConfig(MBLAZETargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  MBLAZETargetMachine &getMBLAZETargetMachine() const {
    return getTM<MBLAZETargetMachine>();
  }

  bool addInstSelector() override;
  void addPreEmitPass() override;
  void addPreRegAlloc() override;
};

} // end anonymous namespace

TargetPassConfig *MBLAZETargetMachine::createPassConfig(PassManagerBase &PM) {
  return new MBLAZEPassConfig(*this, PM);
}

bool MBLAZEPassConfig::addInstSelector() {
  addPass(createMBLAZEISelDag(getMBLAZETargetMachine(), getOptLevel()));
  return false;
}

void MBLAZEPassConfig::addPreEmitPass() { addPass(createMBLAZEBranchFinalizePass()); }

void MBLAZEPassConfig::addPreRegAlloc() {
    addPass(createMBLAZEExpandPseudosPass());
    addPass(createMBLAZEOptAddrMode());
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMBLAZETarget() {
  RegisterTargetMachine<MBLAZETargetMachine> X(getTheMBLAZETarget());
}

TargetTransformInfo
MBLAZETargetMachine::getTargetTransformInfo(const Function &F) {
  return TargetTransformInfo(MBLAZETTIImpl(this, F));
}
