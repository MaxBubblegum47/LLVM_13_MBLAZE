//===-- MBLAZETargetMachine.cpp - Define TargetMachine for MBLAZE -------------===//
//
//
//                  The LLVM Compiler Infrastructure
//
//
//===----------------------------------------------------------------------===//
//
// Implements the info about MBLAZE target spec.
//
//===----------------------------------------------------------------------===//
#include "MBLAZETargetMachine.h"
#include "TargetInfo/MBLAZETargetInfo.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"
#include  "llvm/Target/TargetOptions.h"

using namespace llvm;
#define DEBUG_TYPE "mblaze"
extern "C" void LLVMInitializeMBLAZETarget() {
      RegisterTargetMachine<MBLAZETargetMachine> X(getTheMBLAZETarget());
}

static std::string computeDataLayout(const Triple &TT) {
  std::string Ret;

  // Only support little endian for now.
  // TODO: Add support for big endian.
  Ret += "e";

  // MBLAZE is always 32-bit target with the MBLAZEv2 ABI as prefer now.
  // It's a 4-byte aligned stack with ELF mangling only.
  Ret += "-m:e-S32-p:32:32-i32:32:32-i64:32:32-f32:32:32-f64:32:32-v64:32:32"
         "-v128:32:32-a:0:32-Fi32-n32";

  return Ret;
}

MBLAZETargetMachine::MBLAZETargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     Optional<Reloc::Model> RM,
                                     Optional<CodeModel::Model> CM,
                                     CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
                        RM.getValueOr(Reloc::Static),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

namespace {
class MBLAZEPassConfig : public TargetPassConfig {
public:
  MBLAZEPassConfig(MBLAZETargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {
      
      }

  MBLAZETargetMachine &getMBLAZETargetMachine() const {
    return getTM<MBLAZETargetMachine>();
  }
};

} // namespace

TargetPassConfig *MBLAZETargetMachine::createPassConfig(PassManagerBase &PM) {
  //  addISelPrepare();
    
  return new MBLAZEPassConfig(*this, PM);
}