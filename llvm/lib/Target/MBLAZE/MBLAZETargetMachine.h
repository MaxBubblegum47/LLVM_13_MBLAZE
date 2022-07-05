#ifndef LEGTARGETMACHINE_H
#define LEGTARGETMACHINE_H

#include "MBLAZE.h"
#include "MBLAZESubtarget.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class MBLAZETargetMachine : public LLVMTargetMachine{
    MBLAZESubtarget Subtarget;
    
    public:
        MBLAZETargetMachine(const Target &T, const Triple &TT, StringRef CPU,
        StringRef FS);
    
    virtual TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

};
}


#endif
