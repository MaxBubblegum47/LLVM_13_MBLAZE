#include "MBLAZERegisterInfo.h"
#include "MBLAZE.h"
#include "MBLAZEInstrInfo.h"
#include "MBLAZEMachineFunctionInfo.h" 
#include "MBLAZESubtarget.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"


using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "MBLAZEGenRegisterInfo.inc" 

MBLAZERegisterInfo::MBLAZERegisterInfo() : MBLAZEGenRegisterInfo(MBLAZE::R1,0U, 0U, 0U, 0U) {}
