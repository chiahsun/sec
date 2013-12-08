#ifndef CDFG_H
#define CDFG_H

#include <iostream>
#include <string>

class Node {
public:
    virtual ~Node() {}
    void print() const {
        std::cout << strPrint(0);
    }
    virtual std::string strPrint(int depth = 0) const = 0;
    void printLispMode() const {
        std::cout << strLispMode(0);
    }
    virtual std::string strLispMode(int depth = 0) const = 0;
};


typedef std::string BitVector;

class VarNode : public Node {
public:
    enum VarNodeType { 
        VAR_INT = 0
      , VAR_BITVECTOR 
    };
private:
    const static std::string VAR_BITVECTOR_DEFAULT;
    const static int VAR_INT_DEFAULT = 0;
    const std::string _varName;
    const VarNodeType _varType;

    const int _varInt;
    const BitVector _varBitvector;
public:
    static VarNode makeInt(std::string name);
    static VarNode makeBitvector(std::string bitvector);
    VarNode(std::string name, int value);
    VarNode(std::string name, std::string bitvectorExpr);

    VarNodeType getType() const;
    std::string getName() const;
    
    int getInt() const;
    BitVector getBitvector() const;
    std::string strPrint(int depth = 0) const;
    std::string strLispMode(int depth = 0) const;

};

class ConstNode : public Node {
public:
    enum ConstNodeType {
        CONST_INT = 0
      , CONST_BITVECTOR
    };
    ConstNode(int Value);
    ConstNode(std::string bitvectorExpr);

    ConstNodeType getType() const;
    
    int getInt() const;
    BitVector getBitvector() const;

    std::string strPrint(int depth = 0) const;
    std::string strLispMode(int depth = 0) const;

private:
    const static std::string CONST_BITVECTOR_DEFAULT;
    const static int CONST_INT_DEFAULT = 0;
    const ConstNodeType _constType;
    const int _constInt;
    const BitVector _constBitvector;
};


#endif // CDFG_H
