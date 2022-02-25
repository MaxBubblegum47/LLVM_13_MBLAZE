//===-- MBlazeTargetMachine.cpp - Define TargetMachine for MBlaze -------------===//
//
//
//                  The LLVM Compiler Infrastructure
//
//
//===----------------------------------------------------------------------===//
//
// Implements the info about MBlaze target spec.
//
//===----------------------------------------------------------------------===//
#include "MBlazeTargetMachine.h"
#include "MBlaze.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;
#define DEBUG_TYPE "MBlaze"
    extern "C" void LLVMInitializeMBlazeTarget() {
}