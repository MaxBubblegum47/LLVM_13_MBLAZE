//===-- MBLAZEInstrFormats.td - MB Instruction defs --------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//  General Information
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

class InstMBLAZE<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin = NoItinerary>
  : Instruction {
    field bits<32> Inst;
    field bits<32> SoftFail = 0;
    let Namespace = "MBLAZE";
    let Size = 4;
    dag OutOperandList = outs;
    dag InOperandList = ins;
    let AsmString = asmstr;
    let Pattern = pattern;
    let DecoderNamespace = "MBLAZE";
    let Itinerary = itin;
}

//===----------------------------------------------------------------------===//
// Pseudo instruction class
//===----------------------------------------------------------------------===//
class MBLAZEPseudo<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin = NoItinerary>:
      InstMBLAZE<outs, ins, asmstr, pattern, itin>{}

//===----------------------------------------------------------------------===//
// Type A instruction class in MBLAZE : <|opcode|rd|ra|rb|flags|>
//===----------------------------------------------------------------------===//

class TA<bits<6> op, bits<11> flags, dag outs, dag ins, string asmstr,
         list<dag> pattern,  InstrItinClass itin = NoItinerary> :
         InstMBLAZE<outs, ins, asmstr, pattern, itin>
{
  bits<5> rd;
  bits<5> ra;
  bits<5> rb;

  let Inst{6-10}  = rd;
  let Inst{11-15} = ra;
  let Inst{16-20} = rb;
  let Inst{21-31} = flags;
}

//===----------------------------------------------------------------------===//
// Type B instruction class in MBLAZE : <|opcode|rd|ra|immediate|>
//===----------------------------------------------------------------------===//

class TB<bits<6> op, dag outs, dag ins, string asmstr, list<dag> pattern,
         InstrItinClass itin> :
         InstMBLAZE<outs, ins, asmstr, pattern, itin>
{
  bits<5>  rd;
  bits<5>  ra;
  bits<16> imm16;

  let Inst{6-10}  = rd;
  let Inst{11-15} = ra;
  let Inst{16-31} = imm16;
}
