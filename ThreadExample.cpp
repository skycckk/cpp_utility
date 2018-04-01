//
// Created by Wei-Chung Huang on 3/25/18.
//

#include "ThreadExample.h"
#include <iostream>
#include <thread>
#include <queue>

#define NUM_THREAD 4

using namespace std;

deque<int> g_deque;
mutex mu;

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

void ThreadExample::producerConsumerTest() {
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();
}

void ThreadExample::producer() {
    int count = 10;
    while (count > 0) {
        lock_guard<mutex> lock(mu);
        g_deque.push_front(count);
        this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}

void ThreadExample::consumer() {
    int data = 0;
    while (data != 1) {
        unique_lock<mutex> lock(mu);
        if (!g_deque.empty()) {
            data = g_deque.back();
            g_deque.pop_back();
            printf("t2 got a value from t1: %d\n", data);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
}