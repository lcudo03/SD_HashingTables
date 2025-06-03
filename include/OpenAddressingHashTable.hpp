#ifndef OPEN_ADDRESSING_HASH_TABLE_HPP
#define OPEN_ADDRESSING_HASH_TABLE_HPP

#include "HashTableBase.hpp"
#include "Array.hpp"

// Struktura przechowująca pojedynczy slot w tablicy mieszającej
struct Slot {
    int key;        // Przechowywany klucz
    int value;      // Przechowywana wartość
    bool occupied;  // Czy slot jest zajęty
    bool deleted;   // Czy slot został oznaczony jako usunięty

    Slot() : key(0), value(0), occupied(false), deleted(false) {}
};

// Klasa implementująca adresowanie otwarte z liniowym sondowaniem
class OpenAddressingHashTable : public HashTableBase<Array<Slot>> {
public:
    // Konstruktor inicjalizujący tablicę
    OpenAddressingHashTable(int size);
    
    // Wstawia parę klucz-wartość do tablicy
    void insert(int key, int value) override;
    
    // Usuwa element o podanym kluczu
    bool remove(int key) override;
    
    // Wyświetla zawartość tablicy
    void print() const override;
};

#endif // OPEN_ADDRESSING_HASH_TABLE_HPP