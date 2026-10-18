# Lecture 6 Exercises — Queues

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Exercise 1: Circular Queue Trace

**Problem:** Given a circular queue of capacity 6 (indices 0-5), initially `front = rear = 0`. After the operations: `push(A)`, `push(B)`, `push(C)`, `pop()`, `pop()`, `push(D)`, `push(E)`, `push(F)`, what are the values of front, rear, and the queue contents?

**[Solution](Solutions.md#exercise-1-circular-queue-trace)**

---

<br>

## Exercise 2: Full vs. Empty

**Problem:** In a circular queue, both the full and the empty states have `front == rear`. How do we distinguish between them?

**[Solution](Solutions.md#exercise-2-full-vs-empty)**

---

<br>

## Exercise 3: Queue vs. Stack

**Problem:** Describe a scenario where a queue is more appropriate than a stack, and vice versa.

**[Solution](Solutions.md#exercise-3-queue-vs-stack)**

---

<br>

## Exercise 4: Linked Queue Operations

**Problem:** Draw the state of a linked queue after: `enqueue(10)`, `enqueue(20)`, `dequeue()`, `enqueue(30)`, `dequeue()`.

**[Solution](Solutions.md#exercise-4-linked-queue-operations)**

---

<br>

## Exercise 5: Array Queue Pop Complexity

**Problem:** Why does a simple (non-circular) array-based queue have $O(n)$ pop complexity? How does the circular queue solve this?

**[Solution](Solutions.md#exercise-5-array-queue-pop-complexity)**
