#include "lexer.h"


static eldr_TokenList tokens = { 0 };

static const dstring *source = NULL;

static index_t current = 0;

static index_t token_start = 0;

static index_t line = 1;


static eldr_TokenType single_char_tokens[] = {
    { '{', TokenType_LEFT_BRACE },
    { '}', TokenType_RIGHT_BRACE },
    { '(', TokenType_LEFT_PAREN },
    { ')', TokenType_RIGHT_PAREN },
    { '[', TokenType_LEFT_BRACKET },
    { ']', TokenType_RIGHT_BRACKET },
};


static bool _is_at_end(void) {
    return current >= dstring_length(source);
}


static char _consume(void) {
    return dstring_at(source, current++);
}


static char _peek(void) {
    if (_is_at_end())
        return '\0';
    return dstring_at(source, current);
}


static char _peek_next(void) {
    if (current + 1 >= dstring_length(source))
        return '\0';
    return dstring_at(source, current + 1);
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