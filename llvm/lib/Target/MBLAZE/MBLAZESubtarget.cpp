#include "MBLAZESubtarget.h"
#include "MBLAZE.h"
#include "MBLAZEGenSubtargetInfo.inc"

using namespace llvm;

void MBLAZESubtarget::anchor() {}

MBLAZESubtarget::MBLAZESubtarget(const std::string &TT,
                                 const std::string &CPU,
                                 const std::string &FS){}
