# Chapter 03 — Arrays and Linked Lists

> **Last Updated:** 2026-03-21

---

## Table of Contents

1. [Linear Lists](#1-linear-lists)
2. [Array Representation](#2-array-representation)
3. [Linked Representation](#3-linked-representation)
4. [Singly Linked Lists](#4-singly-linked-lists)
5. [Doubly Linked Lists](#5-doubly-linked-lists)
6. [Circular Lists](#6-circular-lists)
7. [Comparison: Array vs. Linked List](#7-comparison-array-vs-linked-list)
8. [Summary](#summary)
9. [Appendix](#appendix)

---

## 1. Linear Lists

### 1.1 Definition

A **linear list** (or ordered list) is a data object of the form $(e_1, e_2, \ldots, e_n)$ where:
- $e_i$ is the $i$-th element
- $n \geq 0$ is the number of elements (finite)
- $e_1$ is the first element, $e_n$ is the last

### 1.2 ADT Operations

| Operation | Description |
|-----------|-------------|
| `empty()` | Check if the list is empty |
| `size()` | Return the number of elements |
| `get(index)` | Return element at given index |
| `indexOf(element)` | Return index of first occurrence |
| `insert(index, element)` | Insert element at given index |
| `erase(index)` | Remove element at given index |

---

## 2. Array Representation

### 2.1 Formula-Based Representation

Using a one-dimensional array with a mapping formula:
$$\text{location}(i) = i - 1 \quad \text{(0-indexed)}$$

Element $e_i$ is stored at `array[i-1]`.

### 2.2 Operation Complexities

| Operation | Time Complexity |
|-----------|----------------|
| `get(index)` | $O(1)$ |
| `indexOf(element)` | $O(n)$ |
| `insert(index, element)` | $O(n)$ (shifting) |
| `erase(index)` | $O(n)$ (shifting) |

### 2.3 Insert Operation

Inserting at position $k$ requires shifting elements $k, k+1, \ldots, n-1$ one position to the right:

```cpp
// Insert element at index k
for (int i = size - 1; i >= k; i--)
    arr[i + 1] = arr[i];  // Shift right
arr[k] = element;
size++;
```

Worst case (insert at 0): $O(n)$ shifts. Best case (insert at end): $O(1)$.

### 2.4 Dynamic Arrays

When the array is full, allocate a **new array of double the size** and copy elements:
- Individual worst case: $O(n)$
- Amortized cost per insertion: $O(1)$

---

## 3. Linked Representation

### 3.1 Node Structure

Each node contains:
- **Data field**: stores the element
- **Link (pointer) field**: points to the next node

```cpp
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(const T& d, Node<T>* n = nullptr) : data(d), next(n) {}
};
```

### 3.2 Advantages over Arrays

- Dynamic size (no pre-allocation)
- Efficient insertion/deletion at known positions: $O(1)$
- No wasted space from unused capacity

### 3.3 Disadvantages

- No random access: $O(n)$ to reach element $i$
- Extra memory for pointers
- Cache-unfriendly (nodes scattered in memory)

---

## 4. Singly Linked Lists

### 4.1 Structure

```
head -> [data|next] -> [data|next] -> [data|next] -> nullptr
```

### 4.2 Key Operations

**Insertion at front**: $O(1)$
```cpp
Node<T>* newNode = new Node<T>(value);
newNode->next = head;
head = newNode;
```

**Deletion at front**: $O(1)$
```cpp
Node<T>* temp = head;
head = head->next;
delete temp;
```

**Search**: $O(n)$
```cpp
Node<T>* curr = head;
while (curr != nullptr) {
    if (curr->data == target) return curr;
    curr = curr->next;
}
return nullptr;
```

**Insertion after a given node**: $O(1)$
```cpp
Node<T>* newNode = new Node<T>(value);
newNode->next = prev->next;
prev->next = newNode;
```

---

## 5. Doubly Linked Lists

### 5.1 Node Structure

```cpp
template <typename T>
struct DNode {
    T data;
    DNode<T>* prev;
    DNode<T>* next;
};
```

### 5.2 Advantages

- Traversal in both directions
- Deletion of a known node in $O(1)$ (no need to find predecessor)
- Useful for undo operations, browser history, etc.

### 5.3 Trade-off

Extra pointer per node (more memory) but bidirectional traversal and simpler deletion.

---

## 6. Circular Lists

### 6.1 Circular Singly Linked List

The last node's `next` pointer points back to the first node instead of `nullptr`.

### 6.2 Use Cases

- Round-robin scheduling
- Circular buffers
- Josephus problem

---

## 7. Comparison: Array vs. Linked List

| Feature | Array | Linked List |
|---------|-------|-------------|
| Access by index | $O(1)$ | $O(n)$ |
| Insert at front | $O(n)$ | $O(1)$ |
| Insert at end | $O(1)$ amortized | $O(1)$ with tail pointer |
| Insert at middle | $O(n)$ | $O(1)$ after finding position |
| Delete at front | $O(n)$ | $O(1)$ |
| Memory overhead | None (contiguous) | Extra pointer per node |
| Cache performance | Excellent | Poor |
| Memory allocation | Contiguous block | Scattered |

---

## Summary

| Concept | Key Point |
|---------|-----------|
| Linear List | Ordered collection $(e_1, \ldots, e_n)$ |
| Array | Direct access $O(1)$; insert/delete $O(n)$ |
| Singly linked list | Sequential access; efficient insert/delete at known positions |
| Doubly linked list | Bidirectional traversal; $O(1)$ deletion of known node |
| Circular list | Last node links back to first; useful for cyclic processes |
| Dynamic array | Amortized $O(1)$ append via doubling strategy |

---

## Appendix

### Iterator Design Pattern

Iterators provide a uniform way to traverse both arrays and linked lists:

```cpp
template <typename T>
class LinkedListIterator {
    Node<T>* current;
public:
    LinkedListIterator(Node<T>* node) : current(node) {}
    T& operator*() { return current->data; }
    LinkedListIterator& operator++() { current = current->next; return *this; }
    bool operator!=(const LinkedListIterator& other) { return current != other.current; }
};
```

### Common Interview Questions

1. **Reverse a linked list** (iterative and recursive)
2. **Detect a cycle** (Floyd's tortoise and hare algorithm)
3. **Find the middle element** (two-pointer technique)
4. **Merge two sorted linked lists**
