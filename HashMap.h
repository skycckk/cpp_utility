//
// Created by Wei-Chung Huang on 3/31/18.
//

#ifndef CPP_UTILITY_HASHMAP_H
#define CPP_UTILITY_HASHMAP_H

#include <iostream>

class HashEntry {
public:
    HashEntry(int key, int value) {
        setKeyValue(key, value);
    }

    int getKey() {return key;}
    int getValue() {return value;}
    void setKeyValue(int key, int value) {this->key = key; this->value = value;}

private:
    int key;
    int value;
};

class HashMap {
public:
    HashMap(int size) {
        table_size = size;
        table = new HashEntry*[size];
        for (int i = 0; i < size; i++) table[i] = NULL;
    }

    ~HashMap() {
        for (int i = 0; i < table_size; i++) {
            if (table[i] != NULL) delete table[i];
        }
        delete[] table;
    }

    void put(int key, int value);
    int get(int key);
    void remove(int key);

private:
    int table_size;
    HashEntry **table;

    int hashFunc(int key);
};

#endif //CPP_UTILITY_HASHMAP_H
