#ifndef ELDR_H
#define ELDR_H

typedef enum {
    eldr_COMPILED = 0,
    eldr_INTERPRETED = (0x01),
    eldr_RUN_REPL    = (0x02 | eldr_INTERPRETED)
} eldr_LanguageMode;

eldr_LanguageMode eldr_get_language_mode(void);

#endif