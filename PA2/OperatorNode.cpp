#include "OperatorNode.h"
#include <iostream>

OperatorNode::OperatorNode(OperationType op, Node* leftptr, Node* rightptr){
    operation = op;
    left = leftptr;
    right = rightptr;
}

//may need a destructor

double OperatorNode::getValue() const{
    double leftValue = left->getValue();
    double rightValue = right ->getValue();

    switch (operation) {
    case Add:
        return leftValue + rightValue;
    case Subtract:
        return leftValue - rightValue;
    case Multiply:
        return leftValue * rightValue;
    case Divide:
        return leftValue / rightValue;
    }
}

void OperatorNode::printnode() const {
    switch (operation) {
    case Add:
        std::cout << " + ";
        break;
    case Subtract:
        std::cout << " - ";
        break;
    case Multiply:
        std::cout << " * ";
        break;
    case Divide:
        std::cout << " / ";
        break;
    }
}

bool OperatorNode::NumOp() const{
    return false;
}
