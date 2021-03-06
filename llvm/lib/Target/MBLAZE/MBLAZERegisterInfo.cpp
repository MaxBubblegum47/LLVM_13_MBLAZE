#include "MBLAZERegisterInfo.h"
#include "MBLAZE.h"
// #include "MBLAZEMachineFunctionInfo.h" --> From MBLAZE Example we should have also this at a certain point
// #include "MBLAZESubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Support/ErrorHandling.h"

#define GET_REGINFO_TARGET_DESC
#include "MBLAZEGenRegisterInfo.inc"

using namespace llvm;

MBLAZERegisterInfo::
MBLAZERegisterInfo(const MBLAZESubtarget &ST, const TargetInstrInfo &tii)
  : MBLAZEGenRegisterInfo(MBLAZE::R15), Subtarget(ST), TII(tii) {}

unsigned MBLAZERegisterInfo::getPICCallReg() {
  return MBLAZE::R20;
}