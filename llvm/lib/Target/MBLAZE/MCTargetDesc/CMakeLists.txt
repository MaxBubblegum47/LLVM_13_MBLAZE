# MCTargetDesc/CMakeLists.txt
add_llvm_component_library(LLVMMBLAZEDesc

MBLAZEAsmBackend.cpp
MBLAZEELFObjectWriter.cpp
MBLAZEMCAsmInfo.cpp
MBLAZEMCTargetDesc.cpp
MBLAZEMCCodeEmitter.cpp
MBLAZEAsmInfo.cpp	

LINK_COMPONENTS

MC
MBLAZEInfo
Support

ADD_TO_COMPONENT

MBLAZE

)