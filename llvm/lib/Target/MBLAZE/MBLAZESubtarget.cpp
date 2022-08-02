#include "MBLAZESubtarget.h"
#include "MBLAZE.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "MBLAZE-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "MBLAZEGenSubtargetInfo.inc"

void MBLAZESubtarget::anchor() {}

MBLAZESubtarget &MBLAZESubtarget::initializeSubtargetDependencies(
    const Triple &TT, StringRef CPU, StringRef FS) {
  // Determine default and user-specified characteristics
  std::string CPUName = std::string(CPU);
  if (CPUName.empty())
    CPUName = "mblaze";
  ParseSubtargetFeatures(CPUName, FS);

  return *this;
}
