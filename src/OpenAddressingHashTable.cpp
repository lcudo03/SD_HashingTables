#include "OpenAddressingHashTable.hpp"
#include <iostream>
#include <stdexcept>

Slot::Slot() : key(0), value(0), occupied(false), deleted(false) {}

OpenAddressingHashTable::OpenAddressingHashTable(int size) : HashTableBase<Array<Slot>>(size) {
    for (int i = 0; i < tableSize; ++i) {
        buckets[i].push_back(Slot());
    }
}

void OpenAddressingHashTable::insert(int key, int value) {
    int index = hashFunction(key);
    int originalIndex = index;
    int firstDeleted = -1;

    do {
        if (!buckets[index][0].occupied) {
            if (firstDeleted != -1) {
                index = firstDeleted;
            }
            buckets[index][0].key = key;
            buckets[index][0].value = value;
            buckets[index][0].occupied = true;
            buckets[index][0].deleted = false;
            return;
        }

        if (buckets[index][0].key == key && !buckets[index][0].deleted) {
            buckets[index][0].value = value;
            return;
        }

        if (buckets[index][0].deleted && firstDeleted == -1) {
            firstDeleted = index;
        }

        index = (index + 1) % tableSize;
    } while (index != originalIndex);

    if (firstDeleted != -1) {
        buckets[firstDeleted][0].key = key;
        buckets[firstDeleted][0].value = value;
        buckets[firstDeleted][0].occupied = true;
        buckets[firstDeleted][0].deleted = false;
    } else {
        throw std::runtime_error("Hash table is full");
    }
}

bool OpenAddressingHashTable::remove(int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    do {
        if (buckets[index][0].occupied && buckets[index][0].key == key && !buckets[index][0].deleted) {
            buckets[index][0].deleted = true;
            return true;
        }

        if (!buckets[index][0].occupied && !buckets[index][0].deleted) {
            break;
        }

        index = (index + 1) % tableSize;
    } while (index != originalIndex);

    return false;
}

void OpenAddressingHashTable::print() const {
    for (int i = 0; i < tableSize; ++i) {
        std::cout << "Slot " << i << ": ";
        if (buckets[i][0].occupied && !buckets[i][0].deleted) {
            std::cout << "[" << buckets[i][0].key << ":" << buckets[i][0].value << "]";
        } else {
            std::cout << "[]";
        }
        std::cout << std::endl;
    }
}