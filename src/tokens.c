#include <stdlib.h>
#include "tokens.h"

Eldr_Token *eldr_Token_new(const Eldr_TokenType type, const DStringView *lexeme, const Eldr_TokenValue value) {
    Eldr_Token *token = (Eldr_Token *) calloc(1, sizeof(Eldr_Token));
    if (token == NULL)
        return NULL;
    
    token->type = type;
    token->lexeme = lexeme;
    token->value = value; 

    return token;
}