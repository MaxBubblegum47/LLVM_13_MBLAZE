//===-- MBLAZEMCTargetDesc.h - MBLAZE Target Descriptions -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides MBLAZE specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCTARGETDESC_H
#define LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCTARGETDESC_H

#include "llvm/MC/MCTargetOptions.h"
#include <memory>

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCRegisterInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class Target;
class Triple;

std::unique_ptr<MCObjectTargetWriter> createMBLAZEELFObjectWriter();

MCAsmBackend *createMBLAZEAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                   const MCRegisterInfo &MRI,
                                   const MCTargetOptions &Options);

MCCodeEmitter *createMBLAZEMCCodeEmitter(const MCInstrInfo &MCII,
                                       const MCRegisterInfo &MRI,
                                       MCContext &Ctx);
} // namespace llvm

#define GET_REGINFO_ENUM
#include "MBLAZEGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "MBLAZEGenInstrInfo.inc"

#endif // LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCTARGETDESC_H
