//===-- MBLAZERegisterInfo.td - MBLAZE Register defs -----------*- tablegen -*-===//
//
//
//                       The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//===----------------------------------------------------------------------===//
// Declarations that describe the MBLAZE register file
//===----------------------------------------------------------------------===//

// We have banks of 32 registers each.
class MBLAZEReg<bits<5> Enc, string n> : Register<n> {
// For tablegen(... -gen-emitter) in CMakeLists.txt
let HWEncoding = Enc;
let Namespace = "MBLAZE";
}

// MBLAZE CPU Registers
class MBLAZEGPRReg<bits<5> Enc, string n> : MBLAZEReg<Enc, n>;

// Special purpose registers have 15-bit values
class MBLAZESReg<bits<15> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "MBLAZE";
}

// MBlaze special purpose registers
class MBLAZESPRReg<bits<15> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "MBLAZE";
}

//===----------------------------------------------------------------------===//
//@Registers
//===----------------------------------------------------------------------===//
// The register string, such as "9" or "gp" will show on "llvm-objdump -d"
//@ All registers definition
let Namespace = "MBLAZE" in {
  def R0  : MBLAZEGPRReg< 0,  "r0">,   DwarfRegNum<[0]>;
  def R1  : MBLAZEGPRReg< 1,  "r1">,   DwarfRegNum<[1]>;
  def R2  : MBLAZEGPRReg< 2,  "r2">,   DwarfRegNum<[2]>;
  def R3  : MBLAZEGPRReg< 3,  "r3">,   DwarfRegNum<[3]>;
  def R4  : MBLAZEGPRReg< 4,  "r4">,   DwarfRegNum<[4]>;
  def R5  : MBLAZEGPRReg< 5,  "r5">,   DwarfRegNum<[5]>;
  def R6  : MBLAZEGPRReg< 6,  "r6">,   DwarfRegNum<[6]>;
  def R7  : MBLAZEGPRReg< 7,  "r7">,   DwarfRegNum<[7]>;
  def R8  : MBLAZEGPRReg< 8,  "r8">,   DwarfRegNum<[8]>;
  def R9  : MBLAZEGPRReg< 9,  "r9">,   DwarfRegNum<[9]>;
  def R10 : MBLAZEGPRReg< 10, "r10">,  DwarfRegNum<[10]>;
  def R11 : MBLAZEGPRReg< 11, "r11">,  DwarfRegNum<[11]>;
  def R12 : MBLAZEGPRReg< 12, "r12">,  DwarfRegNum<[12]>;
  def R13 : MBLAZEGPRReg< 13, "r13">,  DwarfRegNum<[13]>;
  def R14 : MBLAZEGPRReg< 14, "r14">,  DwarfRegNum<[14]>;
  def R15 : MBLAZEGPRReg< 15, "r15">,  DwarfRegNum<[15]>;
  def R16 : MBLAZEGPRReg< 16, "r16">,  DwarfRegNum<[16]>;
  def R17 : MBLAZEGPRReg< 17, "r17">,  DwarfRegNum<[17]>;
  def R18 : MBLAZEGPRReg< 18, "r18">,  DwarfRegNum<[18]>;
  def R19 : MBLAZEGPRReg< 19, "r19">,  DwarfRegNum<[19]>;
  def R20 : MBLAZEGPRReg< 20, "r20">,  DwarfRegNum<[20]>;
  def R21 : MBLAZEGPRReg< 21, "r21">,  DwarfRegNum<[21]>;
  def R22 : MBLAZEGPRReg< 22, "r22">,  DwarfRegNum<[22]>;
  def R23 : MBLAZEGPRReg< 23, "r23">,  DwarfRegNum<[23]>;
  def R24 : MBLAZEGPRReg< 24, "r24">,  DwarfRegNum<[24]>;
  def R25 : MBLAZEGPRReg< 25, "r25">,  DwarfRegNum<[25]>;
  def R26 : MBLAZEGPRReg< 26, "r26">,  DwarfRegNum<[26]>;
  def R27 : MBLAZEGPRReg< 27, "r27">,  DwarfRegNum<[27]>;
  def R28 : MBLAZEGPRReg< 28, "r28">,  DwarfRegNum<[28]>;
  def R29 : MBLAZEGPRReg< 29, "r29">,  DwarfRegNum<[29]>;
  def R30 : MBLAZEGPRReg< 30, "r30">,  DwarfRegNum<[30]>;
  def R31 : MBLAZEGPRReg< 31, "r31">,  DwarfRegNum<[31]>;

  // Special Purpose Registers
  def RPC    : MBLAZESPRReg<0x0000, "rpc">,    DwarfRegNum<[32]>;
  def RMSR   : MBLAZESPRReg<0x0001, "rmsr">,   DwarfRegNum<[33]>;
  def REAR   : MBLAZESPRReg<0x0003, "rear">,   DwarfRegNum<[34]>;
  def RESR   : MBLAZESPRReg<0x0005, "resr">,   DwarfRegNum<[35]>;
  def RFSR   : MBLAZESPRReg<0x0007, "rfsr">,   DwarfRegNum<[36]>;
  def RBTR   : MBLAZESPRReg<0x000B, "rbtr">,   DwarfRegNum<[37]>;
  def REDR   : MBLAZESPRReg<0x000D, "redr">,   DwarfRegNum<[38]>;
  def RPID   : MBLAZESPRReg<0x1000, "rpid">,   DwarfRegNum<[39]>;
  def RZPR   : MBLAZESPRReg<0x1001, "rzpr">,   DwarfRegNum<[40]>;
  def RTLBX  : MBLAZESPRReg<0x1002, "rtlbx">,  DwarfRegNum<[41]>;
  def RTLBLO : MBLAZESPRReg<0x1003, "rtlblo">, DwarfRegNum<[42]>;
  def RTLBHI : MBLAZESPRReg<0x1004, "rtlbhi">, DwarfRegNum<[43]>;
  def RTLBSX : MBLAZESPRReg<0x1004, "rtlbsx">, DwarfRegNum<[44]>;
  def RPVR0  : MBLAZESPRReg<0x2000, "rpvr0">,  DwarfRegNum<[45]>;
  def RPVR1  : MBLAZESPRReg<0x2001, "rpvr1">,  DwarfRegNum<[46]>;
  def RPVR2  : MBLAZESPRReg<0x2002, "rpvr2">,  DwarfRegNum<[47]>;
  def RPVR3  : MBLAZESPRReg<0x2003, "rpvr3">,  DwarfRegNum<[48]>;
  def RPVR4  : MBLAZESPRReg<0x2004, "rpvr4">,  DwarfRegNum<[49]>;
  def RPVR5  : MBLAZESPRReg<0x2005, "rpvr5">,  DwarfRegNum<[50]>;
  def RPVR6  : MBLAZESPRReg<0x2006, "rpvr6">,  DwarfRegNum<[51]>;
  def RPVR7  : MBLAZESPRReg<0x2007, "rpvr7">,  DwarfRegNum<[52]>;
  def RPVR8  : MBLAZESPRReg<0x2008, "rpvr8">,  DwarfRegNum<[53]>;
  def RPVR9  : MBLAZESPRReg<0x2009, "rpvr9">,  DwarfRegNum<[54]>;
  def RPVR10 : MBLAZESPRReg<0x200A, "rpvr10">, DwarfRegNum<[55]>;
  def RPVR11 : MBLAZESPRReg<0x200B, "rpvr11">, DwarfRegNum<[56]>;

  // The carry bit. In the Microblaze this is really bit 29 of the
  // MSR register but this is the only bit of that register that we
  // are interested in modeling.
  def CARRY  : MBLAZESPRReg<0x0000, "rmsr[c]">;
}
//===----------------------------------------------------------------------===//
//@Register Classes
//===----------------------------------------------------------------------===//
// def CPURegs : RegisterClass<"MBLAZE", [i32], 32, (add
// // Reserved
// R0,
// R1)>;

def SPR : RegisterClass<"MBlaze", [i32], 32, (add
  // Reserved
  RPC,
  RMSR,
  REAR,
  RESR,
  RFSR,
  RBTR,
  REDR,
  RPID,
  RZPR,
  RTLBX,
  RTLBLO,
  RTLBHI,
  RPVR0,
  RPVR1,
  RPVR2,
  RPVR3,
  RPVR4,
  RPVR5,
  RPVR6,
  RPVR7,
  RPVR8,
  RPVR9,
  RPVR10,
  RPVR11
  )>

{
  let isAllocatable = 0;
}

def CRC : RegisterClass<"MBlaze", [i32], 32, (add CARRY)> {
  let CopyCost = -1;
}
