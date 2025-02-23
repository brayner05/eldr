#include <stdio.h>
#include <stdlib.h>
#include "eldr.h"
#include "dstring.h"

static eldr_LanguageMode language_mode = eldr_COMPILED;


eldr_LanguageMode eldr_get_language_mode(void) {
    return language_mode;
}


static dstring *readln(FILE *file) {
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

    dstring *dstr = dstring_new(raw_str);
    free(raw_str);

    return dstr;
}


static void run_repl(void) {
    static dstring *exit_keyword = NULL;
    if (exit_keyword == NULL)
        exit_keyword = dstring_new("quit");

    while (1) {
        printf("eldr: ");
        dstring *line = readln(stdin);

        if (dstring_equals(line, exit_keyword))
            break;
            
        dstring_delete(line);
    }

    dstring_delete(exit_keyword);
}


int main(int argc, char *argv[]) {
    if (argc == 1) {
        language_mode = eldr_RUN_REPL;
        run_repl();
        return EXIT_SUCCESS;
    }

    puts(argv[0]);
}