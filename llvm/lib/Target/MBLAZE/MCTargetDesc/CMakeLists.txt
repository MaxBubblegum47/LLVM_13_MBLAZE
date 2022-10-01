add_llvm_component_library(LLVMMBLAZEDesc
  MBLAZEInstPrinter.cpp
  MBLAZEMCTargetDesc.cpp
  MBLAZEMCAsmInfo.cpp

  LINK_COMPONENTS
  MC
  Support
  MBLAZEInfo

  ADD_TO_COMPONENT
  MBLAZE
  )
