//
// Created by Wei-Chung Huang on 3/23/18.
//

#include "WrapStdQueue.h"

void WrapStdQueue::push(int v) {
    lock_guard<mutex> lock(mtx);
    my_queue.push(v);
    cv.notify_one();
}

int WrapStdQueue::pop() {
    unique_lock<mutex> lock(mtx);
    auto now = chrono::system_clock::now();
    while (my_queue.empty())
        cv.wait_until(lock, now + chrono::seconds(1));

    int val = my_queue.front();
    my_queue.pop();

    return val;
}