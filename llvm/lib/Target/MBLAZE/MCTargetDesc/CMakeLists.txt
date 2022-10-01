add_llvm_component_library(LLVMMBLAZEDesc

MBLAZEMCTargetDesc.cpp

LINK_COMPONENTS

MC
MBLAZEInfo
Support

ADD_TO_COMPONENT

MBLAZE

)