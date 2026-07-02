#include <stdio.h>
#include "slice.h"

int main() {

    // Example of using a slice of slices (2D slice)
    Slice s = make(int, 0, 2);
    s = append(s, (int){1});
    s = append(s, (int){2});
    Slice s1 = make(int, 0, 2);
    s1 = append(s1, (int){3});
    s1 = append(s1, (int){4});

    Slice matrix = make(Slice, 0, 4); // 2x2 matrix;
    
    matrix = append(matrix, s); // first row
    matrix = append(matrix, s1); // second row

    for (size_t i = 0; i < len(matrix); i++)
    {
        Slice* slice = get(matrix, i);

       printf("Row %zu:\n", i);

       for (size_t j = 0; j < len(*slice); j++)
       {
           int* elem = get(*slice, j);
           printf("Index: %zu, Value: %d\n", j, *elem);
       }
    }
    
    delete(matrix);
    delete(s);
    delete(s1);

    // Example of using slice_copy
    Slice dst = make(int, 2, 2);
    Slice src = make(int, 0, 4);
    src = append(src, (int){1});
    src = append(src, (int){2});
    src = append(src, (int){3});
    src = append(src, (int){4});

    int n = copy(dst, src);
    printf("Copied %d elements\n", n);

    for (size_t i = 0; i < len(dst); i++)
    {
        int* elem = get(dst, i);
        printf("Index: %zu, Value: %d\n", i, *elem);
    }
    
}    