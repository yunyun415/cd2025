#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int isalpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isdigit(char c) {
    return (c >= '0' && c <= '9');
}

int isalnum(char c) {
    return isalpha(c) || isdigit(c);
}

int isspace(char c) {
    return (c == ' ' || c == '\n' || c == '\t');
}

// Token 
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
    SEMICOLON_TOKEN
} TokenType;


typedef struct {
    TokenType type;
    char* value;
} Token;


TokenType checkKeyword(char* str) {
    if (strcmp(str, "int") == 0) return TYPE_TOKEN;
    if (strcmp(str, "main") == 0) return MAIN_TOKEN;
    if (strcmp(str, "if") == 0) return IF_TOKEN;
    if (strcmp(str, "else") == 0) return ELSE_TOKEN;
    if (strcmp(str, "while") == 0) return WHILE_TOKEN;
    return ID_TOKEN;
}


void printToken(Token token) {
    switch(token.type) {
        case TYPE_TOKEN: printf("TYPE_TOKEN"); break;
        case MAIN_TOKEN: printf("MAIN_TOKEN"); break;
        case IF_TOKEN: printf("IF_TOKEN"); break;
        case ELSE_TOKEN: printf("ELSE_TOKEN"); break;
        case WHILE_TOKEN: printf("WHILE_TOKEN"); break;
        case ID_TOKEN: printf("ID_TOKEN: %s", token.value); break;
        case LITERAL_TOKEN: printf("LITERAL_TOKEN: %s", token.value); break;
        case ASSIGN_TOKEN: printf("ASSIGN_TOKEN"); break;
        case EQUAL_TOKEN: printf("EQUAL_TOKEN"); break;
        case GREATER_TOKEN: printf("GREATER_TOKEN"); break;
        case LESS_TOKEN: printf("LESS_TOKEN"); break;
        case GREATEREQUAL_TOKEN: printf("GREATEREQUAL_TOKEN"); break;
        case LESSEQUAL_TOKEN: printf("LESSEQUAL_TOKEN"); break;
        case PLUS_TOKEN: printf("PLUS_TOKEN"); break;
        case MINUS_TOKEN: printf("MINUS_TOKEN"); break;
        case LEFTPAREN_TOKEN: printf("LEFTPAREN_TOKEN"); break;
        case REFTPAREN_TOKEN: printf("REFTPAREN_TOKEN"); break;
        case LEFTBRACE_TOKEN: printf("LEFTBRACE_TOKEN"); break;
        case REFTBRACE_TOKEN: printf("REFTBRACE_TOKEN"); break;
        case SEMICOLON_TOKEN: printf("SEMICOLON_TOKEN"); break;
    }
    printf("\n");
}

void lexer() {
    int in_char;
    char buffer[100];
    int bufferIndex = 0;

    while ((in_char = getchar()) != EOF) {
        
        if (isspace(in_char)) continue;

        if (isalpha(in_char)) {
            bufferIndex = 0;
            buffer[bufferIndex++] = in_char;
            
            while (isalnum(in_char = getchar())) {
                buffer[bufferIndex++] = in_char;
            }
            buffer[bufferIndex] = '\0';
            
            Token token;
            token.type = checkKeyword(buffer);
            token.value = strdup(buffer);
            printToken(token);
            free(token.value);
            
            ungetc(in_char, stdin);
        }
        else if (isdigit(in_char)) {
            bufferIndex = 0;
            buffer[bufferIndex++] = in_char;
            
            while (isdigit(in_char = getchar())) {
                buffer[bufferIndex++] = in_char;
            }
            buffer[bufferIndex] = '\0';
            
            Token token;
            token.type = LITERAL_TOKEN;
            token.value = strdup(buffer);
            printToken(token);
            free(token.value);
            
            ungetc(in_char, stdin);
        }
       
        else {
            Token token;
            switch(in_char) {
                case '=': 
                    if ((in_char = getchar()) == '=') {
                        token.type = EQUAL_TOKEN;
                        printToken(token);
                    } else {
                        token.type = ASSIGN_TOKEN;
                        printToken(token);
                        ungetc(in_char, stdin);
                    }
                    break;
                case '>': 
                    if ((in_char = getchar()) == '=') {
                        token.type = GREATEREQUAL_TOKEN;
                        printToken(token);
                    } else {
                        token.type = GREATER_TOKEN;
                        printToken(token);
                        ungetc(in_char, stdin);
                    }
                    break;
                case '<':
                    if ((in_char = getchar()) == '=') {
                        token.type = LESSEQUAL_TOKEN;
                        printToken(token);
                    } else {
                        token.type = LESS_TOKEN;
                        printToken(token);
                        ungetc(in_char, stdin);
                    }
                    break;
                case '+': 
                    token.type = PLUS_TOKEN;
                    printToken(token);
                    break;
                case '-': 
                    token.type = MINUS_TOKEN;
                    printToken(token);
                    break;
                case '(': 
                    token.type = LEFTPAREN_TOKEN;
                    printToken(token);
                    break;
                case ')': 
                    token.type = REFTPAREN_TOKEN;
                    printToken(token);
                    break;
                case '{': 
                    token.type = LEFTBRACE_TOKEN;
                    printToken(token);
                    break;
                case '}': 
                    token.type = REFTBRACE_TOKEN;
                    printToken(token);
                    break;
                case ';': 
                    token.type = SEMICOLON_TOKEN;
                    printToken(token);
                    break;
            }
        }
    }
}

int main() {
    lexer();
    return 0;
}
