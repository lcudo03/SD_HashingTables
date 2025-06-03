#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "ChainingHashTable.hpp"
#include "OpenAddressingHashTable.hpp"
#include "AVLHashTable.hpp"

const int DEFAULT_TABLE_SIZE = 100; // Stały rozmiar tablicy

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInputBuffer();
            return value;
        }
        clearInputBuffer();
        std::cout << "Niepoprawna wartosc. Sprobuj ponownie.\n";
    }
}

template <typename HashTable>
void hashTableOperations() {
    HashTable table(DEFAULT_TABLE_SIZE); // Używamy stałego rozmiaru
    
    while (true) {
        std::cout << "\n===== MENU OPERACJI =====\n";
        std::cout << "1. Wczytaj z pliku\n";
        std::cout << "2. Dodaj element\n";
        std::cout << "3. Usun element\n";
        std::cout << "4. Wyswietl zawartosc\n";
        std::cout << "5. Powrot do menu glownego\n";
        std::cout << "Wybierz opcje: ";

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1: {
                std::cout << "Podaj nazwe pliku: ";
                std::string filename;
                std::getline(std::cin, filename);

                std::ifstream file(filename);
                if (!file) {
                    std::cout << "Nie mozna otworzyc pliku!\n";
                    break;
                }

                // Tworzymy nową tabelę zamiast czyścić starą
                table = HashTable(DEFAULT_TABLE_SIZE);

                int key, value;
                while (file >> key >> value) {
                    table.insert(key, value);
                }
                std::cout << "Dane wczytane z pliku.\n";
                break;
            }
            case 2: {
                int key = getIntInput("Podaj klucz: ");
                int value = getIntInput("Podaj wartosc: ");
                table.insert(key, value);
                std::cout << "Element dodany.\n";
                break;
            }
            case 3: {
                int key = getIntInput("Podaj klucz do usuniecia: ");
                if (table.remove(key)) {
                    std::cout << "Element usuniety.\n";
                } else {
                    std::cout << "Element nie znaleziony.\n";
                }
                break;
            }
            case 4:
                table.print();
                break;
            case 5:
                return;
            default:
                std::cout << "Niepoprawny wybor. Sprobuj ponownie.\n";
        }
    }
}

void mainMenu() {
    while (true) {
        std::cout << "\n===== MENU GLOWNE =====\n";
        std::cout << "1. Adresowanie lancuchowe\n";
        std::cout << "2. Adresowanie otwarte\n";
        std::cout << "3. Drzewa AVL\n";
        std::cout << "0. Wyjscie\n";
        std::cout << "Wybierz opcje: ";

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1:
                hashTableOperations<ChainingHashTable>();
                break;
            case 2:
                hashTableOperations<OpenAddressingHashTable>();
                break;
            case 3:
                hashTableOperations<AVLHashTable>();
                break;
            case 0:
                return;
            default:
                std::cout << "Niepoprawny wybor. Sprobuj ponownie.\n";
        }
    }
}

int main() {
    mainMenu();
    return 0;
}