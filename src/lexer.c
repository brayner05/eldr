#include <stdlib.h>
#include "lexer.h"
#include "tokens.h"

static Eldr_TokenList _tokens = { 0 };

static const DString *_source = NULL;

static index_t _current = 0;

static index_t _token_start = 0;

static index_t _line = 1;


static bool _is_at_end(void) {
    return _current >= DString_Length(_source);
}


static char _consume(void) {
    return DString_At(_source, _current++);
}


static char _peek(void) {
    if (_is_at_end())
        return '\0';
    return DString_At(_source, _current);
}


static char _peek_next(void) {
    if (_current + 1 >= DString_Length(_source))
        return '\0';
    return DString_At(_source, _current + 1);
}


static bool _match(char ch) {
    return _peek() == ch;
}


static void _scan_next(void) {
    char ch = _consume();
    switch (ch) {
        default: break;
    }
}


static Eldr_LexNode *_add_token(Eldr_Token *token) {
    Eldr_LexNode *node = (Eldr_LexNode *) calloc(1, sizeof(Eldr_LexNode));
    if (node == NULL)
        return NULL;

    node->token = token;
    if (_tokens.head == NULL) {
        _tokens.head = _tokens.tail = node;
        return node;
    }

    _tokens.tail->next = node;
    node->prev = _tokens.tail;
    _tokens.tail = node;

    return node;
}


bool Eldr_Lexer_Init(const DString *source) {
    if (source == NULL)
        return false;

    _source = source;
    return true;
}


Eldr_TokenList Eldr_Lexer_Tokenize(void) {
    while (!_is_at_end()) {
        _scan_next();
        _token_start = _current;
    }

    Eldr_TokenValue eofValue = { .byte_value = (int8_t) TokenType_EOF };
    Eldr_Token *token = Eldr_Token_New(TokenType_EOF, NULL, eofValue);
    // if (token == NULL)

    _add_token(token);
    return _tokens;
}