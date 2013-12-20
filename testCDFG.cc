#include "CDFG.h"
#include "UnitTest.h"

void testVar() {
    {
        VarNode* p1 = VarNode::makeInt("p1");
        assertEqual("p1", p1->getName(), "Test make int name");
        assertEqual(SORT_INT, p1->getSort().getSortType(), "Test make int type");
        assertEqual("[VAR]\np1 int", p1->strPrint(0), "Test VarNode print"); 
        assertEqual("(VAR p1 int)", p1->strLispMode(0), "Test VarNode print lisp mode");
        delete p1;
    }
    {
        VarNode* p2 = VarNode::makeBitvector("p2", 8);
        assertEqual("p2", p2->getName(), "Test make bitvector name");
        assertEqual(SORT_BITVECTOR, p2->getSort().getSortType(), "Test make bitvector type");
        assertEqual("[VAR]\np2 bitvector 8", p2->strPrint(0), "Test Varnod print");
        assertEqual("(VAR p2 bitvector 8)", p2->strLispMode(0), "Test VarNode lisp mode");
        delete p2;
    }
}

void testConst() {
    {
        ConstNode v(10);
        assertEqual(SORT_INT, v.getSort().getSortType(), "Test ConstNode Type");
        assertEqual(10, v.getInt(), "Test ConstNode Int");
        assertEqual("[CONST]\n10", v.strPrint(0), "Test ConstNode print");
        assertEqual("(CONST 10)", v.strLispMode(0), "Test ConstNode lisp mode");
    }
    {
        ConstNode v("10101011");
        assertEqual(SORT_BITVECTOR, v.getSort().getSortType(), "Test ConstNode Type");
        assertEqual("10101011", v.getBitvector(), "Test ConstNode Bitvector");
        assertEqual("[CONST]\n\"10101011\"", v.strPrint(0), "Test ConstNode print");
        assertEqual("(CONST \"10101011\")", v.strLispMode(0), "Test ConstNode lisp mode");
    }
    {
        ConstNode* p = ConstNode::makeInt(10);
        assertEqual(SORT_INT, p->getSort().getSortType(), "Test ConstNode Type");
        assertEqual(10, p->getInt(), "Test ConstNode Int");
        assertEqual("[CONST]\n10", p->strPrint(0), "Test ConstNode print");
        assertEqual("(CONST 10)", p->strLispMode(0), "Test ConstNode lisp mode");
        delete p;
        
    }
    {
        ConstNode* p = ConstNode::makeBitvector("10101011");
        assertEqual(SORT_BITVECTOR, p->getSort().getSortType(), "Test ConstNode Type");
        assertNonEqual("10001011", p->getBitvector(), "Test ConstNode Bitvector");
        assertEqual("[CONST]\n\"10101011\"", p->strPrint(0), "Test ConstNode print");
        assertEqual("(CONST \"10101011\")", p->strLispMode(0), "Test ConstNode lisp mode");
        delete p;
    }
}

void testGt() {
    {
        OpNode* p = OpNode::makeGt(ConstNode::makeBitvector("101"), ConstNode::makeBitvector("011"));
        assertEqual(OpNode::OP_GT, p->getOpType(), "Test Gt node op type");
        intendedFail(OpNode::OP_LEQ, p->getOpType(), "Fail Gt node op type with Leq");
        assertEqual("[GT]\n[CONST]\n\"101\"\n[CONST]\n\"011\"", p->strPrint(0), "Test Gt node print");
        assertEqual("(GT (CONST \"101\") (CONST \"011\"))", p->strLispMode(0), "Test Gt node lisp mode");
        delete p;
    }
}

void testAssign() {
    {
        AssignNode* p = AssignNode::makeAssign(VarNode::makeInt("a"), ConstNode::makeInt(10));
        assertEqual(SORT_INT, p->getLhs()->getSort().getSortType(), "Test AssignNode lhs type");
        assertEqual(SORT_INT, p->getRhs()->getSort().getSortType(), "Test AssignNode rhs type");
        assertEqual("[ASSIGN]\n[VAR]\na int\n[CONST]\n10", p->strPrint(0), "Test VarNode print"); 
        assertEqual("(ASSIGN (VAR a int) (CONST 10))", p->strLispMode(0), "Test VarNode print lisp mode");
        delete p;
    }
}


void testBlock() {
    {
        AssignNode* p1 = AssignNode::makeAssign(VarNode::makeInt("a"), ConstNode::makeInt(10));
        AssignNode* p2 = AssignNode::makeAssign(VarNode::makeInt("a"), ConstNode::makeInt(11));
        AssignNode* p3 = AssignNode::makeAssign(VarNode::makeInt("a"), ConstNode::makeInt(12));

        Node* vec[] = {p1, p2, p3};
        size_t size_vec = sizeof(vec)/sizeof(&vec[0]);
        BlockNode* p = BlockNode::makeBlock(&vec[0], &vec[size_vec]);
        assertEqual("[BLOCK]\n[ASSIGN]\n[VAR]\na int\n[CONST]\n10\n[ASSIGN]\n[VAR]\na int\n[CONST]\n11[ASSIGN]\n[VAR]\na int\n[CONST]\n12", p->strPrint(0), "Test VarNode print"); 
        assertEqual("(BLOCK (ASSIGN (VAR a int) (CONST 10)) (ASSIGN (VAR a int) (CONST 11)) (ASSIGN (VAR a int) (CONST 12)))", p->strLispMode(0), "Test VarNode print lisp mode");
        delete p;
        delete p1;
        delete p2;
        delete p3;
    }
}

void testBranch() {
    {
        OpNode* pc = OpNode::makeGt(ConstNode::makeBitvector("101"), ConstNode::makeBitvector("011"));
        AssignNode* p1 = AssignNode::makeAssign(VarNode::makeInt("a"), ConstNode::makeInt(10));
        AssignNode* p2 = AssignNode::makeAssign(VarNode::makeInt("a"), ConstNode::makeInt(11));
        BranchNode* p = BranchNode::makeBranch(pc, p1, p2);

        assertEqual(pc, p->getCond(), "Test cond pointer");
        assertEqual(p1, p->getThen(), "Test then pointer");
        assertEqual(p2, p->getElse(), "Test else pointer");

        // assertEqual("[BRANCH]\n[COND]\n[]")

        delete p;
        delete pc;
        delete p1;
        delete p2;
    }
}

int main() {
    testVar();
    testConst();

    testAssign();

    testGt();

    testBlock();

    testBranch();

    return 0;
}
