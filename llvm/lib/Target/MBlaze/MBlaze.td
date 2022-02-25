//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//
include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Register File, Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//
include "MBlazeRegisterInfo.td"
//include "MBlazeCallingConv.td"
//include "MBlazeSchedule.td"
//include "MBlazeInstrFormats.td"

//def MBlazeInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// MBlaze processors supported.
//===----------------------------------------------------------------------===//
def : Processor<"mblaze",  NoItineraries, []>;

def MBlazeAsmParser : AsmParser; // Right now there isn't any sort of parser variant
def MBlazeAsmWriter : AsmWriter;

def MBlaze : Target  {
    //let InstructionSet = MBlazeInstrInfo;
    let AssemblyParsers = [MBlazeAsmParser];
    let AssemblyWriters = [MBlazeAsmWriter];
    let AllowRegisterRenaming = 1; // I need to investigate on this function
}
