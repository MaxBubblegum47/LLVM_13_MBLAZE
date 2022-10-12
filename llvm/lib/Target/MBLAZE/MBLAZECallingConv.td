//===- MBLAZECallingConv.td - Calling Conventions for MBLAZE -----*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for MBLAZE MBLAZEhitecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// MBLAZE Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_MBLAZE : CallingConv<[
  // i32 are returned in registers R3, R4
  CCIfType<[i32,f32], CCAssignToReg<[R3, R4]>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

def CC_MBLAZE : CallingConv<[
  CCIfType<[i32,f32], CCAssignToStack<4, 4>>
]>;

def CSR_MBLAZE : CalleeSavedRegs<(add (sequence "R%u", 21, 31), GP, FP)>;
