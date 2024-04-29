#include "NumberToken.h"
#include <iostream>


NumberToken::NumberToken(TokenType type, Token* ptrnext, double value) : Token(type,ptrnext){

    numericValue = value;
}

double NumberToken::getValue() const {
    return numericValue;
}

TokenType NumberToken::getType() const{
    return TokenType::num;
}

void NumberToken::print() const{
    std::cout<< "Number Token:" << numericValue <<std::endl;
}

OperatorType NumberToken::getOpType() const{
    return Addition;
}
