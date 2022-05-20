//===-- MBLAZESubtarget.h - Define Subtarget for the MBLAZE ----*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the MBLAZE specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//
#include "MBLAZE.h"
#include "MBLAZEGenSubtargetInfo.inc"

namespace llvm {
class MBLAZESubtarget : public MBLAZEGenSubtargetInfo {
    Triple TargetTriple;
    virtual void anchor();
    MBLAZEInstrInfo InstrInfo;
    MBLAZETargetLowering TLInfo;
    MBLAZEFrameLowering FrameLowering;
    
    public:
        MBLAZESubtarget(const Triple &TT, const std::string &CPU,
            const std::string &FS,
            const TargetMachine &TM);
        
        void ParseSubtargetFeatures(StringRef CPU, StringRef FS);
        
        const TargetFrameLowering *getFrameLowering() const
        { return &FrameLowering; }

        const MBLAZEInstrInfo *getInstrInfo() const 
        { return &InstrInfo; }
        
        const MBLAZERegisterInfo *getRegisterInfo() const 
        { return &InstrInfo.getRegisterInfo(); }
        
        const MBLAZETargetLowering *getTargetLowering() const
        { return &TLInfo; }
    };
} // End llvm namespace


