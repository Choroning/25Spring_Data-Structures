/**
 * @file    Lab_PerformanceMeasurement.cpp
 * @brief   Demonstrates timing, profiling, and performance measurement techniques
 * @author  Cheolwon Park
 * @date    2025-03-10
 */

#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <functional>

/**
 * @brief Measures the execution time of a given function
 * @param func The function to measure
 * @param label A descriptive label for the output
 * @param iterations Number of times to repeat (for averaging)
 * @return Average execution time in microseconds
 */
double measureTime(std::function<void()> func, const std::string& label, int iterations = 10) {
    // Warm-up run
    func();

    auto totalStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        func();
    }
    auto totalEnd = std::chrono::high_resolution_clock::now();

    double avgMicroseconds =
        std::chrono::duration_cast<std::chrono::microseconds>(totalEnd - totalStart).count()
        / static_cast<double>(iterations);

    std::cout << std::setw(35) << std::left << label
              << " | Avg: " << std::fixed << std::setprecision(2)
              << avgMicroseconds << " us" << std::endl;

    return avgMicroseconds;
}

// ============================================================
// Example algorithms with different time complexities
// ============================================================

/**
 * @brief O(1) - Constant time: Access array element by index
 */
int constantTimeAccess(const std::vector<int>& arr, int index) {
    return arr[index];
}

/**
 * @brief O(n) - Linear time: Find maximum element
 */
int linearMax(const std::vector<int>& arr) {
    int maxVal = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

/**
 * @brief O(n^2) - Quadratic time: Bubble sort
 */
void bubbleSort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

/**
 * @brief O(n log n) - Linearithmic time: Merge sort helper
 */
void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)   temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int idx = 0; idx < k; idx++)
        arr[left + idx] = temp[idx];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/**
 * @brief O(log n) - Logarithmic time: Binary search
 */
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = static_cast<int>(arr.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

/**
 * @brief Generates a random vector of given size
 */
std::vector<int> generateRandomVector(int size) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = rand() % (size * 10);
    }
    return vec;
}

/**
 * @brief Step count demonstration
 */
void stepCountDemo() {
    std::cout << "\n=== Step Count Demonstration ===" << std::endl;
    std::cout << "Matrix Addition (n x n):" << std::endl;

    for (int n : {10, 50, 100, 200}) {
        long long steps = 0;
        std::vector<std::vector<int>> A(n, std::vector<int>(n, 1));
        std::vector<std::vector<int>> B(n, std::vector<int>(n, 2));
        std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

        for (int i = 0; i < n; i++) {        // n+1 comparisons
            steps++;
            for (int j = 0; j < n; j++) {    // n*(n+1) comparisons
                steps++;
                C[i][j] = A[i][j] + B[i][j]; // n*n assignments
                steps++;
            }
            steps++; // inner loop final comparison
        }
        steps++; // outer loop final comparison

        std::cout << "  n = " << std::setw(4) << n
                  << " | Steps = " << std::setw(10) << steps
                  << " | 2n^2 + 2n + 1 = " << 2*n*n + 2*n + 1
                  << std::endl;
    }
}

/**
 * @brief Space complexity demonstration
 */
void spaceComplexityDemo() {
    std::cout << "\n=== Space Complexity Demonstration ===" << std::endl;

    // Iterative sum: O(1) extra space
    std::cout << "Iterative sum: O(1) extra space" << std::endl;
    auto iterativeSum = [](const std::vector<int>& arr) -> long long {
        long long total = 0;  // Only 1 extra variable
        for (size_t i = 0; i < arr.size(); i++)
            total += arr[i];
        return total;
    };

    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "  Sum = " << iterativeSum(data) << std::endl;
    std::cout << "  Extra variables: total (1 long long), i (1 size_t)" << std::endl;
    std::cout << "  Space: O(1) regardless of input size" << std::endl;
}

int main() {
    srand(42); // Fixed seed for reproducibility

    std::cout << "========================================" << std::endl;
    std::cout << "   Performance Measurement Demo" << std::endl;
    std::cout << "========================================" << std::endl;

    // --------------------------------------------------
    // 1. Compare algorithms at different input sizes
    // --------------------------------------------------
    std::cout << "\n=== Timing Different Complexities ===" << std::endl;

    for (int size : {1000, 5000, 10000}) {
        std::cout << "\n--- Input size: " << size << " ---" << std::endl;

        auto data = generateRandomVector(size);
        auto sorted_data = data;
        std::sort(sorted_data.begin(), sorted_data.end());

        // O(1) access
        measureTime([&]() {
            volatile int x = constantTimeAccess(data, size / 2);
            (void)x;
        }, "O(1) Array access");

        // O(log n) binary search
        measureTime([&]() {
            volatile int x = binarySearch(sorted_data, sorted_data[size / 2]);
            (void)x;
        }, "O(log n) Binary search");

        // O(n) linear search
        measureTime([&]() {
            volatile int x = linearMax(data);
            (void)x;
        }, "O(n) Find maximum");

        // O(n log n) merge sort
        if (size <= 10000) {
            measureTime([&]() {
                auto copy = data;
                mergeSort(copy, 0, static_cast<int>(copy.size()) - 1);
            }, "O(n log n) Merge sort");
        }

        // O(n^2) bubble sort (only for small sizes)
        if (size <= 5000) {
            measureTime([&]() {
                auto copy = data;
                bubbleSort(copy);
            }, "O(n^2) Bubble sort", 3);
        }
    }

    // --------------------------------------------------
    // 2. Step count demonstration
    // --------------------------------------------------
    stepCountDemo();

    // --------------------------------------------------
    // 3. Space complexity demonstration
    // --------------------------------------------------
    spaceComplexityDemo();

    // --------------------------------------------------
    // 4. Using clock() for CPU time
    // --------------------------------------------------
    std::cout << "\n=== CPU Time using clock() ===" << std::endl;
    {
        auto data = generateRandomVector(50000);
        clock_t start = clock();
        auto copy = data;
        std::sort(copy.begin(), copy.end());
        clock_t end = clock();
        double cpuTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        std::cout << "  Sorting 50000 elements: " << std::fixed
                  << std::setprecision(6) << cpuTime << " seconds (CPU time)" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
