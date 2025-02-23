#ifndef DSTRING_H
#define DSTRING_H
#include <stddef.h>
#include <stdbool.h>

#define INDEX_MAX (index_t)(-1)

typedef struct dstring dstring;

typedef struct dstring_view dstring_view;

typedef size_t index_t;

extern dstring *dstring_new(const char *str);

extern void dstring_delete(dstring *self);

extern char dstring_at(const dstring *self, const index_t i);

extern dstring *dstring_append(const dstring *self, const dstring *source);

static inline dstring *dstring_appends(const dstring *self, const char *str){
    return dstring_append(self, dstring_new(str));
}

extern size_t dstring_length(const dstring *self);

static inline dstring *dstring_empty(void) {
    return dstring_new("");
}

/**
 * Gets a substring of `self` from `start` (inclusive) to `end` (exclusive).
 * Note A new `dstring` is allocated in this function.
 * 
 * @param self the `dstring` to operate on
 * @param start the index to start from (inclusive)
 * @param end the index to end at (exclusive)
 * 
 * @returns a substring of `self`
 */
extern dstring *dstring_substring(const dstring *self, const index_t start, const index_t end);

extern const char *dstring_to_char_ptr(const dstring *self);

extern bool dstring_equals(const dstring *self, const dstring *other);


/**
 * Creates a string view of `source` from `start` (inclusive) to `end` (exclusive)
 */
extern dstring_view *dstring_view_new(const dstring *source, index_t start, index_t end);

extern const char *dstring_view_to_char_ptr(const dstring_view *self);

#endif