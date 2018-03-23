//
// Created by Wei-Chung Huang on 3/23/18.
//

#include "UnitTestDriver.h"

void *UnitTestDriver::multicoreThreadProcessorQueue(void *lp_param) {
    ThreadParamQueue *p_param = (ThreadParamQueue *)lp_param;
    int id = p_param->id;
    WrapStdQueue *p_my_queue = p_param->p_queue;

    p_my_queue->push(id);
    p_my_queue->push(id + 10);

    p_my_queue->pop();
    p_my_queue->pop();

    return NULL;
}

void UnitTestDriver::testQueue() {
    printf("Testing thread-safe queue...\n");
    const int n_threads = 4;
    pthread_t thread_id[n_threads];
    ThreadParamQueue params[4];
    WrapStdQueue my_queue;
    for (int i = 0; i < n_threads; i++) {
        params[i].id = i;
        params[i].p_queue = &my_queue;
        pthread_create(&thread_id[i], NULL, multicoreThreadProcessorQueue, &params[i]);
    }

    for (int i = 0; i < n_threads; i++) {
        pthread_join(thread_id[i], NULL);
    }
    printf("Testing thread-safe queue...passed\n\n");
}