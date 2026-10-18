# Lecture 10 — Binary Search Trees

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-18

> **Learning Objectives:**
> 1. Implement binary search tree (BST) operations (insert, delete, search)
> 2. Analyze BST performance in balanced and degenerate cases
> 3. Explain why self-balancing trees (AVL trees, Red-Black trees) are needed
> 4. Find elements by rank using the `leftSize` field of an indexed BST

---

## Table of Contents

- [1. Binary Search Tree Definition](#1-binary-search-tree-definition)
  - [1.1 Search Trees and Dictionaries](#11-search-trees-and-dictionaries)
  - [1.2 Definition and Properties](#12-definition-and-properties)
  - [1.3 Examples](#13-examples)
  - [1.4 Representation](#14-representation)
- [2. BST Operations](#2-bst-operations)
  - [2.1 Ascending Output](#21-ascending-output)
  - [2.2 Search](#22-search)
  - [2.3 Insert](#23-insert)
  - [2.4 Delete](#24-delete)
- [3. BST Height Analysis](#3-bst-height-analysis)
  - [3.1 Best Case](#31-best-case)
  - [3.2 Worst Case](#32-worst-case)
- [4. Indexed Binary Search Tree](#4-indexed-binary-search-tree)
  - [4.1 Definition](#41-definition)
  - [4.2 Rank-Based Operations](#42-rank-based-operations)
- [5. BST with Duplicates](#5-bst-with-duplicates)
- [6. Appendix](#6-appendix)
  - [6.1 Comparison with Other Dictionary Structures](#61-comparison-with-other-dictionary-structures)
  - [6.2 Interview Tips](#62-interview-tips)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Binary Search Tree Definition

### 1.1 Search Trees and Dictionaries

A **search tree** is a structure well suited to implementing the dictionaries of Lecture 7.

- Search trees give similar or better performance than skip lists and hash tables. Their average performance does not match the $O(1)$ of hash tables, but a search tree that stays balanced guarantees $O(\log n)$ even in the worst case (Section 6.1).
- Search trees are particularly suited to accessing data sequentially in key order or by rank.

### 1.2 Definition and Properties

A **binary search tree (BST)** is a binary tree that may be empty. A nonempty BST satisfies the following.

1. Each node has a key (or value), and no two nodes have the same key, that is, **all keys are distinct**.
2. For every node $x$, all keys in the **left subtree** of $x$ are **smaller** than the key in $x$.
3. For every node $x$, all keys in the **right subtree** of $x$ are **larger** than the key in $x$.
4. The left and right subtrees of the root are also binary search trees.

Properties 2 and 3 are conditions on all keys of a subtree, not on a single child.

> **Key Point:** The BST property is recursive, so every subtree is itself a valid BST. An **inorder traversal** of a BST outputs the keys in **ascending** (sorted) order.

### 1.3 Examples

```text
(a)      20
       /    \
     15      25
    /  \       \
  12    10      22
```

*Figure 1. Binary tree (a), which is not a BST*

```text
    30            60
   /  \            \
  5    40          70
 / \              /  \
2   -            65   80
```

*Figure 2. Binary trees (b) and (c), which are BSTs*

Of the three binary trees in Figures 1 and 2, (b) and (c) are BSTs. Tree (b) with root 30 is a BST: left subtree keys {2, 5} < 30 < {40} right subtree. The left child 2 of 5 is smaller than 5, and its right child is empty (-). Tree (c) with root 60 is a BST. The right subtree keys {65, 70, 80} of 60 are all larger than 60, and the left child 65 and right child 80 of 70 also satisfy the properties.

Tree (a) is **not** a BST. The right child 10 of 15 is smaller than 15, and the right child 22 of 25 is smaller than 25, so it violates property 3. In this way, a tree is not a BST if any subtree contains even one key that violates the properties. For example, a tree where the left subtree contains a key larger than the root violates property 2, so it is not a BST.

### 1.4 Representation

Since the number of elements and the shape of a BST change dynamically with insertions and deletions, BSTs are usually represented using the **linked representation** (each node has an `element` and two child pointers `leftChild` and `rightChild`).

The code of this lecture simplifies the element to a single integer key and uses the following node structure.

```cpp
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};
```

`left` and `right` point to the left and right children, and they are `nullptr` when the child does not exist. The constructor makes the new node a leaf with no children.

---

<br>

## 2. BST Operations

### 2.1 Ascending Output

The operation that outputs all elements in ascending order of keys (ascend) is an inorder traversal (left, root, right). By properties 2 and 3, all keys in the left subtree of each node are smaller than the node's key and all keys in the right subtree are larger, so outputting the whole left subtree first, then the node, then the right subtree gives sorted order. Each node is visited once, so the time is $O(n)$.

```text
              20
           /      \
         10        40
        /  \      /
       6    15   30
      / \       /
     2   8     25
```

*Figure 3. The BST used in the examples of Sections 2.1 and 2.3*

An inorder traversal of the BST in Figure 3 outputs 2, 6, 8, 10, 15, 20, 25, 30, 40.

### 2.2 Search

To search for a key $k$ in a BST:

1. Start at the **root**.
2. If the root is NULL, the tree is empty and the search **fails** (key not found).
3. If $k <$ root's key, search the **left subtree**.
4. If $k >$ root's key, search the **right subtree**.
5. If $k =$ root's key, the search **succeeds** and terminates.

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

The function returns the node if the key is found and `nullptr` otherwise. Each recursive call moves down one level, so the number of nodes visited is at most the height of the tree.

**Time complexity:** $O(h)$ where $h$ is the height of the tree.

### 2.3 Insert

To insert a new element with key $k$:

1. **Search** for $k$ in the BST.
2. If the search is **successful** (key already exists), it is a duplicate, so **do not insert**.
3. If the search is **unsuccessful**, insert the new element at the point where the search terminated.

The new element is inserted where the search failed because that point is where the new key belongs. At each node on the search path, left or right was chosen by comparing with the new key, so attaching the new node as a leaf at the empty pointer at the end of the path keeps properties 2 and 3 for every node on the path. Also, a later search for the same key follows the same path and arrives at this point.

Inserting 35, 7, 18, and 40 in turn into the BST of Figure 3 proceeds as follows.

- 35 is larger than 20, smaller than 40, and larger than 30. The search fails at the right child slot of 30, so 35 is inserted there.
- 7 is compared with 20, 10, 6, and 8, and the search fails at the left child slot of 8, so 7 is inserted there. This insertion goes down to the deepest level, which is the worst case, and its time is $O(h)$.
- 18 is compared with 20, 10, and 15 and goes into the right child slot of 15.
- 40 is not inserted, because the search succeeds at the right child of the root.

```text
                20
            /        \
          10          40
        /    \       /
       6      15    30
      / \       \   / \
     2   8      18 25  35
        /
       7
```

*Figure 4. The result of inserting 35, 7, and 18 into the BST of Figure 3*

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

`insert` returns the root of the subtree, and the caller reconnects that value to its child pointer. When it reaches an empty slot (`nullptr`), it creates and returns a new node, so the parent of that slot comes to point to the new node.

**Time complexity:** $O(h)$. The insertion point is always the null pointer where the search terminated, and the new node is attached there as a leaf.

### 2.4 Delete

Deletion has **three cases** depending on the node being deleted.

**Case 1: Leaf node (degree 0)**
- Remove the node by setting its parent's pointer to NULL.

**Case 2: Degree 1 node (one child)**
- Replace the node with its single child; that is, the one nonempty subtree takes the node's position. If the node being deleted is the root, its child becomes the new root.

**Case 3: Degree 2 node (two children)**
- Replace the node's key with one of the following.
  - The **largest key in the left subtree** (inorder predecessor)
  - The **smallest key in the right subtree** (inorder successor)
- Then delete the predecessor or successor node from which the key was taken. This node is guaranteed to have degree 0 or 1.

**Finding the inorder predecessor:** Move to the left child, then follow right-child pointers until reaching a node whose right-child pointer is NULL.

**Finding the inorder successor:** Move to the right child, then follow left-child pointers until reaching a node whose left-child pointer is NULL.

The node with the largest key in the left subtree has no right child, because a right child would have a larger key. For the same reason, the node with the smallest key in the right subtree has no left child.

The three cases are illustrated in turn on the tree of Figure 4.

- **Case 1:** Deleting the leaf 7 sets the left pointer of 8 to NULL. Then deleting the leaf 35 sets the right pointer of 30 to NULL.
- **Case 2:** In the tree with 7 and 35 deleted, the degree 1 nodes are 40 (left child 30), 30 (left child 25), and 15 (right child 18). Deleting 40 lets 30 take the position of 40, so 30 becomes the right child of 20. Then deleting 15 makes 18 the right child of 10.
- **Case 3:** Back in the tree of Figure 4, the degree 2 nodes are 20, 10, 6, and 30. To delete 10 by replacing it with the largest key in the left subtree, go from the left child 6 of 10 to the right until 8, whose right pointer is NULL, so 8 is the replacement key. Put 8 in the place of 10 and delete the original node of 8 (a degree 1 node with the left child 7) by Case 2, which makes 7 the right child of 6. Figure 5 shows the result.

```text
                20
            /        \
           8          40
        /    \       /
       6      15    30
      / \       \   / \
     2   7      18 25  35
```

*Figure 5. The result of deleting 10 from the tree of Figure 4 by replacing it with the largest key in the left subtree*

Deleting the root 20 from the tree of Figure 4 gives different results for the two methods. The largest key in the left subtree is 18, found by following right pointers from 10 through 15 to 18. Moving 18 to the root and deleting the original leaf of 18 sets the right pointer of 15 to NULL. The smallest key in the right subtree is 25, found by following left pointers from 40 through 30 to 25. Moving 25 to the root and deleting the original leaf of 25 sets the left pointer of 30 to NULL. Both results are BSTs, since their inorder traversals are sorted as 2, 6, 7, 8, 10, 15, 18, 25, 30, 35, 40.

The following delete function uses the largest key in the left subtree for Case 3.

```cpp
// Deletes the node with key and returns the new root of the subtree
Node* erase(Node* node, int key) {
    if (node == nullptr) return nullptr;            // key not found
    if (key < node->key) {
        node->left = erase(node->left, key);
    } else if (key > node->key) {
        node->right = erase(node->right, key);
    } else if (node->left != nullptr && node->right != nullptr) {
        Node* pred = node->left;                    // Case 3: max of left subtree
        while (pred->right != nullptr) pred = pred->right;
        node->key = pred->key;                      // copy the key
        node->left = erase(node->left, pred->key);  // delete the original node
    } else {
        Node* child = (node->left != nullptr) ? node->left : node->right;
        delete node;                                // Cases 1 and 2
        return child;                               // nullptr for a leaf
    }
    return node;
}
```

If the key is smaller or larger than the current node's key, the function deletes recursively in that subtree and reconnects the returned new subtree root to the child pointer. If the key matches and the node has two children, it follows right pointers to the end of the left subtree to find the node `pred` with the largest key, copies that key into the current node, and then deletes that key from the left subtree. If the node has at most one child, it frees the node and returns the remaining child (`nullptr` for a leaf), so the parent points directly to that child. Calling `erase(root, 10)` on the tree of Figure 4 produces the tree of Figure 5.

**Time complexity:** $O(h)$ for all three cases. Finding the node to delete takes $O(h)$, and in Case 3 finding the replacement key and deleting its node takes another $O(h)$.

> **Key Point:** Case 3 is the trickiest. The replacement key (inorder predecessor or successor) is always in a node with degree 0 or 1, reducing Case 3 to Case 1 or Case 2.

---

<br>

## 3. BST Height Analysis

All BST operations (search, insert, delete) have time complexity $O(h)$ where $h$ is the tree height. Height in this section is the number of levels (the root is level 1), as defined in Lecture 8.

### 3.1 Best Case

A BST with $n$ nodes has height at least $\lceil \log_2(n+1) \rceil$. This is because a binary tree of height $h$ has at most $2^h - 1$ nodes, so $n \leq 2^h - 1$ (Lecture 8). A well-balanced BST, shaped like a complete binary tree, reaches this minimum height $h = \lceil \log_2(n+1) \rceil$, giving $O(\log n)$ operations.

This occurs when keys are inserted in a balanced order (e.g., median first, then medians of subarrays, etc.).

### 3.2 Worst Case

A degenerate (skewed) BST with $n$ nodes has height $h = n$, giving $O(n)$ operations.

This occurs when keys are inserted in **sorted order** (ascending or descending), producing a linked list structure.

| Scenario | Height | Operation Time |
|:---------|:-------|:---------------|
| Best case (balanced) | $O(\log n)$ | $O(\log n)$ |
| Worst case (skewed) | $O(n)$ | $O(n)$ |
| Average case (random) | $O(\log n)$ | $O(\log n)$ |

*Table 1. Height and operation time by BST shape*

> **Key Point:** To guarantee $O(\log n)$ height, use self-balancing BSTs such as AVL trees or Red-Black trees. B-trees, which keep several keys in one node, are balanced multiway search trees rather than binary trees, and they serve the same purpose.

---

<br>

## 4. Indexed Binary Search Tree

### 4.1 Definition

An **indexed BST** is a BST that adds a `leftSize` field to each node, and `leftSize` stores the number of elements in the node's left subtree. Since all elements of the left subtree are smaller than the node, `leftSize` equals the **rank** of the node within the subtree rooted at it, counted from 0 (its index).

```text
         8 [20]         <- leftSize=8, key=20
        /       \
    4 [10]     3 [40]
    /    \     /    \
 1[6]  1[15] 1[30]  0[42]
```

*Figure 6. The top three levels of an indexed BST with the leftSize and [key] of each node*

Figure 6 shows the top three levels of an indexed BST with 15 keys. Below them, 6 has the children 2 and 8, 8 has the left child 7, 15 has the children 12 and 18, 30 has the children 25 and 35, and 42 has the right child 43. Among these nodes, only 8, which has the left child 7, has `leftSize` 1, and the others have 0. Listing the keys in ascending order gives Table 2, and the `leftSize` 8 of the root 20 equals the index of 20 in sorted order.

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
| Key | 2 | 6 | 7 | 8 | 10 | 12 | 15 | 18 | 20 | 25 | 30 | 35 | 40 | 42 | 43 |

*Table 2. Sorted order and indices of the keys in the indexed BST of Figure 6*

### 4.2 Rank-Based Operations

With the `leftSize` field, we can perform the following.
- **Find by rank:** get the element with a given index counted from 0, that is, the $k$-th smallest element, in $O(h)$ time.
- **Rank of a key:** find the position of a given key in sorted order in $O(h)$ time.

These operations are not efficient on a standard BST without the index. A standard BST must count from the front by an inorder traversal, which takes $O(n)$.

**Find by rank:** To find the element whose index is `index`, do the following at each node $x$.
- If `index` equals the `leftSize` of $x$, $x$ is the answer.
- If `index` is smaller than `leftSize`, the element is in the left subtree, so go down to the left.
- If `index` is larger than `leftSize`, the `leftSize` elements of the left subtree and $x$ itself must be skipped, so subtract `leftSize + 1` from `index` and go down to the right.

```cpp
// Finds the node holding the element with the given 0-based index in ascending order
INode* get(INode* node, int index) {
    while (node != nullptr) {
        if (index == node->leftSize) return node;   // current node
        if (index < node->leftSize) {
            node = node->left;                      // in the left subtree
        } else {
            index -= node->leftSize + 1;            // skip left subtree and current node
            node = node->right;
        }
    }
    return nullptr;                                 // index out of range
}
```

`INode` is the node structure `Node` with an added integer field `leftSize`. The $k$-th smallest element counted from 1 is the element with index $k - 1$. For example, to find the element with index 9 in the tree of Figure 6, at the root 20 we have $9 > 8$, so the index becomes $9 - 8 - 1 = 0$ and we go right to 40. At 40, $0 < 3$, so we go left to 30; at 30, $0 < 1$, so we go left to 25; and at 25, $0 = 0$, so 25 is the answer. In Table 2, the key with index 9 is also 25.

**Rank of a key:** While searching for the key, add `leftSize + 1` of the node passed each time we go down to the right, and add the node's `leftSize` when the key is found. For example, searching for 35 adds $8 + 1 = 9$ when going right at 20, goes left at 40, and adds $1 + 1 = 2$ when going right at 30. Adding the `leftSize` 0 at 35 gives the rank $9 + 2 + 0 = 11$, which equals the index of 35 in Table 2.

**Maintaining leftSize:** On insertion, `leftSize` increases by 1 at each node where the search path goes left, and on deletion, it decreases by 1 at each node where the path to the physically removed node goes left. Therefore insert and delete remain $O(h)$ with `leftSize` maintained.

---

<br>

## 5. BST with Duplicates

To allow duplicate keys in a BST, remove the requirement that all keys be distinct (property 1) and modify the definition as follows.
1. Replace "smaller" with "smaller or equal to" in property 2.
2. Replace "larger" with "larger or equal to" in property 3.

This allows multiple nodes with the same key value. Insertion then does not stop at an equal key but keeps going down into a fixed side (for example, the right subtree) and puts the new node in the empty slot.

---

<br>

## 6. Appendix

### 6.1 Comparison with Other Dictionary Structures

| Structure | Search | Insert | Delete |
|:----------|:-------|:-------|:-------|
| Sorted array | $O(\log n)$ | $O(n)$ | $O(n)$ |
| Skip list | $O(\log n)$ avg | $O(\log n)$ avg | $O(\log n)$ avg |
| Hash table (chaining) | $O(1)$ avg | $O(1)$ avg | $O(1)$ avg |
| BST | $O(\log n)$ avg | $O(\log n)$ avg | $O(\log n)$ avg |
| Balanced BST (AVL/RB) | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ |

*Table 3. Time complexity of search, insert, and delete by dictionary structure*

The structures marked avg are slower in the worst case. For example, a BST takes $O(n)$ when it degenerates as in Section 3.2. A balanced BST takes $O(\log n)$ even in the worst case.

BSTs are particularly ideal for **sequential access** (inorder traversal) and **rank-based queries**, which hash tables cannot efficiently support.

### 6.2 Interview Tips

- Know all three delete cases and be able to trace through examples.
- Understand when a BST degenerates and how balanced BSTs prevent it.
- Checking that the inorder traversal of a BST is in ascending order is a classic way to verify the BST property.

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:----------|
| BST Definition | At every node, the keys in the left subtree are smaller than the node's key and the keys in the right subtree are larger, and this holds recursively in every subtree. |
| Inorder Traversal | An inorder traversal of a BST outputs the keys in ascending order. |
| Search | Done in $O(h)$ by comparing keys and recursing left or right. |
| Insert | Done in $O(h)$ by searching for the insertion point and attaching the new node as a leaf at the null pointer where the search failed. |
| Delete Leaf | Remove the node by setting its parent's pointer to NULL. |
| Delete Degree 1 | Replace the node with its single child. |
| Delete Degree 2 | Replace the key with the inorder predecessor or successor and then delete that node (degree 0 or 1). |
| Best Height | A balanced tree has height $\lceil \log_2(n+1) \rceil$, that is, $O(\log n)$. |
| Worst Height | A degenerate tree built by sorted insertion has height $n$, that is, $O(n)$. |
| Indexed BST | The `leftSize` field (number of elements in the left subtree) enables rank-based queries in $O(h)$. |
| BST with Duplicates | Including equality in the inequalities of properties 2 and 3 allows several copies of the same key. |

---

<br>

## Self-Check Questions

1. **Is it a BST?** In a binary tree, the root 50 has the left child 30 and the right child 70, and 30 has the right child 60. Is it a BST? Explain what wrong conclusion you reach by comparing only parents and children.

   <details>
   <summary>Answer</summary>

   It is not a BST. Looking only at parent-child pairs, 30 < 50 (left child), 70 > 50 (right child), and 60 > 30 (right child) are all correct, so it is easy to misjudge it as a BST. However, 60 is in the left subtree of 50 and is larger than 50, so it violates property 2. This can also be seen from the inorder traversal 30, 60, 50, 70, which is not in ascending order. Properties 2 and 3 are conditions on the whole subtree, not on a single child.

   </details>

2. **Inorder predecessor and successor:** In the tree of Figure 4, find the inorder predecessor and inorder successor of 30 and of 6.

   <details>
   <summary>Answer</summary>

   The predecessor of 30 starts at the left child 25, whose right pointer is NULL, so it is 25. The successor of 30 starts at the right child 35, whose left pointer is NULL, so it is 35. The predecessor of 6 is the left child 2. The successor of 6 goes to the right child 8 and follows the left pointer to 7, whose left pointer is NULL, so it is 7. These equal the keys immediately before and after each key in the inorder traversal 2, 6, 7, 8, ..., 25, 30, 35.

   </details>

3. **Insertion order and height:** Give one insertion order of the keys 1 through 7 into an empty BST that minimizes the height, and find that height. What is the height if the keys are inserted in descending order?

   <details>
   <summary>Answer</summary>

   Inserting in the order 4, 2, 6, 1, 3, 5, 7 (the median of each range first) gives a full binary tree of 7 nodes with the minimum height $\lceil \log_2 8 \rceil = 3$. Inserting in the order 7, 6, 5, 4, 3, 2, 1 gives a skewed tree in which every node has only a left child, so the height is 7.

   </details>

4. **Indexed BST:** In the indexed BST of Figure 6, use `leftSize` to find the 6th smallest element, and find the rank (index counted from 0) of the key 7.

   <details>
   <summary>Answer</summary>

   The 6th smallest element is the element with index 5. At the root 20, $5 < 8$, so go left to 10. At 10, $5 > 4$, so the index becomes $5 - 4 - 1 = 0$ and go right to 15. At 15, $0 < 1$, so go left to 12, and at 12, $0 = 0$, so the answer is 12. For the rank of 7, go left at 20 and 10, add $1 + 1 = 2$ when going right at 6, go left at 8 to find 7, and add its `leftSize` 0, so the rank is 2. Both results agree with Table 2 (key 12 at index 5, key 7 at index 2).

   </details>
