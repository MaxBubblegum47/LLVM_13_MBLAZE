//===- MBLAZEMCTargetDesc.cpp - MBLAZE Target Descriptions ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides MBLAZE specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "MBLAZEMCTargetDesc.h"
#include "MBLAZEInstPrinter.h"
#include "MBLAZEMCAsmInfo.h"
#include "MBLAZETargetStreamer.h"
#include "TargetInfo/MBLAZETargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "MBLAZEGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "MBLAZEGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "MBLAZEGenRegisterInfo.inc"

static MCInstrInfo *createMBLAZEMCInstrInfo() {
  auto *X = new MCInstrInfo();
  InitMBLAZEMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createMBLAZEMCRegisterInfo(const Triple &TT) {
  auto *X = new MCRegisterInfo();
  InitMBLAZEMCRegisterInfo(X, MBLAZE::R15);
  return X;
}

static MCSubtargetInfo *createMBLAZEMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createMBLAZEMCSubtargetInfoImpl(TT, CPU, /*TuneCPU=*/CPU, FS);
}

static MCAsmInfo *createMBLAZEMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new MBLAZEMCAsmInfo(TT);

  // Initial state of the frame pointer is SP.
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, MBLAZE::R1, 0);
  MAI->addInitialFrameState(Inst);

  return MAI;
}

static MCInstPrinter *createMBLAZEMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  return new MBLAZEInstPrinter(MAI, MII, MRI);
}

MBLAZETargetStreamer::MBLAZETargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
MBLAZETargetStreamer::~MBLAZETargetStreamer() = default;

static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new MBLAZETargetStreamer(S);
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMBLAZETargetMC() {
  // Register the MC asm info.
  Target &TheMBLAZETarget = getTheMBLAZETarget();
  RegisterMCAsmInfoFn X(TheMBLAZETarget, createMBLAZEMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheMBLAZETarget, createMBLAZEMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheMBLAZETarget, createMBLAZEMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheMBLAZETarget,
                                          createMBLAZEMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheMBLAZETarget, createMBLAZEMCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheMBLAZETarget,
                                            createTargetAsmStreamer);
}
