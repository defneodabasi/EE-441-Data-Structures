#ifndef SYNTAXTREE_H_INCLUDED
#define SYNTAXTREE_H_INCLUDED

#include "Node.h"

class SyntaxTree{
private:
    Node* rootptr;
public:

    Node* getRoot();

    SyntaxTree(Node* root);

    void destructRecursively(Node* root);
    ~SyntaxTree(void);

    void print(Node* root); //InorderPrint
};

#endif // SYNTAXTREE_H_INCLUDED
