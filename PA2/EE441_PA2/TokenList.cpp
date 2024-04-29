#include "TokenList.h"
#include <iostream>

TokenList::TokenList(Token* head) {
    headPointer = head;
}
TokenList::~TokenList(void) {
    if (headPointer == nullptr){
        return;
    }else{
        Token* currPointer = headPointer;

        while(currPointer->next != nullptr){
            Token* deletedToken = currPointer;
            currPointer = currPointer->next;
            delete deletedToken;
        }
        delete currPointer;
    }
}

Token* TokenList::GetHeadptr(){
    return headPointer;
}

void TokenList::InsertAfter(Token* p){
    if (headPointer == nullptr){
        headPointer = p;
    }else if (headPointer->next == nullptr){
        headPointer->next = p;
    }else{
        Token* currPointer = headPointer;
        while(currPointer->next != nullptr){
            currPointer = currPointer->next;
        }
        currPointer->next = p;
    }

}

