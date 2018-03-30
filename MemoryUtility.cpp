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
    char *c_src = NULL;
    char *c_dst = NULL;
    if (n >= 4) {
        int *i_src = (int *)src;
        int *i_dst = (int *)dst;
        if ((size_t)i_dst < (size_t)i_src) {
            int i = 0;
            for (; i < n / 4; i++) i_dst[i] = i_src[i];
            int rem = n - i * 4;
            c_src = (char *)(i_src + i);
            c_dst = (char *)(i_dst + i);
            for (int i = 0; i < rem; i++) c_dst[i] = c_src[i];
        } else {
            c_src = (char *)src;
            c_dst = (char *)dst;
            int end = n & ~3;
            for (int i = n - 1; i >= end; i--) c_dst[i] = c_src[i];
            for (int i = end / 4 - 1; i >= 0; i--) i_dst[i] = i_src[i];
        }
    }

    return c_dst;
}