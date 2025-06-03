#include "OpenAddressingHashTable.hpp"
#include <iostream>
#include <stdexcept>

// Konstruktor - inicjalizuje tablicę slotów
OpenAddressingHashTable::OpenAddressingHashTable(int size) : HashTableBase<Array<Slot>>(size) {
    for (int i = 0; i < tableSize; ++i) {
        buckets[i].push_back(Slot()); // Dodaje pusty slot do każdego kubełka
    }
}

// Wstawianie elementu do tablicy
void OpenAddressingHashTable::insert(int key, int value) {
    int index = hashFunction(key); // Oblicz początkowy indeks
    int originalIndex = index;     // Zapamiętaj oryginalny indeks
    int firstDeleted = -1;         // Śledzi pierwszy napotkany usunięty slot

    // Przeszukaj tablicę liniowo
    do {
        if (!buckets[index][0].occupied) {
            // Znaleziono wolny slot
            if (firstDeleted != -1) index = firstDeleted; // Użyj pierwszego usuniętego slotu
            buckets[index][0].key = key;
            buckets[index][0].value = value;
            buckets[index][0].occupied = true;
            buckets[index][0].deleted = false;
            return;
        }

        // Aktualizacja istniejącego klucza
        if (buckets[index][0].key == key && !buckets[index][0].deleted) {
            buckets[index][0].value = value;
            return;
        }

        // Zapamiętaj pierwszy usunięty slot
        if (buckets[index][0].deleted && firstDeleted == -1) {
            firstDeleted = index;
        }

        index = (index + 1) % tableSize; // Przejdź do następnego slotu
    } while (index != originalIndex);    // Kontynuuj aż do pełnego obrotu

    // Jeśli znaleziono usunięty slot, użyj go
    if (firstDeleted != -1) {
        buckets[firstDeleted][0].key = key;
        buckets[firstDeleted][0].value = value;
        buckets[firstDeleted][0].occupied = true;
        buckets[firstDeleted][0].deleted = false;
    } else {
        throw std::runtime_error("Hash table is full"); // Tablica pełna
    }
}

// Usuwanie elementu z tablicy
bool OpenAddressingHashTable::remove(int key) {
    int index = hashFunction(key); // Oblicz początkowy indeks
    int originalIndex = index;     // Zapamiętaj oryginalny indeks

    // Przeszukaj tablicę liniowo
    do {
        // Znaleziono element do usunięcia
        if (buckets[index][0].occupied && buckets[index][0].key == key && !buckets[index][0].deleted) {
            buckets[index][0].deleted = true; // Oznacz jako usunięty
            return true;
        }

        // Zakończ jeśli napotkano pusty, nieusunięty slot
        if (!buckets[index][0].occupied && !buckets[index][0].deleted) {
            break;
        }

        index = (index + 1) % tableSize; // Przejdź do następnego slotu
    } while (index != originalIndex);    // Kontynuuj aż do pełnego obrotu

    return false; // Nie znaleziono klucza
}

// Wyświetlanie zawartości tablicy
void OpenAddressingHashTable::print() const {
    for (int i = 0; i < tableSize; ++i) {
        std::cout << "Slot " << i << ": ";
        // Wyświetl tylko zajęte i nieusunięte sloty
        if (buckets[i][0].occupied && !buckets[i][0].deleted) {
            std::cout << "[" << buckets[i][0].key << ":" << buckets[i][0].value << "]";
        } else {
            std::cout << "[]"; // Puste lub usunięte sloty
        }
        std::cout << std::endl;
    }
}