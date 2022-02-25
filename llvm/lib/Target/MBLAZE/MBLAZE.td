//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//
include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Register File, Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//
include "MBLAZERegisterInfo.td"
//include "MBLAZECallingConv.td"
//include "MBLAZESchedule.td"
//include "MBLAZEInstrFormats.td"

//def MBLAZEInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// MBLAZE processors supported.
//===----------------------------------------------------------------------===//
def : Processor<"mblaze",  NoItineraries, []>;

def MBLAZEAsmParser : AsmParser; // Right now there isn't any sort of parser variant
def MBLAZEAsmWriter : AsmWriter;

def MBLAZE : Target  {
    //let InstructionSet = MBLAZEInstrInfo;
    let AssemblyParsers = [MBLAZEAsmParser];
    let AssemblyWriters = [MBLAZEAsmWriter];
    let AllowRegisterRenaming = 1; // I need to investigate on this function
}
