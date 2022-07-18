//===-- MBLAZEELFObjectWriter.cpp - MBLAZE ELF Writer -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MBLAZEMCTargetDesc.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCObjectWriter.h"

#define DEBUG_TYPE "MBLAZE-elf-object-writer"

using namespace llvm;

namespace {

class MBLAZEELFObjectWriter : public MCELFObjectTargetWriter {
public:
  MBLAZEELFObjectWriter(uint8_t OSABI = 0)
      : MCELFObjectTargetWriter(false, OSABI, ELF::EM_MBLAZE, true){};
  ~MBLAZEELFObjectWriter() {}

  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
};

} // namespace

unsigned MBLAZEELFObjectWriter::getRelocType(MCContext &Ctx,
                                           const MCValue &Target,
                                           const MCFixup &Fixup,
                                           bool IsPCRel) const {
  // Determine the type of the relocation.
  switch ((unsigned)Fixup.getKind()) {
  default:
    llvm_unreachable("invalid fixup kind!");
  }
}

std::unique_ptr<MCObjectTargetWriter> llvm::createMBLAZEELFObjectWriter() {
  return std::make_unique<MBLAZEELFObjectWriter>();
}
