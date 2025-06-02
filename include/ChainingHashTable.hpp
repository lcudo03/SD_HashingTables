#ifndef CHAINING_HASH_TABLE_HPP
#define CHAINING_HASH_TABLE_HPP

#include "HashTableBase.hpp"
#include "LinkedList.hpp"

class Pair {
public:
    int key;
    int value;
    Pair(int k, int v);
    bool operator==(const Pair& other) const;
};

class ChainingHashTable : public HashTableBase<LinkedList<Pair>> {
public:
    ChainingHashTable(int size);
    void insert(int key, int value) override;
    bool remove(int key) override;
    void print() const override;
};

#endif // CHAINING_HASH_TABLE_HPP