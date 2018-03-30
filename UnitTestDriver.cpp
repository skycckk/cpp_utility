//
// Created by Wei-Chung Huang on 3/23/18.
//

#include "UnitTestDriver.h"
#include "CircularCharQueue.h"
#include "BitManipulation.h"
#include "ThreadExample.h"
#include "MemoryUtility.h"

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

void UnitTestDriver::testCircularCharQueue() {
    printf("Testing circular char queue...\n");

    CircularCharQueue queue = CircularCharQueue(5);
    // Should print "queue size: 5 - queue count: 0"
    printf("queue size: %d - queue count: %d\n", queue.size(), queue.count());

    queue.push('a');

    // Should print "queue size: 5 - queue count: 1"
    printf("queue size: %d - queue count: %d\n", queue.size(), queue.count());

    queue.pop();

    // Should print "queue size: 5 - queue count: 0"
    printf("queue size: %d - queue count: %d\n", queue.size(), queue.count());

    queue.push('a');
    queue.push('b');
    queue.push('c');
    queue.push('d');
    queue.push('f');
    queue.push('g'); // should not be pushed

    for (int i = 0; i < 3; i++) {
        try {
            printf("pop: %c\n", queue.pop());
        } catch (int e) {
            if (e == 10) printf("Queue is empty\n");
        }
    }
    // pop: a b c
    // remain: d f

    queue.push('p');
    queue.push('q');
    queue.push('r');
    queue.push('t');
    // queue: d f p q r


    for (int i = 0; i < 5; i++) {
        try {
            printf("pop: %c\n", queue.pop());
        } catch (int e) {
            if (e == 10) printf("Queue is empty\n");
        }
    }
    // pop: d f p q r

    printf("Testing circular char queue...passed\n");
}

void UnitTestDriver::testBitManipulation() {
    printf("Testing bit manipulation...\n");
    BitManipulation bit_test = BitManipulation();

    const int n = 5;
    int input[n] = {1123444, 111, 66612345, 443333444, 0};
    for (int i = 0; i < n; i++) {
        int output = bit_test.longestContinuousDigit(input[i]);
        printf("input: %d -> output: %d\n", input[i], output);
    }
    printf("Testing bit manipulation...passed\n\n");

    printf("Testing bit manipulation (operation)...\n");
    int num = 15;
    printf("Get 0x%08x bit0: 0x%08x\n", num, bit_test.getBit(num, 0));
    printf("Get 0x%08x bit1: 0x%08x\n", num, bit_test.getBit(num, 1));
    printf("Get 0x%08x bit2: 0x%08x\n", num, bit_test.getBit(num, 2));
    printf("Get 0x%08x bit3: 0x%08x\n", num, bit_test.getBit(num, 3));
    printf("Get 0x%08x bit4: 0x%08x\n", num, bit_test.getBit(num, 4));

    printf("Set 0x%08x bit4 to 1: 0x%08x\n", num, bit_test.setBit(num, 4));
    printf("Clear 0x%08x bit2 to 0: 0x%08x\n", num, bit_test.clearBit(num, 2));
    printf("Update 0x%08x bit7 to 1: 0x%08x\n", num, bit_test.updateBit(num, 7, 1));
    printf("Update 0x%08x bit0 to 0: 0x%08x\n", num, bit_test.updateBit(num, 0, 0));

    printf("Testing bit manipulation (operation)...passed\n");
}

void UnitTestDriver::testThread() {
    printf("Testing threading...\n");
    ThreadExample thread_ex = ThreadExample();
    thread_ex.threadLocalStorageTestCase();
    printf("Testing threading...passed\n");
}

void UnitTestDriver::testAlgorithm() {
    printf("Testing algorithm (reverse string)...\n");
    char str[128] = "hello, world!!";
    printf("old str: %s\n", str);
    reverse(str);
    printf("new str: %s\n", str);
}

void UnitTestDriver::testMemory() {
    MemoryUtility mem = MemoryUtility();
    char str[] = "memmove can be very useful......";
    printf("before memcpy: %s\n", str);
    mem.my_memcpy(str + 10, str, 11);
    printf(" after memcpy: %s\n", str);
}

void UnitTestDriver::reverse(char *str) {
    if (str == NULL) return;
    int n = 0;
    char *p_str = str;
    while (*p_str != '\0') {
        n++;
        p_str++;
    }

    for (int i = 0; i < n / 2; i++) {
        char tmp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = tmp;
    }
}