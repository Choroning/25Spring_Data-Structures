# Lecture 6 Solutions — Queues

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Table of Contents

- [Exercise 1: Circular Queue Trace](#exercise-1-circular-queue-trace)
- [Exercise 2: Full vs. Empty](#exercise-2-full-vs-empty)
- [Exercise 3: Queue vs. Stack](#exercise-3-queue-vs-stack)
- [Exercise 4: Linked Queue Operations](#exercise-4-linked-queue-operations)
- [Exercise 5: Array Queue Pop Complexity](#exercise-5-array-queue-pop-complexity)

---

<br>

## Exercise 1: Circular Queue Trace

**Problem:** Given a circular queue of capacity 6 (indices 0-5), initially `front = rear = 0`. After the operations: `push(A)`, `push(B)`, `push(C)`, `pop()`, `pop()`, `push(D)`, `push(E)`, `push(F)`, what are the values of front, rear, and the queue contents?

### Solution

**Answer:** `front = 2`, `rear = 0`. After push(A): rear=1, A at [1]. push(B): rear=2, B at [2]. push(C): rear=3, C at [3]. pop(): front=1, removes A. pop(): front=2, removes B. push(D): rear=4, D at [4]. push(E): rear=5, E at [5]. push(F): rear=0, F at [0]. So front=2, rear=0. Elements: C at [3], D at [4], E at [5], F at [0].

```text
  [0]   [1]   [2]   [3]   [4]   [5]
+-----+-----+-----+-----+-----+-----+
|  F  |     |     |  C  |  D  |  E  |
+-----+-----+-----+-----+-----+-----+
   ^           ^
  rear       front
```

*Figure 1. State of the circular queue after all operations*

**Explanation:** The circular queue wraps around using modulo. After `rear` reaches index 5, the next push wraps to index 0. The queue now holds 4 elements, C, D, E, F, and [1] and [2] are empty. One more element can go into [1], but [2], where `front` points, stays unused even when the queue is full, to distinguish full from empty. One more push therefore makes `rear = 1` and fills the queue (`(1 + 1) % 6 == 2 == front`), and the push after that is refused.

---

<br>

## Exercise 2: Full vs. Empty

**Problem:** In a circular queue, both the full and the empty states have `front == rear`. How do we distinguish between them?

### Solution

**Answer:** The standard approach wastes one array slot: the queue is full when `(rear + 1) % capacity == front`, and empty when `front == rear`. An alternative is to maintain a separate count variable.

**Explanation:** By reserving one slot, a queue of capacity $n$ can hold at most $n-1$ elements. When only the positions `front` and `rear` are tracked, the empty condition is `front == rear` and the full condition is `(rear + 1) % capacity == front`. With a count variable (`NumElements`) or a boolean that records whether the last operation was an add (`lastOperationIsAdd`), all $n$ slots can be used (Lecture 6, Section 3.3).

---

<br>

## Exercise 3: Queue vs. Stack

**Problem:** Describe a scenario where a queue is more appropriate than a stack, and vice versa.

### Solution

**Answer:** A queue suits CPU scheduling, because processes should be served in the order they arrive, which requires FIFO fairness. A stack suits undo operations in a text editor, because the most recent action should be undone first, which requires LIFO order.

**Explanation:** Queues preserve the order of arrival, making them ideal for fairness-based processing. Stacks reverse the order, making them ideal for tracking nested or hierarchical operations.

---

<br>

## Exercise 4: Linked Queue Operations

**Problem:** Draw the state of a linked queue after: `enqueue(10)`, `enqueue(20)`, `dequeue()`, `enqueue(30)`, `dequeue()`.

### Solution

**Answer:** Final state: front -> [30] -> nullptr, rear -> [30]. Queue contains only 30.

```text
frontNode ---> [ 30 | nullptr ] <--- rearNode
```

*Figure 2. The linked queue after all operations*

**Explanation:** enqueue(10): front->[10], rear->[10]. enqueue(20): front->[10]->[20], rear->[20]. dequeue(): removes 10, front->[20], rear->[20]. enqueue(30): front->[20]->[30], rear->[30]. dequeue(): removes 20, front->[30], rear->[30].

---

<br>

## Exercise 5: Array Queue Pop Complexity

**Problem:** Why does a simple (non-circular) array-based queue have $O(n)$ pop complexity? How does the circular queue solve this?

### Solution

**Answer:** In a simple array queue with `front` fixed at index 0, popping requires shifting all remaining elements one position to the left, which is $O(n)$. The circular queue solves this by allowing `front` to move forward using `front = (front + 1) % capacity`, making pop $O(1)$ without any shifting.

**Explanation:** The key insight is that we do not need to keep the first element at index 0. By using modular arithmetic, both front and rear can wrap around the array, reusing space freed by dequeue operations.
