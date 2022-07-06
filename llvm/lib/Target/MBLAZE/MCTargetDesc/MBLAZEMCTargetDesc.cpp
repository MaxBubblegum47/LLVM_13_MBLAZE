//===-- MBLAZEMCTargetDesc.cpp - MBLAZE Target Descriptions -------------------===//
//
//
//                  The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides MBLAZE specific target descriptions.
//
//===----------------------------------------------------------------------===//
#include "MBLAZEMCTargetDesc.h"
#include "llvm/MC/MachineLocation.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstPrinter.h"

#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "MBLAZEGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "MBLAZEGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "MBLAZEGenRegisterInfo.inc"

static MCInstrInfo *createMBLAZEInstrInfo(){
    MCInstrInfo *X = new MCInstrInfo();
    InitMBLAZEMCInstrInfo(X);
    return X;
}

static MCSubtargetInfo *createMBLAZEMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU,
                                                 StringRef FS) {
  
  std::string CPUName = std::string(CPU);                                                  
  if (CPUName.empty())
    CPUName = "generic";

  return createMBLAZEMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
  // MCSubtargetInfo *X = new MCSubtargetInfo();
  // CreateMBLAZEMCSubtargetInfo(X, TT, CPU, FS);
  // return X;
  //return createMBLAZEMCSubtargetInfoImpl(TT, CPU, FS);
}


extern "C" void LLVMInitializeMBLAZETargetMC() {
     TargetRegistry::RegisterMCSubtargetInfo(TheMBLAZETarget, createMBLAZEMCSubtargetInfo);
}

