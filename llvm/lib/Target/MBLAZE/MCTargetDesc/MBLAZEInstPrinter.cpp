//===-- MBLAZEInstPrinter.cpp - Convert MBLAZE MCInst to assembly syntax --===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints an MBLAZE MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "asm-printer"
#include "MBLAZEInstPrinter.h"
#include "MBLAZE.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
using namespace llvm;


// Include the auto-generated portion of the assembly writer.
#include "MBLAZEGenAsmWriter.inc"

void MBLAZEInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                               StringRef Annot, const MCSubtargetInfo &STI,
                               raw_ostream &O) {
  printInstruction(MI, Address, O);
  printAnnotation(O, Annot);
}


void MBLAZEInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                     raw_ostream &O, const char *Modifier) {
  assert((Modifier == 0 || Modifier[0] == 0) && "No modifiers supported");
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg()) {
    O << getRegisterName(Op.getReg());
  } else if (Op.isImm()) {
    O << (int32_t)Op.getImm();
  } else {
    assert(Op.isExpr() && "unknown operand kind in printOperand");
    O << *Op.getExpr();
  }
}

void MBLAZEInstPrinter::printFSLImm(const MCInst *MI, int OpNo,
                                    raw_ostream &O) {
  const MCOperand &MO = MI->getOperand(OpNo);
  if (MO.isImm())
    O << "rfsl" << MO.getImm();
  else
    printOperand(MI, OpNo, O, NULL);
}

void MBLAZEInstPrinter::printUnsignedImm(const MCInst *MI, int OpNo,
                                        raw_ostream &O) {
  const MCOperand &MO = MI->getOperand(OpNo);
  if (MO.isImm())
    O << (uint32_t)MO.getImm();
  else
    printOperand(MI, OpNo, O, NULL);
}

void MBLAZEInstPrinter::printMemOperand(const MCInst *MI, int OpNo,
                                        raw_ostream &O, const char *Modifier) {
  printOperand(MI, OpNo, O, NULL);
  O << ", ";
  printOperand(MI, OpNo+1, O, NULL);
}