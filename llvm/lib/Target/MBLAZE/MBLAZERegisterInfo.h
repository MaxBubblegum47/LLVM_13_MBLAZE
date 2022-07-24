#ifndef MBLAZEREGISTERINFO_H
#define MBLAZEREGISTERINFO_H

#include "MBLAZE.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "MBLAZEGenRegisterInfo.inc"

namespace llvm {
class MBLAZESubtarget;
class TargetInstrInfo;
class Type;

namespace MBLAZE {
  /// SubregIndex - The index of various sized subregister classes. Note that
  /// these indices must be kept in sync with the class indices in the
  /// MBLAZERegisterInfo.td file.
  enum SubregIndex {
    SUBREG_FPEVEN = 1, SUBREG_FPODD = 2
  };
}

struct MBLAZERegisterInfo : public MBLAZEGenRegisterInfo {
  const MBLAZESubtarget &Subtarget;
  const TargetInstrInfo &TII;

  MBLAZERegisterInfo(const MBLAZESubtarget &Subtarget,
                     const TargetInstrInfo &tii);

  /// Get PIC indirect call register
  static unsigned getPICCallReg();

  /// Code Generation virtual methods...
  const uint16_t *getCalleeSavedRegs(const MachineFunction* MF = 0) const;

  BitVector getReservedRegs(const MachineFunction &MF) const;

  /// Stack Frame Processing Methods
  void eliminateFrameIndex(MachineBasicBlock::iterator II,
                           int SPAdj, unsigned FIOperandNum,
                           RegScavenger *RS = NULL) const;

  void processFunctionBeforeFrameFinalized(MachineFunction &MF,
                                           RegScavenger *RS = NULL) const;

  /// Debug information queries.
//   unsigned getFrameRegister(const MachineFunction &MF) const;

  /// Exception handling queries.
  unsigned getEHExceptionRegister() const;
  unsigned getEHHandlerRegister() const;
};

} // end namespace llvm

#endif
