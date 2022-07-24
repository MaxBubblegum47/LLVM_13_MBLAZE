//===-- MBLAZEMCTargetDesc.cpp - MBLAZE Target Descriptions -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// This file provides MBLAZE specific target descriptions.
///
//===----------------------------------------------------------------------===//
#include <iostream>
#include "MBLAZEMCTargetDesc.h"

#include "TargetInfo/MBLAZETargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/MC/MCStreamer.h"
#define GET_INSTRINFO_MC_DESC
#include "MBLAZEGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "MBLAZEGenRegisterInfo.inc"

using namespace llvm;



static MCInstrInfo *createMBLAZEMCInstrInfo() {
  MCInstrInfo *Info = new MCInstrInfo();
  InitMBLAZEMCInstrInfo(Info);
 std::cout << "création des objets pour MBLAZE "<< '\n';
  return Info;
}

static MCRegisterInfo *createMBLAZEMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *Info = new MCRegisterInfo();
  InitMBLAZEMCRegisterInfo(Info, MBLAZE::R1);
  return Info;
}
static MCSubtargetInfo* createMBLAZEMCSubtargetInfo 	( 	const Triple &  	TT,
		StringRef  	CPU,
		StringRef  	FS 
	) 		{
		
		
}





extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMBLAZETargetMC() {
	printf("init mc ");
	std::cout << "ini t_mc " << '\n';
  auto &MBLAZETarget = getTheMBLAZETarget();
  // TargetRegistry::RegisterMCAsmBackend(MBLAZETarget, createMBLAZEAsmBackend);
  // TargetRegistry::RegisterMCAsmInfo(MBLAZETarget, createMBLAZEMCAsmInfo);
  TargetRegistry::RegisterMCInstrInfo(MBLAZETarget, createMBLAZEMCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(MBLAZETarget, createMBLAZEMCRegisterInfo);
  // TargetRegistry::RegisterMCSubtargetInfo(MBLAZETarget, createMBLAZEMCSubtargetInfo);
  // TargetRegistry::RegisterMCCodeEmitter(MBLAZETarget, createMBLAZEMCCodeEmitter);

}
