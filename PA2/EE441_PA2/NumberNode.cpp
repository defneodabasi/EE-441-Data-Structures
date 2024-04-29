#include "NumberNode.h"
#include <iostream>

//constructor
NumberNode::NumberNode(double num, Node* leftNode, Node* rightNode){
    value = num;
    left = leftNode;
    right = rightNode;
}

double NumberNode::getValue() const {
    return value;
}

void NumberNode::printnode() const {
    std::cout << value;
}

bool NumberNode::NumOp() const{
    return true;
}
