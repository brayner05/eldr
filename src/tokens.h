#ifndef ELDR_TOKENS_H
#define ELDR_TOKENS_H

#include <stdint.h>
#include "dstring.h"

typedef enum {
    // Types
    TokenType_FLOAT, TokenType_DOUBLE, TokenType_INTEGER, TokenType_STRING, 
    TokenType_CHARACTER, TokenType_STRUCT, TokenType_ENUM,

    // Arithmetic
    TokenType_CARET, TokenType_PLUS, TokenType_PLUS_EQUAL, 
    TokenType_MINUS, TokenType_MINUS_EQUAL, TokenType_ADDRESS, 
    TokenType_STAR, TokenType_STAR_EQUAL, TokenType_SLASH, 
    TokenType_SLASH_EQUAL,

    // Brackets
    TokenType_LEFT_PAREN, TokenType_RIGHT_PAREN, TokenType_LEFT_BRACE, 
    TokenType_RIGHT_BRACE, TokenType_LEFT_BRACKET, TokenType_RIGHT_BRACKET,

    // Comparison
    TokenType_LESS, TokenType_LESS_EQUAL, TokenType_GREATER, TokenType_GREATER_EQUAL,
    TokenType_EQUAL, TokenType_EQUAL_EQUAL, TokenType_BANG, TokenType_BANG_EQUAL,

    // Bitwise Operators
    TokenType_BIT_AND, TokenType_BIT_AND_EQUAL, TokenType_BIT_OR, TokenType_BIT_OR_EQUAL,
    TokenType_CARET_EQUAL, TokenType_BIT_NOT, TokenType_BIT_NOT_EQUAL,

    // Keywords
    TokenType_RETURN, TokenType_BREAK, TokenType_CONTINUE, 
    TokenType_FOR, TokenType_WHILE, TokenType_VAR, TokenType_VOID,
    TokenType_HEAPALLOC, TokenType_NULLPTR, TokenType_TYPE,

    // Miscellaneous
    TokenType_DOT, TokenType_COMMA, 
    TokenType_COLON, TokenType_SEMICOLON, TokenType_IDENTIFIER, 
    TokenType_EOF
} eldr_TokenType;


typedef union {
    float float_value;
    double double_value;
    int8_t byte_value;
    int16_t short_value;
    int32_t int_value;
    int64_t long_value;
#ifdef __SIZEOF__INT128__
    __int128_t very_long_value;
#endif
    const char *string_value;
    const void *pointer_value;
} eldr_TokenValue;


typedef struct Token {
    const eldr_TokenType type;
    const dstring_view *lexeme;
    const eldr_TokenValue value;
} eldr_Token;


#endif