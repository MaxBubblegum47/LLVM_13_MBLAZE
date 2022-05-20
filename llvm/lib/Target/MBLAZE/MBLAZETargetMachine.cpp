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
//#include "MBLAZETargetMachine.h"
#include "MBLAZE.h"
#include "TargetInfo/MBLAZETargetInfo.h"
#include "MBLAZETargetMachine.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"
#include  "llvm/Target/TargetOptions.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMBLAZETarget() {
  RegisterTargetMachine<MBLAZETargetMachine> X(getTheMBLAZETarget());
//   auto *PR = PassRegistry::getPassRegistry();
//   initializeGlobalISel(*PR);
//   initializeMBLAZEMergeBaseOffsetOptPass(*PR);
//   initializeMBLAZEExpandPseudoPass(*PR);
//   initializeMBLAZEInsertVSETVLIPass(*PR);
}

namespace {
    class MBLAZEPassConfig : public TargetPassConfig {
    public:
        MBLAZEPassConfig(MBLAZETargetMachine &TM, PassManagerBase
        &PM)
        : TargetPassConfig(TM, PM) {}
 
        MBLAZETargetMachine &getMBLAZETargetMachine() const {
            return getTM<MBLAZETargetMachine>();
        }

        // bool addInstSelector() override {
        //     addPass(createMBLAZEISelDag(getMBLAZETargetMachine(),
        //     getOptLevel()));
        //     return false;
        // }
    };
} // namespace

TargetPassConfig *MBLAZETargetMachine::createPassConfig(PassManagerBase &PM) {
    return new MBLAZEPassConfig(*this, PM);
}