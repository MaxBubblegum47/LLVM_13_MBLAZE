#include "MBLAZESubtarget.h"
#include "MBLAZE.h"
#include "MBLAZEGenSubtarget.inc"

using namespace llvm;

MBLAZESubtarget::MBLAZESubtarget(const std::string &TT,
                                 const std::string &CPU,
                                 const std::string &FS):
{
  std::string CPUName = "MBLAZE"
  ParseSubtargetFeatures(CPUName, FS);
}