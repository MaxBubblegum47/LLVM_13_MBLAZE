add_llvm_component_group(MBLAZE)

set(LLVM_TARGET_DEFINITIONS MBLAZE.td)

tablegen(LLVM MBLAZEGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM MBLAZEGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM MBLAZEGenCallingConv.inc -gen-callingconv)
tablegen(LLVM MBLAZEGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM MBLAZEGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM MBLAZEGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM MBLAZEGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM MBLAZEGenSubtargetInfo.inc -gen-subtarget)
#tablegen(LLVM MBLAZEGenMCPseudoLowering.inc -gen-pseudo-lowering)

# MBLAZECommonTableGen must be defined
add_public_tablegen_target(MBLAZECommonTableGen)

# MBLAZECodeGen should match with LLVMBuild.txt MBLAZECodeGen
add_llvm_target(MBLAZECodeGen
MBLAZEAsmPrinter.cpp
MBLAZEInstrInfo.cpp
MBLAZEFrameLowering.cpp
MBLAZEMCInstLower.cpp
MBLAZEISelDAGToDAG.cpp
MBLAZESubtarget.cpp
MBLAZERegisterInfo.cpp
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

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)