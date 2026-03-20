# Chapter 10 — Binary Search Trees

> **Last Updated:** 2026-03-21

---

## Table of Contents

- [1. Binary Search Tree Definition](#1-binary-search-tree-definition)
  - [1.1 Definition and Properties](#11-definition-and-properties)
  - [1.2 Examples](#12-examples)
  - [1.3 Representation](#13-representation)
- [2. BST Operations](#2-bst-operations)
  - [2.1 Search](#21-search)
  - [2.2 Insert](#22-insert)
  - [2.3 Delete](#23-delete)
- [3. BST Height Analysis](#3-bst-height-analysis)
  - [3.1 Best Case](#31-best-case)
  - [3.2 Worst Case](#32-worst-case)
- [4. Indexed Binary Search Tree](#4-indexed-binary-search-tree)
  - [4.1 Definition](#41-definition)
  - [4.2 Rank-Based Operations](#42-rank-based-operations)
- [5. BST with Duplicates](#5-bst-with-duplicates)
- [Summary](#summary)
- [Appendix](#appendix)

---

<br>

## 1. Binary Search Tree Definition

### 1.1 Definition and Properties

A **binary search tree (BST)** is a binary tree that may be empty. A nonempty BST satisfies:

1. Each node has a key (or value), and **all keys are distinct**
2. For every node $x$, all keys in the **left subtree** of $x$ are **smaller** than the key in $x$
3. For every node $x$, all keys in the **right subtree** of $x$ are **larger** than the key in $x$
4. The left and right subtrees of the root are also binary search trees

> **Key Point:** The BST property is recursive: every subtree is itself a valid BST. An **inorder traversal** of a BST outputs the keys in **ascending** (sorted) order.

### 1.2 Examples

```
    30            60
   /  \            \
  5    40          70
 / \              /  \
2   -            65   80
```

Tree (b) with root 30 is a BST: left subtree keys {2, 5} < 30 < {40} right subtree. Tree (c) with root 60 is a BST. However, a tree where the left subtree contains a key larger than the root is **not** a BST.

### 1.3 Representation

Since the number of elements and the shape of a BST change dynamically with insertions and deletions, BSTs are usually represented using the **linked representation** (each node has `leftChild`, `element`, `rightChild` pointers).

---

<br>

## 2. BST Operations

### 2.1 Search

To search for a key $k$ in a BST:

1. Start at the **root**
2. If the root is NULL, the search **fails** (key not found)
3. If $k <$ root's key, search the **left subtree**
4. If $k >$ root's key, search the **right subtree**
5. If $k =$ root's key, the search **succeeds**

```cpp
Node* search(Node* node, int key) {
    if (node == nullptr || node->key == key)
        return node;
    if (key < node->key)
        return search(node->left, key);
    else
        return search(node->right, key);
}
```

**Time complexity:** $O(h)$ where $h$ is the height of the tree.

### 2.2 Insert

To insert a new element with key $k$:

1. **Search** for $k$ in the BST
2. If the search is **successful** (key already exists), **do not insert** (duplicate)
3. If the search is **unsuccessful**, insert the new element at the point where the search terminated

```cpp
Node* insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    // If key == node->key, do nothing (no duplicates)
    return node;
}
```

**Time complexity:** $O(h)$ — the insertion point is always at a leaf or null pointer.

### 2.3 Delete

Deletion has **three cases** depending on the node being deleted:

**Case 1: Leaf node (degree 0)**
- Simply remove the node by setting its parent's pointer to NULL

**Case 2: Degree 1 node (one child)**
- Replace the node with its single child (the child takes the node's position)

**Case 3: Degree 2 node (two children)**
- Replace the node's key with either:
  - The **largest key in the left subtree** (inorder predecessor), OR
  - The **smallest key in the right subtree** (inorder successor)
- Then delete the predecessor/successor node (which is guaranteed to be degree 0 or 1)

**Finding the inorder predecessor:** Move to the left child, then follow right-child pointers until reaching a node whose right-child pointer is NULL.

**Finding the inorder successor:** Move to the right child, then follow left-child pointers until reaching a node whose left-child pointer is NULL.

**Time complexity:** $O(h)$ for all three cases.

> **Key Point:** Case 3 is the trickiest. The replacement key (inorder predecessor or successor) is always in a node with degree 0 or 1, reducing Case 3 to Case 1 or Case 2.

---

<br>

## 3. BST Height Analysis

All BST operations (search, insert, delete) have time complexity $O(h)$ where $h$ is the tree height.

### 3.1 Best Case

A balanced BST with $n$ nodes has height $h = \lceil \log_2(n+1) \rceil$, giving $O(\log n)$ operations.

This occurs when keys are inserted in a balanced order (e.g., median first, then medians of subarrays, etc.).

### 3.2 Worst Case

A degenerate (skewed) BST with $n$ nodes has height $h = n$, giving $O(n)$ operations.

This occurs when keys are inserted in **sorted order** (ascending or descending), producing a linked list structure.

| Scenario | Height | Operation Time |
|:---------|:-------|:---------------|
| Best case (balanced) | $O(\log n)$ | $O(\log n)$ |
| Worst case (skewed) | $O(n)$ | $O(n)$ |
| Average case (random) | $O(\log n)$ | $O(\log n)$ |

> **Key Point:** To guarantee $O(\log n)$ height, use self-balancing BSTs such as AVL trees, Red-Black trees, or B-trees.

---

<br>

## 4. Indexed Binary Search Tree

### 4.1 Definition

An **indexed BST** adds a `leftSize` field to each node, which stores the number of elements in its left subtree + 1 (i.e., the **rank** of the node within its subtree).

```
         8 [20]         <- leftSize=8, key=20
        /       \
    4 [10]     3 [40]
    /    \     /    \
 1[6]  1[15] 1[30]  0[42]
```

### 4.2 Rank-Based Operations

With the `leftSize` field, we can perform:
- **Find by rank** (get the $k$-th smallest element) in $O(h)$
- **Rank of a key** in $O(h)$

These operations are not efficient on a standard BST without the index.

---

<br>

## 5. BST with Duplicates

To allow duplicate keys in a BST, modify the definition:
1. Replace "smaller" with "smaller or equal to" in property 2
2. Replace "larger" with "larger or equal to" in property 3

This allows multiple nodes with the same key value.

---

## Summary

| Concept | Key Point |
|:--------|:----------|
| BST Definition | Left subtree keys < root < right subtree keys; recursive |
| Inorder Traversal | Produces keys in ascending order |
| Search | $O(h)$ — compare and recurse left or right |
| Insert | $O(h)$ — search to find the insertion point |
| Delete Leaf | Simply remove the node |
| Delete Degree 1 | Replace with the single child |
| Delete Degree 2 | Replace with inorder predecessor or successor |
| Best Height | $O(\log n)$ — balanced tree |
| Worst Height | $O(n)$ — degenerate (sorted insertion) |
| Indexed BST | `leftSize` field enables rank-based queries in $O(h)$ |

---

## Appendix

### Comparison with Other Dictionary Structures

| Structure | Search | Insert | Delete |
|:----------|:-------|:-------|:-------|
| Sorted array | $O(\log n)$ | $O(n)$ | $O(n)$ |
| Skip list | $O(\log n)$ avg | $O(\log n)$ avg | $O(\log n)$ avg |
| Hash table (chaining) | $O(1)$ avg | $O(1)$ avg | $O(1)$ avg |
| BST | $O(\log n)$ avg | $O(\log n)$ avg | $O(\log n)$ avg |
| Balanced BST (AVL/RB) | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ |

BSTs are particularly ideal for **sequential access** (inorder traversal) and **rank-based queries**, which hash tables cannot efficiently support.

### Interview Tips

- Know all three delete cases and be able to trace through examples
- Understand when a BST degenerates and how balanced BSTs prevent it
- Inorder traversal of a BST is a classic way to verify the BST property
