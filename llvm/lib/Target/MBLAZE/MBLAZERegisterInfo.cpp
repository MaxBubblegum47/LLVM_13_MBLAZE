#include "MBLAZERegisterInfo.h"
#include "MBLAZE.h"
// #include "MBLAZEMachineFunctionInfo.h" --> From MBLAZE Example we should have also this at a certain point
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

// BUG --> error: invalid ‘static_cast’ from type ‘const llvm::TargetFrameLowering*’ to type ‘const llvm::MBLAZEFrameLowering*’
#define GET_REGINFO_TARGET_DESC
#include "MBLAZEGenRegisterInfo.inc" 