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
  CCIfType<[i32,f32], CCAssignToReg<[R3, R4]>>
]>;

def CC_MBLAZE : CallingConv<[
  CCIfType<[i32,f32], CCCustom<"CC_MBLAZE_AssignReg">>,
  CCIfType<[i32,f32], CCAssignToStack<4, 4>>
]>;
