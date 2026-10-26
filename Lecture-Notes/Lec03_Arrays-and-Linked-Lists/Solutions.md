# Lecture 3 Solutions — Arrays and Linked Lists

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-26

---

<br>

## Table of Contents

- [Exercise 1: Array Insert Complexity](#exercise-1-array-insert-complexity)
- [Exercise 2: Linked List Advantages](#exercise-2-linked-list-advantages)
- [Exercise 3: Doubly Linked List Deletion](#exercise-3-doubly-linked-list-deletion)
- [Exercise 4: Circular Linked List](#exercise-4-circular-linked-list)
- [Exercise 5: Dynamic Array Amortized Cost](#exercise-5-dynamic-array-amortized-cost)

---

<br>

## Exercise 1: Array Insert Complexity

**Problem:** What is the time complexity of inserting an element at position 0 of an array-based list with $n$ elements? Explain why.

### Solution

**Answer:** $O(n)$.

**Explanation:** Inserting at position 0 requires shifting all $n$ existing elements one position to the right to make room for the new element. Each shift is an $O(1)$ operation, and there are $n$ shifts, so the total is $O(n)$.

---

<br>

## Exercise 2: Linked List Advantages

**Problem:** Give two advantages and two disadvantages of a singly linked list compared to an array.

### Solution

**Answer:**
- Advantages: (1) Dynamic size: no need to pre-allocate a fixed capacity. (2) $O(1)$ insertion/deletion at the front without shifting.
- Disadvantages: (1) No random access: accessing the $i$-th element requires $O(n)$ traversal. (2) Extra memory for storing next pointers.

**Explanation:** The choice between array and linked list depends on the dominant operations. If frequent random access is needed, arrays are better. If frequent insertions/deletions at arbitrary positions are needed, linked lists may be preferable.

---

<br>

## Exercise 3: Doubly Linked List Deletion

**Problem:** Why can a doubly linked list delete a known node in $O(1)$, while a singly linked list requires $O(n)$?

### Solution

**Answer:** In a doubly linked list, each node has a `prev` pointer, so we can directly access the predecessor to update its `next` pointer. In a singly linked list, we must traverse from the head to find the predecessor, which takes $O(n)$.

**Explanation:** Deletion requires updating the predecessor's `next` pointer to bypass the deleted node. With a `prev` pointer, this is immediate. Without it, a linear scan is needed.

---

<br>

## Exercise 4: Circular Linked List

**Problem:** In a circular singly linked list, how do you detect that you have traversed all nodes?

### Solution

**Answer:** Start from any node and continue traversing until you reach the starting node again.

**Explanation:** Since the last node's `next` points back to the first node, the traversal forms a cycle. By comparing the current node with the starting node, we can detect when a full traversal is complete: `do { ... curr = curr->next; } while (curr != start);` If the list is empty, there is no node to visit, so check whether the starting node is `NULL` before entering this loop.

---

<br>

## Exercise 5: Dynamic Array Amortized Cost

**Problem:** Explain why the amortized cost of inserting at the end of a dynamic array (which doubles in size when full) is $O(1)$.

### Solution

**Answer:** When the array is full, we allocate a new array of double the size and copy all $n$ elements, costing $O(n)$. However, this doubling happens only after $n$ insertions. If the initial capacity is 1 and $n$ is a power of 2, the copying cost during $n$ insertions is $1 + 2 + \cdots + n/2 = n - 1$, so adding the cost $n$ of the insertions themselves, the total cost of $n$ insertions is $n + n/2 + n/4 + \cdots + 1 = 2n - 1 \leq 2n = O(n)$. For general $n$, the copying cost is still less than $2n$, so the total cost is less than $3n$. Thus the amortized cost per insertion is $O(n)/n = O(1)$.

**Explanation:** Using the aggregate method, the sum of copy costs over all doublings forms a geometric series that stays below $2n$, making the average cost per operation constant.
