#include "MBLAZEFrameLowering.h"
#include "MBLAZESubtarget.h"
#include "MBLAZEInstrInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "mblaze-frame-lowering"

using namespace llvm;

// Prologue
void MBLAZEFrameLowering::emitPrologue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}

// Epilogue
void MBLAZEFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}

bool MBLAZEFrameLowering::hasFP(const MachineFunction &MF) const {}
