/**
 * @file    Lab_MaxHeap.cpp
 * @brief   Array-based max heap with insert, deleteMax, and heapify (initialization)
 * @author  Cheolwon Park
 * @date    2025-06-02
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

/**
 * @class MaxHeap
 * @brief Array-based max heap implementation
 *
 * A max heap is a complete binary tree where every parent >= its children.
 * Uses 1-based indexing: heap[1] is the root.
 * - Parent of i: i/2
 * - Left child of i: 2*i
 * - Right child of i: 2*i + 1
 */
template <typename T>
class MaxHeap {
private:
    std::vector<T> heap_; // 1-based indexing (heap_[0] unused)
    int heapSize_;

    /**
     * @brief Bubble up element at position i to restore heap property - O(log n)
     */
    void bubbleUp(int i) {
        T element = heap_[i];
        while (i > 1 && heap_[i / 2] < element) {
            heap_[i] = heap_[i / 2]; // Move parent down
            i /= 2;
        }
        heap_[i] = element;
    }

    /**
     * @brief Trickle down element at position i to restore heap property - O(log n)
     */
    void trickleDown(int i) {
        T element = heap_[i];
        int child = 2 * i; // Left child

        while (child <= heapSize_) {
            // Pick the larger child
            if (child < heapSize_ && heap_[child] < heap_[child + 1]) {
                child++;
            }

            // If element >= larger child, we found the right spot
            if (element >= heap_[child]) break;

            // Move child up
            heap_[i] = heap_[child];
            i = child;
            child *= 2;
        }

        heap_[i] = element;
    }

public:
    /**
     * @brief Construct an empty max heap with given initial capacity
     */
    explicit MaxHeap(int capacity = 16)
        : heap_(capacity + 1), heapSize_(0) {}

    /**
     * @brief Insert an element into the max heap - O(log n)
     * @param element The element to insert
     */
    void insert(const T& element) {
        // Resize if necessary
        if (heapSize_ + 1 >= static_cast<int>(heap_.size())) {
            heap_.resize(heap_.size() * 2);
        }

        heap_[++heapSize_] = element;
        bubbleUp(heapSize_);
    }

    /**
     * @brief Remove and return the maximum element - O(log n)
     * @return The maximum element
     * @throws std::underflow_error if heap is empty
     */
    T deleteMax() {
        if (heapSize_ == 0)
            throw std::underflow_error("Heap is empty");

        T maxElement = heap_[1];
        heap_[1] = heap_[heapSize_--];
        trickleDown(1);
        return maxElement;
    }

    /**
     * @brief Return the maximum element without removing - O(1)
     */
    const T& top() const {
        if (heapSize_ == 0)
            throw std::underflow_error("Heap is empty");
        return heap_[1];
    }

    /**
     * @brief Initialize max heap from an array using bottom-up approach - O(n)
     * @param arr The array of elements
     * @param n Number of elements
     */
    void heapify(const T* arr, int n) {
        // Copy elements to heap (1-based)
        heap_.resize(n + 1);
        heapSize_ = n;
        for (int i = 0; i < n; i++) {
            heap_[i + 1] = arr[i];
        }

        // Bottom-up: start from the last internal node
        for (int i = heapSize_ / 2; i >= 1; i--) {
            trickleDown(i);
        }
    }

    bool empty() const { return heapSize_ == 0; }
    int size() const { return heapSize_; }

    /**
     * @brief Display the heap as an array and as a tree structure
     */
    void display() const {
        std::cout << "Heap array: [";
        for (int i = 1; i <= heapSize_; i++) {
            if (i > 1) std::cout << ", ";
            std::cout << heap_[i];
        }
        std::cout << "] (size=" << heapSize_ << ")" << std::endl;
    }

    /**
     * @brief Verify the max heap property
     * @return true if valid max heap
     */
    bool isValid() const {
        for (int i = 1; i <= heapSize_; i++) {
            int left = 2 * i;
            int right = 2 * i + 1;
            if (left <= heapSize_ && heap_[i] < heap_[left]) return false;
            if (right <= heapSize_ && heap_[i] < heap_[right]) return false;
        }
        return true;
    }
};

// ============================================================
// Application: Heap Sort
// ============================================================

/**
 * @brief Sort an array in ascending order using heap sort - O(n log n)
 */
template <typename T>
void heapSort(T arr[], int n) {
    MaxHeap<T> heap;
    heap.heapify(arr, n);

    // Extract max elements in reverse order
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = heap.deleteMax();
    }
}

// ============================================================
// Main: Demonstrate max heap operations
// ============================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Max Heap Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // Basic insert operations
    std::cout << "\n--- Insert Operations ---" << std::endl;
    MaxHeap<int> heap;

    int values[] = {9, 8, 7, 6, 7, 2, 6, 5, 1};
    for (int v : values) {
        heap.insert(v);
        std::cout << "Inserted " << v << " -> ";
        heap.display();
    }

    std::cout << "\nMax element: " << heap.top() << std::endl;
    std::cout << "Heap valid: " << (heap.isValid() ? "YES" : "NO") << std::endl;

    // Insert 20 (should bubble up to root)
    std::cout << "\n--- Insert 20 (larger than root) ---" << std::endl;
    heap.insert(20);
    heap.display();
    std::cout << "New max: " << heap.top() << std::endl;

    // Delete max operations
    std::cout << "\n--- DeleteMax Operations ---" << std::endl;
    while (!heap.empty()) {
        int maxVal = heap.deleteMax();
        std::cout << "Deleted max: " << maxVal << " -> ";
        heap.display();
    }

    // Heapify (bottom-up initialization)
    std::cout << "\n--- Heapify (O(n) initialization) ---" << std::endl;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int n = 11;

    std::cout << "Input array: [";
    for (int i = 0; i < n; i++) {
        if (i > 0) std::cout << ", ";
        std::cout << arr[i];
    }
    std::cout << "]" << std::endl;

    MaxHeap<int> heap2;
    heap2.heapify(arr, n);
    std::cout << "After heapify: ";
    heap2.display();
    std::cout << "Heap valid: " << (heap2.isValid() ? "YES" : "NO") << std::endl;

    // Heap sort
    std::cout << "\n--- Heap Sort ---" << std::endl;
    int sortArr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    int sortN = 9;

    std::cout << "Before sort: [";
    for (int i = 0; i < sortN; i++) {
        if (i > 0) std::cout << ", ";
        std::cout << sortArr[i];
    }
    std::cout << "]" << std::endl;

    heapSort(sortArr, sortN);

    std::cout << "After sort:  [";
    for (int i = 0; i < sortN; i++) {
        if (i > 0) std::cout << ", ";
        std::cout << sortArr[i];
    }
    std::cout << "]" << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
