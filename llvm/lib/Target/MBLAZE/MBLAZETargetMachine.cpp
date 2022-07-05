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
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"
#include  "llvm/Target/TargetOptions.h"

using namespace llvm;

MBLAZETargetMachine::MBLAZETargetMachine(const Target &T, const Triple &TT, StringRef CPU, 
StringRef FS);

namespace {
class MBLAZEPassConfig : public TargetPassConfig {
public:
    MBLAZEPassConfig(MBLAZETargetMachine *TM, PassManagerBase &PM) 
        : TargetPassConfig(TM, PM) {}

    MBLAZETargetMachine &getMBLAZETargetMachine() const {
        return getTM<MBLAZETargetMachine>();
    }    
};

}

#define DEBUG_TYPE "MBLAZE"
extern "C" void LLVMInitializeMBLAZETarget() {
    RegisterTargetMachine<MBLAZETargetMachine> X(TheMBLAZETarget);
}
