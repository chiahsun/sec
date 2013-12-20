#ifndef CDFG_H
#define CDFG_H

#include <iostream>
#include <string>
#include <vector>

#include "CDFGCheck.h"

class Sort;

enum SortType {
    SORT_INT
  , SORT_BITVECTOR
};


class Node {
public:
    virtual ~Node() {}
    void print() const {
        std::cout << strPrint(0);
    }
    void printLispMode() const {
        std::cout << strLispMode(0);
    }
    virtual std::string strPrint(int depth = 0) const = 0;
    virtual std::string strLispMode(int depth = 0) const = 0;
    
    virtual Sort getSort() const = 0;
};


typedef std::string BitVector;

class Sort {
public:
    static Sort makeIntSort() {
        Sort s;
        s._type = SORT_INT;
        return s;
    }
    static Sort makeBitvectorSort(int size) {
        Sort s;
        s._type = SORT_BITVECTOR;
        s._bitvectorSize = size;
        return s;
    }

    SortType getSortType() const {
        return _type;
    }
    int getBitvectorSize() const {
        assert(getSortType() == SORT_BITVECTOR);
        return _bitvectorSize;
    }
    inline bool operator == (const Sort & rhs) {
        return (getSortType() == rhs.getSortType())
            && ((getSortType() != SORT_BITVECTOR) || 
                (getBitvectorSize() == rhs.getBitvectorSize()));
    }
private:
    SortType _type;
    int _bitvectorSize;
};

class VarNode : public Node {
private:
    const std::string _varName;
    const Sort        _varSort;     

    VarNode(std::string name, Sort sort);

public:
    static VarNode* makeInt(std::string name);
    static VarNode* makeBitvector(std::string name, int size);


    Sort getSort() const;
    std::string getName() const;
    
    std::string strPrint(int depth = 0) const;
    std::string strLispMode(int depth = 0) const;
};

class ConstNode : public Node {
public:
    static ConstNode* makeInt(int value);
    static ConstNode* makeBitvector(std::string bitvectorExpr);
    ConstNode(int value);
    ConstNode(std::string bitvectorExpr);

    Sort getSort() const;
    
    int getInt() const;
    BitVector getBitvector() const;

    std::string strPrint(int depth = 0) const;
    std::string strLispMode(int depth = 0) const;

private:
    const Sort _constSort;
    const static std::string CONST_BITVECTOR_DEFAULT;
    const static int CONST_INT_DEFAULT = 0;
    const int _constInt;
    const BitVector _constBitvector;
};


class OpNode : public Node {
public:
    enum OpNodeType {
      // UNARY
        OP_NOT = 0
      , OP_BITWISE_NEGATTION

      // BINARY
      , OP_GT
      , OP_LT
      , OP_GEQ
      , OP_LEQ
      , OP_SHR
      , OP_SHL
      , OP_PLUS
      , OP_MINUS
      , OP_MULT
      , OP_DIV
      , OP_BITWISE_AND
      , OP_BITWISE_OR
      , OP_BITWISE_XOR
      , OP_BIT_SELECT
      , OP_REAPTED_CONCAT
      , OP_CONCAT

      // TERNARY
      , OP_RANGE_SELECT

      // END MARK : DO NOT USE
      , OP_TABLE_END
    };

    OpNode() {
        _nodeThird = _nodeSecond = _nodeThird = 0;
    }
    static OpNode* makeGt(Node* x, Node* y);

    CDFGCheckInterface* checkFunc;

    inline OpNodeType getOpType() const
      { return _nodeOpType; }

    bool check() {
        return checkFunc->check(this);
    }
    // bool checkValid()
    // Formula getFormula
    // Node* substituteVar
    Sort getSort() const;

    inline Node* getNodeFirst() { return _nodeFirst; }
    inline Node* getNodeSecond() { return _nodeSecond; }
    Node* getNodeThird() { return _nodeThird; }

    friend class CDFGCheckInterface;
    std::string strPrint(int depth = 0) const;
    std::string strLispMode(int depth = 0) const;

private:
    Node* _nodeFirst;
    Node* _nodeSecond;
    Node* _nodeThird;

    OpNodeType _nodeOpType;
};

class AssignNode : public Node {
public:
    static AssignNode* makeAssign(Node* lhs,Node* rhs);

    inline Node* getLhs() const { return _pNodeLhs; }
    inline Node* getRhs() const { return _pNodeRhs; }

    std::string strPrint(int depth = 0) const;
    std::string strLispMode(int depth = 0) const;
    
    Sort getSort() const { assert(0); }
private:
    Node* _pNodeLhs;
    Node* _pNodeRhs;
};

class BlockNode : public Node {
public:
    static BlockNode* makeBlock();
    static BlockNode* makeBlock(Node** begin,Node** end);

    std::string strPrint(int depth = 0) const;
    std::string strLispMode(int depth = 0) const;

    Sort getSort() const { assert(0); }
private:
    std::vector<Node*> _vecNode;
};

class BranchNode : public Node {
public:
    static BranchNode* makeBranch(Node* pCond,Node* pThen,Node* pElse);
    static Node* NULL_NODE;

    std::string strPrint(int depth = 0) const;
    std::string strLispMode(int depth = 0) const;

    inline Node* getCond() const { return _pCondNode; }
    inline Node* getThen() const { return _pThenNode; }
    inline Node* getElse() const { return _pElseNode; }

    Sort getSort() const { assert(0); }
private:
    Node* _pCondNode;
    Node* _pThenNode;
    Node* _pElseNode;
};
#endif // CDFG_H
