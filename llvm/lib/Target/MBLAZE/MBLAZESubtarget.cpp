//===-- MBLAZESubtarget.cpp - MBLAZE Subtarget Information ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the MBLAZE specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "MBLAZESubtarget.h"
#include "MBLAZE.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "MBLAZE-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "MBLAZEGenSubtargetInfo.inc"

void MBLAZESubtarget::anchor() { }

MBLAZESubtarget &MBLAZESubtarget::initializeSubtargetDependencies(StringRef CPU,
                                                                StringRef FS) {
  // UseSoftMulDiv = false;
  // IsV9 = false;
  // IsLeon = false;
  // V8DeprecatedInsts = false;
  // IsVIS = false;
  // IsVIS2 = false;
  // IsVIS3 = false;
  // HasHardQuad = false;
  // UsePopc = false;
  // UseSoftFloat = false;
  // HasNoFSMULD = false;
  // HasNoFMULS = false;

  // // Leon features
  // HasLeonCasa = false;
  // HasUmacSmac = false;
  // HasPWRPSR = false;
  // InsertNOPLoad = false;
  // FixAllFDIVSQRT = false;
  // DetectRoundChange = false;
  // HasLeonCycleCounter = false;

  // Determine default and user specified characteristics
  std::string CPUName = std::string(CPU);
  CPUName = "generic";

  // Parse features string.
  ParseSubtargetFeatures(CPUName, /*TuneCPU*/ CPUName, FS);


  return *this;
}

MBLAZESubtarget::MBLAZESubtarget(const Triple &TT, const std::string &CPU,
                               const std::string &FS)
    : MBLAZEGenSubtargetInfo(TT, CPU, /*TuneCPU*/ CPU, FS), TargetTriple(TT),
      {}



