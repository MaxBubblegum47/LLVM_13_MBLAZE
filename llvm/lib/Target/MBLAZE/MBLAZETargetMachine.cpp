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

#define DEBUG_TYPE "mblaze"
extern "C" void LLVMInitializeMBLAZETarget() {}
