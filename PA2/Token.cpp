#include "Token.h"
#include <iostream>

Token::Token(const TokenType type=TokenType::num, Token *ptrnext=NULL){
    typetoken = type;
    next = ptrnext;

}
