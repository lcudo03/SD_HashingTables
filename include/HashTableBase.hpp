#ifndef HASH_TABLE_BASE_HPP
#define HASH_TABLE_BASE_HPP

// Szablon klasy bazowej dla tablic mieszających
template <typename BucketType>
class HashTableBase {
protected:
    int tableSize;       // Rozmiar tablicy mieszającej
    BucketType* buckets; // Wskaźnik na tablicę kubełków

    // Wirtualna funkcja haszująca
    virtual int hashFunction(int key) const;

public:
    // Konstruktor przyjmujący rozmiar tablicy
    HashTableBase(int size);
    
    // Wirtualny destruktor
    virtual ~HashTableBase();

    // Czysto wirtualne metody interfejsu:
    virtual void insert(int key, int value) = 0;  // Wstawianie elementu
    virtual bool remove(int key) = 0;             // Usuwanie elementu
    virtual void print() const = 0;               // Wyświetlanie zawartości
};

// Implementacja funkcji haszującej (modulo z rozmiarem tablicy)
template <typename BucketType>
int HashTableBase<BucketType>::hashFunction(int key) const {
    return key % tableSize;
}

// Implementacja konstruktora (alokacja pamięci dla kubełków)
template <typename BucketType>
HashTableBase<BucketType>::HashTableBase(int size) : tableSize(size) {
    buckets = new BucketType[tableSize];
}

// Implementacja destruktora (zwolnienie pamięci)
template <typename BucketType>
HashTableBase<BucketType>::~HashTableBase() {
    delete[] buckets;
}

#endif // HASH_TABLE_BASE_HPP