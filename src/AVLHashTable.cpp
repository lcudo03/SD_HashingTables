#include "AVLHashTable.hpp"
#include <iostream>

AVLHashTable::AVLHashTable(int size) : HashTableBase<AVLTree>(size) {}

void AVLHashTable::insert(int key, int value) {
    int index = hashFunction(key);
    buckets[index].insert(key, value);
}

bool AVLHashTable::remove(int key) {
    int index = hashFunction(key);
    return buckets[index].remove(key);
}

void AVLHashTable::print() const {
    for (int i = 0; i < tableSize; ++i) {
        std::cout << "Bucket " << i << ": [AVL Tree]";
        std::cout << std::endl;
    }
}