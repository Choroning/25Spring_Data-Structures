# Chapter 10 — Quiz

> **Last Updated:** 2026-03-21

---

## Q1. BST Construction

**Question:** Insert the following keys into an initially empty BST in the given order: 20, 10, 40, 6, 15, 30, 25, 35. Draw the resulting BST and give its inorder traversal.

**Answer:**
```
         20
        /   \
      10     40
     /  \    /
    6   15  30
           /  \
          25   35
```
Inorder traversal: 6, 10, 15, 20, 25, 30, 35, 40.

**Explanation:** Each key is inserted by searching for its position. Keys smaller than the current node go left, larger go right. Inorder traversal (left, root, right) of a BST always produces keys in ascending order.

---

## Q2. BST Deletion Cases

**Question:** Using the BST from Q1, perform the following deletions in order and show the tree after each: (a) delete 6 (leaf), (b) delete 40 (degree 1), (c) delete 20 (degree 2, use inorder successor).

**Answer:**
(a) Delete 6 (leaf): simply remove. Tree: 20(10(_, 15), 40(30(25, 35), _)).
(b) Delete 40 (degree 1, has left child 30): replace 40 with 30. Tree: 20(10(_, 15), 30(25, 35)).
(c) Delete 20 (degree 2): inorder successor is 25 (smallest in right subtree). Replace 20 with 25, then remove original 25 node. Final tree: 25(10(_, 15), 30(_, 35)).

**Explanation:** Leaf deletion is trivial. Degree-1 deletion replaces the node with its child. Degree-2 deletion replaces the key with the inorder successor (go right, then follow left pointers to the end), which is guaranteed to be in a leaf or degree-1 node.

---

## Q3. BST Worst Case

**Question:** Insert keys 1, 2, 3, 4, 5 into an empty BST. What is the resulting tree structure? What is the time complexity of searching for key 5?

**Answer:** The tree becomes a right-skewed chain: 1 -> 2 -> 3 -> 4 -> 5. Searching for 5 requires visiting all 5 nodes: $O(n) = O(5)$.

**Explanation:** Inserting keys in sorted (ascending or descending) order produces a degenerate BST that is essentially a linked list. Height = $n$, so all operations are $O(n)$. This is the worst-case scenario for BSTs and motivates the use of self-balancing trees (AVL, Red-Black).

---

## Q4. BST Search Complexity

**Question:** A BST has $n = 1000$ nodes. What is the minimum and maximum number of comparisons needed to search for a key?

**Answer:** Minimum: 1 comparison (key is at the root). Maximum comparisons (worst case): $h$ where $h$ is the height. Best height = $\lceil \log_2 1001 \rceil = 10$, so best worst-case is 10. Degenerate height = 1000, so worst worst-case is 1000 comparisons.

**Explanation:** The number of comparisons equals the depth of the target node + 1 (or the height if the key is not found). A balanced BST keeps height at $O(\log n)$, while a degenerate BST has height $O(n)$.

---

## Q5. Indexed BST

**Question:** In an indexed BST, each node stores `leftSize` (number of nodes in its left subtree). Given the tree from Q1, what is the `leftSize` value for each node? How would you find the 5th smallest element?

**Answer:** leftSize values: 20:3, 10:1, 40:2, 6:0, 15:0, 30:1, 25:0, 35:0. To find the 5th smallest: start at root 20 (leftSize=3). 5 > 3+1=4, so go right and search for rank 5-4=1. At 40 (leftSize=2), 1 < 2, go left. At 30 (leftSize=1), 1 = 1, found! The 5th smallest is 25. Wait -- let me retrace. leftSize of 30 is 1. rank 1 = leftSize+1? No, leftSize is number of elements in left subtree. At 30: leftSize=1, searching for rank 1. Since 1 <= leftSize=1, go left. At 25: leftSize=0, searching for rank 1. Since 1 = 0+1, found! 5th smallest = 25.

**Explanation:** To find the $k$-th smallest element: at each node, if $k \leq$ leftSize, go left. If $k =$ leftSize + 1, the current node is the answer. If $k >$ leftSize + 1, go right with $k' = k - \text{leftSize} - 1$. Time: $O(h)$.
