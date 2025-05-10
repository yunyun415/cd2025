#include <stdio.h>  
#include <string.h>  

typedef enum {  
    TYPE_TOKEN,  
    MAIN_TOKEN,  
    IF_TOKEN,  
    ELSE_TOKEN,  
    WHILE_TOKEN,  
    ID_TOKEN,  
    LITERAL_TOKEN,  
    ASSIGN_TOKEN,  
    EQUAL_TOKEN,  
    GREATER_TOKEN,  
    LESS_TOKEN,  
    GREATEREQUAL_TOKEN,  
    LESSEQUAL_TOKEN,  
    PLUS_TOKEN,  
    MINUS_TOKEN,  
    LEFTPAREN_TOKEN,  
    REFTPAREN_TOKEN,  
    LEFTBRACE_TOKEN,  
    REFTBRACE_TOKEN,  
    SEMICOLON_TOKEN,  
    END_TOKEN  
} TokenType;  

typedef struct {  
    TokenType type;  
    char value[100];  
} Token;  

Token current_token;  
int token_pos = 0;  

void getNextToken();  
void parseProgram();  
void parseBlock();  
void parseStatement();  
void parseAssignStatement();  
void parseIfStatement();  
void parseWhileStatement();  
void parseExpression();  
void parseTerm();  
void parseFactor();  

void getNextToken() {  
    static Token tokens[] = {  
        {TYPE_TOKEN, "int"},  
        {MAIN_TOKEN, "main"},  
        {LEFTPAREN_TOKEN, "("},  
        {REFTPAREN_TOKEN, ")"},  
        {LEFTBRACE_TOKEN, "{"},  
        {TYPE_TOKEN, "int"},  
        {ID_TOKEN, "x"},  
        {ASSIGN_TOKEN, "="},  
        {LITERAL_TOKEN, "10"},  
        {SEMICOLON_TOKEN, ";"},  
        {IF_TOKEN, "if"},  
        {LEFTPAREN_TOKEN, "("},  
        {ID_TOKEN, "x"},  
        {GREATER_TOKEN, ">"},  
        {LITERAL_TOKEN, "5"},  
        {REFTPAREN_TOKEN, ")"},  
        {LEFTBRACE_TOKEN, "{"},  
        {ID_TOKEN, "x"},  
        {ASSIGN_TOKEN, "="},  
        {ID_TOKEN, "x"},  
        {PLUS_TOKEN, "+"},  
        {LITERAL_TOKEN, "1"},  
        {SEMICOLON_TOKEN, ";"},  
        {REFTBRACE_TOKEN, "}"},  
        {REFTBRACE_TOKEN, "}"},  
        {END_TOKEN, ""}  
    };  
    
    current_token = tokens[token_pos++];  
}  

void match(TokenType expected) {  
    if (current_token.type == expected) {  
        getNextToken();  
    } else {  
        printf("Syntax Error: Unexpected token\n");  
    }  
}  

void parseProgram() {  
    match(TYPE_TOKEN);  
    match(MAIN_TOKEN);  
    match(LEFTPAREN_TOKEN);  
    match(REFTPAREN_TOKEN);  
    parseBlock();  
}  

void parseBlock() {  
    match(LEFTBRACE_TOKEN);  
    
    while (current_token.type != REFTBRACE_TOKEN) {  
        parseStatement();  
    }  
    
    match(REFTBRACE_TOKEN);  
}  

void parseStatement() {  
    switch (current_token.type) {  
        case TYPE_TOKEN:  
            match(TYPE_TOKEN);  
            match(ID_TOKEN);  
            match(SEMICOLON_TOKEN);  
            break;  
        case ID_TOKEN:  
            parseAssignStatement();  
            break;  
        case IF_TOKEN:  
            parseIfStatement();  
            break;  
        case WHILE_TOKEN:  
            parseWhileStatement();  
            break;  
        default:  
            printf("Syntax Error: Unexpected statement\n");  
    }  
}  

void parseAssignStatement() {  
    match(ID_TOKEN);  
    match(ASSIGN_TOKEN);  
    parseExpression();  
    match(SEMICOLON_TOKEN);  
}  

void parseIfStatement() {  
    match(IF_TOKEN);  
    match(LEFTPAREN_TOKEN);  
    parse
