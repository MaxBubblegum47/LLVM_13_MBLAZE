#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZESUBTARGET_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZESUBTARGET_H

#include "MBLAZE.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include <string>

#define GET_SUBTARGETINFO_HEADER
#include "MBLAZEGenSubtargetInfo.inc"

namespace llvm {
    class StringRef;

    class MBLAZESubtarget : public MBLAZEGenSubtargetInfo {
        virtual void anchor();
        const DataLayout DL;

        public:
            MBLAZESubtarget(const Triple &TT, StringRef CPU, StringRef FS);

    };
}

#endif