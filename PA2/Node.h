#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED



class Node{
public:
    Node* left;
    Node* right;

    virtual double getValue() const = 0;
    virtual void printnode() const = 0;
    virtual bool NumOp() const = 0;
};

#endif // NODE_H_INCLUDED
