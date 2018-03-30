//
// Created by Wei-Chung Huang on 3/23/18.
//

#ifndef CPP_UTILITY_BITMANIPULATION_H
#define CPP_UTILITY_BITMANIPULATION_H

class BitManipulation {
public:
    // return the longest continuous digit in a given integer
    int longestContinuousDigit(int n);
    int setBit(int num, int i);
    bool getBit(int num, int i);
    int clearBit(int num, int i);
    int updateBit(int num, int i, bool bit);
    int insertion(int m, int n, int j, int i);
    int flipBitToWin(int num);
    void nextNumber(int num, int &smallest, int &largest);
    int bitSwapRequired(int a, int b);
    int swapOddEvenBits(int x);
};

#endif //CPP_UTILITY_BITMANIPULATION_H
