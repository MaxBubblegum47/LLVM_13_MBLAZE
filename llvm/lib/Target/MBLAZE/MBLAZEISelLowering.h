//===- MBLAZEISelLowering.h - MBLAZE DAG Lowering Interface -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that MBLAZE uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZEISELLOWERING_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZEISELLOWERING_H

#include "MBLAZE.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

// Forward delcarations
class MBLAZESubtarget;
class MBLAZETargetMachine;

namespace MBLAZEISD {
    enum NodeType {
      // Start the numbering from where ISD NodeType finishes.
      FIRST_NUMBER = ISD::BUILTIN_OP_END,

      // Jump and link (call)
      JmpLink,

      // Handle gp_rel (small data/bss sections) relocation.
      GPRel,

      // Select CC Pseudo Instruction
      Select_CC,

      // Wrap up multiple types of instructions
      Wrap,

      // Integer Compare
      ICmp,

      // Return from subroutine
      Ret,

      // Return from interrupt
      IRet
    };
  }

} // end namespace MBLAZEISD

// //===--------------------------------------------------------------------===//
// // TargetLowering Implementation
// //===--------------------------------------------------------------------===//
// class MBLAZETargetLowering : public TargetLowering {
// public:
//   explicit MBLAZETargetLowering(const TargetMachine &TM,
//                              const MBLAZESubtarget &Subtarget);

//   /// Provide custom lowering hooks for some operations.
//   SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;

//   /// This method returns the name of a target specific DAG node.
//   const char *getTargetNodeName(unsigned Opcode) const override;

//   /// Return true if the addressing mode represented by AM is legal for this
//   /// target, for a load/store of the specified type.
//   bool isLegalAddressingMode(const DataLayout &DL, const AddrMode &AM, Type *Ty,
//                              unsigned AS,
//                              Instruction *I = nullptr) const override;

// private:
//   const MBLAZESubtarget &Subtarget;

//   // Lower Operand helpers
//   SDValue LowerCallArguments(SDValue Chain, CallingConv::ID CallConv,
//                              bool isVarArg,
//                              const SmallVectorImpl<ISD::InputArg> &Ins,
//                              SDLoc dl, SelectionDAG &DAG,
//                              SmallVectorImpl<SDValue> &InVals) const;
//   // Lower Operand specifics
//   SDValue LowerJumpTable(SDValue Op, SelectionDAG &DAG) const;
//   SDValue LowerFRAMEADDR(SDValue Op, SelectionDAG &DAG) const;
//   SDValue LowerSELECT_CC(SDValue Op, SelectionDAG &DAG) const;
//   SDValue LowerBR_CC(SDValue Op, SelectionDAG &DAG) const;
//   SDValue LowerSIGN_EXTEND_INREG(SDValue Op, SelectionDAG &DAG) const;
//   SDValue LowerGlobalAddress(SDValue Op, SelectionDAG &DAG) const;
//   SDValue PerformDAGCombine(SDNode *N, DAGCombinerInfo &DCI) const override;

//   SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
//                                bool isVarArg,
//                                const SmallVectorImpl<ISD::InputArg> &Ins,
//                                const SDLoc &dl, SelectionDAG &DAG,
//                                SmallVectorImpl<SDValue> &InVals) const override;

//   SDValue LowerCall(TargetLowering::CallLoweringInfo &CLI,
//                     SmallVectorImpl<SDValue> &InVals) const override;

//   SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
//                       const SmallVectorImpl<ISD::OutputArg> &Outs,
//                       const SmallVectorImpl<SDValue> &OutVals, const SDLoc &dl,
//                       SelectionDAG &DAG) const override;

//   bool CanLowerReturn(CallingConv::ID CallConv, MachineFunction &MF,
//                       bool isVarArg,
//                       const SmallVectorImpl<ISD::OutputArg> &ArgsFlags,
//                       LLVMContext &Context) const override;

//   bool mayBeEmittedAsTailCall(const CallInst *CI) const override;
// };

// } // end namespace llvm

#endif // LLVM_LIB_TARGET_MBLAZE_MBLAZEISELLOWERING_H
