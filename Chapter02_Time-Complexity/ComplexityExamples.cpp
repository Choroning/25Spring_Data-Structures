/**
 * @file    ComplexityExamples.cpp
 * @brief   Demonstrates algorithms with O(1), O(log n), O(n), O(n log n), and O(n^2) complexities
 * @author  Cheolwon Park
 * @date    2025-03-17
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <algorithm>

// ============================================================
// O(1) - Constant Time
// ============================================================

/**
 * @brief Accesses an element by index in constant time
 */
int constantAccess(const std::vector<int>& arr, int index) {
    return arr[index];  // Direct memory access: O(1)
}

/**
 * @brief Checks if a number is even (constant time operation)
 */
bool isEven(int n) {
    return (n & 1) == 0;  // Bitwise AND: O(1)
}

// ============================================================
// O(log n) - Logarithmic Time
// ============================================================

/**
 * @brief Binary search on a sorted array
 * @param arr Sorted array
 * @param target Element to find
 * @return Index of target, or -1 if not found
 */
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = static_cast<int>(arr.size()) - 1;
    int comparisons = 0;

    while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            std::cout << "    Found at index " << mid
                      << " in " << comparisons << " comparisons" << std::endl;
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    std::cout << "    Not found after " << comparisons << " comparisons" << std::endl;
    return -1;
}

/**
 * @brief Computes integer logarithm base 2 iteratively
 */
int intLog2(int n) {
    int count = 0;
    while (n > 1) {
        n /= 2;
        count++;
    }
    return count;  // O(log n) iterations
}

// ============================================================
// O(n) - Linear Time
// ============================================================

/**
 * @brief Linear search through an unsorted array
 */
int linearSearch(const std::vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return static_cast<int>(i);
    }
    return -1;
}

/**
 * @brief Computes the sum of all elements in an array
 */
long long linearSum(const std::vector<int>& arr) {
    long long sum = 0;
    for (int x : arr) {
        sum += x;
    }
    return sum;
}

/**
 * @brief Finds the maximum element in an array
 */
int findMax(const std::vector<int>& arr) {
    int maxVal = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

// ============================================================
// O(n log n) - Linearithmic Time
// ============================================================

/**
 * @brief Merge sort implementation
 */
void merge(std::vector<int>& arr, int l, int m, int r) {
    std::vector<int> temp(r - l + 1);
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (int idx = 0; idx < k; idx++) arr[l + idx] = temp[idx];
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ============================================================
// O(n^2) - Quadratic Time
// ============================================================

/**
 * @brief Selection sort: finds minimum and swaps to front
 */
void selectionSort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

/**
 * @brief Checks if any two elements in the array are equal (brute force)
 */
bool hasDuplicateBrute(const std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) return true;
        }
    }
    return false;
}

// ============================================================
// Utility: Timing helper
// ============================================================

template <typename Func>
double timeFunction(Func f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Time Complexity Examples" << std::endl;
    std::cout << "========================================" << std::endl;

    // ----- O(1) Demo -----
    std::cout << "\n--- O(1): Constant Time ---" << std::endl;
    std::vector<int> arr = {10, 20, 30, 40, 50};
    std::cout << "  arr[2] = " << constantAccess(arr, 2) << std::endl;
    std::cout << "  isEven(42) = " << (isEven(42) ? "true" : "false") << std::endl;
    std::cout << "  These operations take the same time regardless of input size." << std::endl;

    // ----- O(log n) Demo -----
    std::cout << "\n--- O(log n): Logarithmic Time ---" << std::endl;
    std::vector<int> sorted = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91, 100, 150, 200};
    std::cout << "  Binary search for 23 in array of size " << sorted.size() << ":" << std::endl;
    binarySearch(sorted, 23);
    std::cout << "  Expected comparisons: ~log2(" << sorted.size() << ") = "
              << std::fixed << std::setprecision(1) << log2(sorted.size()) << std::endl;

    for (int n : {16, 256, 4096, 65536}) {
        std::cout << "  intLog2(" << n << ") = " << intLog2(n)
                  << " (iterations = log2(n))" << std::endl;
    }

    // ----- O(n) Demo -----
    std::cout << "\n--- O(n): Linear Time ---" << std::endl;
    std::vector<int> data(1000);
    for (int i = 0; i < 1000; i++) data[i] = i * 3;
    std::cout << "  Sum of 1000 elements: " << linearSum(data) << std::endl;
    std::cout << "  Max of 1000 elements: " << findMax(data) << std::endl;

    // ----- O(n log n) vs O(n^2) Timing Comparison -----
    std::cout << "\n--- O(n log n) vs O(n^2): Sorting Comparison ---" << std::endl;
    std::cout << std::setw(10) << "n"
              << std::setw(20) << "MergeSort (us)"
              << std::setw(20) << "SelectionSort (us)"
              << std::setw(15) << "Ratio" << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    srand(42);
    for (int n : {500, 1000, 2000, 4000, 8000}) {
        std::vector<int> testData(n);
        for (int i = 0; i < n; i++) testData[i] = rand() % 100000;

        auto copy1 = testData;
        auto copy2 = testData;

        double mergeTime = timeFunction([&]() {
            mergeSort(copy1, 0, n - 1);
        });

        double selectTime = timeFunction([&]() {
            selectionSort(copy2);
        });

        std::cout << std::setw(10) << n
                  << std::setw(20) << std::fixed << std::setprecision(0) << mergeTime
                  << std::setw(20) << selectTime
                  << std::setw(15) << std::setprecision(1) << selectTime / mergeTime << "x"
                  << std::endl;
    }

    // ----- Growth Rate Visualization -----
    std::cout << "\n--- Growth Rate Comparison (operation counts) ---" << std::endl;
    std::cout << std::setw(10) << "n"
              << std::setw(12) << "log n"
              << std::setw(12) << "n"
              << std::setw(12) << "n log n"
              << std::setw(12) << "n^2" << std::endl;
    std::cout << std::string(58, '-') << std::endl;

    for (int n : {10, 100, 1000, 10000, 100000}) {
        std::cout << std::setw(10) << n
                  << std::setw(12) << std::setprecision(1) << log2(n)
                  << std::setw(12) << n
                  << std::setw(12) << static_cast<long long>(n * log2(n))
                  << std::setw(12) << static_cast<long long>(n) * n << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
