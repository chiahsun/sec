#include "CDFG.h"
#include <cassert>
#include <sstream>


std::string strIndent = "  ";
const std::string ConstNode::CONST_BITVECTOR_DEFAULT = "0";

std::string indent(int i = 1) {
    std::stringstream ss;
    for (int k = 0; k < i; ++k) ss << strIndent;
    return ss.str();
}

VarNode::VarNode(std::string name, Sort sort) 
  : _varName(name)
  , _varSort(sort) 
 { }

VarNode* VarNode::makeInt(std::string name) {
    return new VarNode(name, Sort::makeIntSort());
}

VarNode* VarNode::makeBitvector(std::string name, int size) {
    return new VarNode(name, Sort::makeBitvectorSort(size));
}
    
Sort VarNode::getSort() const
  { return _varSort; }

std::string VarNode::getName() const
  { return _varName; }
    

std::string VarNode::strPrint(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    switch (getSort().getSortType()) {
        case SORT_INT:
            ss << "[VAR]\n" << getName() << " int"; 
            break;
        case SORT_BITVECTOR:
            ss << "[VAR]\n" << getName() << " bitvector " << getSort().getBitvectorSize();
            break;
        default:
            break;
    }
    return ss.str();
}

std::string VarNode::strLispMode(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    switch (getSort().getSortType()) {
        case SORT_INT:
            ss << "(VAR " << getName() << " int)";
            break;
        case SORT_BITVECTOR:
            ss << "(VAR " << getName() << " bitvector " << getSort().getBitvectorSize() << ")";
            break;
        default:
            break;
    }    
    return ss.str();
}

ConstNode::ConstNode(int value)
  : _constSort(Sort::makeIntSort())
  , _constInt(value)
  , _constBitvector(CONST_BITVECTOR_DEFAULT)
  {}

ConstNode::ConstNode(std::string bitvectorExpr)
  : _constSort(Sort::makeBitvectorSort(bitvectorExpr.size()))
  , _constInt(CONST_INT_DEFAULT)
  , _constBitvector(bitvectorExpr)
  { }

ConstNode* ConstNode::makeInt(int value){
    return new ConstNode(ConstNode(value));
}

ConstNode* ConstNode::makeBitvector(std::string bitvectorExpr){
    return new ConstNode(ConstNode(bitvectorExpr));
}

Sort ConstNode::getSort() const
  { return _constSort; }

int ConstNode::getInt() const
  { return _constInt; }

BitVector ConstNode::getBitvector() const
  { return _constBitvector; }

std::string ConstNode::strPrint(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    switch (getSort().getSortType()) {
        case SORT_INT:
            ss << "[CONST]\n" << getInt(); 
            break;
        case SORT_BITVECTOR:
            ss << "[CONST]\n\"" << getBitvector()<<"\"";
            break;
        default:
            break;
    }
    return ss.str();
}

std::string ConstNode::strLispMode(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    switch (getSort().getSortType()) {
        case SORT_INT:
            ss << "(CONST " << getInt() << ")";
            break;
        case SORT_BITVECTOR:
            ss << "(CONST \"" << getBitvector() << "\")";
            break;
        default:
            break;
    }    
    return ss.str();
}

static const char* OpNodeStringTbl[OpNode::OP_TABLE_END] =
{ "NOT", "NEG", "GT", "LT", "GEQ"
, "LEQ", "SHR", "SHL", "PLUS", "MINUS"
, "MULT", "DIV", "AND", "OR", "XOR"
, "SELECT", "REPEAT_CONCAT", "CONCAT"
, "RANGE_SELECT"};


OpNode* OpNode::makeGt(Node* x, Node* y) {
    OpNode* p = new OpNode;
    p->_nodeOpType = OP_GT;
    p->_nodeFirst = x;
    p->_nodeSecond = y;
    p->checkFunc = new GtCheck();
    return p;
}

std::string OpNode::strPrint(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    ss << "[";
    ss << OpNodeStringTbl[getOpType()];
    ss << "]";
    if (_nodeFirst)
        ss << '\n' << _nodeFirst->strPrint();
    if (_nodeSecond)
        ss << '\n' << _nodeSecond->strPrint();
    if (_nodeThird)
        ss << '\n' << _nodeThird->strPrint();
    return ss.str();
}

std::string OpNode::strLispMode(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    ss << "(";
    ss << OpNodeStringTbl[getOpType()];
    if (_nodeFirst)
        ss << ' ' << _nodeFirst->strLispMode();
    if (_nodeSecond)
        ss << ' ' << _nodeSecond->strLispMode();
    if (_nodeThird)
        ss << ' ' << _nodeThird->strLispMode();
    ss << ")";
    return ss.str();
}

Sort OpNode::getSort() const {
    assert(_nodeFirst);

    return _nodeFirst->getSort();
}

AssignNode* AssignNode::makeAssign(Node* lhs, Node* rhs) {
    AssignNode* p = new AssignNode;
    p->_pNodeLhs = lhs;
    p->_pNodeRhs = rhs;
    return p;
}

std::string AssignNode::strPrint(int depth) const {
    std::stringstream ss;
    ss << indent(depth);

    ss << "[ASSIGN]\n";
    ss << getLhs()->strPrint() << std::endl;
    ss << getRhs()->strPrint();
    return ss.str();
}

std::string AssignNode::strLispMode(int depth) const{
    std::stringstream ss;
    ss << indent(depth);
    ss << "(ASSIGN ";
    ss << getLhs()->strLispMode() << ' ';
    ss << getRhs()->strLispMode();
    ss << ")";
    return ss.str();
}

BlockNode* BlockNode::makeBlock(Node** begin,Node** end) {

    BlockNode* pBlock = new BlockNode;
    
    std::vector<Node*> vec(begin, end);
    pBlock->_vecNode = vec;

    return pBlock;
}

std::string BlockNode::strPrint(int depth) const {
    std::stringstream ss;
    ss << indent(depth);

    ss << "[BLOCK]";
    for (unsigned int i = 0; i < _vecNode.size(); ++i) {
        if (i != _vecNode.size() - 1)
            ss << '\n';
        ss << _vecNode[i]->strPrint();
    }
    return ss.str();
}

std::string BlockNode::strLispMode(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    ss << "(BLOCK";

    for (unsigned int i = 0; i < _vecNode.size(); ++i) {
        ss << ' ';
        ss << _vecNode[i]->strLispMode();
    }
    ss << ")";
    return ss.str();
}

BlockNode* BlockNode::makeBlock() {
    BlockNode* p = new BlockNode;
    return p;
}

BranchNode* BranchNode::makeBranch(Node* pCond, Node* pThen, Node* pElse){
    BranchNode* p = new BranchNode;
    p->_pCondNode = pCond;
    p->_pThenNode = pThen;
    p->_pElseNode = pElse;

    if (!pCond) pCond = NULL_NODE;
    if (!pThen) pThen = NULL_NODE;
    if (!pElse) pElse = NULL_NODE;

    return p;
}

std::string BranchNode::strPrint(int depth) const{
    std::stringstream ss;
    ss << indent(depth);

    ss << "[BRANCH]\n";
    ss << "[COND]\n";
    ss << getCond()->strPrint();
    ss << "\n[THEN]\n";
    ss << getThen()->strPrint();
    ss << "\n[ELSE]\n";
    ss << getElse()->strPrint();

    return ss.str();
}

std::string BranchNode::strLispMode(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    
    ss << "(BRANCH (COND ";
    ss << getCond()->strLispMode();
    ss << ") (THEN ";
    ss << getThen()->strLispMode();
    ss << ") (ELSE ";
    ss << getElse()->strLispMode();
    ss << ")";

    return ss.str();
}
    
Node* BranchNode::NULL_NODE = BlockNode::makeBlock();
