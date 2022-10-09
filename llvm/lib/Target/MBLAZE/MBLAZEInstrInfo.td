//===-- MBLAZEInstrInfo.td - MBLAZE Instruction defs -------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//
include "MBLAZEInstrFormats.td"

//===----------------------------------------------------------------------===//
// MBLAZE type profiles
//===----------------------------------------------------------------------===//

def SDT_MBLAZERet     : SDTypeProfile<0, 1, [SDTCisInt<0>]>;
def SDT_MBCallSeqEnd   : SDCallSeqEnd<[SDTCisVT<0, i32>, SDTCisVT<1, i32>]>;

//===----------------------------------------------------------------------===//
// MBLAZE specific nodes
//===----------------------------------------------------------------------===//

def MBLAZERet     : SDNode<"MBLAZEISD::RET", SDTNone,
                           [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def MBWrapper   : SDNode<"MBLAZEISD::Wrap", SDTIntUnaryOp>;

def callseq_end   : SDNode<"ISD::CALLSEQ_END", SDT_MBCallSeqEnd,
                              [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

//===----------------------------------------------------------------------===//
// MBLAZE Operand, Complex Patterns and Transformations Definitions.
//===----------------------------------------------------------------------===//

def simm16      : Operand<i32>;
// def uimm5       : Operand<i32>;
def uimm16      : Operand<i32>;
// def uimm15      : Operand<i32>;
// def fimm        : Operand<f32>;

//===----------------------------------------------------------------------===//
// Pseudo instructions
//===----------------------------------------------------------------------===//

// This instruction not works for the moment, I need to fix them
// // As stack alignment is always done with addiu, we need a 16-bit immediate
let Defs = [R1], Uses = [R1] in {
def ADJCALLSTACKDOWN : MBLAZEPseudo<(outs), (ins uimm16:$amt0, simm16:$amt1),
                                  "#ADJCALLSTACKDOWN $amt0",
                                  [(callseq_end timm:$amt0, timm:$amt1)]>;
def ADJCALLSTACKUP   : MBLAZEPseudo<(outs), (ins uimm16:$amt2, simm16:$amt3),
                                  "#ADJCALLSTACKUP $amt2",
                                  [(callseq_end timm:$amt2, timm:$amt3)]>;
}

//===----------------------------------------------------------------------===//
// Instructions specific format
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Arithmetic Instructions
//===----------------------------------------------------------------------===//
class Arith<bits<6> op, bits<11> flags, string instr_asm, SDNode OpNode,
            InstrItinClass itin> :
            TA<op, flags, (outs GPR:$dst), (ins GPR:$b, GPR:$c),
               !strconcat(instr_asm, "   $dst, $b, $c"),
               [(set GPR:$dst, (OpNode GPR:$b, GPR:$c))], itin>;



let isCommutable = 1, isAsCheapAsAMove = 1 in {

  def ADD    :  Arith<0x00, 0x000, "add    ", addc, IIC_ALU>;

}

//===----------------------------------------------------------------------===//
// Return
//===----------------------------------------------------------------------===//
def RTSD : InstMBLAZE<(outs), (ins), "j_s\t[%blink]", [(MBLAZERet)]> {
  let Inst{11-0} = 10110110000;
}


