//
// Created by Wei-Chung Huang on 3/25/18.
//

#ifndef CPP_UTILITY_THREADEXAMPLE_H
#define CPP_UTILITY_THREADEXAMPLE_H


class ThreadExample {

    struct ThreadParam {
        int id;
        ThreadParam() {
            id = -1;
        }
    };

    static void producer();
    static void consumer();

public:
    void threadLocalStorageTestCase();
    static void *multicoreProcessor(void *lp_param);

    void producerConsumerTest();
};

#endif //CPP_UTILITY_THREADEXAMPLE_H
