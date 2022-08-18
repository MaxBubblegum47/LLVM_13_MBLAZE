#include "MBLAZE.h"
#include "MBLAZETargetMachine.h" //this could be broken at the time I'm writing down this file
#include "llvm/CodeGen/SelectionDAGISel.h"

namespace llvm {
    class MBLAZEDAGToDAGISel : public SelectionDAGISel{
    
    public:
        explicit MBLAZEDAGToDAGISel(MBLAZETargetMachine &TargetMachine)
            : SelectionDAGISel(TargetMachine){}
    };

    //#include "MBLAZEGenDAGISel.inc"


}