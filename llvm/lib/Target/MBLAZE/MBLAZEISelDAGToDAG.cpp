#include "MBLAZEISelDAGToDAG.h"
#include "MCTargetDesc/MBLAZEMCTargetDesc.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/Support/Alignment.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/KnownBits.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace{
  class MBLAZEDAGToDAGISel : public SelectionDAGISel {
  public:
    MBLAZEDAGToDAGISel(MBLAZETargetMachine &TM, CodeGenOpt::Level OptLevel)
        : SelectionDAGISel(TM, OptLevel) {}

    private:
        StringRef getPassName() const override {
            return "MBLAZE DAG->DAG Pattern Instruction Selection";
        }

    
    //#include "MBLAZEGenDAGISel.inc"

    };

}