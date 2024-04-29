#include "SyntaxTree.h"
#include <iostream>
using namespace std;

SyntaxTree::SyntaxTree(Node* root){
    rootptr = root;
}

Node* SyntaxTree::getRoot(){
    return rootptr;
}

void SyntaxTree::destructRecursively(Node* root){
    if(root) {
        destructRecursively(root->left);
        destructRecursively(root->right);
        delete root;
    }
}

SyntaxTree::~SyntaxTree(void){
    destructRecursively(rootptr);
}
//InorderPrint will be implemented
void SyntaxTree::print(Node* t){
    if (t != nullptr) {
        if (t->NumOp()==false)
            cout << "(";
        print(t->left);
        t->printnode();
        print(t->right);
        if (t->NumOp()==false)
            cout << ")";
    }else {
        cout <<"";
    }
}

