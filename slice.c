#include "slice.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Function to set the value of an element at a specific index in the slice
void slice_set(Slice s, size_t index, void *elem) {
    if (index >= s.len)
    {
        fprintf(stderr, "Index out of range. Index: %zu, Length: %zu\n", index, s.len);
        abort();
    }
    
    void* dest = (char*)s.ptr + index * s.elem_size;
    memcpy(dest, elem, s.elem_size);

}

// Function to free the memory allocated for the slice
void slice_free(Slice* s) {
    free(s->ptr);
    s->ptr = NULL;
    s->cap = 0;
    s->len = 0;
}

// Function to copy elements from the source slice to the destination slice
size_t slice_copy(Slice dst, Slice src) {
    if (dst.elem_size != src.elem_size) 
    {
        fprintf(stderr, "Error: Element sizes do not match. Destination size: %zu, Source size: %zu\n", dst.elem_size, src.elem_size);
        return 0;
    }

    size_t min_len = (dst.len < src.len) ? dst.len : src.len;

    memmove(dst.ptr, src.ptr, min_len * dst.elem_size);
    
    return min_len;
    
}    

// Function to create a new slice with the specified element size, length, and capacity
Slice slice_make(size_t elem_size, size_t len, size_t cap) {
    
    Slice empty = {NULL, 0, 0, 0};

    if (len > cap || cap == 0) {
        fprintf(stderr, "Error: Invalid slice parameters. Length: %zu, Capacity: %zu\n", len, cap);
        return empty;
    }

    void *arr = calloc(cap, elem_size);

    if (arr == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for slice.\n");
        return empty;
    }

    Slice s = {arr, len, cap, elem_size};

    return s;
    
}

// Function to append an element to the slice, resizing if necessary
Slice slice_append(Slice s, void *elem) {

    if (s.ptr == NULL || elem == NULL)
    {
        fprintf(stderr, "Error: Pointer or element is NULL.\n");
        abort();
    }
    
    size_t new_len = s.len + 1;
    size_t new_cap = s.cap;

    if (new_len > s.cap) {

        if (s.cap >= 1024) {

            if (s.cap > SIZE_MAX - (s.cap / 4)) {
                fprintf(stderr, "Error: Slice capacity overflow. Current capacity: %zu\n", s.cap);
                return s;
            }

            new_cap = s.cap + (s.cap / 4);
        } else {

            if (s.cap > SIZE_MAX / 2)
            {
                fprintf(stderr, "Error: Slice capacity overflow. Current capacity: %zu\n", s.cap);
                return s;
            }

            new_cap = s.cap * 2;
            
        }

        if (new_cap > SIZE_MAX / s.elem_size)
        {
            fprintf(stderr, "Error: Slice capacity overflow. Current capacity: %zu\n", s.cap);
            return s;
        }

        void* new_arr = realloc(s.ptr, new_cap * s.elem_size);

        if (new_arr == NULL)
        {
            fprintf(stderr, "Error: Failed to reallocate memory for slice.\n");
            abort();

        }

        s.ptr = new_arr;
        s.cap = new_cap;

    }

    s.len = new_len;

    void* dest = (char*)s.ptr + (s.len - 1) * s.elem_size;
    memcpy(dest, elem, s.elem_size);

    return s;

}

// Function to get the pointer to the element at a specific index in the slice
void* slice_get(Slice s, size_t index) {

    if (index >= s.len) {
        fprintf(stderr, "Index out of range. Index: %zu, Length: %zu\n", index, s.len);
        abort();
    }

    return (char*)s.ptr + index * s.elem_size;
}

// Function to set the value of an element at a specific index in the slice
size_t slice_len(Slice s) {return s.len;}

// Function to get the capacity of the slice
size_t slice_cap(Slice s) { return s.cap;}
