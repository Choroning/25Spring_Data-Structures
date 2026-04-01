# Chapter 06 — Queues

> **Last Updated:** 2026-04-01
>
> Carrano & Henry, Data Structures and Abstractions with Java 4th Ed. Ch 6

> **Prerequisites**: [Programming Language] Java. [Data Structures] Stacks (Ch 5).
>
> **Learning Objectives**:
> 1. Implement queues using arrays and linked lists
> 2. Apply circular array technique for efficient queue operations
> 3. Distinguish queue variants (deque, priority queue)

---

## Table of Contents

1. [Queue ADT](#1-queue-adt)
2. [Array-Based Queue](#2-array-based-queue)
3. [Circular Queue](#3-circular-queue)
4. [Linked Queue](#4-linked-queue)
5. [Double-Ended Queue (Deque)](#5-double-ended-queue-deque)
6. [Applications of Queues](#6-applications-of-queues)
7. [Summary](#summary)
8. [Appendix](#appendix)

---

<br>

## 1. Queue ADT

### 1.1 Definition

A **queue** is a linear list where:
- Additions (insertions / enqueue) are done at the **rear** only
- Removals (deletions / dequeue) are done at the **front** only

This follows the **FIFO** (First In, First Out) principle.

> **Key Point:** In stacks, push and pop are all made at top (LIFO). In queues, push is at rear and pop is at front (FIFO).

### 1.2 Core Operations

| Operation | Description | Complexity |
|-----------|-------------|------------|
| `push(x)` / `enqueue(x)` | Insert element at rear | $O(1)$ |
| `pop()` / `dequeue()` | Remove element from front | $O(1)$ |
| `front()` | Return front element | $O(1)$ |
| `back()` | Return rear element | $O(1)$ |
| `empty()` | Check if queue is empty | $O(1)$ |
| `size()` | Return number of elements | $O(1)$ |

---

<br>

## 2. Array-Based Queue

### 2.1 Simple Array Queue

Using `front` at the left end and `rear` at the right end:
- `front` always equals zero
- `push(x)`: `array[++rear] = x` — $O(1)$
- `pop()`: shift all elements left — $O(n)$

This is inefficient because `pop()` requires $O(n)$ shifts.

### 2.2 Modified Formula

Use a modified location formula where `front` can move right:
$$\text{location}(i) = \text{location}(1) + i - 1$$

- `pop()`: increment `front` by 1 — $O(1)$
- Problem: when `rear = MaxSize - 1` and `front > 0`, space is wasted at the front

---

<br>

## 3. Circular Queue

### 3.1 Concept

Treat the array as **circular** using the modulo operation:

$$\text{location}(i) = (\text{location}(1) + i - 1) \% \text{MaxSize}$$

Both add and delete operations become $O(1)$.

### 3.2 Implementation Details

- **Moving clockwise**: `rear = (rear + 1) % queue.length`
- Use integer variables `theFront` and `theBack`:
  - `theFront` is one position counterclockwise from the first element
  - `theBack` gives the position of the last element
- Initialize: `front = rear = 0`

### 3.3 Full vs. Empty Distinction

When the queue becomes full through additions: `front == rear`.
When the queue becomes empty through removals: `front == rear`.

We **cannot distinguish** between full and empty using only `front` and `rear`.

**Solution**: Waste one slot — the queue is full when `(rear + 1) % capacity == front`. This means maximum $\text{capacity} - 1$ elements.

### 3.4 Add Operation (Enqueue)

```cpp
void push(const T& element) {
    int newRear = (rear + 1) % capacity;
    if (newRear == front)
        throw std::overflow_error("Queue is full");
    rear = newRear;
    queue[rear] = element;
}
```

### 3.5 Remove Operation (Dequeue)

```cpp
T pop() {
    if (front == rear)
        throw std::underflow_error("Queue is empty");
    front = (front + 1) % capacity;
    return queue[front];
}
```

---

<br>

## 4. Linked Queue

### 4.1 Implementation

Use a singly linked list with both `front` and `rear` pointers:
- `enqueue`: insert at rear — $O(1)$
- `dequeue`: remove from front — $O(1)$

```cpp
struct Node {
    T data;
    Node* next;
};
Node* frontNode;
Node* rearNode;
```

### 4.2 Advantages

- No size limitation (dynamic memory)
- No wasted space from circular array slot

---

<br>

## 5. Double-Ended Queue (Deque)

A **deque** allows insertion and deletion at both ends:
- `pushFront`, `pushBack`, `popFront`, `popBack`
- All operations $O(1)$

---

<br>

## 6. Applications of Queues

### 6.1 CPU Scheduling

- Round-robin scheduling: processes take turns using the CPU
- Ready queue holds processes waiting for execution

### 6.2 Breadth-First Search (BFS)

```
enqueue(start)
while queue is not empty:
    node = dequeue()
    for each neighbor of node:
        if not visited:
            mark visited
            enqueue(neighbor)
```

### 6.3 Buffer Management

- Print job spooling
- Keyboard input buffer
- Network packet buffering

---

<br>

## Summary

| Concept | Key Point |
|---------|-----------|
| Queue | FIFO data structure; insert at rear, remove from front |
| Simple array queue | Pop requires $O(n)$ shifting |
| Circular array queue | Modulo arithmetic; all ops $O(1)$; waste one slot |
| Full vs. empty | Both have `front == rear`; use capacity-1 or a counter |
| Linked queue | Front and rear pointers; truly dynamic |
| Deque | Double-ended; insert/remove at both ends |

---

<br>

## Appendix

### Circular Queue vs. Linear Queue

| Property | Linear Queue | Circular Queue |
|----------|-------------|----------------|
| Pop | $O(n)$ or wastes space | $O(1)$ |
| Space utilization | May leave gaps at front | Reuses freed space |
| Full detection | `rear == capacity - 1` | `(rear+1) % cap == front` |
| Implementation | Simple | Requires modulo arithmetic |

### Queue Variants

- **Priority Queue**: Elements dequeued by priority (Chapter 9)
- **Circular Buffer**: Fixed-size, overwriting oldest data
- **Message Queue**: Inter-process communication (OS concept)
