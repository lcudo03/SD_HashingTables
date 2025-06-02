#ifndef OPEN_ADDRESSING_HASH_TABLE_HPP
#define OPEN_ADDRESSING_HASH_TABLE_HPP

#include "HashTableBase.hpp"
#include "Array.hpp"

struct Slot {
    int key;
    int value;
    bool occupied;
    bool deleted;

    Slot();
};

class OpenAddressingHashTable : public HashTableBase<Array<Slot>> {
public:
    OpenAddressingHashTable(int size);
    void insert(int key, int value) override;
    bool remove(int key) override;
    void print() const override;
};

#endif // OPEN_ADDRESSING_HASH_TABLE_HPP