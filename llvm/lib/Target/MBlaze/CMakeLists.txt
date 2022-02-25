add_llvm_component_group(MBlaze)

set(LLVM_TARGET_DEFINITIONS MBlaze.td)

# Generate MBlazeGenRegisterInfo.inc and MBlazeGenInstrInfo.inc which included by
# your hand code C++ files.
# MBlazeGenRegisterInfo.inc came from MBlazeRegisterInfo.td, MBlazeGenInstrInfo.inc
# came from MBlazeInstrInfo.td.
tablegen(LLVM MBlazeGenRegisterInfo.inc -gen-register-info)
#tablegen(LLVM MBlazeGenInstrInfo.inc -gen-instr-info)
#tablegen(LLVM MBlazeGenSubtargetInfo.inc -gen-subtarget)
#tablegen(LLVM MBlazeGenMCPseudoLowering.inc -gen-pseudo-lowering)

# MBlazeCommonTableGen must be defined
add_public_tablegen_target(MBlazeCommonTableGen)
# MBlazeCodeGen should match with LLVMBuild.txt MBlazeCodeGen
add_llvm_target(MBlazeCodeGen
MBlazeTargetMachine.cpp
LINK_COMPONENTS
Analysis
AsmPrinter
CodeGen
Core
MC
MBlazeDesc
MBlazeInfo
SelectionDAG
Support
Target
GlobalISel
ADD_TO_COMPONENT
MBlaze
)
# Should match with "subdirectories = MCTargetDesc TargetInfo" in LLVMBuild.txt
#add_subdirectory(TargetInfo)
#add_subdirectory(MCTargetDesc)