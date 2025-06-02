#ifndef HASH_TABLE_BASE_HPP
#define HASH_TABLE_BASE_HPP

template <typename BucketType>
class HashTableBase {
protected:
    int tableSize;
    BucketType* buckets;

    virtual int hashFunction(int key) const;

public:
    HashTableBase(int size);
    virtual ~HashTableBase();

    virtual void insert(int key, int value) = 0;
    virtual bool remove(int key) = 0;
    virtual void print() const = 0;
};

template <typename BucketType>
int HashTableBase<BucketType>::hashFunction(int key) const {
    return key % tableSize;
}

template <typename BucketType>
HashTableBase<BucketType>::HashTableBase(int size) : tableSize(size) {
    buckets = new BucketType[tableSize];
}

template <typename BucketType>
HashTableBase<BucketType>::~HashTableBase() {
    delete[] buckets;
}

#endif // HASH_TABLE_BASE_HPP