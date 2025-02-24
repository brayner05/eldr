#ifndef ELDR_H
#define ELDR_H

#include "dstring.h"

typedef enum {
    Eldr_COMPILED = 0,
    Eldr_INTERPRETED = (0x01),
    Eldr_RUN_REPL    = (0x02 | Eldr_INTERPRETED)
} Eldr_LanguageMode;


typedef struct {
    DString *message;
    index_t line;
} Eldr_Error;


Eldr_LanguageMode Eldr_GetLanguageMode(void);

// void eldr_report_error(const Eldr_Error *error);

#endif