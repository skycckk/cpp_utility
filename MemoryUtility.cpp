//
// Created by Wei-Chung Huang on 3/25/18.
//

#include "MemoryUtility.h"

void* MemoryUtility::aligned_malloc(size_t required_bytes, size_t alignment) {
    int offset = alignment - 1 + sizeof(void*);
    void *p1 = malloc(required_bytes + offset);
    if (p1 == NULL) return NULL;
    void *p2 = (void *)(((size_t)p1 + offset) & ~(alignment - 1));
    ((void **)p2)[-1] = p1;

    return p2;
}

void MemoryUtility::aligned_free(void *p2) {
    void *p1 = ((void **)p2)[-1];
    free(p1);
}

int** MemoryUtility::my2DAlloc(int rows, int cols) {
    if (rows < 1 || cols < 1) return NULL;
    int **buffer = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        buffer[i] = (int *)malloc(cols * sizeof(int));
    }

    return buffer;
}

void* MemoryUtility::my_memcpy(void *dst, void *src, size_t n) {
    char *c_src = (char *)src;
    char *c_dst = (char *)dst;
    int int_size = sizeof(int);
    if (n >= int_size) {
        int *i_src = (int *)src;
        int *i_dst = (int *)dst;
        int align_end = n & ~(int_size - 1);
        if ((size_t)i_dst < (size_t)i_src) {
            for (int i = 0; i < n / int_size; i++) i_dst[i] = i_src[i];
            for (int i = align_end; i < n; i++) c_dst[i] = c_src[i];
        } else {
            for (int i = n - 1; i >= align_end; i--) c_dst[i] = c_src[i];
            for (int i = 0; i < n / int_size; i++) i_dst[i] = i_src[i];
        }
    } else {
        if ((size_t)dst < (size_t)src)  for (int i = 0; i < n; i++) c_dst[i] = c_src[i];
        else for (int i = n - 1; i >= 0; i--) c_dst[i] = c_src[i];
    }

    return c_dst;
}