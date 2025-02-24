#ifndef DSTRING_H
#define DSTRING_H
#include <stddef.h>
#include <stdbool.h>

#define INDEX_MAX (index_t)(-1)

typedef struct DString DString;

typedef struct DStringView DStringView;

typedef size_t index_t;

extern DString *DString_New(const char *str);

extern void DString_Delete(DString *self);

extern char DString_At(const DString *self, const index_t i);

extern DString *DString_Append(const DString *self, const DString *source);

static inline DString *DString_AppendRaw(const DString *self, const char *str){
    return DString_Append(self, DString_New(str));
}

extern size_t DString_Length(const DString *self);

static inline DString *DString_Empty(void) {
    return DString_New("");
}

/**
 * Gets a substring of `self` from `start` (inclusive) to `end` (exclusive).
 * Note A new `DString` is allocated in this function.
 * 
 * @param self the `DString` to operate on
 * @param start the index to start from (inclusive)
 * @param end the index to end at (exclusive)
 * 
 * @returns a substring of `self`
 */
extern DString *DString_Substring(const DString *self, const index_t start, const index_t end);

extern const char *DString_ToCharPtr(const DString *self);

extern bool DString_Equals(const DString *self, const DString *other);


/**
 * Creates a string view of `source` from `start` (inclusive) to `end` (exclusive)
 */
extern DStringView *DStringView_New(DString *source, index_t start, index_t end);

extern const char *DStringView_ToCharPtr(const DStringView *self);

#endif