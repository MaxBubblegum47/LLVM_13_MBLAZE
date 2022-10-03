#include "MBLAZEInstrInfo.h"
#include "MBLAZE.h"
#include "MBLAZEMachineFunctionInfo.h"
#include "MBLAZESubtarget.h"
#include "MCTargetDesc/MBLAZEInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "MBLAZEGenInstrInfo.inc"


void MBLAZEInstrInfo::anchor() {}

MBLAZEInstrInfo::MBLAZEInstrInfo()
    : MBLAZEGenInstrInfo(MBLAZE::ADJCALLSTACKDOWN, MBLAZE::ADJCALLSTACKUP), RI() {}


