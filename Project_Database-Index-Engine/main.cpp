/**
 * @file    main.cpp
 * @brief   B+ tree index engine demo with benchmarks
 * @author  Cheolwon Park
 * @date    2025-06-16
 */

#include "BPlusTree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>

/**
 * @brief Measure elapsed time for a given operation
 */
class Timer {
    std::chrono::high_resolution_clock::time_point start_;
public:
    Timer() : start_(std::chrono::high_resolution_clock::now()) {}
    double elapsedMs() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - start_).count();
    }
};

void demonstrateBasicOperations() {
    std::cout << "========================================" << std::endl;
    std::cout << "  B+ Tree Basic Operations (Order 4)" << std::endl;
    std::cout << "========================================" << std::endl;

    BPlusTree<4> tree;

    // Insert operations
    std::cout << "\n--- Sequential Insert ---" << std::endl;
    int keys[] = {10, 20, 5, 15, 25, 30, 35, 40, 3, 7, 12, 18, 22, 28};
    for (int k : keys) {
        tree.insert(k, k * 100);
        std::cout << "Inserted key=" << k << ", value=" << k * 100 << std::endl;
    }

    std::cout << "\nTree structure:" << std::endl;
    tree.display();
    std::cout << "Size: " << tree.size() << std::endl;

    // Search operations
    std::cout << "\n--- Search Operations ---" << std::endl;
    int searchKeys[] = {15, 25, 7, 42};
    for (int k : searchKeys) {
        int* result = tree.search(k);
        if (result) {
            std::cout << "search(" << k << ") = " << *result << std::endl;
        } else {
            std::cout << "search(" << k << ") = NOT FOUND" << std::endl;
        }
    }

    // Range query
    std::cout << "\n--- Range Query [10, 30] ---" << std::endl;
    auto range = tree.rangeQuery(10, 30);
    std::cout << "Results: ";
    for (const auto& p : range) {
        std::cout << "(" << p.first << "," << p.second << ") ";
    }
    std::cout << std::endl;

    // Delete operations
    std::cout << "\n--- Delete Operations ---" << std::endl;
    int delKeys[] = {15, 30, 5};
    for (int k : delKeys) {
        bool removed = tree.remove(k);
        std::cout << "remove(" << k << ") = " << (removed ? "SUCCESS" : "NOT FOUND") << std::endl;
    }

    std::cout << "\nTree after deletions:" << std::endl;
    tree.display();
    std::cout << "Size: " << tree.size() << std::endl;
}

void runBenchmarks() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  B+ Tree Benchmarks" << std::endl;
    std::cout << "========================================" << std::endl;

    const std::vector<int> sizes = {1000, 10000, 100000};

    for (int n : sizes) {
        std::cout << "\n--- N = " << n << " ---" << std::endl;

        // Generate random keys
        std::vector<int> keys(n);
        std::mt19937 rng(42);
        for (int i = 0; i < n; i++) keys[i] = i;
        std::shuffle(keys.begin(), keys.end(), rng);

        BPlusTree<4> tree;

        // Benchmark insert
        {
            Timer t;
            for (int i = 0; i < n; i++) {
                tree.insert(keys[i], keys[i] * 10);
            }
            std::cout << "Insert " << n << " elements: " << t.elapsedMs() << " ms" << std::endl;
        }

        // Benchmark search (all keys)
        {
            Timer t;
            int found = 0;
            for (int i = 0; i < n; i++) {
                if (tree.search(keys[i])) found++;
            }
            std::cout << "Search " << n << " elements: " << t.elapsedMs() << " ms"
                      << " (found " << found << ")" << std::endl;
        }

        // Benchmark range query
        {
            int low = n / 4, high = 3 * n / 4;
            Timer t;
            auto results = tree.rangeQuery(low, high);
            std::cout << "Range query [" << low << "," << high << "]: "
                      << t.elapsedMs() << " ms"
                      << " (" << results.size() << " results)" << std::endl;
        }

        // Benchmark delete (half the keys)
        {
            Timer t;
            int deleted = 0;
            for (int i = 0; i < n / 2; i++) {
                if (tree.remove(keys[i])) deleted++;
            }
            std::cout << "Delete " << n / 2 << " elements: " << t.elapsedMs() << " ms"
                      << " (deleted " << deleted << ")" << std::endl;
        }
    }
}

int main() {
    demonstrateBasicOperations();
    runBenchmarks();

    std::cout << "\n========================================" << std::endl;
    std::cout << "   All Demos Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
