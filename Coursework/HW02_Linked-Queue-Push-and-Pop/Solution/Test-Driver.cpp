/**
 * @file    Test-Driver.cpp
 * @brief   Test driver for push and pop of the type 1 and type 2 linked queues (HW2)
 * @author  Cheolwon Park
 * @date    2026-10-19
 * @note    Written with Claude Code for this archive, only to compile and run
 *          the submitted functions. It is not part of the submitted homework;
 *          the full program used for the submission was not kept. The timing
 *          experiment follows the screenshot of the submission (N = 200,000).
 *
 * Build and run from this folder (an optional argument replaces N):
 *     g++ -std=c++17 -Wall -Wextra -pedantic -o hw2 Test-Driver.cpp
 *     ./hw2
 *     ./hw2 20000
 */

#include <chrono>
#include <cstdlib>
#include <iostream>

/**
 * @class Node
 * @brief Node with a data field and a link field
 */
template <class T>
class Node {
public:
    explicit Node(const T& data) : data(data), link(nullptr) {}

    T data;
    Node<T>* link;
};

/**
 * @class Queue
 * @brief Linked queue in one of two representations
 *
 * Type 1: front -> ... -> rear -> nullptr (each node points toward the rear).
 * Type 2: rear -> ... -> front -> nullptr (each node points toward the front).
 */
template <class T>
class Queue {
public:
    explicit Queue(int type) : type(type), front(nullptr), rear(nullptr), queueSize(0) {}

    /** @brief Delete the remaining nodes by following the links from where they start */
    ~Queue() {
        Node<T>* cur = (type == 1) ? front : rear;
        while (cur != nullptr) {
            Node<T>* next = cur->link;
            delete cur;
            cur = next;
        }
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    // The submitted functions, included unchanged
#include "Push-and-Pop.cpp"

    int size() const { return queueSize; }

private:
    int type;           // 1 or 2
    Node<T>* front;     // node that pop removes
    Node<T>* rear;      // node that push added last
    int queueSize;      // number of elements
};

/** @brief Push 0, 1, ..., count - 1, then print the elements in the order pop returns them */
static void showPopOrder(int type, int count) {
    Queue<int> q(type);
    for (int i = 0; i < count; ++i)
        q.push(i);

    std::cout << "type" << type << " pop order :";
    while (q.size() > 0)
        std::cout << ' ' << q.pop();
    std::cout << '\n';
}

/** @brief Push n elements, then return the time in milliseconds to pop all of them */
static long long popTime(int type, int n) {
    Queue<int> q(type);
    for (int i = 0; i < n; ++i)
        q.push(i);

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) {
        if (q.pop() != i) {     // FIFO check: the i-th pop must return i
            std::cout << "type" << type << " pop order is wrong at " << i << '\n';
            break;
        }
    }
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main(int argc, char* argv[]) {
    int n = 200'000;            // number of elements in the timing experiment
    if (argc > 1)
        n = std::atoi(argv[1]);

    showPopOrder(1, 5);
    showPopOrder(2, 5);

    std::cout << "type1 pop time : " << popTime(1, n) << "ms\n";
    std::cout << "type2 pop time : " << popTime(2, n) << "ms\n";
    return 0;
}
