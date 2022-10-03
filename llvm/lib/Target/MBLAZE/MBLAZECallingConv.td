//===- MBLAZECallingConv.td - Calling Conventions for MBLAZE -*- tablegen -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for MBLAZE architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// MBLAZE ABI Calling Convention
//===----------------------------------------------------------------------===//

def RetCC_MBLAZE : CallingConv<[
  // i32 are returned in registers R3, R4
  CCIfType<[i32,f32], CCAssignToReg<[R3, R4]>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

def CC_MBLAZE : CallingConv<[
  // this need to be change in terms of registers, I just set some random
  // register to see if it is working
  CCIfType<[i32, f32], CCAssignToReg<[R0, R1, R2, R3, R4, R5, R6, R7]>>,
  CCIfType<[i32,f32], CCAssignToStack<4, 4>>
]>;