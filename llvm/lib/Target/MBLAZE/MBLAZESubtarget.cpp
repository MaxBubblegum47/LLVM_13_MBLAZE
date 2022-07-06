#include "MBLAZESubtarget.h"
#include "MBLAZE.h"
#include "MBLAZEGenSubtargetInfo.inc"
#include "TargetInfo/MBLAZETargetInfo.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

void MBLAZESubtarget::anchor() {}

void MBLAZESubtarget::initSubtargetFeatures(StringRef CPU, StringRef FS) {
  std::string CPUName = std::string(CPU);
  if (CPUName.empty())
    CPUName = "generic";

  ParseSubtargetFeatures(CPUName, /*TuneCPU*/ CPUName, FS);
}

MBLAZESubtarget &MBLAZESubtarget::initializeSubtargetDependencies(StringRef CPU,
                                                                StringRef FS) {
  initSubtargetFeatures(CPU, FS);
  return *this;
}

MBLAZESubtarget::MBLAZESubtarget(const std::string &TT,
                                 const std::string &CPU,
                                 const std::string &FS)
                                 MBLAZEGenSubtargetInfo(TT, CPU, /*Tune CPU*/ CPU, FS){}
