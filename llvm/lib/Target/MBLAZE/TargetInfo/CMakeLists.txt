add_llvm_component_library(LLVMMBLAZEInfo
  MBLAZETargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  MBLAZE
  )
