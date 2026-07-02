#pragma once

#include <stddef.h>

typedef enum {
    false,
    true,
} bool;

typedef struct
{
    void *ptr;
    size_t len;
    size_t cap;
    size_t elem_size;
    bool is_owner;
} Slice;

size_t slice_len(Slice s);
size_t slice_cap(Slice s);
Slice slice_make(size_t elem_size, size_t len, size_t cap);
void* slice_get(Slice s, size_t index);
void slice_free(Slice* s);
void slice_set(Slice s, size_t index, void* elem);
Slice slice_append(Slice s, void *elem);
size_t slice_copy(Slice dst, Slice src);
Slice slice_sub(Slice s, size_t start, size_t end);

#define make(type, len, cap) slice_make(sizeof(type), len, cap) 
#define len(s) slice_len(s)
#define cap(s) slice_cap(s)
#define get(s, index) slice_get(s, index)
#define append(s, elem) slice_append(s, &(elem))
#define delete(s) slice_free(&(s))
#define set(s, index, elem) slice_set(s, index, &(elem))
#define copy(dst, src) slice_copy(dst, src)
#define sub(s, start, end) slice_sub(s, start, end);