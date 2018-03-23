//
// Created by Wei-Chung Huang on 3/23/18.
//

#include "CircularCharQueue.h"


bool CircularCharQueue::push(char c) {
    if (count() >= buffer_size) return false;
    p_buffer[tail] = c;
    tail = (tail + 1) % buffer_size;
    n_elements++;

    return true;
}

char CircularCharQueue::pop() {
    if (count() < 1) throw 10;

    char element = p_buffer[head];
    head = (head + 1) % buffer_size;
    n_elements--;

    return element;
}

int CircularCharQueue::count() {
    return n_elements;
}

int CircularCharQueue::size() {
    return buffer_size;
}