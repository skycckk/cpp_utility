//
// Created by Wei-Chung Huang on 3/31/18.
//

#include "HashMap.h"

void HashMap::put(int key, int value) {
    int hash_value = hashFunc(key);
    while (table[hash_value] != NULL && table[hash_value]->getKey() != key)
        hash_value = (hash_value + 1) % table_size;

    HashEntry *entry = NULL;
    if (table[hash_value] == NULL) entry = new HashEntry(key, value);
    else entry = table[hash_value];

    entry->setKeyValue(key, value);
    table[hash_value] = entry;
}

int HashMap::get(int key) {
    int hash_value = hashFunc(key);
    while (table[hash_value] != NULL && table[hash_value]->getKey() != key)
        hash_value = (hash_value + 1) % table_size;

    return table[hash_value] == NULL ? -1 : table[hash_value]->getValue();
}

void HashMap::remove(int key) {
    int hash_value = hashFunc(key);
    while (table[hash_value] != NULL && table[hash_value]->getKey() != key)
        hash_value = (hash_value + 1) % table_size;

    if (table[hash_value] != NULL) {
        delete table[hash_value];
        table[hash_value] = NULL;
    }
}

int HashMap::hashFunc(int key) {
    return key % table_size;
}