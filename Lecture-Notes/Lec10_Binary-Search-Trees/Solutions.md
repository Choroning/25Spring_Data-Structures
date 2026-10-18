# Lecture 10 Solutions — Binary Search Trees

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Table of Contents

- [Exercise 1: BST Construction](#exercise-1-bst-construction)
- [Exercise 2: BST Deletion Cases](#exercise-2-bst-deletion-cases)
- [Exercise 3: BST Worst Case](#exercise-3-bst-worst-case)
- [Exercise 4: BST Search Complexity](#exercise-4-bst-search-complexity)
- [Exercise 5: Indexed BST](#exercise-5-indexed-bst)

---

<br>

## Exercise 1: BST Construction

**Problem:** Insert the following keys into an initially empty BST in the given order: 20, 10, 40, 6, 15, 30, 25, 35. Draw the resulting BST and give its inorder traversal.

### Solution

**Answer:**

```text
         20
        /   \
      10     40
     /  \    /
    6   15  30
           /  \
          25   35
```

*Figure 1. The BST obtained by inserting 20, 10, 40, 6, 15, 30, 25, 35 in turn*

Inorder traversal: 6, 10, 15, 20, 25, 30, 35, 40.

**Explanation:** Each key is inserted by searching for its position. Keys smaller than the current node go left, larger go right. Inorder traversal (left, root, right) of a BST always produces keys in ascending order.

---

<br>

## Exercise 2: BST Deletion Cases

**Problem:** Using the BST from Exercise 1, perform the following deletions in order and show the tree after each: (a) delete 6 (leaf), (b) delete 40 (degree 1), (c) delete 20 (degree 2, use inorder successor).

### Solution

**Answer:** Trees are written in the form `a(b, c)`, where the node with key a has the left subtree b and the right subtree c, and `_` is an empty subtree.

- (a) Delete 6 (leaf): simply remove it. The tree is 20(10(_, 15), 40(30(25, 35), _)).
- (b) Delete 40 (degree 1, has left child 30): replace 40 with 30. The tree is 20(10(_, 15), 30(25, 35)).
- (c) Delete 20 (degree 2): the inorder successor is 25 (smallest in right subtree). Replace 20 with 25, then remove the original 25 node. The final tree is 25(10(_, 15), 30(_, 35)).

```text
       25
     /    \
   10      30
     \       \
      15      35
```

*Figure 2. The BST after the three deletions*

**Explanation:** Leaf deletion is trivial. Degree-1 deletion replaces the node with its child. Degree-2 deletion replaces the key with the inorder successor (go right, then follow left pointers to the end), which is guaranteed to be in a leaf or degree-1 node.

---

<br>

## Exercise 3: BST Worst Case

**Problem:** Insert keys 1, 2, 3, 4, 5 into an empty BST. What is the resulting tree structure? What is the time complexity of searching for key 5?

### Solution

**Answer:** The tree becomes the right-skewed chain 1 → 2 → 3 → 4 → 5, in which every node has only a right child. Searching for 5 requires visiting all 5 nodes with 5 comparisons, which is $O(n)$.

**Explanation:** Inserting keys in sorted (ascending or descending) order produces a degenerate BST that is essentially a linked list. The height is $n$, so all operations are $O(n)$. This is the worst-case scenario for BSTs and motivates the use of self-balancing trees (AVL, Red-Black).

---

<br>

## Exercise 4: BST Search Complexity

**Problem:** A BST has $n = 1000$ nodes. What is the minimum and maximum number of comparisons needed to search for a key?

### Solution

**Answer:** Height is counted as the number of levels (the root is level 1), as defined in Lecture 8. The minimum is 1 comparison, when the key is at the root. The maximum number of comparisons (worst case) is the height $h$. The lowest possible height is $\lceil \log_2 1001 \rceil = 10$ (since $2^9 = 512 < 1001 \leq 1024 = 2^{10}$), so the worst case in a balanced tree is 10. A degenerate tree has height 1000, so the worst case in the worst-shaped tree is 1000 comparisons.

**Explanation:** When the key is found, the number of comparisons equals the level of the target node, that is, the number of branches from the root to the target node plus 1. When the key is not found, at most height comparisons are made. A balanced BST keeps height at $O(\log n)$, while a degenerate BST has height $O(n)$.

---

<br>

## Exercise 5: Indexed BST

**Problem:** In an indexed BST, each node stores `leftSize` (number of nodes in its left subtree). Given the tree from Exercise 1, what is the `leftSize` value for each node? How would you find the 5th smallest element?

### Solution

**Answer:** The `leftSize` values are 20: 3, 10: 1, 40: 3, 6: 0, 15: 0, 30: 1, 25: 0, and 35: 0. The left subtree of 40 contains the three nodes 30, 25, and 35, so the `leftSize` of 40 is 3.

Find the 5th smallest element with the rank $k = 5$ counted from 1.

1. At the root 20 (`leftSize` 3), $5 > 3 + 1 = 4$, so go right and search for rank $5 - 4 = 1$.
2. At 40 (`leftSize` 3), $1 \leq 3$, so go left.
3. At 30 (`leftSize` 1), $1 \leq 1$, so go left.
4. At 25 (`leftSize` 0), $1 = 0 + 1$, so 25 is the answer.

Therefore the 5th smallest element is 25, which is the fifth key of the inorder traversal 6, 10, 15, 20, 25, 30, 35, 40.

**Explanation:** To find the $k$-th smallest element, do the following at each node. If $k \leq$ leftSize, go left. If $k =$ leftSize + 1, the current node is the answer. If $k >$ leftSize + 1, go right with $k' = k - \text{leftSize} - 1$. Time: $O(h)$. This is the same method as finding the element with the 0-based index $k - 1$ in [Section 4.2 of Lecture 10](Concepts_Lecture.md#42-rank-based-operations).
