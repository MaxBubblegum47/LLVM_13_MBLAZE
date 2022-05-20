#include "MBLAZESubtarget.h"
#include "MCTargetDesc/MBLAZEMCTargetDesc.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class MBLAZETargetMachine : public LLVMTargetMachine {
//   std::unique_ptr<TargetLoweringObjectFile> TLOF;
//   mutable StringMap<std::unique_ptr<MBLAZESubtarget>> SubtargetMap;

public:
  MBLAZETargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                     CodeGenOpt::Level OL, bool JIT);

//   const MBLAZESubtarget *getSubtargetImpl(const Function &F) const override;
//   // DO NOT IMPLEMENT: There is no such thing as a valid default subtarget,
//   // subtargets are per-function entities based on the target-specific
//   // attributes of each function.
//   const MBLAZESubtarget *getSubtargetImpl() const = delete;

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
    };
} // namespace llvm

