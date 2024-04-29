#ifndef TOKENLIST_H_INCLUDED
#define TOKENLIST_H_INCLUDED

#include "Token.h"

class TokenList {
private:
    Token* headPointer;
public:

    //Constructor
    //Initialize new tokenlist with header token
    TokenList(Token* head);
    ~TokenList(void);

    Token* GetHeadptr();

    void InsertAfter(Token* p);
};
#endif // TOKENLIST_H_INCLUDED
