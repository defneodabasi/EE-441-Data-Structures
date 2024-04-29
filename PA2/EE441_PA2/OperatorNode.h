#ifndef OPERATORNODE_H_INCLUDED
#define OPERATORNODE_H_INCLUDED

#include "Node.h"

enum OperationType{
    Add,
    Subtract,
    Multiply,
    Divide
};

class OperatorNode : public Node{
private:
    OperationType operation;

public:
    OperatorNode(OperationType op, Node* leftNode, Node* rightNode);
    double getValue() const override;
    void printnode() const override;
    bool NumOp() const override;
};
#endif // OPERATORNODE_H_INCLUDED
