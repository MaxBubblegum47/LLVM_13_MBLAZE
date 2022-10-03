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
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

MBLAZETargetMachine::~MBLAZETargetMachine() = default;

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
  // void addPreEmitPass() override;
  // void addPreRegAlloc() override;
};

} // namespace


//NEW CONFIGURATION TAKEN FROM MBLAZE
TargetPassConfig *MBLAZETargetMachine::createPassConfig(PassManagerBase &PM) {
  return new MBLAZEPassConfig(*this, PM);
}

bool MBLAZEPassConfig::addInstSelector() {
  addPass(createMBLAZEISelDag(getMBLAZETargetMachine(), getOptLevel()));
  return false;
}

//void MBLAZEPassConfig::addPreEmitPass() { addPass(createMBLAZEBranchFinalizePass()); }

// void MBLAZEPassConfig::addPreRegAlloc() {
//     addPass(createMBLAZEExpandPseudosPass());
//     addPass(createMBLAZEOptAddrMode());
// }



// OLD CONFIGURATION
// TargetPassConfig *MBLAZETargetMachine::createPassConfig(PassManagerBase &PM) {
//   //  addISelPrepare();
    
//   return new MBLAZEPassConfig(*this, PM);
// }

// bool MBLAZEPassConfig::addInstSelector() {
//   addPass(createMBLAZEISelDag(getMBLAZETargetMachine(), getOptLevel()));
//   return false;
// }

// Force static initialization.
// extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMBLAZETarget() {
//   RegisterTargetMachine<MBLAZETargetMachine> X(getTheMBLAZETarget());
// }

// TargetTransformInfo
// MBLAZETargetMachine::getTargetTransformInfo(const Function &F) {
//   return TargetTransformInfo(MBLAZETTIImpl(this, F));
// }
