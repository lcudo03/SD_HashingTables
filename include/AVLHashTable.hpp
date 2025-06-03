#ifndef AVL_HASH_TABLE_HPP
#define AVL_HASH_TABLE_HPP

#include "HashTableBase.hpp"
#include "AVLTree.hpp"

class AVLHashTable : public HashTableBase<AVLTree> {
public:
    AVLHashTable(int size);
    void insert(int key, int value) override;
    bool remove(int key) override;
    void print() const override;
};

#endif // AVL_HASH_TABLE_HPP