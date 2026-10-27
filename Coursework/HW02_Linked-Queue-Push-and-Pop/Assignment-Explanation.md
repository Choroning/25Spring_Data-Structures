# HW2 Assignment Explanation — Linked Queue Push and Pop

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-27

> **Learning Objectives:**
> 1. Describe the direction of the links and the positions of `front` and `rear` in the two representations of a linked queue (type 1 and type 2)
> 2. Explain why push takes $O(1)$ in both representations
> 3. Explain why pop in type 2 takes $O(n)$ to find the new front, and the cost of popping all $n$ elements
> 4. Handle the boundary cases of an empty queue and a one-element queue in push and pop
> 5. Interpret measured execution times in terms of time complexity

---

## Table of Contents

- [1. Homework Layout and How to Run](#1-homework-layout-and-how-to-run)
- [2. Requirements](#2-requirements)
  - [2.1 Two Representations of a Linked Queue](#21-two-representations-of-a-linked-queue)
  - [2.2 Problems and Points](#22-problems-and-points)
- [3. Design and Solution](#3-design-and-solution)
  - [3.1 push](#31-push)
  - [3.2 pop in Type 1](#32-pop-in-type-1)
  - [3.3 pop in Type 2](#33-pop-in-type-2)
  - [3.4 pop on an Empty Queue](#34-pop-on-an-empty-queue)
- [4. Testing](#4-testing)
  - [4.1 Screenshot](#41-screenshot)
  - [4.2 Results with the Test Driver](#42-results-with-the-test-driver)
- [5. Interpreting the Execution Times](#5-interpreting-the-execution-times)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Homework Layout and How to Run

The homework asks for the member functions `push` and `pop` of the linked queue class `Queue<T>` in two representations (type 1 and type 2), and for a screenshot of the completed program measuring the pop time of the two representations. It uses the linked queue of Lecture 6 (Section 4) directly. The handout is in [`Original/Assignment.md`](Original/Assignment.md).

```text
Coursework/HW02_Linked-Queue-Push-and-Pop/
├── Original/
│   ├── Assignment.md       # handout (English)
│   └── Assignment.ko.md    # handout (Korean)
└── Solution/
    ├── Push-and-Pop.cpp    # solution of push and pop
    └── Test-Driver.cpp     # test driver that runs the two functions
```

*Figure 1. Directory layout of HW2*

```bash
cd Coursework/HW02_Linked-Queue-Push-and-Pop/Solution
g++ -std=c++17 -Wall -Wextra -pedantic -o hw2 Test-Driver.cpp
./hw2           # measures with 200,000 elements (takes about 20 seconds)
./hw2 20000     # the number of elements can be changed with an argument
```

> **Note:** `Test-Driver.cpp` is a test driver that compiles and runs the two functions, and its measurement method and number of elements (200,000) follow the screenshot in Section 4.1. The two functions enter the class definition through `#include`. The driver is described in the [HW2 Code Walkthrough](Code-Walkthrough.md).

---

<br>

## 2. Requirements

### 2.1 Two Representations of a Linked Queue

The queue is a chain of nodes of the class `Node<T>` (data field `data`, link field `link`); `front` points to the node that came in first and will be popped next, and `rear` points to the node pushed last. The empty queue is the state in which both `front` and `rear` are `nullptr`. The two representations differ in the direction of the links.

- **Type 1:** Each node points to the node pushed right after it. The links run from `front` toward `rear`, and the link of `rear` is `nullptr`.
- **Type 2:** Each node points to the node pushed right before it. The links run from `rear` toward `front`, and the link of `front` is `nullptr`.

```text
(a) Type 1: the links run from the front toward the rear
 front                                         rear
   |                                             |
   v                                             v
 [ 1 ] ---> [ 2 ] ---> [ 3 ] ---> [ 4 ] ---> [ 5 ] ---> NULL

(b) Type 2: the links run from the rear toward the front
          front                                         rear
            |                                             |
            v                                             v
NULL <--- [ 1 ] <--- [ 2 ] <--- [ 3 ] <--- [ 4 ] <--- [ 5 ]
```

*Figure 2. Type 1 and type 2 queues after pushing 1, 2, 3, 4, 5 in turn*

The two representations are the two ways of assigning the head and tail of a chain to the two ends of a queue in Lecture 6, Section 4.1. Type 1 is method (a), with the head as the front and the tail as the rear, and type 2 is method (b), with the head as the rear and the tail as the front. Lecture 6 concludes that (a) is better because pop in (b) takes $\Theta(n)$, and this homework confirms the difference through an implementation and execution times.

### 2.2 Problems and Points

| Problem | Content | Points |
|:-----|:-----|-----:|
| 1 | `push`: (1-1) push for type 1 (20 points), (1-2) push for type 2 (10 points) | 30 |
| 2 | `pop`: (2-1) pop for type 1 (20 points), (2-2) pop for type 2 (30 points) | 50 |
| 3 | Run the program with the completed code and capture screenshots of the results | 20 |

*Table 1. Problems and points of HW2*

The skeleton code increments `queueSize` at the end of `push`, and at the end of `pop` it decrements `queueSize` and returns the local variable `popData`. The representation depends on whether the member `type`, set at construction, is 1 or not.

---

<br>

## 3. Design and Solution

### 3.1 push

```cpp
if (type == 1) {
    if (rear == nullptr) {
        front = rear = newNode;       // empty queue: the new node is both front and rear
    } else {
        rear->link = newNode;         // the current rear points to the new node
        rear       = newNode;
    }
}
else {
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        newNode->link = rear;         // the new node points to the current rear
        rear          = newNode;
    }
}
```

In both representations, pushing onto an empty queue makes the new node both the front and the rear. Since the constructor of `Node<T>` sets the link to `nullptr`, a one-node queue has the same shape in both representations. Otherwise, type 1 changes the link of the current rear to the new node, and type 2 sets the link of the new node to the current rear. Either way only one link and `rear` change, so push takes $O(1)$. Whether the queue is empty is decided by `rear`, and this test is always correct because the pops of Sections 3.2 and 3.3 reset both `front` and `rear` to `nullptr` when they remove the last element.

### 3.2 pop in Type 1

```cpp
if (front == nullptr) return T();

Node<T>* popNode = front;
popData          = popNode->data;

front = front->link;                  // the next node becomes the new front
if (front == nullptr)
    rear = nullptr;                   // the last element was removed, so clear the rear too

delete popNode;
```

In type 1 the link of the front is the next front, so it suffices to move `front` one node ahead and delete the original front. This takes $O(1)$ and is the same method as `pop` in Lecture 6, Section 4.2. If `rear` were not set to `nullptr` when the last element is removed, `rear` would keep pointing to a freed node, and the next push would decide that the queue is not empty and write into the link of the freed node.

### 3.3 pop in Type 2

```cpp
if (front == nullptr) return T();

popData = front->data;

if (front == rear) {                  // only one element
    delete front;
    front = rear = nullptr;
} else {
    Node<T>* prev = rear;
    while (prev->link != front)       // find, starting at the rear, the node whose link is the front
        prev = prev->link;

    delete front;
    front      = prev;                // that node becomes the new front
    front->link = nullptr;            // the new front ends the chain
}
```

In type 2 the links point toward the front, so there is no way to go from the front to the next front (the node pushed right after the front). That node is the one whose link points to the current front, so the code finds it by starting at `rear` and following the links. With $k$ elements $(k \ge 2)$, `prev` starts at the rear and stops at the second node from the front, so the loop runs $k - 2$ times and one pop takes $\Theta(k)$. After finding the new front, the code deletes the original front and sets the link of the new front to `nullptr` so that it does not point to the freed node.

Handling the one-element case separately is also necessary. Then `front` and `rear` are the same node and its link is `nullptr`, so running the loop as is would make `prev` become `nullptr` and then read `prev->link`, dereferencing a null pointer. The solution avoids this case by deleting the node and clearing both pointers when `front == rear`.

### 3.4 pop on an Empty Queue

In both representations, pop on an empty queue returns `T()` before it reaches `queueSize--`, so the element count never becomes negative and the state of the queue does not change.

> **Caution:** `T()` is 0 for `int`, so the caller cannot distinguish the return value for an empty queue from an actual element 0. `pop` in Lecture 6, Section 4.2 throws a `std::underflow_error` exception on an empty queue. Since the return value alone cannot signal an empty queue, the caller must check the element count before calling pop, and the test driver also pops only while `size()` is greater than 0.

---

<br>

## 4. Testing

### 4.1 Screenshot

The program pushes 200,000 elements into a type 1 queue and a type 2 queue, then measures and prints the time to pop all of them. The upper part of the screenshot is the code that sets the element count `N` and pushes into the type 1 queue `q1`, and the lower part is the execution result.

![Figure 3. Run that measures the pop time of type 1 and type 2 with 200,000 elements](../../images/HW02_Pop-Time.png)

*Figure 3. Run that measures the pop time of type 1 and type 2 with 200,000 elements*

The pop time is 1ms for type 1 and 16,664ms for type 2, a difference of more than a factor of 10,000. The example screenshot in the handout (type 1 2ms, type 2 313ms) shows the same tendency. Section 5 interprets where the difference comes from.

### 4.2 Results with the Test Driver

`Test-Driver.cpp` first pushes 0-4 into both representations and prints the order in which they are popped, then measures the pop time with 200,000 elements. While measuring, it also checks that the $i$-th pop returns $i$ and prints the position if the first-in, first-out order breaks. Compiled with Apple clang 21 without optimization options and run on an Apple M2 Pro, it gives the following result.

```text
type1 pop order : 0 1 2 3 4
type2 pop order : 0 1 2 3 4
type1 pop time : 2ms
type2 pop time : 21651ms
```

Both representations return the elements in the order they were pushed, and the order does not break in 200,000 pops either. The difference in time is on the same scale as in Figure 3. Other cases give the following results.

| Case | Result |
|:-----|:-----|
| pop on an empty queue | Both representations return 0 and the element count stays 0 |
| push 1, 2, pop, push 3, pop, pop, push 4, 5, pop | Both representations return 1, 2, 3, 4 in turn and the element count becomes 1 |
| AddressSanitizer and UndefinedBehaviorSanitizer (2,000 elements) | No errors |
| macOS `leaks --atExit` (3,000 elements) | 0 bytes leaked |

*Table 2. Results with the test driver*

---

<br>

## 5. Interpreting the Execution Times

In type 1 one pop takes $O(1)$, so removing all $n$ elements takes $O(n)$. In type 2 one pop on $k$ elements runs the loop $k - 2$ times, so removing all $n$ elements from a full queue takes the following number of iterations.

$$
\sum_{k=2}^{n} (k - 2) = \frac{(n-1)(n-2)}{2} \approx \frac{n^2}{2}
$$

For $n = 200{,}000$ this is 19,999,700,001 iterations, about $2.0 \times 10^{10}$. Dividing the 16,664ms of Figure 3 by this count gives about 0.83ns per iteration. Each iteration must read the address of the next node with `prev = prev->link` before the next comparison can be made, so the iterations cannot overlap. Measuring with different element counts confirms that the time of type 2 grows with the square of the count.

| Elements $n$ | Type 1 | Type 2 | Loop iterations of type 2, $(n-1)(n-2)/2$ |
|-----:|-----:|-----:|-----:|
| 25,000 | 0ms | 353ms | 312,462,501 |
| 50,000 | 0ms | 1,365ms | 1,249,925,001 |
| 100,000 | 1ms | 5,466ms | 4,999,850,001 |
| 200,000 | 2ms | 21,651ms | 19,999,700,001 |

*Table 3. Pop time by number of elements (test driver, same environment as Table 2)*

Each time the element count doubles, the time of type 2 grows by 3.87, 4.00, and 3.96 times, about four times each, while type 1 stays near 0 at millisecond resolution. Even for the same queue operation, the direction of the links alone changes the cost of pop from $O(1)$ to $\Theta(n)$, which becomes the difference between $O(n)$ and $O(n^2)$ in a program that repeats the operation $n$ times. A linked queue is therefore implemented as type 1, with the links running from the front toward the rear, as Lecture 6 concludes.

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| Type 1 | The links run from the front toward the rear; push sets the link of the rear to the new node and pop moves `front` to the next node, both in $O(1)$. |
| Type 2 | The links run from the rear toward the front; push makes the new node point to the rear in $O(1)$, but pop must find the new front starting at the rear, in $\Theta(n)$. |
| Returning to an empty queue | Popping the last element must set both `front` and `rear` to `nullptr` so that the next push correctly sees an empty queue. |
| Boundary cases of type 2 | With one element the node is deleted without the loop; otherwise the link of the new front is set to `nullptr` so that it does not point to the freed node. |
| pop on an empty queue | It returns `T()` without changing the element count, but the return value alone cannot be distinguished from an actual element. |
| Execution time | Popping all $n$ elements takes $O(n)$ in type 1 and $O(n^2)$ in type 2, with $(n-1)(n-2)/2$ iterations, which appeared as 1ms versus 16,664ms for 200,000 elements. |

---

<br>

## Self-Check Questions

1. **Iteration count:** When a type 2 queue holds 1, 2, 3, 4, 5, how many times does the while loop run in one pop, and which node does `prev` point to when the loop ends?

   <details>
   <summary>Answer</summary>

   `prev` starts at node 5, the rear, and moves to 4, 3, and 2, and it stops because the link of node 2 is node 1, the front. The loop runs $k - 2 = 3$ times, and node 2, which `prev` points to, becomes the new front.

   </details>

2. **Clearing the rear:** If `if (front == nullptr) rear = nullptr;` is removed from pop in type 1, what happens when a one-element queue is popped and then pushed again?

   <details>
   <summary>Answer</summary>

   After the pop, `front` is `nullptr` but `rear` points to a freed node. The next push sees that `rear` is not `nullptr`, treats the queue as non-empty, and writes the new node into the link of the freed node (use after free). Since `front` is still `nullptr`, the new node can never be popped.

   </details>

3. **One-element type 2 queue:** If pop in type 2 runs only the `else` part without the `front == rear` branch, what happens with one element?

   <details>
   <summary>Answer</summary>

   `prev` starts at `rear`, the same node as the front. Its link is `nullptr`, which differs from `front`, so `prev` moves to `nullptr`, and the next condition check reads `prev->link`, dereferencing a null pointer.

   </details>

4. **Link of the new front:** What goes wrong if `front->link = nullptr;` is removed from pop in type 2?

   <details>
   <summary>Answer</summary>

   The link of the new front keeps pointing to the node just freed. The loop of the next pop only looks for the node whose link is the front and never reads the link of the front, so the problem does not show at once, but code that follows the links until `nullptr` (for example, the destructor of the test driver) reads the freed node and frees it again.

   </details>

5. **Predicting the time:** In the same environment as Figure 3, about how long should the pop time of type 2 be with 400,000 elements?

   <details>
   <summary>Answer</summary>

   The iteration count $(n-1)(n-2)/2$ grows with the square of $n$, so doubling the element count makes the time about four times longer. About four times 16,664ms, around 66,000ms, or a little over a minute, is expected. Type 1 grows linearly with the element count, so it stays around 2ms.

   </details>
