//
// Created by Wei-Chung Huang on 3/23/18.
//

#include "BitManipulation.h"

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