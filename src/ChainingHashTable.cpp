#include "ChainingHashTable.hpp"
#include <iostream>

Pair::Pair(int k, int v) : key(k), value(v) {}

bool Pair::operator==(const Pair& other) const {
    return key == other.key;
}

ChainingHashTable::ChainingHashTable(int size) : HashTableBase<LinkedList<Pair>>(size) {}

void ChainingHashTable::insert(int key, int value) {
    int index = hashFunction(key);
    
    // Sprawdzamy czy klucz już istnieje
    for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
        if (it->key == key) {
            it->value = value; // Aktualizujemy wartość jeśli klucz istnieje
            return;
        }
    }
    
    // Jeśli klucz nie istnieje, dodajemy nową parę
    buckets[index].push_back(Pair(key, value));
}

bool ChainingHashTable::remove(int key) {
    int index = hashFunction(key);
    
    // Tworzymy tymczasowy obiekt Pair do porównania
    Pair temp(key, 0);
    
    // Usuwamy parę z listy
    return buckets[index].remove(temp);
}

void ChainingHashTable::print() const {
    for (int i = 0; i < tableSize; ++i) {
        std::cout << "Bucket " << i << ": ";
        
        // Iterujemy przez wszystkie elementy w kubelku
        for (auto it = buckets[i].begin(); it != buckets[i].end(); ++it) {
            std::cout << "[" << it->key << ":" << it->value << "] ";
        }
        
        std::cout << std::endl;
    }
}