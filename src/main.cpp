#include "ChainingHashTable.hpp"
#include "OpenAddressingHashTable.hpp"
#include "PerformanceTester.hpp"
#include <vector>
#include <iostream>


int main() {
    try {
        std::vector<int> testSizes = {5000, 8000, 10000};
        int repetitions = 3;

        PerformanceTester::testHashTablePerformance<ChainingHashTable>("Chaining Hash Table", testSizes, repetitions);
        PerformanceTester::testHashTablePerformance<OpenAddressingHashTable>("Open Addressing Hash Table", testSizes, repetitions);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}