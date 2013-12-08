#include "CDFG.h"
#include <cassert>
#include <sstream>

std::string strIndent = "  ";
const std::string VarNode::VAR_BITVECTOR_DEFAULT = "0";
const std::string ConstNode::CONST_BITVECTOR_DEFAULT = "0";

std::string indent(int i = 1) {
    std::stringstream ss;
    for (int k = 0; k < i; ++k) ss << strIndent;
    return ss.str();
}

VarNode VarNode::makeInt(std::string name) {
    return VarNode(name, VAR_INT_DEFAULT);
}

VarNode VarNode::makeBitvector(std::string name) {
    return VarNode(name, VAR_BITVECTOR_DEFAULT);
}

VarNode::VarNode(std::string name, int value) 
  : _varName(name)
  , _varType(VAR_INT)
  , _varInt(value)
  , _varBitvector(VAR_BITVECTOR_DEFAULT)
  { }

VarNode::VarNode(std::string name, std::string bitvectorExpr)
  : _varName(name)
  , _varType(VAR_BITVECTOR)
  , _varInt(VAR_INT_DEFAULT)
  , _varBitvector(bitvectorExpr)
  { }
    
VarNode::VarNodeType VarNode::getType() const
  { return _varType; }

std::string VarNode::getName() const
  { return _varName; }
    
int VarNode::getInt() const
  { assert(getType() == VAR_INT); return _varInt; }
    
BitVector VarNode::getBitvector() const
  { assert(getType() == VAR_BITVECTOR); return _varBitvector; }

std::string VarNode::strPrint(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    switch (getType()) {
        case VAR_INT:
            ss << "[VAR]\n" << getName() << " int"; 
            break;
        case VAR_BITVECTOR:
            ss << "[VAR]\n" << getName() << " bitvector " << _varBitvector.size();
            break;
        default:
            break;
    }
    return ss.str();
}

std::string VarNode::strLispMode(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    switch (getType()) {
        case VAR_INT:
            ss << "(VAR " << getName() << " int)";
            break;
        case VAR_BITVECTOR:
            ss << "(VAR " << getName() << " bitvector " << _varBitvector.size() << ")";
            break;
        default:
            break;
    }    
    return ss.str();
}

ConstNode::ConstNode(int Value)
  : _constType(CONST_INT)
  , _constInt(Value)
  , _constBitvector(CONST_BITVECTOR_DEFAULT)
  {}

ConstNode::ConstNode(std::string bitvectorExpr)
  : _constType(CONST_BITVECTOR)
  , _constInt(CONST_INT_DEFAULT)
  , _constBitvector(bitvectorExpr)
  { }

ConstNode::ConstNodeType ConstNode::getType() const
  { return _constType; }

int ConstNode::getInt() const
  { return _constInt; }

BitVector ConstNode::getBitvector() const
  { return _constBitvector; }

std::string ConstNode::strPrint(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    switch (getType()) {
        case CONST_INT:
            ss << "[CONST]\n" << getInt(); 
            break;
        case CONST_BITVECTOR:
            ss << "[CONST]\n" << getBitvector();
            break;
        default:
            break;
    }
    return ss.str();
}

std::string ConstNode::strLispMode(int depth) const {
    std::stringstream ss;
    ss << indent(depth);
    switch (getType()) {
        case CONST_INT:
            ss << "(CONST " << getInt() << ")";
            break;
        case CONST_BITVECTOR:
            ss << "(CONST " << getBitvector() << ")";
            break;
        default:
            break;
    }    
    return ss.str();
}
