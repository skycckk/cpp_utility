//
// Created by Wei-Chung Huang on 3/23/18.
//

#ifndef CPP_UTILITY_CIRCULARCHARQUEUE_H
#define CPP_UTILITY_CIRCULARCHARQUEUE_H

#include <stdlib.h>
#include <iostream>

class CircularCharQueue {
private:
    int buffer_size;
    char *p_buffer;
    int n_elements;
    int head;  // the index for an element to be pop up
    int tail;  // the index for an element to push

public:
    CircularCharQueue (int buffer_size) {
        this->buffer_size = buffer_size;
        p_buffer = (char *)malloc(sizeof(char) * buffer_size);
        tail = 0;
        head = 0;
        n_elements = 0;
    }

    ~CircularCharQueue () {
        free(p_buffer);
    }

    /// Add a char to the back of the queue
    /// @returns Whether push was successful.
    bool push(char c);

    /// Return the char at the front of the queue or throw if empty.
    char pop();

    /// Return the number of elements currently in the queue
    int count();

    /// Return the size of the queue's buffer
    int size();

};

#endif //CPP_UTILITY_CIRCULARCHARQUEUE_H
