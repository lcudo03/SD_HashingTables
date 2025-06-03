#include "AVLHashTable.hpp"
#include <iostream>

// Konstruktor - inicjalizuje tablicę mieszającą o podanym rozmiarze
AVLHashTable::AVLHashTable(int size) : HashTableBase<AVLTree>(size) {}

// Wstawia parę klucz-wartość do tablicy
void AVLHashTable::insert(int key, int value) {
    int index = hashFunction(key);    // Oblicza indeks kubełka
    buckets[index].insert(key, value); // Wstawia do drzewa AVL w kubełku
}

// Usuwa element o podanym kluczu z tablicy
bool AVLHashTable::remove(int key) {
    int index = hashFunction(key);    // Oblicza indeks kubełka
    return buckets[index].remove(key); // Usuwa z drzewa AVL w kubełku
}

// Wyświetla zawartość tablicy (uproszczona wersja)
void AVLHashTable::print() const {
    for (int i = 0; i < tableSize; ++i) {  // Dla każdego kubełka
        std::cout << "Bucket " << i << ": [AVL Tree]"; // Informacja o typie
        std::cout << std::endl;
    }
}