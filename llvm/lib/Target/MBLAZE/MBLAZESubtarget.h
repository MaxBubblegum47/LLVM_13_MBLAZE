#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZESUBTARGET_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZESUBTARGET_H

 
#include "MCTargetDesc/MBLAZEMCTargetDesc.h"
#include  "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"
#include "llvm/CodeGen/GlobalISel/RegisterBankInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

#define GET_SUBTARGETINFO_HEADER
#include "MBLAZEGenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class MBLAZESubtarget : public MBLAZEGenSubtargetInfo {
  virtual void anchor();
  
  // MBLAZEFrameLowering FrameLowering;
  MBLAZEInstrInfo InstrInfo; // --> error: ‘MBLAZEInstrInfo’ does not name a type; did you mean ‘MCInstrInfo’?
  MBLAZERegisterInfo RegInfo; // -->  error: ‘MBLAZERegisterInfo’ does not name a type; did you mean ‘MCRegisterInfo’?
  // MBLAZETargetLowering TLInfo;
  SelectionDAGTargetInfo TSInfo; // -->  error: ‘MBLAZEInstrInfo’ does not name a type; did you mean ‘MCInstrInfo’? this might be a problem with class definition I guess?
  std::unique_ptr<CallLowering> CallLoweringInfo;

  /// Initializes using the passed in CPU and feature strings so that we can
  /// use initializer lists for subtarget initialization.
  MBLAZESubtarget &initializeSubtargetDependencies(const Triple &TT,
                                                  StringRef CPU, StringRef FS);

public:
  // Initializes the data members to match that of the specified triple.
  MBLAZESubtarget(const Triple &TT, StringRef CPU, const std::string &FS, const TargetMachine &TM);

 
  // Parses features string setting specified subtarget options. The
  // definition of this function is auto-generated by tblgen.
  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);

//   const MBLAZEFrameLowering *getFrameLowering() const override {
//     return &FrameLowering;
//   }
     const MBLAZEInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  
  const MBLAZERegisterInfo *getRegisterInfo() const override {
    return &RegInfo;
  }
  
//   const MBLAZETargetLowering *getTargetLowering() const override {
//     return &TLInfo;
//   }

};
} // End llvm namespace

#endif