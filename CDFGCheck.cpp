#include "CDFGCheck.h"
#include "CDFG.h"

bool CDFGCheckInterface::check(VarNode* pNode) {
    std::cerr << "*Error: " << "Not implemented yet." << std::endl;
    assert(0);
}

bool CDFGCheckInterface::check(ConstNode* pNode) {
    std::cerr << "*Error: " << "Not implemented yet." << std::endl;
    assert(0);
}

bool CDFGCheckInterface::check(OpNode* pNode) {
    std::cerr << "*Error: " << "Not implemented yet." << std::endl;
    assert(0);
}



bool GtCheck::check(VarNode* pNode) {
    std::cerr << "*Error: " << "This should not be called." << std::endl;
    assert(0);
}

bool GtCheck::check(ConstNode* pNode) {
    std::cerr << "*Error: " << "This should not be called." << std::endl;
    assert(0);
}


bool GtCheck::check(OpNode* pNode) {

    Node* pNodeFst = pNode->getNodeFirst();
    Node* pNodeSnd = pNode->getNodeSecond(); 

    if (!pNodeFst || !pNodeSnd) return false;

    SortType nodeFstSort = pNode->getNodeFirst()->getSort().getSortType();
    SortType nodeSndSort = pNode->getNodeSecond()->getSort().getSortType();

    return (nodeFstSort == nodeSndSort);   

}
