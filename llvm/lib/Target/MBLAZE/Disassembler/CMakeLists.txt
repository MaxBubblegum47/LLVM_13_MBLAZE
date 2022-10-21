add_llvm_component_library(LLVMMBLAZEDisassembler
  MBLAZEDisassembler.cpp

  LINK_COMPONENTS
  MCDisassembler
  Support
  MBLAZEInfo

  ADD_TO_COMPONENT
  MBLAZE
  )
