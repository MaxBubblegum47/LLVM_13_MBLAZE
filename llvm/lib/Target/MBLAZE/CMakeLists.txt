add_llvm_component_group(MBLAZE)

set(LLVM_TARGET_DEFINITIONS MBLAZE.td)

# Generate MBLAZEGenRegisterInfo.inc and MBLAZEGenInstrInfo.inc which included by
# your hand code C++ files.
# MBLAZEGenRegisterInfo.inc came from MBLAZERegisterInfo.td, MBLAZEGenInstrInfo.inc
# came from MBLAZEInstrInfo.td.
tablegen(LLVM MBLAZEGenCallingConv.inc -gen-callingconv)
tablegen(LLVM MBLAZEGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM MBLAZEGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM MBLAZEGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM MBLAZEGenRegisterInfo.inc -gen-register-info)

# MBLAZECommonTableGen must be defined
add_public_tablegen_target(MBLAZECommonTableGen)

# MBLAZECodeGen should match with LLVMBuild.txt MBLAZECodeGen
add_llvm_target(MBLAZECodeGen
MBLAZESubtarget.cpp
MBLAZETargetMachine.cpp

LINK_COMPONENTS
Analysis
AsmPrinter
CodeGen
Core
MC
MBLAZEDesc
MBLAZEInfo
SelectionDAG
Support
Target
GlobalISel

ADD_TO_COMPONENT
MBLAZE
)

# Should match with "subdirectories = MCTargetDesc TargetInfo" in LLVMBuild.txt
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)