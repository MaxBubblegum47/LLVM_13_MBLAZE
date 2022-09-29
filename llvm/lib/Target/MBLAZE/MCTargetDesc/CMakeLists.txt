# MCTargetDesc/CMakeLists.txt
add_llvm_component_library(LLVMMBLAZEDesc

MBLAZEInstPrinter.cpp
MBLAZEMCTargetDesc.cpp
MBLAZEMCAsmInfo.cpp

LINK_COMPONENTS

MC
MBLAZEInfo
Support

ADD_TO_COMPONENT

MBLAZE

)