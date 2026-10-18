# Chapter 06 — Quiz

> **Last Updated:** 2026-03-21

---

## Q1. Circular Queue Trace

**Question:** Given a circular queue of capacity 6 (indices 0-5), initially `front = rear = 0`. After the operations: `push(A)`, `push(B)`, `push(C)`, `pop()`, `pop()`, `push(D)`, `push(E)`, `push(F)`, what are the values of front, rear, and the queue contents?

**Answer:** `front = 2`, `rear = 0`. Queue contents at indices [3]=D, [4]=E, [5]=F, [0]= (empty slot). Active elements: C, D, E, F. Wait — let me retrace. After push(A): rear=1, A at [1]. push(B): rear=2, B at [2]. push(C): rear=3, C at [3]. pop(): front=1, removes A. pop(): front=2, removes B. push(D): rear=4, D at [4]. push(E): rear=5, E at [5]. push(F): rear=0, F at [0]. So front=2, rear=0. Elements: C at [3], D at [4], E at [5], F at [0].

**Explanation:** The circular queue wraps around using modulo. After `rear` reaches index 5, the next push wraps to index 0. The queue now holds 4 elements: C, D, E, F. One slot (index [1] or [2]) remains unused to distinguish full from empty.

---

## Q2. Full vs. Empty

**Question:** In a circular queue, both "full" and "empty" states have `front == rear`. How do we distinguish between them?

**Answer:** The standard approach wastes one array slot: the queue is full when `(rear + 1) % capacity == front`, and empty when `front == rear`. An alternative is to maintain a separate count variable.

**Explanation:** By reserving one slot, a queue of capacity $n$ can hold at most $n-1$ elements. When only the positions `front` and `rear` are tracked, the empty condition is `front == rear` and the full condition is `(rear + 1) % capacity == front`.

---

## Q3. Queue vs. Stack

**Question:** Describe a scenario where a queue is more appropriate than a stack, and vice versa.

**Answer:** Queue: CPU scheduling (processes should be served in the order they arrive — FIFO fairness). Stack: Undo operations in a text editor (the most recent action should be undone first — LIFO).

**Explanation:** Queues preserve the order of arrival, making them ideal for fairness-based processing. Stacks reverse the order, making them ideal for tracking nested or hierarchical operations.

---

## Q4. Linked Queue Operations

**Question:** Draw the state of a linked queue after: `enqueue(10)`, `enqueue(20)`, `dequeue()`, `enqueue(30)`, `dequeue()`.

**Answer:** Final state: front -> [30] -> nullptr, rear -> [30]. Queue contains only 30.

**Explanation:** enqueue(10): front->[10], rear->[10]. enqueue(20): front->[10]->[20], rear->[20]. dequeue(): removes 10, front->[20], rear->[20]. enqueue(30): front->[20]->[30], rear->[30]. dequeue(): removes 20, front->[30], rear->[30].

---

## Q5. Array Queue Pop Complexity

**Question:** Why does a simple (non-circular) array-based queue have $O(n)$ pop complexity? How does the circular queue solve this?

**Answer:** In a simple array queue with `front` fixed at index 0, popping requires shifting all remaining elements one position to the left, which is $O(n)$. The circular queue solves this by allowing `front` to move forward using `front = (front + 1) % capacity`, making pop $O(1)$ without any shifting.

**Explanation:** The key insight is that we do not need to keep the first element at index 0. By using modular arithmetic, both front and rear can wrap around the array, reusing space freed by dequeue operations.
