//
// Created by Wei-Chung Huang on 3/23/18.
//

#ifndef CPP_UTILITY_UNITTESTDRIVER_H
#define CPP_UTILITY_UNITTESTDRIVER_H

#include <iostream>
#include "WrapStdQueue.h"

class UnitTestDriver {
private:
    void reverse(char *str);
    struct ThreadParamQueue {
        int id;
        WrapStdQueue *p_queue;
        ThreadParamQueue() {
            id = 0;
            p_queue = NULL;
        };
    };
    static void *multicoreThreadProcessorQueue(void *lp_param);
public:
    void testQueue();
    void testCircularCharQueue();
    void testBitManipulation();
    void testThread();
    void testAlgorithm();
    void testMemory();
    void testFile();
};

#endif //CPP_UTILITY_UNITTESTDRIVER_H
