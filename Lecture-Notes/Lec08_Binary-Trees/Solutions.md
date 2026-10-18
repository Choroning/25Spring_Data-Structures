# Lecture 8 Solutions — Binary Trees

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Table of Contents

- [Exercise 1: Binary Tree Properties](#exercise-1-binary-tree-properties)
- [Exercise 2: Traversal Orders](#exercise-2-traversal-orders)
- [Exercise 3: Complete Binary Tree](#exercise-3-complete-binary-tree)
- [Exercise 4: Expression Tree Evaluation](#exercise-4-expression-tree-evaluation)
- [Exercise 5: Array vs. Linked Representation](#exercise-5-array-vs-linked-representation)

---

<br>

## Exercise 1: Binary Tree Properties

**Problem:** A binary tree has height $h = 5$. What is the minimum and maximum number of nodes it can have? Height is counted as the number of levels of the tree (the root is at level 1).

### Solution

**Answer:** The minimum is $h = 5$ nodes (degenerate or skewed tree), and the maximum is $2^5 - 1 = 31$ nodes (full binary tree).

**Explanation:** A binary tree of height $h$ has at least $h$ nodes (a single chain from root to leaf) and at most $2^h - 1$ nodes (every level completely filled). Under the same definition, the minimum height for $n$ nodes is $\lceil \log_2(n+1) \rceil$. These formulas hold when height is counted in levels. Under the definition that counts height in edges, a tree of height 5 has 6 levels, so it has at least 6 and at most $2^6 - 1 = 63$ nodes, and the minimum height becomes $\lceil \log_2(n+1) \rceil - 1$.

---

<br>

## Exercise 2: Traversal Orders

**Problem:** Given the following binary tree (Figure 1), write the preorder, inorder, postorder, and level-order traversals.

```text
        A
       / \
      B    C
     / \    \
    D   E    F
   /       / \
  G       H   I
```

*Figure 1. Binary tree of Exercise 2*

### Solution

**Answer:**
- Preorder (root, left, right): A, B, D, G, E, C, F, H, I
- Inorder (left, root, right): G, D, B, E, A, C, H, F, I
- Postorder (left, right, root): G, D, E, B, H, I, F, C, A
- Level-order: A, B, C, D, E, F, G, H, I

**Explanation:** Preorder visits the root first, then recursively visits the left subtree and the right subtree. Inorder visits the left subtree, then the root, then the right subtree. Since C has no left child, C comes before its right subtree (H, F, I) in the inorder traversal. Postorder visits both subtrees before the root, so the root A comes last. Level-order uses a queue to process nodes level by level.

---

<br>

## Exercise 3: Complete Binary Tree

**Problem:** A complete binary tree has 21 nodes. (a) What is its height? (b) How many leaf nodes does it have? (c) How many nodes have exactly one child?

### Solution

**Answer:** (a) Height $= \lceil \log_2(21+1) \rceil = \lceil \log_2 22 \rceil = \lceil 4.46 \rceil = 5$. Level 1 holds node 1, level 2 holds 2 and 3, level 3 holds 4 through 7, level 4 holds 8 through 15, and level 5 holds 16 through 21, so there are 5 levels. (b) The last internal node is at position $\lfloor 21/2 \rfloor = 10$. So the number of leaf nodes is $21 - 10 = 11$. (c) Since 21 is odd, every internal node has 2 children. The last internal node 10 also has 2 children, since $2 \times 10 = 20 \leq 21$ and $2 \times 10 + 1 = 21 \leq 21$. So 0 nodes have exactly one child.

**Explanation:** In a complete binary tree with $n$ nodes, internal nodes occupy positions 1 through $\lfloor n/2 \rfloor$. If $n$ is odd, every internal node has exactly 2 children. If $n$ is even, only node $n/2$ has only a left child. The height in (a) is counted in levels; counted in edges it is 4.

---

<br>

## Exercise 4: Expression Tree Evaluation

**Problem:** Construct the expression tree for the postfix expression `3 5 + 2 * 7 -` and evaluate it.

### Solution

**Answer:** The expression tree is shown in Figure 2.

```text
        -
       / \
      *   7
     / \
    +   2
   / \
  3   5
```

*Figure 2. Expression tree of the postfix expression 3 5 + 2 * 7 -*

Evaluation: $(3 + 5) = 8$, $8 \times 2 = 16$, $16 - 7 = 9$. Result: **9**.

**Explanation:** To build an expression tree from postfix, scan left to right. For each operand, create a leaf node and push it on the stack (Lecture 5). For each operator, pop two nodes (right then left), create a new node with the operator, attach them as children, and push the new node. When the scan ends, the single node left on the stack is the root. Postorder traversal of the result gives back the original postfix expression.

---

<br>

## Exercise 5: Array vs. Linked Representation

**Problem:** A right-skewed binary tree has 4 nodes (a, b, c, d where each node has only a right child). How many array slots are needed for the array representation? Why is linked representation preferred?

### Solution

**Answer:** Node positions are 1, 3, 7, 15. The array needs $2^h = 2^4 = 16$ slots, positions 0 through 15, but only 4 are used. The other 12 are empty, so the space waste is 75%. Linked representation needs only $4 \times \text{sizeof(node)}$ with no wasted space.

**Explanation:** In the array representation, a right-skewed tree places nodes at positions $1, 3, 7, 15, \ldots$ (following the right child formula $2x+1$). This exponential growth in indices wastes enormous space. Linked representation stores only the nodes that exist, making it far more space-efficient for non-complete trees.
