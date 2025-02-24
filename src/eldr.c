#include <stdio.h>
#include <stdlib.h>
#include "eldr.h"
#include "dstring.h"

static Eldr_LanguageMode language_mode = Eldr_COMPILED;


Eldr_LanguageMode Eldr_GetLanguageMode(void) {
    return language_mode;
}


static DString *_readln(FILE *file) {
    static const size_t chunk_size = 0x100;
    size_t capacity = chunk_size + 1;
    size_t length = 0;

    char *raw_str = (char *) calloc(capacity, sizeof(char));
    if (raw_str == NULL)
        return NULL;

    int next;
    while ((next = fgetc(file)) != EOF && next != '\n') {
        if (length == capacity - 1) {
            capacity += chunk_size;
            raw_str = (char *) realloc(raw_str, capacity);
        }
        raw_str[length++] = next;
    }

    DString *dstr = DString_New(raw_str);
    free(raw_str);

    return dstr;
}


static void _run_repl(void) {
    static DString *exit_keyword = NULL;
    if (exit_keyword == NULL)
        exit_keyword = DString_New("quit");

    while (1) {
        printf("eldr: ");
        DString *line = _readln(stdin);

        if (DString_Equals(line, exit_keyword))
            break;
            
        DString_Delete(line);
    }

    DString_Delete(exit_keyword);
}


int main(int argc, char *argv[]) {
    if (argc == 1) {
        language_mode = Eldr_RUN_REPL;
        _run_repl();
        return EXIT_SUCCESS;
    }

    puts(argv[0]);
}