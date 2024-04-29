#include "OperatorToken.h"
#include <iostream>
using namespace std;

OperatorToken::OperatorToken(TokenType type, Token* ptrnext,OperatorType oper): Token(type,ptrnext){
    opType = oper;
}
OperatorType OperatorToken::getOpType()const {
    return opType;
}

TokenType OperatorToken::getType() const{
    return TokenType::oper;
}

void OperatorToken::print() const{
    cout<<"Operator Token:  ";
    switch (opType) {
    case Addition:
        cout << "+" ;
        break;
    case Subtraction:
        cout << "-" ;
        break;
    case Multiplication:
        cout << "*";
        break;
    case Division:
        cout << "/";
        break;
    }
}
