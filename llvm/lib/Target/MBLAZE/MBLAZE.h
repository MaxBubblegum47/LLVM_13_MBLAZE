//===-- MBLAZE.h - Top-level interface for MBLAZE representation ----*- C++ -*-===//
//
//
//                      The LLVM Compiler Infrastructure
//

//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM MBLAZE back-end.
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZE_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZE_H

//#include "MBLAZEConfig.h"
#include "MCTargetDesc/MBLAZEMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
    class MBLAZERegisterBankInfo;
    class MBLAZESubtarget;
    class MBLAZEGenSubtargetInfo;
    class MBLAZEInstrInfo;
    class MBLAZERegisterInfo;
    class MBLAZETargetMachine;
    class MBLAZEFrameLowering;
    class MBLAZETargetLowering;
    class AsmPrinter;
    class FunctionPass;
    class InstructionSelector;
    class MCInst;
    class MCOperand;
    class MachineInstr;
    class MachineOperand;
    class PassRegistry;
    class TargetFrameLowering;
} // end namespace llvm;
#endif