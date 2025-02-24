#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dstring.h"

#define min(x, y) ((x) < (y) ? (x) : (y))

struct DString {
    char *data;
    size_t length;
};


struct DStringView {
    DString *source;
    index_t start;
    index_t end;
};


static DString *_dstring_allocate(size_t length) {
    DString *dstr = (DString *) calloc(1, sizeof(DString));
    if (dstr == NULL)
        return NULL;

    dstr->length = length;
    dstr->data = (char *) malloc(dstr->length * sizeof(char));
    if (dstr->data == NULL)
        return NULL;

    return dstr;
}


DString *DString_New(const char *str) {
    size_t length = strlen(str);

    DString *dstr = _dstring_allocate(length);
    if (dstr == NULL)
        return NULL;

    strncpy(dstr->data, str, length);

    return dstr;
}


void DString_Delete(DString *self) {
    if (self == NULL)
        return;

    if (self->data != NULL)
        free(self->data);

    free(self);
}


char DString_At(const DString *self, const index_t i) {
    assert(i < self->length);
    return self->data[i];
}


size_t DString_Length(const DString *self) {
    return self->length;
}


DString *DString_Append(const DString *self, const DString *source) {
    size_t new_length = self->length + source->length;
    DString *dstr = _dstring_allocate(new_length);
    if (dstr == NULL)
        return NULL;
    
    strncpy(dstr->data, self->data, self->length);
    strncpy(&dstr->data[self->length], source->data, source->length);

    return dstr;
}


DString *DString_Substring(const DString *self, const index_t start, const index_t end) {
    if (self == NULL || start >= end)
        return NULL;

    size_t length = min(end, self->length) - start;

    DString *dstr = _dstring_allocate(length);
    if (dstr == NULL)
        return NULL;

    strncpy(dstr->data, &self->data[start], length);
    return dstr;
}


const char *DString_ToCharPtr(const DString *dstr) {
    return (const char *) dstr->data;
}


bool DString_Equals(const DString *self, const DString *other) {
    if (self->length != other->length)
        return false;
    
    for (index_t i = 0; i < self->length; ++i) {
        if (DString_At(self, i) != DString_At(other, i))
            return false;
    }

    return true;
}


DStringView *DStringView_New(DString *source, index_t start, index_t end) {
    DStringView *view = calloc(1, sizeof(DStringView));
    if (view == NULL)
        return NULL;

    view->source = source;
    view->start = start;
    view->end = end;
    
    return view;
}


const char *DStringView_ToCharPtr(const DStringView *self) {
    if (self == NULL)
        return NULL;

    const DString *substring = DString_Substring(self->source, self->start, self->end);
    if (substring == NULL)
        return NULL;

    return DString_ToCharPtr(substring);
}