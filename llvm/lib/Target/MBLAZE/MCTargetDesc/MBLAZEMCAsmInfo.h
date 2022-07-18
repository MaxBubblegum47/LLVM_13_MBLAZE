#ifndef LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCASMINFO_H
#define LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class MBLAZEMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit MBLAZEMCAsmInfo(const Triple &TargetTriple);
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_MBLAZE_MCTARGETDESC_MBLAZEMCASMINFO_H
