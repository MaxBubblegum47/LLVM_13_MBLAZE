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

// This is a holy orders, if someone change anything the project
// will be broken
include "MBLAZESchedule.td"
include "MBLAZERegisterInfo.td"
include "MBLAZECallingConv.td"
include "MBLAZEInstrInfo.td"

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