#ifndef ELDR_LEXER_H
#define ELDR_LEXER_H

#include <stdbool.h>
#include "tokens.h"

typedef struct eldr_LexNode {
    const eldr_Token token;
    struct eldr_LexNode *next;
    struct eldr_LexNode *prev;
} eldr_LexNode;


typedef struct {
    eldr_LexNode *head;
    eldr_LexNode *tail;
} eldr_TokenList;




#endif