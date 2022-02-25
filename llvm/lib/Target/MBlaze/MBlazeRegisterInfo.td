//===-- MBlazeRegisterInfo.td - MBlaze Register defs -----------*- tablegen -*-===//
//
//
//          The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//===----------------------------------------------------------------------===//
// Declarations that describe the MBlaze register file
//===----------------------------------------------------------------------===//
// We have banks of 16 registers each.
class MBlazeReg<bits<16> Enc, string n> : Register<n> {
// For tablegen(... -gen-emitter) in CMakeLists.txt
let HWEncoding = Enc;
let Namespace = "MBlaze";
}
// MBlaze CPU Registers
class MBlazeGPRReg<bits<16> Enc, string n> : MBlazeReg<Enc, n>;

// Co-processor 0 Registers
//class MBlazeC0Reg<bits<16> Enc, string n> : MBlazeReg<Enc, n>;

//===----------------------------------------------------------------------===//
//@Registers
//===----------------------------------------------------------------------===//
// The register string, such as "9" or "gp" will show on "llvm-objdump -d"
//@ All registers definition
let Namespace = "MBlaze" in {
  def R0  : MBlazeGPRReg< 0,  "r0">,   DwarfRegNum<[0]>;
  def R1  : MBlazeGPRReg< 1,  "r1">,   DwarfRegNum<[1]>;
  def R2  : MBlazeGPRReg< 2,  "r2">,   DwarfRegNum<[2]>;
  def R3  : MBlazeGPRReg< 3,  "r3">,   DwarfRegNum<[3]>;
  def R4  : MBlazeGPRReg< 4,  "r4">,   DwarfRegNum<[4]>;
  def R5  : MBlazeGPRReg< 5,  "r5">,   DwarfRegNum<[5]>;
  def R6  : MBlazeGPRReg< 6,  "r6">,   DwarfRegNum<[6]>;
  def R7  : MBlazeGPRReg< 7,  "r7">,   DwarfRegNum<[7]>;
  def R8  : MBlazeGPRReg< 8,  "r8">,   DwarfRegNum<[8]>;
  def R9  : MBlazeGPRReg< 9,  "r9">,   DwarfRegNum<[9]>;
  def R10 : MBlazeGPRReg< 10, "r10">,  DwarfRegNum<[10]>;
  def R11 : MBlazeGPRReg< 11, "r11">,  DwarfRegNum<[11]>;
  def R12 : MBlazeGPRReg< 12, "r12">,  DwarfRegNum<[12]>;
  def R13 : MBlazeGPRReg< 13, "r13">,  DwarfRegNum<[13]>;
  def R14 : MBlazeGPRReg< 14, "r14">,  DwarfRegNum<[14]>;
  def R15 : MBlazeGPRReg< 15, "r15">,  DwarfRegNum<[15]>;
  def R16 : MBlazeGPRReg< 16, "r16">,  DwarfRegNum<[16]>;
  def R17 : MBlazeGPRReg< 17, "r17">,  DwarfRegNum<[17]>;
  def R18 : MBlazeGPRReg< 18, "r18">,  DwarfRegNum<[18]>;
  def R19 : MBlazeGPRReg< 19, "r19">,  DwarfRegNum<[19]>;
  def R20 : MBlazeGPRReg< 20, "r20">,  DwarfRegNum<[20]>;
  def R21 : MBlazeGPRReg< 21, "r21">,  DwarfRegNum<[21]>;
  def R22 : MBlazeGPRReg< 22, "r22">,  DwarfRegNum<[22]>;
  def R23 : MBlazeGPRReg< 23, "r23">,  DwarfRegNum<[23]>;
  def R24 : MBlazeGPRReg< 24, "r24">,  DwarfRegNum<[24]>;
  def R25 : MBlazeGPRReg< 25, "r25">,  DwarfRegNum<[25]>;
  def R26 : MBlazeGPRReg< 26, "r26">,  DwarfRegNum<[26]>;
  def R27 : MBlazeGPRReg< 27, "r27">,  DwarfRegNum<[27]>;
  def R28 : MBlazeGPRReg< 28, "r28">,  DwarfRegNum<[28]>;
  def R29 : MBlazeGPRReg< 29, "r29">,  DwarfRegNum<[29]>;
  def R30 : MBlazeGPRReg< 30, "r30">,  DwarfRegNum<[30]>;
  def R31 : MBlazeGPRReg< 31, "r31">,  DwarfRegNum<[31]>;

  // Special Purpose Registers
  // def RPC    : MBlazeSPRReg<0x0000, "rpc">,    DwarfRegNum<[32]>;
  // def RMSR   : MBlazeSPRReg<0x0001, "rmsr">,   DwarfRegNum<[33]>;
  // def REAR   : MBlazeSPRReg<0x0003, "rear">,   DwarfRegNum<[34]>;
  // def RESR   : MBlazeSPRReg<0x0005, "resr">,   DwarfRegNum<[35]>;
  // def RFSR   : MBlazeSPRReg<0x0007, "rfsr">,   DwarfRegNum<[36]>;
  // def RBTR   : MBlazeSPRReg<0x000B, "rbtr">,   DwarfRegNum<[37]>;
  // def REDR   : MBlazeSPRReg<0x000D, "redr">,   DwarfRegNum<[38]>;
  // def RPID   : MBlazeSPRReg<0x1000, "rpid">,   DwarfRegNum<[39]>;
  // def RZPR   : MBlazeSPRReg<0x1001, "rzpr">,   DwarfRegNum<[40]>;
  // def RTLBX  : MBlazeSPRReg<0x1002, "rtlbx">,  DwarfRegNum<[41]>;
  // def RTLBLO : MBlazeSPRReg<0x1003, "rtlblo">, DwarfRegNum<[42]>;
  // def RTLBHI : MBlazeSPRReg<0x1004, "rtlbhi">, DwarfRegNum<[43]>;
  // def RTLBSX : MBlazeSPRReg<0x1004, "rtlbsx">, DwarfRegNum<[44]>;
  // def RPVR0  : MBlazeSPRReg<0x2000, "rpvr0">,  DwarfRegNum<[45]>;
  // def RPVR1  : MBlazeSPRReg<0x2001, "rpvr1">,  DwarfRegNum<[46]>;
  // def RPVR2  : MBlazeSPRReg<0x2002, "rpvr2">,  DwarfRegNum<[47]>;
  // def RPVR3  : MBlazeSPRReg<0x2003, "rpvr3">,  DwarfRegNum<[48]>;
  // def RPVR4  : MBlazeSPRReg<0x2004, "rpvr4">,  DwarfRegNum<[49]>;
  // def RPVR5  : MBlazeSPRReg<0x2005, "rpvr5">,  DwarfRegNum<[50]>;
  // def RPVR6  : MBlazeSPRReg<0x2006, "rpvr6">,  DwarfRegNum<[51]>;
  // def RPVR7  : MBlazeSPRReg<0x2007, "rpvr7">,  DwarfRegNum<[52]>;
  // def RPVR8  : MBlazeSPRReg<0x2008, "rpvr8">,  DwarfRegNum<[53]>;
  // def RPVR9  : MBlazeSPRReg<0x2009, "rpvr9">,  DwarfRegNum<[54]>;
  // def RPVR10 : MBlazeSPRReg<0x200A, "rpvr10">, DwarfRegNum<[55]>;
  // def RPVR11 : MBlazeSPRReg<0x200B, "rpvr11">, DwarfRegNum<[56]>;

  // The carry bit. In the Microblaze this is really bit 29 of the
  // MSR register but this is the only bit of that register that we
  // are interested in modeling.
  // def CARRY  : MBlazeSPRReg<0x0000, "rmsr[c]">;
}
//===----------------------------------------------------------------------===//
//@Register Classes
//===----------------------------------------------------------------------===//
def CPURegs : RegisterClass<"MBlaze", [i32], 32, (add
// Reserved
R0,
R1)>;

//@Status Registers class
// def SR
// : RegisterClass<"MBlaze", [i32], 32, (add SW)>;
// //@Co-processor 0 Registers class
// def C0Regs : RegisterClass<"MBlaze", [i32], 32, (add PC, EPC)>;