# Chapter 09 — Priority Queues and Heaps

> **Last Updated:** 2026-03-21

---

## Table of Contents

- [1. Priority Queues](#1-priority-queues)
  - [1.1 Definition](#11-definition)
  - [1.2 Min and Max Priority Queues](#12-min-and-max-priority-queues)
  - [1.3 Implementation Options](#13-implementation-options)
- [2. Max and Min Trees](#2-max-and-min-trees)
  - [2.1 Max Tree](#21-max-tree)
  - [2.2 Min Tree](#22-min-tree)
- [3. Heaps](#3-heaps)
  - [3.1 Definition](#31-definition)
  - [3.2 Array Representation](#32-array-representation)
  - [3.3 Heap Insert — Bubble Up](#33-heap-insert--bubble-up)
  - [3.4 Heap Delete — Trickle Down](#34-heap-delete--trickle-down)
  - [3.5 Heap Initialization](#35-heap-initialization)
  - [3.6 Complexity Summary](#36-complexity-summary)
- [4. Leftist Trees](#4-leftist-trees)
  - [4.1 Motivation](#41-motivation)
  - [4.2 S-Values (Shortest Path)](#42-s-values-shortest-path)
  - [4.3 Leftist Tree Definition](#43-leftist-tree-definition)
  - [4.4 Merge Operation](#44-merge-operation)
  - [4.5 Insert and Delete via Merge](#45-insert-and-delete-via-merge)
- [Summary](#summary)
- [Appendix](#appendix)

---

<br>

## 1. Priority Queues

### 1.1 Definition

A **priority queue** is a collection of zero or more elements where each element has a **priority or value**. Unlike FIFO queues, the order of deletion is **determined by the element priority**, not arrival order.

### 1.2 Min and Max Priority Queues

| Type | Find | Delete | Insert |
|:-----|:-----|:-------|:-------|
| **Min Priority Queue** | Element with **minimum** priority | Remove min element | Insert new element |
| **Max Priority Queue** | Element with **maximum** priority | Remove max element | Insert new element |

Two or more elements can have the same priority.

### 1.3 Implementation Options

Priority queues are primarily implemented using:
1. **Heaps** — a complete binary tree stored in an array
2. **Leftist trees** — a linked data structure suitable for efficient merging

> **Key Point:** Heaps provide $O(\log n)$ insert and delete operations with $O(1)$ find-max/find-min. Leftist trees additionally support $O(\log n)$ merge of two priority queues.

---

<br>

## 2. Max and Min Trees

### 2.1 Max Tree

A **max tree** is a tree in which the value in each node is **greater than or equal** to those in its children (if any). The root contains the **maximum** element.

Nodes of a max tree may have more than two children (i.e., it may not be a binary tree).

### 2.2 Min Tree

A **min tree** is a tree in which the value in each node is **less than or equal** to those in its children. The root contains the **minimum** element.

---

<br>

## 3. Heaps

### 3.1 Definition

A **max heap** (min heap) is a **max (min) tree** that is also a **complete binary tree**.

- Max heap: every parent $\geq$ its children; root = maximum
- Min heap: every parent $\leq$ its children; root = minimum

**Not a max heap if:** the tree satisfies the max-tree property but is NOT a complete binary tree (e.g., missing a middle node on the last level).

### 3.2 Array Representation

Since a heap is a complete binary tree, it is efficiently represented as an array using the node number properties:

```
Heap:       [_, 9, 8, 7, 6, 7, 2, 6, 5, 1]
Index:       0  1  2  3  4  5  6  7  8  9
```

- Parent of node $i$: $\lfloor i/2 \rfloor$
- Left child of node $i$: $2i$
- Right child of node $i$: $2i + 1$

### 3.3 Heap Insert — Bubble Up

To insert a new element into a max heap:

1. Place the new element at the **next available position** (end of array, maintaining completeness)
2. **Bubble up**: compare the new element with its parent; if it is larger, swap them
3. Repeat until the heap property is restored or the root is reached

```cpp
int currentNode = ++heapSize;
while (currentNode != 1 && heap[currentNode / 2] < theElement) {
    heap[currentNode] = heap[currentNode / 2]; // move parent down
    currentNode /= 2;                          // move to parent
}
heap[currentNode] = theElement;
```

**Time complexity:** $O(\log n)$ — at most one comparison per level, and there are $\lceil \log_2 n \rceil$ levels.

### 3.4 Heap Delete — Trickle Down

To delete the max element from a max heap:

1. **Remove the root** (max element)
2. Take the **last element** in the heap and attempt to place it at the root
3. **Trickle down**: compare with children; swap with the **larger child** if it is bigger
4. Repeat until the heap property is restored or a leaf is reached

```cpp
T lastElement = heap[heapSize--];
int currentNode = 1, child = 2;
while (child <= heapSize) {
    if (child < heapSize && heap[child] < heap[child + 1])
        child++;                              // use larger child
    if (lastElement >= heap[child])
        break;                                // found the spot
    heap[currentNode] = heap[child];          // move child up
    currentNode = child;
    child *= 2;
}
heap[currentNode] = lastElement;
```

**Time complexity:** $O(\log n)$ — same reasoning as insertion.

> **Key Point:** During trickle-down, if both children are larger than the element being placed, select **either one** (typically the larger child for max heap to maintain efficiency).

### 3.5 Heap Initialization

Given an arbitrary array of $n$ elements, build a max heap in $O(n)$ time:

1. Start at the **rightmost internal node** (position $\lfloor n/2 \rfloor$)
2. Apply **trickle-down** (sift-down) at each internal node, moving from right to left, bottom to top
3. Continue until the root is processed

```cpp
for (int root = heapSize / 2; root >= 1; root--) {
    // Trickle down from 'root'
    T rootElement = heap[root];
    int child = 2 * root;
    while (child <= heapSize) {
        if (child < heapSize && heap[child] < heap[child + 1])
            child++;
        if (rootElement >= heap[child]) break;
        heap[child / 2] = heap[child];
        child *= 2;
    }
    heap[child / 2] = rootElement;
}
```

**Example:** Input array `[-, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]` becomes max heap `[-, 11, 10, 7, 9, 5, 6, 3, 8, 4, 2, 1]` after initialization.

**Time complexity:** $O(n)$ — not $O(n \log n)$. The key insight is that most nodes are near the bottom and require very few swaps.

### 3.6 Complexity Summary

| Operation | Time Complexity |
|:----------|:---------------|
| Insert | $O(\log n)$ |
| Delete max/min | $O(\log n)$ |
| Find max/min | $O(1)$ |
| Initialization (heapify) | $O(n)$ |

---

<br>

## 4. Leftist Trees

### 4.1 Motivation

Heaps do not support efficient **merge** of two heaps. Merging two heaps of sizes $m$ and $n$ using standard heap operations requires $O((m+n) \log(m+n))$. Leftist trees enable $O(\log(m+n))$ merge.

### 4.2 S-Values (Shortest Path)

The **s-value** (or **rank**) of a node $x$ is the length of the shortest path from $x$ to an **external node** (null descendant):

- $s(\text{null}) = 0$
- $s(x) = 1 + \min(s(x.\text{left}), s(x.\text{right}))$

### 4.3 Leftist Tree Definition

A **leftist tree** is a binary tree such that for every internal node $x$:

$$s(x.\text{left}) \geq s(x.\text{right})$$

This means the tree is "biased" toward the left: the right path from any node is always at most as long as the left path.

**Property:** The right path from the root of a leftist tree with $n$ internal nodes has at most $\lfloor \log_2(n+1) \rfloor$ nodes.

A **min leftist tree** is a leftist tree that is also a min tree (root = minimum).

### 4.4 Merge Operation

The merge is the fundamental operation for leftist trees. To merge two min leftist trees $A$ and $B$:

1. Compare roots; let the smaller root be the root of the merged tree
2. Recursively merge the right subtree of the smaller root with the other tree
3. After merging, if $s(\text{left}) < s(\text{right})$, **swap** left and right children
4. Update the s-value: $s(\text{root}) = s(\text{right}) + 1$

**Time complexity:** $O(\log m + \log n)$ since the merge follows right paths, which have logarithmic length.

### 4.5 Insert and Delete via Merge

- **Insert:** Create a new single-node leftist tree and merge it with the existing tree — $O(\log n)$
- **Delete min:** Remove the root, then merge its left and right subtrees — $O(\log n)$

> **Key Point:** All leftist tree operations reduce to the merge operation, making it the cornerstone of this data structure.

---

## Summary

| Concept | Key Point |
|:--------|:----------|
| Priority Queue | Elements deleted by priority, not arrival order |
| Max/Min Tree | Parent $\geq$ ($\leq$) children; root is max (min) |
| Heap | Max/min tree + complete binary tree; array-based |
| Heap Insert | Bubble up — $O(\log n)$ |
| Heap Delete | Trickle down — $O(\log n)$ |
| Heap Initialization | Bottom-up sift-down — $O(n)$ |
| Leftist Tree | $s(\text{left}) \geq s(\text{right})$ at every node |
| S-Value | Shortest path length to an external node |
| Leftist Merge | $O(\log m + \log n)$ — enables fast insert and delete |

---

## Appendix

### Why Heap Initialization is O(n)

The bottom-up approach works because:
- $n/2$ nodes are leaves (0 swaps)
- $n/4$ nodes need at most 1 swap
- $n/8$ nodes need at most 2 swaps
- Total work: $\sum_{i=1}^{\log n} \frac{n}{2^{i+1}} \cdot i = O(n)$

### Heap Sort

Heap sort uses a max heap: extract the maximum $n$ times to produce a sorted array. Time: $O(n \log n)$. Space: $O(1)$ (in-place).

### Real-World Applications

- **Heaps:** Dijkstra's shortest path, A* search, OS task scheduling, median maintenance
- **Leftist Trees:** External sorting, mergeable priority queues in graph algorithms
