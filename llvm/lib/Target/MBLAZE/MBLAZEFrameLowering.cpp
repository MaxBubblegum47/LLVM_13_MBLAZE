#include "MBLAZEFrameLowering.h"
#include "MBLAZEInstrInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/MC/MCDwarf.h"

using namespace llvm;

// Prologue
void MBLAZEFrameLowering::emitPrologue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}

// Epilogue
void MBLAZEFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}