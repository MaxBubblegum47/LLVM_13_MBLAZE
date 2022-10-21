add_llvm_component_group(MBLAZE)

set(LLVM_TARGET_DEFINITIONS MBLAZE.td)

tablegen(LLVM MBLAZEGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM MBLAZEGenCallingConv.inc -gen-callingconv)
tablegen(LLVM MBLAZEGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM MBLAZEGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM MBLAZEGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM MBLAZEGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM MBLAZEGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(MBLAZECommonTableGen)

add_llvm_target(MBLAZECodeGen
  MBLAZEAsmPrinter.cpp
  MBLAZEBranchFinalize.cpp
  MBLAZEExpandPseudos.cpp
  MBLAZEFrameLowering.cpp
  MBLAZEInstrInfo.cpp
  MBLAZEISelDAGToDAG.cpp
  MBLAZEISelLowering.cpp
  MBLAZEMachineFunctionInfo.cpp
  MBLAZEMCInstLower.cpp
  MBLAZEOptAddrMode.cpp
  MBLAZERegisterInfo.cpp
  MBLAZESubtarget.cpp
  MBLAZETargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  SelectionDAG
  Support
  Target
  TransformUtils
  MBLAZEDesc
  MBLAZEInfo

  ADD_TO_COMPONENT
  MBLAZE
)

add_subdirectory(Disassembler)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
