//===-- MBLAZEInstrFormats.td - MB Instruction defs --------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Format specifies the encoding used by the instruction.  This is part of the
// ad-hoc solution used to emit machine instruction encodings by our machine
// code emitter.
class Format<bits<6> val> {
      bits<6> Value = val;
}

def FPseudo : Format<0>;
def FRRR    : Format<1>;  // ADD, OR, etc.


//===----------------------------------------------------------------------===//
//  Describe MBLAZE instructions format
//
//  CPU INSTRUCTION FORMATS
//
//  opcode  - operation code.
//  rd      - dst reg.
//  ra      - first src. reg.
//  rb      - second src. reg.
//  imm16   - 16-bit immediate value.
//
//===----------------------------------------------------------------------===//

// Generic MBLAZE Format
class MBLAZEInst<bits<6> op, Format form, dag outs, dag ins, string asmstr,
                 list<dag> pattern, InstrItinClass itin> : Instruction {
  let Namespace = "MBLAZE";
  field bits<32> Inst;

  bits<6> opcode = op;
  Format Form = form;
  bits<6> FormBits = Form.Value;

  // Top 6 bits are the 'opcode' field
  let Inst{0-5} = opcode;

  // If the instruction is marked as a pseudo, set isCodeGenOnly so that the
  // assembler and disassmbler ignore it.
  let isCodeGenOnly = !eq(!cast<string>(form), "FPseudo");

  dag OutOperandList = outs;
  dag InOperandList  = ins;

  let AsmString   = asmstr;
  let Pattern     = pattern;
  let Itinerary   = itin;

  // TSFlags layout should be kept in sync with MBLAZEInstrInfo.h.
  let TSFlags{5-0}   = FormBits;
}

//===----------------------------------------------------------------------===//
// Pseudo instruction class
//===----------------------------------------------------------------------===//
class MBLAZEPseudo<dag outs, dag ins, string asmstr, list<dag> pattern>:
      MBLAZEInst<0x0, FPseudo, outs, ins, asmstr, pattern, IIC_Pseudo>;

//===----------------------------------------------------------------------===//
// Type A instruction class in MBLAZE : <|opcode|rd|ra|rb|flags|>
//===----------------------------------------------------------------------===//

class TA<bits<6> op, bits<11> flags, dag outs, dag ins, string asmstr,
         list<dag> pattern, InstrItinClass itin> :
         MBLAZEInst<op,FRRR,outs, ins, asmstr, pattern, itin>
{
  bits<5> rd;
  bits<5> ra;
  bits<5> rb;

  let Inst{6-10}  = rd;
  let Inst{11-15} = ra;
  let Inst{16-20} = rb;
  let Inst{21-31} = flags;
}

