//===- MBLAZEInstPrinter.cpp - MBLAZE MCInst to assembly syntax -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an MBLAZE MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "MBLAZEInstPrinter.h"
#include "MCTargetDesc/MBLAZEInfo.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#include "MBLAZEGenAsmWriter.inc"

template <class T>
static const char *BadConditionCode(T cc) {
  LLVM_DEBUG(dbgs() << "Unknown condition code passed: " << cc << "\n");
  return "{unknown-cc}";
}

static const char *MBLAZEBRCondCodeToString(MBLAZECC::BRCondCode BRCC) {
  switch (BRCC) {
  case MBLAZECC::BREQ:
    return "eq";
  case MBLAZECC::BRNE:
    return "ne";
  case MBLAZECC::BRLT:
    return "lt";
  case MBLAZECC::BRGE:
    return "ge";
  case MBLAZECC::BRLO:
    return "lo";
  case MBLAZECC::BRHS:
    return "hs";
  }
  return BadConditionCode(BRCC);
}

static const char *MBLAZECondCodeToString(MBLAZECC::CondCode CC) {
  switch (CC) {
  case MBLAZECC::EQ:
    return "eq";
  case MBLAZECC::NE:
    return "ne";
  case MBLAZECC::P:
    return "p";
  case MBLAZECC::N:
    return "n";
  case MBLAZECC::HS:
    return "hs";
  case MBLAZECC::LO:
    return "lo";
  case MBLAZECC::GT:
    return "gt";
  case MBLAZECC::GE:
    return "ge";
  case MBLAZECC::VS:
    return "vs";
  case MBLAZECC::VC:
    return "vc";
  case MBLAZECC::LT:
    return "lt";
  case MBLAZECC::LE:
    return "le";
  case MBLAZECC::HI:
    return "hi";
  case MBLAZECC::LS:
    return "ls";
  case MBLAZECC::PNZ:
    return "pnz";
  case MBLAZECC::AL:
    return "al";
  case MBLAZECC::NZ:
    return "nz";
  case MBLAZECC::Z:
    return "z";
  }
  return BadConditionCode(CC);
}

void MBLAZEInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {
  OS << StringRef(getRegisterName(RegNo)).lower();
}

void MBLAZEInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                               StringRef Annot, const MCSubtargetInfo &STI,
                               raw_ostream &O) {
  printInstruction(MI, Address, O);
  printAnnotation(O, Annot);
}

static void printExpr(const MCExpr *Expr, const MCAsmInfo *MAI,
                      raw_ostream &OS) {
  int Offset = 0;
  const MCSymbolRefExpr *SRE;

  if (const auto *CE = dyn_cast<MCConstantExpr>(Expr)) {
    OS << "0x";
    OS.write_hex(CE->getValue());
    return;
  }

  if (const auto *BE = dyn_cast<MCBinaryExpr>(Expr)) {
    SRE = dyn_cast<MCSymbolRefExpr>(BE->getLHS());
    const auto *CE = dyn_cast<MCConstantExpr>(BE->getRHS());
    assert(SRE && CE && "Binary expression must be sym+const.");
    Offset = CE->getValue();
  } else {
    SRE = dyn_cast<MCSymbolRefExpr>(Expr);
    assert(SRE && "Unexpected MCExpr type.");
  }
  assert(SRE->getKind() == MCSymbolRefExpr::VK_None);

  // Symbols are prefixed with '@'
  OS << '@';
  SRE->getSymbol().print(OS, MAI);

  if (Offset) {
    if (Offset > 0)
      OS << '+';
    OS << Offset;
  }
}

void MBLAZEInstPrinter::printOperand(const MCInst *MI, unsigned OpNum,
                                  raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNum);
  if (Op.isReg()) {
    printRegName(O, Op.getReg());
    return;
  }

  if (Op.isImm()) {
    O << Op.getImm();
    return;
  }

  assert(Op.isExpr() && "unknown operand kind in printOperand");
  printExpr(Op.getExpr(), &MAI, O);
}

void MBLAZEInstPrinter::printMemOperand(const MCInst *MI, unsigned OpNum,
                                       raw_ostream &O) {
  const MCOperand &base = MI->getOperand(OpNum);
  const MCOperand &offset = MI->getOperand(OpNum + 1);
  assert(base.isReg() && "Base should be register.");
  assert(offset.isImm() && "Offset should be immediate.");
  printRegName(O, base.getReg());
  O << "," << offset.getImm();
}

void MBLAZEInstPrinter::printPredicateOperand(const MCInst *MI, unsigned OpNum,
                                           raw_ostream &O) {

  const MCOperand &Op = MI->getOperand(OpNum);
  assert(Op.isImm() && "Predicate operand is immediate.");
  O << MBLAZECondCodeToString((MBLAZECC::CondCode)Op.getImm());
}

void MBLAZEInstPrinter::printBRCCPredicateOperand(const MCInst *MI, unsigned OpNum,
                                               raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNum);
  assert(Op.isImm() && "Predicate operand is immediate.");
  O << MBLAZEBRCondCodeToString((MBLAZECC::BRCondCode)Op.getImm());
}

void MBLAZEInstPrinter::printCCOperand(const MCInst *MI, int OpNum,
                                    raw_ostream &O) {
  O << MBLAZECondCodeToString((MBLAZECC::CondCode)MI->getOperand(OpNum).getImm());
}

void MBLAZEInstPrinter::printU6ShiftedBy(unsigned ShiftBy, const MCInst *MI,
                                      int OpNum, raw_ostream &O) {
  const MCOperand &MO = MI->getOperand(OpNum);
  if (MO.isImm()) {
    unsigned Value = MO.getImm();
    unsigned Value2 = Value >> ShiftBy;
    if (Value2 > 0x3F || (Value2 << ShiftBy != Value)) {
      errs() << "!!! Instruction has out-of-range U6 immediate operand:\n"
             << "    Opcode is " << MI->getOpcode() << "; operand value is "
             << Value;
      if (ShiftBy)
        errs() << " scaled by " << (1 << ShiftBy) << "\n";
      assert(false && "instruction has wrong format");
    }
  }
  printOperand(MI, OpNum, O);
}

void MBLAZEInstPrinter::printU6(const MCInst *MI, int OpNum, raw_ostream &O) {
  printU6ShiftedBy(0, MI, OpNum, O);
}
