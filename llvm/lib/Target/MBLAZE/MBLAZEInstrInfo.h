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
  explicit MBLAZEInstrInfo(MBLAZESubtarget &STI); // STI refers to subtarget feature that right now i don't have
    
  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI,
                  const DebugLoc &DL, MCRegister DstReg, MCRegister SrcReg,
                  bool KillSrc) const override;  
      
    };                                            // but at the same time i'm not super sure about how to do a function
}                                                 // without inlcuding it

#endif