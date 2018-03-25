//
// Created by Wei-Chung Huang on 3/25/18.
//

#include "ThreadExample.h"
#include <iostream>

#define NUM_THREAD 4

__thread int g_count = 0;
void* ThreadExample::multicoreProcessor(void *lp_param) {
    ThreadParam *param = (ThreadParam *)lp_param;
    while (g_count++ < 500) {
        printf("(%d)->g_count: %d\n", param->id, g_count);
    }

    return NULL;
}

void ThreadExample::threadLocalStorageTestCase() {
    pthread_t tid[NUM_THREAD];

    ThreadParam param[NUM_THREAD];

    for (int i = 0; i < NUM_THREAD; i++) {
        param[i].id = i;
        pthread_create(&tid[i], NULL, multicoreProcessor, &param[i]);
    }

    for (int i = 0; i < NUM_THREAD; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("Final g_count: %d\n", g_count);
}