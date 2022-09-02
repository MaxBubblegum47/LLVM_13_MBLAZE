#ifndef LLVM_LIB_TARGET_MBLAZE_MBLAZEFRAMELOWERING_H
#define LLVM_LIB_TARGET_MBLAZE_MBLAZEFRAMELOWERING_H

#include "MBLAZE.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
    class MBLAZEFrameLowering : public TargetFrameLowering {
        public:
            explicit MBLAZEFrameLowering()
                : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(16), 0) {} //taken directly from RISCV

            void emitPrologue(MachineFunction &MF) const;
            void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const;
    };
}

#endif