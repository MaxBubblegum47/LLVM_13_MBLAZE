
#include "MBLAZEMCAsmInfo.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/MC/MCStreamer.h"

using namespace llvm;

void MBLAZEMCAsmInfo::anchor() {}

MBLAZEMCAsmInfo::MBLAZEMCAsmInfo(const Triple &TargetTriple) {
  AlignmentIsInBytes = false;
  SupportsDebugInformation = true;
  CommentString = "//";

  ExceptionsType = ExceptionHandling::DwarfCFI;
}
