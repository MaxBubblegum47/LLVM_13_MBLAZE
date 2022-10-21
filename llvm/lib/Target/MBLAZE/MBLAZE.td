//===- MBLAZE.td - Describe the MBLAZE Target Machine ------------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// MBLAZE Subtarget features
//===----------------------------------------------------------------------===//

def FeatureNORM
    : SubtargetFeature<"norm", "Xnorm", "true",
                       "Enable support for norm instruction.">;

//===----------------------------------------------------------------------===//
// Registers, calling conventions, instruction descriptions
//===----------------------------------------------------------------------===//

include "MBLAZERegisterInfo.td"
include "MBLAZEInstrInfo.td"
include "MBLAZECallingConv.td"

def MBLAZEInstrInfo : InstrInfo;

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def MBLAZE : Target {
  let InstructionSet = MBLAZEInstrInfo;
}
