#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZEINSTRINFO_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZEINSTRINFO_H

#include "MBLAZERegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "MBLAZEGenInstrInfo.inc"

namespace llvm {

class MBLAZESubtarget;

class MBLAZEInstrInfo : public MBLAZEGenInstrInfo {
  const MBLAZERegisterInfo RI;
  virtual void anchor();

public:
  MBLAZEInstrInfo();

  const MBLAZERegisterInfo &getRegisterInfo() const { return RI; }
      
    };                                            
}                                                 

#endif