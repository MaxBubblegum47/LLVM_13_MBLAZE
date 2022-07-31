#include "MBLAZE.h"
#include "MBLAZEInstrInfo.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/MemoryLocation.h"
#include "llvm/CodeGen/LiveVariables.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "MBLAZEGenInstrInfo.inc"

namespace llvm {
namespace MBLAZEVPseudosTable {

using namespace MBLAZE;

} // namespace MBLAZEVPseudosTable
} // namespace llvm

MBLAZEInstrInfo::MBLAZEInstrInfo(MBLAZESubtarget &STI)
    : MBLAZEGenInstrInfo(MBLAZE::ADJCALLSTACKDOWN, MBLAZE::ADJCALLSTACKUP)
    {}


void MBLAZEInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                 MachineBasicBlock::iterator MBBI,
                                 const DebugLoc &DL, MCRegister DstReg,
                                 MCRegister SrcReg, bool KillSrc) const {
  if (MBLAZE::GPRRegClass.contains(DstReg, SrcReg)) {
    BuildMI(MBB, MBBI, DL, get(MBLAZE::ADDI), DstReg)
        .addReg(SrcReg, getKillRegState(KillSrc))
        .addImm(0);
    return;
  }    
}