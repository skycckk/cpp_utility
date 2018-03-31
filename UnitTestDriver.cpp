//
// Created by Wei-Chung Huang on 3/23/18.
//

#include "UnitTestDriver.h"
#include "CircularCharQueue.h"
#include "BitManipulation.h"
#include "ThreadExample.h"
#include "MemoryUtility.h"
#include "FileUtility.h"

void my_swap(int *num, int i, int j) {
    num[i] ^= num[j];
    num[j] ^= num[i];
    num[i] ^= num[j];
}
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
    printf("Testing bit manipulation (operation)...passed\n\n");

    printf("Testing bit manipulation (problems)...\n");
    printf("Insertion test: 0x%08x\n", bit_test.insertion(0x13, 0x400, 6, 2));
    printf("Flip Bit to Win(1775): %d\n", bit_test.flipBitToWin(1775));
    num = 5;
    int next_smallest = 0;
    int next_largest = 0;
    bit_test.nextNumber(num, next_smallest, next_largest);
    printf("Next Number of %d: smallest %d and largest %d\n", num, next_smallest, next_largest);

    int num1 = 29;
    int num2 = 15;
    printf("Bits to equal(%d, %d): %d\n", num1, num2, bit_test.bitSwapRequired(num1, num2));
    printf("Swap odd and even of 27: %d\n", bit_test.swapOddEvenBits(27));

    printf("Testing bit manipulation (problems)...passed\n");
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


    int nums[7] =  {1,5,2,3,4,8,7};
    int nums2[7] = {1,5,2,3,4,8,7};
    for (int i = 0; i < 7; i++) printf("%d ", nums[i]);
    printf("\n");
    partitionArray(nums, 7, 5);
    for (int i = 0; i < 7; i++) printf("%d ", nums[i]);
    printf("\n");

    partitionArrayInplace(nums2, 7, 5);
    for (int i = 0; i < 7; i++) printf("%d ", nums2[i]);
    printf("\n");

}

void UnitTestDriver::testMemory() {
    MemoryUtility mem = MemoryUtility();
    char str[] = "memmove can be very useful......";
    printf("before memcpy: %s\n", str);
    mem.my_memcpy(str + 10, str, 11);
    printf(" after memcpy: %s\n", str);
}

void UnitTestDriver::testFile() {
    FileUtility file_utility;
    char file_path[256];
    cin >> file_path;
    file_utility.tail(file_path, 5);
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

void UnitTestDriver::partitionArray(int *arr, int n, int target) {
    if (arr == NULL) return;
    int i = 0;
    int j = n - 1;
    // use O(n) space as dst
    int *tmp = (int *)malloc(n * sizeof(int));
    for (int curr = 0; curr < n; curr++) {
        if (arr[curr] > target) tmp[j--] = arr[curr];
        else if (arr[curr] < target) tmp[i++] = arr[curr];
    }
    // if i > j, means target was not found
    // if i == j, target was found and only one
    // if i < j, has multiple targets
    while (i <= j) tmp[i++] = target;
    memcpy(arr, tmp, n * sizeof(int));

    free(tmp);
}

void UnitTestDriver::partitionArrayInplace(int *arr, int n, int target) {
    if (arr == NULL) return;
    // do a partial partition sort except for the pivot is an arbitrary number.
    // note that if there are multiple targets, then the order is not guaranteed.

    int index = 0;
    int j = n - 1;
    int i = 0;
    while (i < j) {
        if (arr[i] > target) {
            my_swap(arr, i, j);
            j--;
        } else {
            if (target == arr[i]) index = i;
            i++;
        }
    }

    if (arr[i] > target) my_swap(arr, i - 1, index);
    else my_swap(arr, index, i);
}
}