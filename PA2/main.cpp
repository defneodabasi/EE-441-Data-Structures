#include "Token.cpp"
#include "NumberToken.cpp"
#include "OperatorToken.cpp"
#include "TokenList.cpp"
#include "NumberNode.cpp"
#include "OperatorNode.cpp"
#include "SyntaxTree.cpp"
#include <iostream>


using namespace std;

TokenList* LexerFunc(string input){
    //creating a tokenlist
    TokenList* tokenListPtr;
    tokenListPtr=new TokenList(nullptr);

    char separator = ' ';
    int i = 0;

    // Temporary string used to split the string.
    string s;
    while (input[i] != '\0') {
        if (input[i] != separator) {
            // Append the char to the temp string.
            s += input[i];
        } else {
            //cout << s << endl;
            if (s == "+"){
                OperatorToken* opToken = new OperatorToken(TokenType::oper, nullptr, OperatorType::Addition);
                tokenListPtr->InsertAfter(opToken);
            }else if(s == "-"){
                OperatorToken* opToken = new OperatorToken(TokenType::oper, nullptr, OperatorType::Subtraction);
                tokenListPtr->InsertAfter(opToken);
            }else if(s == "*"){
                OperatorToken* opToken = new OperatorToken(TokenType::oper, nullptr, OperatorType::Multiplication);
                tokenListPtr->InsertAfter(opToken);
            }else if(s == "/"){
                OperatorToken* opToken = new OperatorToken(TokenType::oper, nullptr, OperatorType::Division);
                tokenListPtr->InsertAfter(opToken);
            }else{
                double x = stod(s);
                NumberToken* numToken = new NumberToken(TokenType::num, nullptr, x);
                tokenListPtr->InsertAfter(numToken);
            }
            s.clear(); //clearing s to hold the next string value
        }
        i++;
    }
    // Output the last stored string.
    //cout << s << endl;
    if (s=="+"){
        OperatorToken* opToken = new OperatorToken(TokenType::oper, nullptr, OperatorType::Addition);
        tokenListPtr->InsertAfter(opToken);
    }else if(s == "-"){
        OperatorToken* opToken = new OperatorToken(TokenType::oper, nullptr, OperatorType::Subtraction);
        tokenListPtr->InsertAfter(opToken);
    }else if(s == "*"){
        OperatorToken* opToken = new OperatorToken(TokenType::oper, nullptr, OperatorType::Multiplication);
        tokenListPtr->InsertAfter(opToken);
    }else if(s == "/"){
        OperatorToken* opToken = new OperatorToken(TokenType::oper, nullptr, OperatorType::Division);
        tokenListPtr->InsertAfter(opToken);
    }else{
        double x = stod(s);
        NumberToken* numToken = new NumberToken(TokenType::num, nullptr, x);
        tokenListPtr->InsertAfter(numToken);
    }
    return tokenListPtr;
}

Node* parseRecursive(Token* &currentPtr){
//    Token* currentPtr = tokenlist.GetHeadptr();
    if (currentPtr == nullptr){
        return nullptr; //TokenList is empty.
    }
//    Token new_tokenlist(currentPtr->next);

    if(currentPtr->getType() == TokenType::oper){
        OperatorType operation = currentPtr->getOpType();
        //cout << "static_cast:"<<operation<<endl;
        currentPtr = currentPtr->next;
        Node* left = parseRecursive(currentPtr);
        Node* right = parseRecursive(currentPtr);

        switch(operation) {
            case OperatorType::Addition:
                return new OperatorNode(OperationType::Add,left,right);
            case OperatorType::Subtraction:
                return new OperatorNode(OperationType::Subtract,left,right);
            case OperatorType::Multiplication:
                return new OperatorNode(OperationType::Multiply,left,right);
            case OperatorType::Division:
                return new OperatorNode(OperationType::Divide,left,right);

        }
    }else if (currentPtr->getType() == TokenType::num){
        double num = static_cast<NumberToken*>(currentPtr)->getValue();
        //cout <<"number node:"<< num <<endl;
        currentPtr = currentPtr->next;
        return new NumberNode(num);
    }
    return nullptr;
}

SyntaxTree* parse(TokenList* &tokenlist){
    Token* headptr = tokenlist->GetHeadptr();

    if (headptr == nullptr){
        return nullptr; //tokenlist is empty
        cout << "token list is empty"<<endl;
    }
    return new SyntaxTree(parseRecursive(headptr));
}

void calculate(string str){
    // A Token list is constructed
    TokenList* myTokenList = new TokenList(nullptr);
    // Lexer function takes the string and return a TokenList pointer.
    myTokenList = LexerFunc(str);
    // SyntaxTree is created
    SyntaxTree* tree = new SyntaxTree(nullptr);
    //parse function takes the TokenList and uses a recursive function inside to make the tree
    tree = parse(myTokenList);
    //root in type Node*
    Node *treehead = tree->getRoot();
    //Inorder print
    tree->print(treehead);
    cout<< " = " << treehead->getValue()<<endl;
}


int main()
{
    string str= "- * + 5.2 -2.7 - 77 1.1 4.5";
    calculate(str);

//    myTokenList->GetHeadptr()->print();
//    myTokenList->GetHeadptr()->next->print();
//    myTokenList->GetHeadptr()->next->next->next->print();
//    myTokenList->GetHeadptr()->next->next->next->next->print();
//    myTokenList->GetHeadptr()->next->next->next->next->next->print();

//    NumberNode* myNumberNode = new NumberNode(5);
//    cout << myNumberNode->getValue() <<endl;
//    myNumberNode->print();

//    OperatorNode* myOperNode = new OperatorNode(OperationType::Add, nullptr, nullptr);
//    myOperNode->print();

//    SyntaxTree* tree = new SyntaxTree(nullptr);
}
