//===-- MBLAZEMCTargetDesc.cpp - MBLAZE Target Descriptions -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// This file provides MBLAZE-specific target descriptions.
///
//===----------------------------------------------------------------------===//

#include "MBLAZEMCTargetDesc.h"
// #include "MBLAZEBaseInfo.h"
// #include "MBLAZEELFStreamer.h"
// #include "MBLAZEInstPrinter.h"
// #include "MBLAZEMCAsmInfo.h"
// #include "MBLAZETargetStreamer.h"
#include "TargetInfo/MBLAZETargetInfo.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "MBLAZEGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "MBLAZEGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "MBLAZEGenSubtargetInfo.inc"

using namespace llvm;

static MCInstrInfo *createMBLAZEMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitMBLAZEMCInstrInfo(X);
  return X;
}

// static MCRegisterInfo *createMBLAZEMCRegisterInfo(const Triple &TT) {
//   MCRegisterInfo *X = new MCRegisterInfo();
//   InitMBLAZEMCRegisterInfo(X, MBLAZE::X1);
//   return X;
// }

// static MCAsmInfo *createMBLAZEMCAsmInfo(const MCRegisterInfo &MRI,
//                                        const Triple &TT,
//                                        const MCTargetOptions &Options) {
//   MCAsmInfo *MAI = new MBLAZEMCAsmInfo(TT);

//   MCRegister SP = MRI.getDwarfRegNum(MBLAZE::X2, true);
//   MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
//   MAI->addInitialFrameState(Inst);

//   return MAI;
// }

// static MCSubtargetInfo *createMBLAZEMCSubtargetInfo(const Triple &TT,
//                                                    StringRef CPU, StringRef FS) {
//   if (CPU.empty())
//     CPU = TT.isArch64Bit() ? "generic-rv64" : "generic-rv32";
//   if (CPU == "generic")
//     report_fatal_error(Twine("CPU 'generic' is not supported. Use ") +
//                        (TT.isArch64Bit() ? "generic-rv64" : "generic-rv32"));
//   return createMBLAZEMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
// }

// static MCInstPrinter *createMBLAZEMCInstPrinter(const Triple &T,
//                                                unsigned SyntaxVariant,
//                                                const MCAsmInfo &MAI,
//                                                const MCInstrInfo &MII,
//                                                const MCRegisterInfo &MRI) {
//   return new MBLAZEInstPrinter(MAI, MII, MRI);
// }

// static MCTargetStreamer *
// createMBLAZEObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI) {
//   const Triple &TT = STI.getTargetTriple();
//   if (TT.isOSBinFormatELF())
//     return new MBLAZETargetELFStreamer(S, STI);
//   return nullptr;
// }

// static MCTargetStreamer *createMBLAZEAsmTargetStreamer(MCStreamer &S,
//                                                       formatted_raw_ostream &OS,
//                                                       MCInstPrinter *InstPrint,
//                                                       bool isVerboseAsm) {
//   return new MBLAZETargetAsmStreamer(S, OS);
// }

// static MCTargetStreamer *createMBLAZENullTargetStreamer(MCStreamer &S) {
//   return new MBLAZETargetStreamer(S);
// }

// namespace {

// class MBLAZEMCInstrAnalysis : public MCInstrAnalysis {
// public:
//   explicit MBLAZEMCInstrAnalysis(const MCInstrInfo *Info)
//       : MCInstrAnalysis(Info) {}

//   bool evaluateBranch(const MCInst &Inst, uint64_t Addr, uint64_t Size,
//                       uint64_t &Target) const override {
//     if (isConditionalBranch(Inst)) {
//       int64_t Imm;
//       if (Size == 2)
//         Imm = Inst.getOperand(1).getImm();
//       else
//         Imm = Inst.getOperand(2).getImm();
//       Target = Addr + Imm;
//       return true;
//     }

//     if (Inst.getOpcode() == MBLAZE::C_JAL || Inst.getOpcode() == MBLAZE::C_J) {
//       Target = Addr + Inst.getOperand(0).getImm();
//       return true;
//     }

//     if (Inst.getOpcode() == MBLAZE::JAL) {
//       Target = Addr + Inst.getOperand(1).getImm();
//       return true;
//     }

//     return false;
//   }
// };

// } // end anonymous namespace

// static MCInstrAnalysis *createMBLAZEInstrAnalysis(const MCInstrInfo *Info) {
//   return new MBLAZEMCInstrAnalysis(Info);
// }

// namespace {
// MCStreamer *createMBLAZEELFStreamer(const Triple &T, MCContext &Context,
//                                    std::unique_ptr<MCAsmBackend> &&MAB,
//                                    std::unique_ptr<MCObjectWriter> &&MOW,
//                                    std::unique_ptr<MCCodeEmitter> &&MCE,
//                                    bool RelaxAll) {
//   return createMBLAZEELFStreamer(Context, std::move(MAB), std::move(MOW),
//                                 std::move(MCE), RelaxAll);
// }
// } // end anonymous namespace

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMBLAZETargetMC() {

  Target &TheMBLAZETarget = getTheMBLAZETarget();


  // for (Target *T : {&getTheMBLAZE32Target(), &getTheMBLAZETarget()}) {
  //   TargetRegistry::RegisterMCAsmInfo(*T, createMBLAZEMCAsmInfo);
  //   TargetRegistry::RegisterMCInstrInfo(*T, createMBLAZEMCInstrInfo);
  //   TargetRegistry::RegisterMCRegInfo(*T, createMBLAZEMCRegisterInfo);
  //   TargetRegistry::RegisterMCAsmBackend(*T, createMBLAZEAsmBackend);
  //   TargetRegistry::RegisterMCCodeEmitter(*T, createMBLAZEMCCodeEmitter);
  //   TargetRegistry::RegisterMCInstPrinter(*T, createMBLAZEMCInstPrinter);
  //   TargetRegistry::RegisterMCSubtargetInfo(*T, createMBLAZEMCSubtargetInfo);
  //   TargetRegistry::RegisterELFStreamer(*T, createMBLAZEELFStreamer);
  //   TargetRegistry::RegisterObjectTargetStreamer(
  //       *T, createMBLAZEObjectTargetStreamer);

  TargetRegistry::RegisterMCInstrInfo(TheMBLAZETarget, createMBLAZEMCInstrInfo);

  // TargetRegistry::RegisterMCInstrAnalysis(*T, createMBLAZEInstrAnalysis);
  // Register the asm target streamer.
  // TargetRegistry::RegisterAsmTargetStreamer(*T, createMBLAZEAsmTargetStreamer);
  // Register the null target streamer.
  // TargetRegistry::RegisterNullTargetStreamer(*T, createMBLAZENullTargetStreamer);

  }
//}
