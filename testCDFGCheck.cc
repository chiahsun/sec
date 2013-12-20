#include "CDFG.h"
#include "UnitTest.h"

void testGt() {
    {
        OpNode* p = OpNode::makeGt( VarNode::makeInt("A")
                                  , VarNode::makeBitvector("B", 10));
        assertEqual(false, p->check(), "Test if int GT bitvector is valid");
    }
    {
        OpNode* p = OpNode::makeGt( VarNode::makeInt("A")
                                  , 0);
        assertNonEqual(true, p->check(), "Test if two pointer not NULL");
    }
}

int main() {

    testGt();

    return 0;
}
