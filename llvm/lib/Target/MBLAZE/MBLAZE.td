//===-- MBLAZEOther.td - Describe the MBLAZE Target Machine ----*- tablegen -*-===//
//
//
//              The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This is the top level entry point for the MBLAZE target.
//===----------------------------------------------------------------------===//
//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//
include "llvm/Target/Target.td"
//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//
include "MBLAZESchedule.td"
include "MBLAZERegisterInfo.td"
include "MBLAZEInstrInfo.td"


//===----------------------------------------------------------------------===//
// Microblaze Subtarget features                                              //
//===----------------------------------------------------------------------===//

// def FeatureBarrel      : SubtargetFeature<"barrel", "HasBarrel", "true",
//                                 "Implements barrel shifter">;
// def FeatureDiv         : SubtargetFeature<"div", "HasDiv", "true",
//                                 "Implements hardware divider">;
// def FeatureMul         : SubtargetFeature<"mul", "HasMul", "true",
//                                 "Implements hardware multiplier">;
// def FeaturePatCmp      : SubtargetFeature<"patcmp", "HasPatCmp", "true",
//                                 "Implements pattern compare instruction">;
// def FeatureFPU         : SubtargetFeature<"fpu", "HasFPU", "true",
//                                 "Implements floating point unit">;
// def FeatureMul64       : SubtargetFeature<"mul64", "HasMul64", "true",
//                                 "Implements multiplier with 64-bit result">;
// def FeatureSqrt        : SubtargetFeature<"sqrt", "HasSqrt", "true",
//                                 "Implements sqrt and floating point convert">;


//===----------------------------------------------------------------------===//
// MBLAZE processors supported.
//===----------------------------------------------------------------------===//

def : Processor<"MBLAZE",  NoItineraries, []>;

//===----------------------------------------------------------------------===//
// Instruction Descriptions
//===----------------------------------------------------------------------===//

def MBLAZEAsmWriter : AsmWriter {
  string AsmWriterClassName  = "InstPrinter";
  bit isMCAsmWriter = 1;
}

def MBLAZEInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// Target Declaration
//===----------------------------------------------------------------------===//

def MBLAZE : Target {
  let InstructionSet = MBLAZEInstrInfo;
  let AssemblyWriters = [MBLAZEAsmWriter];
}