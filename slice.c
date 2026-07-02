#include "slice.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

Slice slice_sub(Slice s, size_t start, size_t end) { 
    if (start > end || end > s.cap) {
        LOG_ERROR("Invalid slice parameters. Start: %zu, End: %zu, Length: %zu\n", start, end, s.len);
        return s;
    }

    void* new_ptr = (char*)s.ptr + start * s.elem_size; 

    if (new_ptr == NULL) {
        PANIC("Failed to create sub-slice. Start: %zu, End: %zu\n", start, end);
    }
    
    Slice new_slice = {new_ptr, end - start, s.cap - start, s.elem_size, false}; 

    return new_slice;
}

// Function to set the value of an element at a specific index in the slice
void slice_set(Slice s, size_t index, void *elem) {
    if (index >= s.len)
    {
        PANIC("Index out of range. Index: %zu, Length: %zu\n", index, s.len);
    }
    
    void* dest = (char*)s.ptr + index * s.elem_size;
    memcpy(dest, elem, s.elem_size);

}

// Function to free the memory allocated for the slice
void slice_free(Slice* s) {
    if (s->is_owner == true)
    {
        free(s->ptr);
    }
    s->ptr = NULL;
    s->cap = 0;
    s->len = 0;
}

// Function to copy elements from the source slice to the destination slice
size_t slice_copy(Slice dst, Slice src) {
    if (dst.elem_size != src.elem_size) 
    {
        LOG_ERROR("Element sizes do not match. Destination size: %zu, Source size: %zu\n", dst.elem_size, src.elem_size);
        return 0;
    }

    size_t min_len = (dst.len < src.len) ? dst.len : src.len;

    memmove(dst.ptr, src.ptr, min_len * dst.elem_size);
    
    return min_len;
    
}    

// Function to create a new slice with the specified element size, length, and capacity
Slice slice_make(size_t elem_size, size_t len, size_t cap) {
    
    Slice empty = {NULL, 0, 0, 0, false};

    if (len > cap || cap == 0) {
        LOG_ERROR("Invalid slice parameters. Length: %zu, Capacity: %zu\n", len, cap);
        return empty;
    }

    void *arr = calloc(cap, elem_size);

    if (arr == NULL)
    {
        LOG_ERROR("Failed to allocate memory for slice.\n");
        return empty;
    }

    Slice s = {arr, len, cap, elem_size, true};

    return s;
    
}

// Function to append an element to the slice, resizing if necessary
Slice slice_append(Slice s, void *elem) {

    if (s.ptr == NULL || elem == NULL)
    {
        PANIC("Pointer or element is NULL.\n");
    }
    
    size_t new_len = s.len + 1;
    size_t new_cap = s.cap;

    if (new_len > s.cap) {

        if (s.cap >= 1024) {

            if (s.cap > SIZE_MAX - (s.cap / 4)) {
                LOG_ERROR("Slice capacity overflow. Current capacity: %zu\n", s.cap);
                return s;
            }

            new_cap = s.cap + (s.cap / 4);
        } else {

            if (s.cap > SIZE_MAX / 2)
            {
                LOG_ERROR("Slice capacity overflow. Current capacity: %zu\n", s.cap);
                return s;
            }

            new_cap = s.cap * 2;
            
        }

        if (new_cap > SIZE_MAX / s.elem_size)
        {
            LOG_ERROR("Slice capacity overflow. Current capacity: %zu\n", s.cap);
            return s;
        }

        void* new_arr = realloc(s.ptr, new_cap * s.elem_size);

        if (new_arr == NULL)
        {
            PANIC("Failed to reallocate memory for slice.\n");

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
        PANIC("Index out of range. Index: %zu, Length: %zu\n", index, s.len);
    }

    return (char*)s.ptr + index * s.elem_size;
}

// Function to set the value of an element at a specific index in the slice
size_t slice_len(Slice s) {return s.len;}

// Function to get the capacity of the slice
size_t slice_cap(Slice s) { return s.cap;}
