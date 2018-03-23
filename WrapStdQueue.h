//
// Created by Wei-Chung Huang on 3/23/18.
//

#ifndef CPP_UTILITY_WRAPSTDQUEUE_H
#define CPP_UTILITY_WRAPSTDQUEUE_H

#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class WrapStdQueue {
private:
    std::queue<int> my_queue;
    mutex mtx;
    condition_variable cv;

public:
    WrapStdQueue() {
    }

    ~WrapStdQueue() {
    }

    void push(int v);
    int pop();
};

#endif //CPP_UTILITY_WRAPSTDQUEUE_H
