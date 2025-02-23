#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dstring.h"

#define min(x, y) ((x) < (y) ? (x) : (y))

struct dstring {
    char *data;
    size_t length;
};


struct dstring_view {
    const dstring *source;
    index_t start;
    index_t end;
};


static dstring *dstring_create(size_t length) {
    dstring *dstr = (dstring *) calloc(1, sizeof(dstring));
    if (dstr == NULL)
        return NULL;

    dstr->length = length;
    dstr->data = (char *) malloc(dstr->length * sizeof(char));
    if (dstr->data == NULL)
        return NULL;

    return dstr;
}


dstring *dstring_new(const char *str) {
    size_t length = strlen(str);

    dstring *dstr = dstring_create(length);
    if (dstr == NULL)
        return NULL;

    strncpy(dstr->data, str, length);

    return dstr;
}


void dstring_delete(dstring *self) {
    if (self == NULL)
        return;

    if (self->data != NULL)
        free(self->data);

    free(self);
}


char dstring_at(const dstring *self, const index_t i) {
    assert(i < self->length);
    return self->data[i];
}


size_t dstring_length(const dstring *self) {
    return self->length;
}


dstring *dstring_append(const dstring *self, const dstring *source) {
    size_t new_length = self->length + source->length;
    dstring *dstr = dstring_create(new_length);
    if (dstr == NULL)
        return NULL;
    
    strncpy(dstr->data, self->data, self->length);
    strncpy(&dstr->data[self->length], source->data, source->length);

    return dstr;
}


dstring *dstring_substring(const dstring *self, const index_t start, const index_t end) {
    if (self == NULL || start >= end)
        return NULL;

    size_t length = min(end, self->length) - start;

    dstring *dstr = dstring_create(length);
    if (dstr == NULL)
        return NULL;

    strncpy(dstr->data, &self->data[start], length);
    return dstr;
}


const char *dstring_to_char_ptr(const dstring *dstr) {
    return (const char *) dstr->data;
}


bool dstring_equals(const dstring *self, const dstring *other) {
    if (self->length != other->length)
        return false;
    
    for (index_t i = 0; i < self->length; ++i) {
        if (dstring_at(self, i) != dstring_at(other, i))
            return false;
    }

    return true;
}


dstring_view *dstring_view_new(const dstring *source, index_t start, index_t end) {
    dstring_view *view = calloc(1, sizeof(dstring_view));
    if (view == NULL)
        return NULL;

    view->source = source;
    view->start = start;
    view->end = end;
    
    return view;
}


const char *dstring_view_to_char_ptr(const dstring_view *self) {
    if (self == NULL)
        return NULL;

    const dstring *substring = dstring_substring(self->source, self->start, self->end);
    if (substring == NULL)
        return NULL;

    return dstring_to_char_ptr(substring);
}