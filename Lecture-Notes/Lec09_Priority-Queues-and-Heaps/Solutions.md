# Lecture 9 Solutions — Priority Queues and Heaps

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Table of Contents

- [Exercise 1: Max Heap Insert Trace](#exercise-1-max-heap-insert-trace)
- [Exercise 2: Max Heap Delete Trace](#exercise-2-max-heap-delete-trace)
- [Exercise 3: Heap Initialization](#exercise-3-heap-initialization)
- [Exercise 4: Is This a Heap?](#exercise-4-is-this-a-heap)
- [Exercise 5: Leftist Tree Merge](#exercise-5-leftist-tree-merge)

---

<br>

## Exercise 1: Max Heap Insert Trace

**Problem:** Given a max heap `[-, 20, 15, 7, 6, 9, 2, 6, 5, 1]`, insert the element 25. Show the heap after insertion.

### Solution

**Answer:** Placing 25 at position 10 gives `[-, 20, 15, 7, 6, 9, 2, 6, 5, 1, 25]`. Then bubble it up.

1. 25 is larger than its parent 9 (position 5), so swap.
2. 25 is larger than its parent 15 (position 2), so swap.
3. 25 is larger than its parent 20 (position 1), so swap.

The final heap is `[-, 25, 20, 7, 6, 15, 2, 6, 5, 1, 9]`.

```text
              25
          /        \
        20          7
      /    \       / \
     6      15    2   6
    / \    /
   5   1  9
```

*Figure 1. The max heap after inserting 25*

**Explanation:** Heap insert places the new element at the end (next available position in the complete binary tree) and bubbles it up by repeatedly comparing with its parent and swapping if larger. The time complexity is $O(\log n)$. With 10 elements the height (number of levels) is $\lceil \log_2 11 \rceil = 4$, so the new element makes at most $4 - 1 = 3$ comparisons. This exercise is the worst case, in which 25 rises to the root and swaps all three times.

---

<br>

## Exercise 2: Max Heap Delete Trace

**Problem:** Given a max heap `[-, 20, 15, 7, 6, 9, 2, 6, 5, 1, 8]`, perform deleteMax. Show the heap after deletion.

### Solution

**Answer:** Remove the root 20. The last element is 8 at position 10, so take it out (heapSize is now 9) and place it at the root. Then trickle it down.

1. Compare the children 15 and 7 and pick the larger 15. Since 8 < 15, swap.
2. At position 2, compare the children 6 and 9 and pick the larger 9. Since 8 < 9, swap.
3. At position 5, the child slot of 8 is position 10, but that element has already been taken out and heapSize is 9, so there is no child. Therefore place 8 at position 5.

The final heap is `[-, 15, 9, 7, 6, 8, 2, 6, 5, 1]`.

**Explanation:** DeleteMax removes the root, replaces it with the last element, and trickles it down. At each level, the element is compared with the larger child and swapped if smaller. The time complexity is $O(\log n)$.

---

<br>

## Exercise 3: Heap Initialization

**Problem:** Build a max heap from the array `[-, 3, 1, 6, 5, 2, 4]` using the bottom-up initialization algorithm. Show each step.

### Solution

**Answer:** Since $n = 6$, start at $\lfloor 6/2 \rfloor = 3$.

- Position 3 (value 6) has only one child, 4 at position 6. Since 6 > 4, no swap. The array is `[-, 3, 1, 6, 5, 2, 4]`.
- Position 2 (value 1) has the children 5 at position 4 and 2 at position 5. The larger child is 5, and 1 < 5, so swap. The array is `[-, 3, 5, 6, 1, 2, 4]`.
- Position 1 (value 3) has the children 5 at position 2 and 6 at position 3. The larger child is 6, and 3 < 6, so swap, giving `[-, 6, 5, 3, 1, 2, 4]`. The element 3 continues trickling down from position 3. Position 3 has only one child, 4 at position 6, and 3 < 4, so swap. The final heap is `[-, 6, 5, 4, 1, 2, 3]`.

**Explanation:** Bottom-up initialization starts at the rightmost internal node and applies trickle down at each. This is $O(n)$ because most nodes are near the bottom and require few swaps.

---

<br>

## Exercise 4: Is This a Heap?

**Problem:** Determine whether each of the following binary trees is a valid max heap: (a) the complete binary tree that holds 14, 12, 7, 10, 8, 6 in level order, that is, the array `[-, 14, 12, 7, 10, 8, 6]` (b) the tree in which the root 9 has the left child 6 and 6 has only a right child 5 (c) the tree in which the root 30 has only a left child 25, that is, the array `[-, 30, 25]`

```text
(a)      14             (b)    9          (c)   30
       /    \                 /                /
     12      7               6               25
    /  \    /                 \
  10    8  6                   5
```

*Figure 2. Three binary trees to be checked for the max heap property*

### Solution

**Answer:**

- (a) It is a max heap. It is a complete binary tree, and every parent is greater than or equal to its children.
- (b) It is not a max heap, because it is not a complete binary tree. The node 6 should have a left child before a right child, and the right child of 9 is empty while the level below contains a node. By values alone, $9 \geq 6 \geq 5$, so the max-tree property holds.
- (c) It is a max heap. It is a complete binary tree with two nodes (node 2 is the left child), and $30 \geq 25$.

**Explanation:** A max heap requires two properties. (1) It must be a complete binary tree, that is, all levels are full except possibly the last, which is filled from the left. (2) Every node's value must be greater than or equal to its children's values. Both conditions must hold. The array representation covers only complete binary trees without gaps, so (b) cannot be written as the array `[-, 9, 6, 5]`; that array would make 5 the right child of 9.

---

<br>

## Exercise 5: Leftist Tree Merge

**Problem:** Explain why leftist trees are preferred over heaps when frequent merge operations are needed. What is the time complexity of merging two leftist trees of sizes $m$ and $n$?

### Solution

**Answer:** Merging two array heaps requires either dumping both arrays together and re-heapifying, or inserting the elements of one heap into the other one at a time. Re-heapifying takes $O(m+n)$, and inserting the elements of the heap of size $m$ takes $O(m \log(m+n))$, so either way the time is at least proportional to the size of one heap. Leftist tree merge follows only the rightmost paths of both trees, which have at most $\lfloor \log_2(m+1) \rfloor$ and $\lfloor \log_2(n+1) \rfloor$ internal nodes, giving $O(\log m + \log n)$ time.

**Explanation:** The leftist property ($s(\text{left}) \geq s(\text{right})$) ensures the right path is short. Since merge only traverses right paths and then adjusts by swapping children, the total work is proportional to the sum of right path lengths, which is logarithmic in the tree sizes.
