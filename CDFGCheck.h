#ifndef CDFG_CHECK_H
#define CDFG_CHECK_H

#include <cassert>
#include <iostream>
#include <cassert>

class Node;
class VarNode;
class ConstNode;
class OpNode;

class CDFGCheckInterface {
public:

    virtual bool check(VarNode* pNode);
    virtual bool check(ConstNode* pNode);
    virtual bool check(OpNode* pNode);
     

    virtual ~CDFGCheckInterface() {
    }
};

class GtCheck : public CDFGCheckInterface {
public:    
    bool check(VarNode* pNode);
    bool check(ConstNode* pNode);
    bool check(OpNode* pNode); 
};

#endif // CDFG_CHECK_H
