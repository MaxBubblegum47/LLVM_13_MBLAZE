#ifndef MBLAZEREGISTERINFO_H
#define MBLAZEREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

// BUG: 
#define GET_REGINFO_HEADER
#include "MBLAZEGenRegisterInfo.inc" 

namespace llvm{
    class TargetInstrInfo;

    struct MBLAZERegisterInfo : public MBLAZEGenRegisterInfo{
        public:
            MBLAZERegisterInfo();
    };

}


#endif
