#include "MBLAZE.h"
#include "MBLAZETargetMachine.h"
#include "TargetInfo/MBLAZETargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMBLAZETarget() {
  RegisterTargetMachine<MBLAZETargetMachine> X(getTheMBLAZETarget());
}

static std::string computeDataLayout(const Triple &TT) {
  std::string Ret;

  // Only support little endian for now.
  Ret += "e";

  // This is just a sample
  Ret += "-m:e-S32-p:32:32";

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

  bool addInstSelector() override;

};

} // namespace

TargetPassConfig *MBLAZETargetMachine::createPassConfig(PassManagerBase &PM) {
  //  addISelPrepare();
    
  return new MBLAZEPassConfig(*this, PM);
}

bool MBLAZEPassConfig::addInstSelector() {
  addPass(createMBLAZEISelDag(getMBLAZETargetMachine(), getOptLevel()));
  return false;
}
