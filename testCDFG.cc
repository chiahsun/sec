#include "CDFG.h"
#include "UnitTest.h"

void testVar() {
    {
        VarNode v("a", 10);
        assertEqual("a", v.getName(), "Test VarNode name");
        assertEqual(VarNode::VAR_INT, v.getType(), "Test VarNode type");
        assertEqual(10, v.getInt(), "Test VarNode Int");
        assertEqual("[VAR]\na int", v.strPrint(0), "Test VarNode print"); 
        assertEqual("(VAR a int)", v.strLispMode(0), "Test VarNode print lisp mode");
        assertEqual("(VAR aa int)", v.strLispMode(0), "Test VarNode print lisp mode");
    }
    {
        VarNode v1 = VarNode::makeInt("v1");
        VarNode v2 = VarNode::makeBitvector("v2");
        assertEqual("v1", v1.getName(), "Test make int name");
        assertEqual("v2", v2.getName(), "Test make bitvector name");
        assertEqual(VarNode::VAR_INT, v1.getType(), "Test make int type");
        assertEqual(VarNode::VAR_BITVECTOR, v2.getType(), "Test make bitvector type");
    }
    {
        VarNode v("b", "10101011");
        assertEqual("b", v.getName(), "Test VarNode name");
        assertEqual(VarNode::VAR_BITVECTOR, v.getType(), "Test VarNode type");
        assertEqual("10101011", v.getBitvector(), "Test VarNode bitvector");
        assertEqual(8, v.getBitvector().size(), "Test VarNode bitvector size");
        assertEqual("[VAR]\nb bitvector 8", v.strPrint(0), "Test Varnod print");
        assertEqual("(VAR b bitvector 8)", v.strLispMode(0), "Test VarNode lisp mode");
    }
}

void testConst() {
    {
        ConstNode v(10);
        assertEqual(ConstNode::CONST_INT, v.getType(), "Test ConstNode Type");
        assertEqual(10, v.getInt(), "Test ConstNode Int");
        assertEqual("[CONST]\n10", v.strPrint(0), "Test ConstNode print");
        assertEqual("(CONST 10)", v.strLispMode(0), "Test ConstNode lisp mode");
    }
    {
        ConstNode v("10101011");
        assertEqual(ConstNode::CONST_BITVECTOR, v.getType(), "Test ConstNode Type");
        assertEqual("10101011", v.getBitvector(), "Test ConstNode Bitvector");
        assertEqual("[CONST]\n\"10101011\"", v.strPrint(0), "Test ConstNode print");
        assertEqual("(CONST \"10101011\")", v.strLispMode(0), "Test ConstNode lisp mode");
    }
}

int main() {
    testVar();
    return 0;
}
