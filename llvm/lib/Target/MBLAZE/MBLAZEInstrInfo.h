#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZEINSTRINFO_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZEINSTRINFO_H

#include "MBLAZERegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/IR/DiagnosticInfo.h"

#define GET_INSTRINFO_HEADER
#include "MBLAZEGenInstrInfo.inc"

namespace llvm {

class MBLAZESubtarget;

class MBLAZEInstrInfo : public MBLAZEGenInstrInfo {

public:
  explicit MBLAZEInstrInfo(MBLAZESubtarget &STI);
    };
}

#endif