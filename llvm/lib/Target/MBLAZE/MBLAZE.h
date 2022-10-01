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

#include "MCTargetDesc/MBLAZEMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class FunctionPass;
class MBLAZETargetMachine;

FunctionPass *createMBLAZEISelDag(MBLAZETargetMachine &TM,
                               CodeGenOpt::Level OptLevel);
FunctionPass *createMBLAZEExpandPseudosPass();
FunctionPass *createMBLAZEOptAddrMode();
FunctionPass *createMBLAZEBranchFinalizePass();

} // end namespace llvm

#endif // LLVM_LIB_TARGET_MBLAZE_MBLAZE_H





//=================================================================================
//  OLD STUFF
//=================================================================================

// #ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZE_H
// #define LLVM_LIB_TARGET_MBLAZE_MBLAZE_H

// //#include "MBLAZEConfig.h"
// #include "MCTargetDesc/MBLAZEMCTargetDesc.h"
// #include "llvm/Target/TargetMachine.h"

// namespace llvm {
//     class MBLAZERegisterInfo;
//     class MBLAZESubtarget;
//     class MBLAZETargetMachine;
//     class AsmPrinter;
//     class FunctionPass;
//     class InstructionSelector;
//     class MCInst;
//     class MCOperand;
//     class MachineInstr;
//     class MachineOperand;
//     class PassRegistry;

//     bool lowerMBLAZEMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
//                                     AsmPrinter &AP);
    
//     bool LowerMBLAZEMachineOperandToMCOperand(const MachineOperand &MO,
//                                          MCOperand &MCOp, const AsmPrinter &AP);


//     FunctionPass *createMBLAZEISelDag(MBLAZETargetMachine &TM,
//                                CodeGenOpt::Level OptLevel);
// FunctionPass *createMBLAZEExpandPseudosPass();
// FunctionPass *createMBLAZEOptAddrMode();
// FunctionPass *createMBLAZEBranchFinalizePass();

    // FunctionPass *createMBLAZEISelDag(MBLAZETargetMachine &TM);

    // FunctionPass *createMBLAZEMergeBaseOffsetOptPass();
    // void initializeMBLAZEMergeBaseOffsetOptPass(PassRegistry &);

    // FunctionPass *createMBLAZEExpandPseudoPass();
    // void initializeMBLAZEExpandPseudoPass(PassRegistry &);

    // FunctionPass *createMBLAZEExpandAtomicPseudoPass();
    // void initializeMBLAZEExpandAtomicPseudoPass(PassRegistry &);

    // FunctionPass *createMBLAZEInsertVSETVLIPass();
    // void initializeMBLAZEInsertVSETVLIPass(PassRegistry &);

    // InstructionSelector *createMBLAZEInstructionSelector(const MBLAZETargetMachine &,
    //                                                     MBLAZESubtarget &,
    //                                                     MBLAZERegisterBankInfo &);
    

    // // idk what is this, maybe some legacy code
    // FunctionPass *createMBLAZEDelaySlotFillerPass(MBLAZETargetMachine &TM);
// } // end namespace llvm;
// #endif