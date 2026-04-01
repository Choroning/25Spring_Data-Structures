# Chapter 08 — Binary Trees

> **Last Updated:** 2026-04-01
>
> Carrano & Henry, Data Structures and Abstractions with Java 4th Ed. Ch 8

> **Prerequisites**: [Programming Language] Java. [Data Structures] Stacks, queues (Ch 5-6).
>
> **Learning Objectives**:
> 1. Implement binary trees and tree traversal algorithms
> 2. Apply preorder, inorder, postorder, and level-order traversals
> 3. Analyze properties of complete and full binary trees

---

## Table of Contents

- [1. Trees and Binary Trees](#1-trees-and-binary-trees)
  - [1.1 Tree Terminology](#11-tree-terminology)
  - [1.2 Binary Tree Definition](#12-binary-tree-definition)
  - [1.3 Difference Between a Tree and a Binary Tree](#13-difference-between-a-tree-and-a-binary-tree)
- [2. Binary Tree Properties](#2-binary-tree-properties)
  - [2.1 Fundamental Properties](#21-fundamental-properties)
  - [2.2 Full Binary Tree](#22-full-binary-tree)
  - [2.3 Complete Binary Tree](#23-complete-binary-tree)
  - [2.4 Node Number Properties](#24-node-number-properties)
- [3. Binary Tree Representation](#3-binary-tree-representation)
  - [3.1 Array Representation](#31-array-representation)
  - [3.2 Linked Representation](#32-linked-representation)
- [4. Binary Tree Traversals](#4-binary-tree-traversals)
  - [4.1 Preorder Traversal](#41-preorder-traversal)
  - [4.2 Inorder Traversal](#42-inorder-traversal)
  - [4.3 Postorder Traversal](#43-postorder-traversal)
  - [4.4 Level-Order Traversal](#44-level-order-traversal)
- [5. Expression Trees](#5-expression-trees)
  - [5.1 Definition](#51-definition)
  - [5.2 Traversal and Expression Forms](#52-traversal-and-expression-forms)
- [Summary](#summary)
- [Appendix](#appendix)

---

<br>

## 1. Trees and Binary Trees

### 1.1 Tree Terminology

| Term | Definition |
|:-----|:-----------|
| **Root** | The topmost node with no parent |
| **Leaf** | A node with no children (degree 0) |
| **Node degree** | The number of children a node has |
| **Tree degree** | The maximum of all node degrees in the tree |
| **Height (depth)** | The number of edges on the longest path from the root to a leaf |
| **Level** | Root is at level 1; children of a level-$i$ node are at level $i+1$ |
| **Parent** | The node directly above a given node |
| **Sibling** | Nodes sharing the same parent |

> **Key Point:** The **degree** of a node is the number of its children. The **degree** of a tree is the maximum node degree. A tree with root Joe having 3 children has tree degree 3.

### 1.2 Binary Tree Definition

A **binary tree** is a finite (possibly empty) collection of elements:
- A nonempty binary tree has a **root** element
- The remaining elements (if any) are partitioned into **two binary trees** called the **left subtree** and **right subtree**

### 1.3 Difference Between a Tree and a Binary Tree

| Property | Tree | Binary Tree |
|:---------|:-----|:------------|
| Empty? | Cannot be empty | May be empty |
| Max degree | No limit | At most 2 |
| Subtree ordering | Unordered | Ordered (left vs. right matters) |

Two binary trees with the same nodes but swapped left/right children are **different** binary trees, but would be the **same** general tree.

---

<br>

## 2. Binary Tree Properties

### 2.1 Fundamental Properties

1. **Edge count:** A binary tree with $n$ elements ($n > 0$) has exactly $n - 1$ edges

2. **Element bounds by height:** A binary tree of height $h$ ($h \geq 0$) has:
   - At least $h$ elements
   - At most $2^h - 1$ elements

3. **Height bounds by element count:** A binary tree with $n$ elements ($n \geq 0$) has height:
   - At least $\lceil \log_2(n+1) \rceil$
   - At most $n$

> **Key Point:** The minimum height $\lceil \log_2(n+1) \rceil$ is achieved by a **complete binary tree**. The maximum height $n$ occurs in a degenerate (skewed) tree.

### 2.2 Full Binary Tree

A **full binary tree** of height $h$ has exactly $2^h - 1$ nodes. Every level is completely filled, and every non-leaf node has exactly two children.

**Numbering scheme:** Nodes are numbered 1 through $2^h - 1$, level by level from top to bottom, left to right within each level.

### 2.3 Complete Binary Tree

A **complete binary tree** with $n$ nodes is a binary tree where:
1. Every level except possibly the last is **completely filled**
2. All nodes on the last level are **as far left as possible**

A full binary tree is a special case of a complete binary tree. A complete binary tree uses the same node numbering as a full binary tree (positions 1 through $n$).

### 2.4 Node Number Properties

For a node numbered $x$ in a full/complete binary tree with $n$ nodes:

| Relationship | Formula | Condition |
|:-------------|:--------|:----------|
| Parent of $x$ | $\lfloor x / 2 \rfloor$ | $x \neq 1$ |
| Left child of $x$ | $2x$ | $2x \leq n$ |
| Right child of $x$ | $2x + 1$ | $2x + 1 \leq n$ |
| Node is a leaf | $2x > n$ | |

> **Key Point:** These properties enable efficient **array representation** of complete binary trees. Node $x$ at index $x$ has its parent at $\lfloor x/2 \rfloor$ and children at $2x$ and $2x+1$.

---

<br>

## 3. Binary Tree Representation

### 3.1 Array Representation

Store element at array position corresponding to its node number in the complete binary tree:

```
tree[] = [ _, a, b, c, d, e, f, g, h, i, j ]
            1  2  3  4  5  6  7  8  9  10
```

**Space requirements:**
- Complete binary tree: exactly $n + 1$ slots
- Right-skewed tree of height $h$: needs $2^h$ slots (wastes the most space)
- An $n$-node binary tree needs between $h + 1$ and $2^h$ slots

### 3.2 Linked Representation

Each node is an object with three fields:
- `leftChild` pointer
- `element` (data)
- `rightChild` pointer

```
struct BinaryTreeNode {
    T element;
    BinaryTreeNode* leftChild;
    BinaryTreeNode* rightChild;
};
```

Space required: $n \times \text{sizeof(BinaryTreeNode)}$ for $n$ nodes.

> **Key Point:** Linked representation is **the most popular** way to represent binary trees because it efficiently handles dynamic trees of any shape. Array representation is best for **complete binary trees** (especially heaps).

---

<br>

## 4. Binary Tree Traversals

A **traversal** visits each element of the binary tree **exactly once**. During each visit, all actions (copy, display, evaluate, etc.) are performed.

### 4.1 Preorder Traversal

**Order:** root, left, right

```
Preorder(node):
    if node is null: return
    visit(node)
    Preorder(node.left)
    Preorder(node.right)
```

**Example:** For expression tree `/ * + a b - c d + e f`, preorder gives the **prefix** form: `/ * + a b - c d + e f`

### 4.2 Inorder Traversal

**Order:** left, root, right

```
Inorder(node):
    if node is null: return
    Inorder(node.left)
    visit(node)
    Inorder(node.right)
```

**Example:** Inorder traversal of an expression tree gives the **infix** form: `a + b * c - d / e + f`

### 4.3 Postorder Traversal

**Order:** left, right, root

```
Postorder(node):
    if node is null: return
    Postorder(node.left)
    Postorder(node.right)
    visit(node)
```

**Example:** Postorder traversal of an expression tree gives the **postfix** form: `a b + c d - * e f + /`

### 4.4 Level-Order Traversal

**Order:** Level by level, left to right within each level. Uses a **queue**:

```
LevelOrder(root):
    if root is null: return
    queue.enqueue(root)
    while queue is not empty:
        node = queue.dequeue()
        visit(node)
        if node.left: queue.enqueue(node.left)
        if node.right: queue.enqueue(node.right)
```

> **Key Point:** Preorder, inorder, and postorder use **recursion** (or a stack). Level-order uses a **queue**. All four traversals visit $n$ nodes in $O(n)$ time.

---

<br>

## 5. Expression Trees

### 5.1 Definition

An **expression tree** is a binary tree where:
- Each **internal node** corresponds to an **operator** (+, -, *, /)
- Each **leaf node** corresponds to an **operand** (a variable or number)

**Example:** The expression `3 + ((5 + 9) * 2)` is represented as:

```
        +
       / \
      3   *
         / \
        +   2
       / \
      5   9
```

### 5.2 Traversal and Expression Forms

| Traversal | Expression Form | Example Output |
|:----------|:---------------|:---------------|
| Preorder | **Prefix** (Polish notation) | `+ 3 * + 5 9 2` |
| Inorder | **Infix** (standard notation) | `3 + 5 + 9 * 2` |
| Postorder | **Postfix** (Reverse Polish) | `3 5 9 + 2 * +` |

> **Key Point:** Inorder traversal of an expression tree without parentheses can be ambiguous. A **fully parenthesized** inorder traversal adds parentheses before each left subtree and after each right subtree.

---

<br>

## Summary

| Concept | Key Point |
|:--------|:----------|
| Binary Tree | Finite collection with root, left subtree, right subtree; max degree 2 |
| Node Degree | Number of children a node has |
| Tree Degree | Maximum of all node degrees |
| $n-1$ Edges | A binary tree with $n > 0$ nodes has exactly $n-1$ edges |
| Height Bounds | $\lceil \log_2(n+1) \rceil \leq h \leq n$ |
| Full Binary Tree | Height $h$, exactly $2^h - 1$ nodes |
| Complete Binary Tree | All levels full except possibly the last; last level left-filled |
| Array Representation | Node $x$ at index $x$; parent at $\lfloor x/2 \rfloor$, children at $2x$ and $2x+1$ |
| Linked Representation | Most common; each node has leftChild, element, rightChild |
| Preorder | root, left, right — prefix expression |
| Inorder | left, root, right — infix expression |
| Postorder | left, right, root — postfix expression |
| Level-Order | Uses a queue; processes level by level |
| Expression Tree | Internal nodes = operators, leaves = operands |

---

<br>

## Appendix

### Traversal Time Complexity

All four traversals (preorder, inorder, postorder, level-order) have $O(n)$ time complexity since each node is visited exactly once.

### Common Binary Tree Operations

- Determine height: $O(n)$ using postorder
- Count nodes: $O(n)$ using any traversal
- Copy tree: $O(n)$ using postorder
- Check equality: $O(n)$ comparing two trees
- Evaluate expression: $O(n)$ using postorder

### Interview Tips

- Know how to reconstruct a binary tree from two traversals (e.g., preorder + inorder)
- Understand the difference between full, complete, and perfect binary trees
- Level-order traversal is the basis for BFS on trees
