#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZETARGETMACHINE_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZETARGETMACHINE_H

#include "MBLAZESubtarget.h"
#include "llvm/IR/DataLayout.h"
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

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
} // namespace llvm

#endif