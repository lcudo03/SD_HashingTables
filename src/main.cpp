#include "ChainingHashTable.hpp"
#include "OpenAddressingHashTable.hpp"
#include "PerformanceTester.hpp"
#include "AVLHashTable.hpp"
#include <vector>
#include <iostream>


int main() {
    try {
        std::vector<int> testSizes = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000};
        int repetitions = 100;

        PerformanceTester::testHashTablePerformance<ChainingHashTable>("Chaining Hash Table", testSizes, repetitions);
        PerformanceTester::testHashTablePerformance<OpenAddressingHashTable>("Open Addressing Hash Table", testSizes, repetitions);
        PerformanceTester::testHashTablePerformance<AVLHashTable>("AVL Hash Table", testSizes, repetitions);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}