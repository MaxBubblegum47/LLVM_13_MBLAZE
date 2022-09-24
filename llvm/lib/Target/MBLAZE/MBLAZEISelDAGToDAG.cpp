#include "MBLAZE.h"
#include "MBLAZETargetMachine.h"
#include "MBLAZEISelLowering.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    class MBLAZEDAGToDAGISel : public SelectionDAGISel {
    public:
        MBLAZEDAGToDAGISel(MBLAZETargetMachine &TM, CodeGenOpt::Level OptLevel)
            : SelectionDAGISel(TM, OptLevel) {}

      void Select(SDNode *N) override;
      bool SelectAddrModeImm(SDValue Addr, SDValue &Base, SDValue &Offset);


        StringRef getPassName() const override {
    return "MBLAZE DAG->DAG Pattern Instruction Selection";
  }

    #include "MBLAZEGenDAGISel.inc"


    };
}


FunctionPass *llvm::createMBLAZEISelDag(MBLAZETargetMachine &TM,
                                     CodeGenOpt::Level OptLevel) {
  return new MBLAZEDAGToDAGISel(TM, OptLevel);
}

bool MBLAZEDAGToDAGISel::SelectAddrModeImm(SDValue Addr, SDValue &Base,
                                        SDValue &Offset) {
  if (Addr.getOpcode() == MBLAZEISD::Wrap) {
    Base = Addr.getOperand(0);
    Offset = CurDAG->getTargetConstant(0, SDLoc(Addr), MVT::i32);
    return true;
  }
  return false;
}

void MBLAZEDAGToDAGISel::Select(SDNode *N) {
  switch (N->getOpcode()) {
  case ISD::Constant: {
    uint64_t CVal = cast<ConstantSDNode>(N)->getZExtValue();
    // ReplaceNode(N, CurDAG->getMachineNode(
    //                    isInt<12>(CVal) ? MBLAZE::MOV_rs12 : MBLAZE::MOV_rlimm,
    //                    SDLoc(N), MVT::i32,
    //                    CurDAG->getTargetConstant(CVal, SDLoc(N), MVT::i32)));
    return;
  }
  }
  SelectCode(N);
}