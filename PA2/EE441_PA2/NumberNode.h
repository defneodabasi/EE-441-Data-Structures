#ifndef NUMBERNODE_H_INCLUDED
#define NUMBERNODE_H_INCLUDED

#include "Node.h"

class NumberNode : public Node{
private:
    double value;

public:
    NumberNode(double val=0, Node* leftNode = NULL, Node* rightNode = NULL);
    double getValue() const override;
    void printnode() const override;
    bool NumOp() const override;
};

#endif // NUMBERNODE_H_INCLUDED
