#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

enum TokenType{
    oper, //0
    num //1
};

enum OperatorType {
    Addition,
    Subtraction,
    Multiplication,
    Division
};

class Token{

public:

    TokenType typetoken;
    Token *next;

    Token(const TokenType type, Token* p);

    virtual TokenType getType() const = 0;
    virtual void print() const = 0;
    virtual OperatorType getOpType() const=0;
};

#endif // TOKEN_H_INCLUDED
