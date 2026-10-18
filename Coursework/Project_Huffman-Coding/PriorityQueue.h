/**
 * @file    PriorityQueue.h
 * @brief   Min-heap priority queue for Huffman tree construction
 * @author  Cheolwon Park
 * @date    2025-06-16
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <stdexcept>
#include <functional>

/**
 * @class MinPriorityQueue
 * @brief Array-based min-heap priority queue
 *
 * Supports a custom comparator. Used by Huffman coding to always
 * extract the two nodes with the smallest frequencies.
 *
 * Time complexity:
 * - insert: O(log n)
 * - extractMin: O(log n)
 * - top: O(1)
 */
template <typename T, typename Compare = std::less<T>>
class MinPriorityQueue {
private:
    std::vector<T> heap_;
    Compare comp_;

    void bubbleUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (comp_(heap_[i], heap_[parent])) {
                std::swap(heap_[i], heap_[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }

    void trickleDown(int i) {
        int n = static_cast<int>(heap_.size());
        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && comp_(heap_[left], heap_[smallest]))
                smallest = left;
            if (right < n && comp_(heap_[right], heap_[smallest]))
                smallest = right;

            if (smallest != i) {
                std::swap(heap_[i], heap_[smallest]);
                i = smallest;
            } else {
                break;
            }
        }
    }

public:
    MinPriorityQueue() = default;
    explicit MinPriorityQueue(Compare comp) : comp_(comp) {}

    void insert(const T& element) {
        heap_.push_back(element);
        bubbleUp(static_cast<int>(heap_.size()) - 1);
    }

    T extractMin() {
        if (heap_.empty())
            throw std::underflow_error("Priority queue is empty");
        T minElement = heap_[0];
        heap_[0] = heap_.back();
        heap_.pop_back();
        if (!heap_.empty()) trickleDown(0);
        return minElement;
    }

    const T& top() const {
        if (heap_.empty())
            throw std::underflow_error("Priority queue is empty");
        return heap_[0];
    }

    bool empty() const { return heap_.empty(); }
    int size() const { return static_cast<int>(heap_.size()); }
};

#endif // PRIORITYQUEUE_H
