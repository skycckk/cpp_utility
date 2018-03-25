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

public:
    void threadLocalStorageTestCase();
    static void *multicoreProcessor(void *lp_param);
};

#endif //CPP_UTILITY_THREADEXAMPLE_H
