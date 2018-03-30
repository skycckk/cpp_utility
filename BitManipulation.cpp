//
// Created by Wei-Chung Huang on 3/23/18.
//

#include "BitManipulation.h"
#include <iostream>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

int BitManipulation::longestContinuousDigit(int n) {

    int res = 0;
    int max_len = 0;
    int prev_digit = -1;
    int count = 0;
    while (n > 0) {
        int digit = n % 10;
        count++;
        if (digit != prev_digit) {
            if (count >= max_len) {
                max_len = count;
                res = prev_digit;
            }
            count = 0;
        }
        prev_digit = digit;
        n = n / 10;
    }

    if (count >= max_len) res = prev_digit;
    if (res == -1) res = n % 10;

    return res;
}

int BitManipulation::setBit(int num, int i) {
    return num | (1 << i);
}

bool BitManipulation::getBit(int num, int i) {
    return ((1 << i) & num) != 0;
}

int BitManipulation::clearBit(int num, int i) {
    return num & ~(1 << i);
}
int BitManipulation::updateBit(int num, int i, bool bit) {
    int v = bit ? 1 : 0;
    return clearBit(num, i) | (v << i);
}

int BitManipulation::insertion(int m, int n, int j, int i) {
    // given integer m and n, insert m into n starts from bit j and ends at bit i
    // assume j and i are all valid
    int mask = ((1 << (j + 1)) - 1) & ~((1 << i) - 1);
    return (n | mask) & ((m << i) | ~mask);
}

int BitManipulation::flipBitToWin(int num) {
    // Flip exactly one bit from 0 to 1, and find the longest sequence of 1's
    int run_len1 = 0;
    int run_len2 = 0;
    int res = 1;
    while (num != 0) {
        int bit = (num & 1) != 0 ? 1 : 0;
        if (bit == 0) {
            run_len1 = run_len2;
            run_len2 = 0;
        } else {
            run_len2++;
        }
        res = MAX(res, run_len1 + run_len2 + 1);
        num = (unsigned  int)num >> 1;
    }

    return res;
}

void BitManipulation::nextNumber(int num, int &smallest, int &largest) {
    int n = num;
    int zero_idx = -1;
    int one_idx = -1;
    int idx = 0;
    smallest = num;
    largest = num;
    while (n != 0) {
        bool is_one = (n & 1);
        if (is_one == true) {
            one_idx = idx;
            break;
        }
        idx++;
        n = (unsigned int)n >> 1;
    }

    n = num;
    for (int i = idx + 1; i < sizeof(num) * 8; i++) {
        bool is_one = n & (1 << i);
        if (!is_one) {
            zero_idx = i;
            break;
        }
    }

    int n_ones = 0;
    n = num;
    for (int i = 0; i < zero_idx; i++) {
        bool is_one = n & (1 << i);
        if (is_one) n_ones++;
    }

    if (zero_idx >= 0 && one_idx >= 0) {
        largest = num | (1 << zero_idx);
        largest = largest & (~0 << zero_idx);
        largest = largest | ((1 << (n_ones - 1)) - 1);
    } else {
        printf("IMPOSSIBLE for largest\n");
    }

    n = num;
    idx = 0;
    while (n != 0) {
        bool is_one = (n & 1);
        if (is_one == false) {
            zero_idx = idx;
            break;
        }
        idx++;
        n = (unsigned int)n >> 1;
    }
    n = num;
    for (int i = idx + 1; i < sizeof(num) * 8; i++) {
        bool is_one = n & (1 << i);
        if (is_one) {
            one_idx = i;
            break;
        }
    }

    n_ones = 0;
    n = num;
    for (int i = 0; i < zero_idx; i++) {
        bool is_one = n & (1 << i);
        if (is_one) n_ones++;
    }

    if (zero_idx >= 0 && one_idx >= 0) {
        smallest = num & ~(1 << one_idx);
        smallest = smallest & (~0 << one_idx);
        smallest = smallest | ((1 << (n_ones + 1)) - 1) << (one_idx - n_ones - 1);
    } else {
        printf("IMPOSSIBLE for smallest\n");
    }
}

int BitManipulation::bitSwapRequired(int a, int b) {
    unsigned int c = a ^ b;
    int n_flips = 0;
    while (c != 0) {
        n_flips++;
        c = c & (c - 1);
    }
    return n_flips;
}

int BitManipulation::swapOddEvenBits(int x) {
    return (((unsigned int)x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
}