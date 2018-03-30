//
// Created by Wei-Chung Huang on 3/25/18.
//

#ifndef CPP_UTILITY_MEMORYUTILITY_H
#define CPP_UTILITY_MEMORYUTILITY_H

#include <iostream>

class MemoryUtility {
public:
    void* aligned_malloc(size_t required_bytes, size_t alignment);
    void aligned_free(void *ptr);
    int** my2DAlloc(int rows, int cols);
    void* my_memcpy(void *dst, void *src, size_t n);
};

#endif //CPP_UTILITY_MEMORYUTILITY_H
