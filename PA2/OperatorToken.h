#ifndef OPERATORTOKEN_H_INCLUDED
#define OPERATORTOKEN_H_INCLUDED

#include "Token.h"

class OperatorToken : public Token{

private:
    OperatorType opType; //Addition, subtraction, multiplication, division
public:
    OperatorToken(TokenType type, Token* ptrnext,OperatorType opType);
    OperatorType getOpType() const;
    TokenType getType() const override;
    void print() const override;

};

#endif // OPERATORTOKEN_H_INCLUDED
