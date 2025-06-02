#ifndef PERFORMANCE_TESTER_HPP
#define PERFORMANCE_TESTER_HPP

#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <stdexcept>

class RandomGenerator {
private:
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    RandomGenerator(int min, int max) : gen(std::random_device{}()), dist(min, max) {}
    int generate() { return dist(gen); }
};

class PerformanceTester {
public:
    static void generateTestData(int* keys, int* values, int size) {
        RandomGenerator rg(1, size * 10);
        for (int i = 0; i < size; ++i) {
            keys[i] = rg.generate();
            values[i] = rg.generate();
        }
    }
    
    template <typename HashTable>
    static void testHashTablePerformance(const std::string& name, const std::vector<int>& sizes, int repetitions) {
        std::cout << "\nTesting performance of " << name << "\n";
        std::cout << "Size\tAvg Insert Time (ns)\tAvg Remove Time (ns)\n";
        std::cout << "------------------------------------------------\n";

        for (int size : sizes) {
            double totalInsertTime = 0;
            double totalRemoveTime = 0;

            for (int rep = 0; rep < repetitions; ++rep) {
                int* keys = new int[size];
                int* values = new int[size];
                generateTestData(keys, values, size);

                HashTable ht(size);

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < size; ++i) {
                    ht.insert(keys[i], values[i]);
                }
                auto end = std::chrono::high_resolution_clock::now();
                totalInsertTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < size; i += 2) {
                    ht.remove(keys[i]);
                }
                end = std::chrono::high_resolution_clock::now();
                totalRemoveTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                delete[] keys;
                delete[] values;
            }

            double avgInsertTime = totalInsertTime / (size * repetitions);
            double avgRemoveTime = totalRemoveTime / ((size / 2) * repetitions);

            std::cout << size << "\t" << avgInsertTime << "\t\t\t" << avgRemoveTime << "\n";
        }
    }
};

#endif // PERFORMANCE_TESTER_HPP