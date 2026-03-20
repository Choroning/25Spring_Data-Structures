/**
 * @file    ArrayQueue.cpp
 * @brief   Circular array-based queue implementation
 * @author  Cheolwon Park
 * @date    2025-04-14
 */

#include <iostream>
#include <stdexcept>
#include <string>

/**
 * @class ArrayQueue
 * @brief Template-based circular array queue
 *
 * Uses one wasted slot to distinguish between full and empty states.
 * Capacity of n holds at most n-1 elements.
 */
template <typename T>
class ArrayQueue {
private:
    T* data_;
    int front_;    // One position before the first element
    int rear_;     // Position of the last element
    int capacity_; // Array size (max elements = capacity_ - 1)

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        int count = size();
        for (int i = 0; i < count; i++) {
            newData[i + 1] = data_[(front_ + 1 + i) % capacity_];
        }
        delete[] data_;
        data_ = newData;
        front_ = 0;
        rear_ = count;
        capacity_ = newCapacity;
    }

public:
    explicit ArrayQueue(int capacity = 16)
        : front_(0), rear_(0), capacity_(capacity + 1) {
        data_ = new T[capacity_];
    }

    ~ArrayQueue() { delete[] data_; }

    ArrayQueue(const ArrayQueue& other)
        : front_(other.front_), rear_(other.rear_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (int i = 0; i < capacity_; i++)
            data_[i] = other.data_[i];
    }

    ArrayQueue& operator=(const ArrayQueue& other) {
        if (this != &other) {
            delete[] data_;
            front_ = other.front_;
            rear_ = other.rear_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            for (int i = 0; i < capacity_; i++)
                data_[i] = other.data_[i];
        }
        return *this;
    }

    bool empty() const { return front_ == rear_; }

    int size() const {
        return (rear_ - front_ + capacity_) % capacity_;
    }

    /**
     * @brief Enqueue element at the rear - O(1) amortized
     */
    void push(const T& element) {
        if ((rear_ + 1) % capacity_ == front_) {
            // Queue full, resize
            resize(2 * capacity_);
        }
        rear_ = (rear_ + 1) % capacity_;
        data_[rear_] = element;
    }

    /**
     * @brief Dequeue element from the front - O(1)
     * @throws std::underflow_error if queue is empty
     */
    T pop() {
        if (empty())
            throw std::underflow_error("Queue is empty");
        front_ = (front_ + 1) % capacity_;
        return data_[front_];
    }

    /**
     * @brief Return front element without removing - O(1)
     */
    const T& front() const {
        if (empty())
            throw std::underflow_error("Queue is empty");
        return data_[(front_ + 1) % capacity_];
    }

    /**
     * @brief Return rear element without removing - O(1)
     */
    const T& back() const {
        if (empty())
            throw std::underflow_error("Queue is empty");
        return data_[rear_];
    }

    void clear() { front_ = rear_ = 0; }

    void print(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << ": ";
        std::cout << "Queue(front -> rear): [";
        int count = size();
        for (int i = 0; i < count; i++) {
            if (i > 0) std::cout << ", ";
            std::cout << data_[(front_ + 1 + i) % capacity_];
        }
        std::cout << "] (size=" << count << ")" << std::endl;
    }
};

// ============================================================
// Application: Hot Potato Simulation (Josephus Problem variant)
// ============================================================

void hotPotato(int n, int k) {
    ArrayQueue<int> queue;
    for (int i = 1; i <= n; i++)
        queue.push(i);

    std::cout << "  Elimination order: ";
    while (queue.size() > 1) {
        // Pass the potato k-1 times
        for (int i = 0; i < k - 1; i++) {
            queue.push(queue.pop());
        }
        std::cout << queue.pop() << " ";
    }
    std::cout << "\n  Survivor: " << queue.front() << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Circular Array Queue Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // Basic operations
    std::cout << "\n--- Basic Operations ---" << std::endl;
    ArrayQueue<int> q;

    for (int i = 1; i <= 5; i++) {
        q.push(i * 10);
        std::cout << "Enqueued " << i * 10 << std::endl;
    }
    q.print("Queue");

    std::cout << "Front: " << q.front() << std::endl;
    std::cout << "Back:  " << q.back() << std::endl;

    std::cout << "Dequeued: " << q.pop() << std::endl;
    std::cout << "Dequeued: " << q.pop() << std::endl;
    q.print("After 2 dequeues");

    // Test wraparound
    std::cout << "\n--- Circular Wraparound ---" << std::endl;
    ArrayQueue<char> cq(5); // capacity 5
    cq.push('A'); cq.push('B'); cq.push('C');
    cq.print("After A,B,C");

    cq.pop(); cq.pop();
    cq.print("After 2 pops");

    cq.push('D'); cq.push('E'); cq.push('F');
    cq.print("After D,E,F (wraps around)");

    // Dynamic resizing
    std::cout << "\n--- Dynamic Resizing ---" << std::endl;
    ArrayQueue<int> dynQ(4);
    for (int i = 1; i <= 10; i++) {
        dynQ.push(i);
    }
    dynQ.print("After pushing 1-10 into capacity-4 queue");

    // String queue
    std::cout << "\n--- String Queue ---" << std::endl;
    ArrayQueue<std::string> sq;
    sq.push("First");
    sq.push("Second");
    sq.push("Third");
    sq.print("String queue");
    std::cout << "Dequeued: " << sq.pop() << std::endl;
    sq.print("After dequeue");

    // Hot Potato (Josephus Problem)
    std::cout << "\n--- Hot Potato (n=7, k=3) ---" << std::endl;
    hotPotato(7, 3);

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
