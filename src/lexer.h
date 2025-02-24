#ifndef ELDR_LEXER_H
#define ELDR_LEXER_H

#include <stdbool.h>
#include "tokens.h"

typedef struct Eldr_LexNode {
    Eldr_Token *token;
    struct Eldr_LexNode *next;
    struct Eldr_LexNode *prev;
} Eldr_LexNode;


typedef struct {
    Eldr_LexNode *head;
    Eldr_LexNode *tail;
} Eldr_TokenList;


bool Eldr_Lexer_Init(const DString *source);

Eldr_TokenList Eldr_Lexer_Tokenize(void);

#endif