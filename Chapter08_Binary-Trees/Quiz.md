# Chapter 08 — Quiz

> **Last Updated:** 2026-03-21

---

## Q1. Binary Tree Properties

**Question:** A binary tree has height $h = 5$. What is the minimum and maximum number of nodes it can have?

**Answer:** Minimum: $h = 5$ nodes (degenerate/skewed tree). Maximum: $2^5 - 1 = 31$ nodes (full binary tree).

**Explanation:** A binary tree of height $h$ has at least $h$ nodes (a single chain from root to leaf) and at most $2^h - 1$ nodes (every level completely filled). The minimum height for $n$ nodes is $\lceil \log_2(n+1) \rceil$.

---

## Q2. Traversal Orders

**Question:** Given the following binary tree, write the preorder, inorder, postorder, and level-order traversals:

```
        A
       / \
      B    C
     / \    \
    D   E    F
   /       / \
  G       H   I
```

**Answer:**
- Preorder (root, left, right): A, B, D, G, E, C, F, H, I
- Inorder (left, root, right): G, D, B, E, A, C, H, F, I
- Postorder (left, right, root): G, D, E, B, H, I, F, C, A
- Level-order: A, B, C, D, E, F, G, H, I

**Explanation:** Preorder visits root first, then recursively visits the left subtree and right subtree. Inorder visits left subtree, then root, then right subtree. Postorder visits both subtrees before root. Level-order uses a queue to process nodes level by level.

---

## Q3. Complete Binary Tree

**Question:** A complete binary tree has 21 nodes. (a) What is its height? (b) How many leaf nodes does it have? (c) How many nodes have exactly one child?

**Answer:** (a) Height = $\lceil \log_2(21+1) \rceil = \lceil \log_2 22 \rceil = \lceil 4.46 \rceil = 5$. (b) The last internal node is at position $\lfloor 21/2 \rfloor = 10$. So leaf nodes = $21 - 10 = 11$. (c) Since $21$ is odd, all internal nodes have 2 children except possibly the last. Since $2 \times 10 = 20 \leq 21$ and $2 \times 10 + 1 = 21 \leq 21$, node 10 has 2 children. So 0 nodes have exactly one child.

**Explanation:** In a complete binary tree with $n$ nodes, internal nodes occupy positions 1 through $\lfloor n/2 \rfloor$. If $n$ is odd, every internal node has exactly 2 children. If $n$ is even, node $n/2$ has only a left child.

---

## Q4. Expression Tree Evaluation

**Question:** Construct the expression tree for the postfix expression `3 5 + 2 * 7 -` and evaluate it.

**Answer:** The expression tree is:
```
        -
       / \
      *   7
     / \
    +   2
   / \
  3   5
```
Evaluation: $(3 + 5) = 8$, $8 \times 2 = 16$, $16 - 7 = 9$. Result: **9**.

**Explanation:** To build an expression tree from postfix: scan left to right. For each operand, create a leaf node and push it on the stack. For each operator, pop two nodes (right then left), create a new node with the operator, attach them as children, and push the new node. Postorder traversal of the result gives back the original postfix expression.

---

## Q5. Array vs. Linked Representation

**Question:** A right-skewed binary tree has 4 nodes (a, b, c, d where each node has only a right child). How many array slots are needed for the array representation? Why is linked representation preferred?

**Answer:** Node positions are 1, 3, 7, 15. Array needs $2^h = 2^4 = 16$ slots, but only 4 are used. Space waste is 75%. Linked representation needs only $4 \times \text{sizeof(node)}$ with no wasted space.

**Explanation:** In the array representation, a right-skewed tree places nodes at positions $1, 3, 7, 15, \ldots$ (following the right child formula $2x+1$). This exponential growth in indices wastes enormous space. Linked representation stores only the nodes that exist, making it far more space-efficient for non-complete trees.
