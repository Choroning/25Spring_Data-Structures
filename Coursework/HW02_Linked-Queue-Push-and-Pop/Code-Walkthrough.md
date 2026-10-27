# HW2 Code Walkthrough — Linked Queue Push and Pop

[Repository Guide](../../README.md) | [English](Code-Walkthrough.md) | [한국어](Code-Walkthrough.ko.md)

> **Last Updated:** 2026-10-27

> **Learning Objectives:**
> 1. Explain the pointers that each branch of `push` and `pop` changes in the two representations
> 2. Explain how `Queue<T>` in the test driver frees the remaining nodes of both representations
> 3. Explain how the driver checks the first-in, first-out order and the pop time
> 4. Trace the execution of push and pop step by step in both representations

---

## Table of Contents

- [1. File Layout](#1-file-layout)
- [2. push](#2-push)
- [3. pop: Type 1](#3-pop-type-1)
- [4. pop: Type 2](#4-pop-type-2)
- [5. Driver Headers and Node](#5-driver-headers-and-node)
- [6. The Queue Class](#6-the-queue-class)
- [7. showPopOrder and popTime](#7-showpoporder-and-poptime)
- [8. main](#8-main)
- [9. Execution Trace](#9-execution-trace)
- [10. Complexity](#10-complexity)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. File Layout

The companion document [HW2 Assignment Explanation](Assignment-Explanation.md) covers the two representations, the design, testing, and the interpretation of the execution times. This document reads the two files in `Solution` from beginning to end. All line numbers refer to the respective file. `Push-and-Pop.cpp` (82 lines) holds the two solution functions, and `Test-Driver.cpp` (111 lines) is a test driver that runs them.

| File | Lines | Part | Kind |
|:-----|:-----|:-----|:-----|
| `Push-and-Pop.cpp` | 1-12 | Doxygen header | File description comment |
| `Push-and-Pop.cpp` | 14-40 | `push` | Solution code |
| `Push-and-Pop.cpp` | 42-82 | `pop` | Solution code |
| `Test-Driver.cpp` | 1-19 | Header comment and `#include` | Test driver |
| `Test-Driver.cpp` | 21-32 | `Node<T>` | Test driver |
| `Test-Driver.cpp` | 34-69 | `Queue<T>` (includes the solution functions at line 60) | Test driver |
| `Test-Driver.cpp` | 71-98 | `showPopOrder`, `popTime` | Test driver |
| `Test-Driver.cpp` | 100-111 | `main` | Test driver |

*Table 1. Layout of the two files*

---

<br>

## 2. push

```cpp
void push(const T& item)
{
    Node<T>* newNode = new Node<T>(item);

    // (1-1) Program an operation push for type1 (20 Points)
    if (type == 1) {
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->link = newNode;
            rear       = newNode;
        }
    }


    // (1-2) Program an operation push for type2 (10 Points)
    else {
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            newNode->link = rear;
            rear          = newNode;
        }
    }

    queueSize++;
}
```

Line 16, which comes from the skeleton code, allocates a new node whose data is `item` and whose link is `nullptr`. Lines 19-26 handle type 1. If the queue is empty (line 20), the new node becomes both the front and the rear (line 21); otherwise the link of the current rear is made to point to the new node (line 23) and the rear moves to the new node (line 24). The link of the new node stays `nullptr` as set by the constructor, so the new rear ends the chain. Lines 30-37 handle type 2. The empty queue is handled the same way; otherwise the link of the new node is made to point to the current rear (line 34) and the rear moves to the new node (line 35). Even with the blank lines 27-28 and a comment between the `if` block and `else`, the syntax is a single `if`-`else` statement. Line 39 is the skeleton code's increment of the element count.

---

<br>

## 3. pop: Type 1

```cpp
T pop()
{
    T popData;

    // (2-1) Program an operation pop for type1 (20 Points)
    if (type == 1) {
        if (front == nullptr) return T();

        Node<T>* popNode = front;
        popData          = popNode->data;

        front = front->link;
        if (front == nullptr)
            rear = nullptr;

        delete popNode;
    }
```

`popData` on line 44 is the return value declared by the skeleton code. Line 48 returns `T()` at once on an empty queue, so it never reaches the decrement of the element count on line 80 and the count does not drop. Lines 50-51 keep the front to delete in `popNode` and copy its data into `popData`. Line 53 moves the front to the next node, and lines 54-55 also set the rear to `nullptr` if the queue has become empty as a result. Line 57 frees the original front. Since the data is copied first and the front is moved before the node is freed, the freed node is never read.

---

<br>

## 4. pop: Type 2

```cpp
    // (2-2) Program an operation pop for type2 (30 Points)
    else {
        if (front == nullptr) return T();

        popData = front->data;

        if (front == rear) {
            delete front;
            front = rear = nullptr;
        } else {
            Node<T>* prev = rear;
            while (prev->link != front)
                prev = prev->link;

            delete front;
            front      = prev;
            front->link = nullptr;
        }
    }

    queueSize--;
    return popData;
}
```

Line 62 handles the empty queue as in type 1, and line 64 copies the data of the front first. Lines 66-68 are the one-element case, which frees the node and clears both pointers. Lines 70-72 start `prev` at the rear and follow the links until they reach the node whose link points to the front. Since the links of type 2 run from the rear toward the front, this loop passes through almost the whole queue and runs $k - 2$ times for $k$ elements. Line 74 frees the original front, line 75 makes `prev` the new front, and line 76 sets the link of the new front to `nullptr`, cutting the connection to the node just freed. Lines 80-81 are the skeleton code's decrement of the element count and return.

---

<br>

## 5. Driver Headers and Node

Lines 1-15 of `Test-Driver.cpp` are the Doxygen header, which states that the file was written for testing and gives the build commands. Lines 17-19 include `<chrono>` for time measurement, `<cstdlib>` for `std::atoi`, which converts the command-line argument to an integer, and `<iostream>` for output.

```cpp
template <class T>
class Node {
public:
    explicit Node(const T& data) : data(data), link(nullptr) {}

    T data;
    Node<T>* link;
};
```

`Node<T>` on lines 25-32 has a data field and a link field, and its constructor sets the link to `nullptr`. The solution's `push` relies on this initial value for the first node pushed onto an empty queue and for the new rear of type 1 to end the chain, so this constructor is a precondition for the two functions to work correctly. Both fields are `public`, so the member functions of `Queue<T>` access them directly.

---

<br>

## 6. The Queue Class

```cpp
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
```

The constructor on line 44 sets the representation and creates an empty queue. The destructor on lines 46-54 frees the nodes left in the queue. The node where the links start is `front` in type 1 and `rear` in type 2, so it starts there and, until it reaches `nullptr`, saves the next node first and frees the current one. With $m$ nodes left this takes $O(m)$. Repeating `pop` in the destructor would take $O(m^2)$ in type 2, so it follows the links directly. Lines 56-57 delete the copy constructor and copy assignment. If copying were allowed, two objects would point to the same nodes and their destructors would each free the same nodes, freeing them twice.

> **[Computer Programming]** The copy constructor and copy assignment operator that the C++ compiler generates copy the members one by one, so a pointer member copies only the address, not the node it points to (a shallow copy). A class that owns dynamically allocated nodes must therefore define these two operations itself or delete them with `= delete`, together with its destructor; this principle is called the rule of three.

Lines 59-60 `#include` the file `Push-and-Pop.cpp` inside the class definition. The preprocessor replaces the line with the contents of the file, so the solution's `push` and `pop` become member functions as they are, and `type`, `front`, `rear`, and `queueSize` inside them refer to the member variables on lines 64-68. `size` on line 62 returns the element count, which the driver uses to avoid popping from an empty queue.

---

<br>

## 7. showPopOrder and popTime

```cpp
static void showPopOrder(int type, int count) {
    Queue<int> q(type);
    for (int i = 0; i < count; ++i)
        q.push(i);

    std::cout << "type" << type << " pop order :";
    while (q.size() > 0)
        std::cout << ' ' << q.pop();
    std::cout << '\n';
}
```

`showPopOrder` on lines 72-81 pushes 0 through `count - 1`, then pops until the queue is empty and prints the elements in the order they come out. If the queue is first-in, first-out, the output is `0 1 2 3 4`, the same as the push order.

```cpp
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
```

`popTime` on lines 84-98 pushes $n$ elements and then times only the $n$ pops. Push takes $O(1)$ in both representations, so it is left out of the measurement. `std::chrono::steady_clock` is a clock that never goes backward even if the system time is adjusted, and the difference between the two time points is converted to milliseconds and returned. Inside the loop, the function compares the $i$-th pop with $i$, and if the order breaks, it prints the position and stops. The cost of one comparison is negligible compared with one pop in type 2.

---

<br>

## 8. main

Line 101 sets the element count for the measurement to 200,000, and lines 102-103 replace it with the command-line argument if one is given. The single quote in `200'000` is the digit separator available since C++14. Lines 105-106 check the pop order of both representations with five elements, and lines 108-109 print the pop time of both representations in the format `type1 pop time : 1ms`. Each queue is a local variable of its function, so its destructor frees the remaining nodes when the function ends.

---

<br>

## 9. Execution Trace

Pushing 1, 2, 3 onto a type 2 queue and popping twice traces as follows. The queue is written from the rear toward the front, following the links.

| Step | Call | Branch executed | Queue after the call (from the rear) | `front` | `rear` |
|:-----|:-----|:-----|:-----|:-----|:-----|
| 1 | `push(1)` | Empty queue (lines 31-32) | `1 -> NULL` | 1 | 1 |
| 2 | `push(2)` | Lines 34-35 | `2 -> 1 -> NULL` | 1 | 2 |
| 3 | `push(3)` | Lines 34-35 | `3 -> 2 -> 1 -> NULL` | 1 | 3 |
| 4 | `pop()` returns 1 | Lines 70-76, 1 iteration (`prev`: 3 to 2) | `3 -> 2 -> NULL` | 2 | 3 |
| 5 | `pop()` returns 2 | Lines 70-76, 0 iterations (`prev`: 3) | `3 -> NULL` | 3 | 3 |

*Table 2. Trace of push and pop on a type 2 queue*

In step 4, `prev` starts at 3; the link of 3 is 2, not the front 1, so `prev` moves once to 2 and stops because the link of 2 is 1. With three elements the loop runs $3 - 2 = 1$ time. The same calls on type 1 run line 21 for the first push and lines 23-24 for the later pushes, and lines 50-57 for pop, with no loop.

---

<br>

## 10. Complexity

With $k$ elements in the queue, the time complexity of each function is as follows.

| Function | Type 1 | Type 2 | Reason |
|:-----|:-----|:-----|:-----|
| `push` | $O(1)$ | $O(1)$ | It changes only one link and `rear` |
| `pop` | $O(1)$ | $\Theta(k)$ | Type 2 moves $k - 2$ times from the rear to find the new front |
| `pop` of all $n$ elements | $O(n)$ | $\Theta(n^2)$ | Type 2 runs $(n-1)(n-2)/2$ loop iterations in total |
| Destructor | $O(k)$ | $O(k)$ | It frees each node once, starting where the links start |

*Table 3. Time complexity of each function in the two representations*

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| File layout | `Push-and-Pop.cpp` holds the two solution functions, and `Test-Driver.cpp` is the test driver that runs them. |
| `push` | On an empty queue the new node becomes both front and rear; otherwise type 1 changes the link of the rear and type 2 the link of the new node, and then `rear` moves. |
| `pop` in type 1 | It copies the data, moves `front` to the next node, frees the original front, and clears `rear` too when the queue becomes empty. |
| `pop` in type 2 | With one element it frees the node at once; otherwise it finds, starting at the rear, the node whose link is the front, makes it the new front, and cuts its link. |
| Constructor of `Node<T>` | It sets the link to `nullptr` so that the solution's `push` does not have to set the link of a new end node separately. |
| Driver | The destructor frees the nodes starting at `front` or `rear` depending on the representation, and `popTime` times only the pops while also checking the first-in, first-out order. |

---

<br>

## Self-Check Questions

1. **Initial value in the constructor:** If the constructor of `Node<T>` did not initialize the link, in which cases of the solution's `push` would problems arise?

   <details>
   <summary>Answer</summary>

   The link of the first node pushed onto an empty queue (in both representations) and of the new node attached at the rear in type 1 would hold garbage. Since the link of the rear in type 1 and the link of the front in type 2 must mark the end of the chain, code that follows the links until `nullptr`, such as the destructor, would read an invalid address. The new node in type 2 is unaffected, because line 34 sets its link.

   </details>

2. **Starting point of the destructor:** What happens in type 2 if the destructor always starts at `front`, regardless of the representation?

   <details>
   <summary>Answer</summary>

   In type 2 the link of `front` is `nullptr`, so the destructor frees only the front node and the loop ends. The other nodes are never freed, and their memory leaks.

   </details>

3. **Measurement range:** Would the results in the table change much if `popTime` also timed the pushes?

   <details>
   <summary>Answer</summary>

   Not much. Push takes $O(1)$ in both representations, so pushing 200,000 elements takes a few milliseconds. The result for type 1 may grow by a few milliseconds, but the result for type 2 stays almost the same, because the $\Theta(n^2)$ pops dominate it.

   </details>

4. **Tracing the loop:** When a type 2 queue holds 1, 2, 3, 4 and is popped four times, how many times does the while loop run in each pop, and does the total match the formula $(n-1)(n-2)/2$?

   <details>
   <summary>Answer</summary>

   It runs 2, 1, and 0 times with 4, 3, and 2 elements, and with one element the `front == rear` branch runs without the loop. The total is 3, and for $n = 4$ the formula gives $(4-1)(4-2)/2 = 3$, so they match.

   </details>
