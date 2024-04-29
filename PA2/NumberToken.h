#ifndef NUMBERTOKEN_H_INCLUDED
#define NUMBERTOKEN_H_INCLUDED

#include "Token.h"

class NumberToken : public Token{

private:
    double numericValue;
public:
    NumberToken(TokenType type, Token* ptrnext,double value);
    double getValue() const;
    TokenType getType() const override;
    void print() const override;
    OperatorType getOpType() const override;
};

#endif // NUMBERTOKEN_H_INCLUDED
