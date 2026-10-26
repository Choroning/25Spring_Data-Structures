# Lecture 3 — Arrays and Linked Lists

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-26

> **Learning Objectives:**
> 1. Implement array-based and linked list data structures
> 2. Compare the time complexity of array and linked list operations
> 3. Apply iterator patterns for sequential access
> 4. Apply several mapping formulas that store a linear list in an array
> 5. Explain why head nodes and circular lists simplify linked list operations

---

## Table of Contents

- [1. Linear Lists](#1-linear-lists)
  - [1.1 Definition](#11-definition)
  - [1.2 ADT Operations](#12-adt-operations)
- [2. Array Representation](#2-array-representation)
  - [2.1 Formula-Based Representation](#21-formula-based-representation)
  - [2.2 Other Mapping Formulas](#22-other-mapping-formulas)
  - [2.3 Basic Representation: element and listSize](#23-basic-representation-element-and-listsize)
  - [2.4 Operation Complexities](#24-operation-complexities)
  - [2.5 Insert Operation](#25-insert-operation)
  - [2.6 Dynamic Arrays](#26-dynamic-arrays)
  - [2.7 Space Complexity](#27-space-complexity)
- [3. Linked Representation](#3-linked-representation)
  - [3.1 Node Structure](#31-node-structure)
  - [3.2 Difference from Array Representation](#32-difference-from-array-representation)
  - [3.3 Advantages over Arrays](#33-advantages-over-arrays)
  - [3.4 Disadvantages](#34-disadvantages)
- [4. Singly Linked Lists](#4-singly-linked-lists)
  - [4.1 Structure](#41-structure)
  - [4.2 Key Operations](#42-key-operations)
  - [4.3 The Chain Class and Its Operations](#43-the-chain-class-and-its-operations)
  - [4.4 Chain with a Head Node](#44-chain-with-a-head-node)
- [5. Doubly Linked Lists](#5-doubly-linked-lists)
  - [5.1 Node Structure](#51-node-structure)
  - [5.2 Advantages](#52-advantages)
  - [5.3 Trade-off](#53-trade-off)
  - [5.4 Circular Doubly Linked Lists](#54-circular-doubly-linked-lists)
- [6. Circular Lists](#6-circular-lists)
  - [6.1 Circular Singly Linked List](#61-circular-singly-linked-list)
  - [6.2 Use Cases](#62-use-cases)
  - [6.3 Circular Lists and Head Nodes](#63-circular-lists-and-head-nodes)
  - [6.4 Deleting the Nodes of a Circular List](#64-deleting-the-nodes-of-a-circular-list)
  - [6.5 Adding a Node at the Front of a Circular List](#65-adding-a-node-at-the-front-of-a-circular-list)
  - [6.6 Searching with a Head Node](#66-searching-with-a-head-node)
- [7. Application of Linked Lists: Polynomials](#7-application-of-linked-lists-polynomials)
  - [7.1 Polynomial Representation](#71-polynomial-representation)
  - [7.2 Adding Polynomials](#72-adding-polynomials)
  - [7.3 Representation with a Circular List and a Head Node](#73-representation-with-a-circular-list-and-a-head-node)
- [8. Linked Stacks and Queues](#8-linked-stacks-and-queues)
- [9. Comparison: Array vs. Linked List](#9-comparison-array-vs-linked-list)
- [10. Appendix](#10-appendix)
  - [10.1 Iterator Design Pattern](#101-iterator-design-pattern)
  - [10.2 Common Interview Questions](#102-common-interview-questions)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Linear Lists

The two main ways to represent data in data structures are to use an **array** and to use **links**, and a linear list can be represented in either way.

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

*Table 1. Operations of the linear list ADT*

---

<br>

## 2. Array Representation

### 2.1 Formula-Based Representation

Using a one-dimensional array with a mapping formula:
$$\text{location}(i) = i - 1 \quad \text{(0-indexed)}$$

Element $e_i$ is stored at `array[i-1]`.

This formula numbers the elements from 1. If positions in the list are counted from 0 (element 0, element 1, ...), the mapping formula becomes $\text{location}(i) = i$. Here $i$ is the location in the list and $\text{location}(i)$ is the index of the array. For example, storing the list (5, 2, 4, 8, 1) of size 5 in a one-dimensional array `element[]` of length (`arrayLength`) 15 with $\text{location}(i) = i$ places the elements in `element[0]` through `element[4]` in order, as in (a) of Figure 1.

### 2.2 Other Mapping Formulas

Changing the mapping formula stores the same list in different positions of the array.

- **Right-to-left mapping:** $\text{location}(i) = \text{arrayLength} - i - 1$. The list elements are stored backwards beginning at the right end of the array. In (b) of Figure 1, $\text{location}(4) = 15 - 4 - 1 = 10$, so element 1 is in `element[10]` and element 5 is in `element[14]`.
- **Wrap-around mapping:** $\text{location}(i) = (\text{location}(0) + i) \,\%\, \text{arrayLength}$. The elements are stored in order beginning at any position in the array, wrapping around to the front of the array when the end is reached. (c) of Figure 1 is the case $\text{location}(0) = 12$, where $\text{location}(4) = (12 + 4) \,\%\, 15 = 1$.
- **Mapping that skips every other position:** storing the elements at indices 0, 2, 4, 6, 8, skipping one position each time ((d) of Figure 1), gives the mapping formula $\text{location}(i) = 2i$.

```text
           0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
(a)       [5][2][4][8][1][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
(b)       [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][1][8][4][2][5]
(c)       [8][1][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][5][2][4]
(d)       [5][ ][2][ ][4][ ][8][ ][1][ ][ ][ ][ ][ ][ ]
```

*Figure 1. Four mappings that store the list (5, 2, 4, 8, 1) in an array of length 15*

### 2.3 Basic Representation: element and listSize

The simplest representation follows two rules.

1. Put element $i$ of the list (counted from 0) in `element[i]`.
2. Use a variable `listSize` to record the current number of elements.

The array operations below assume this representation.

### 2.4 Operation Complexities

| Operation | Time Complexity |
|-----------|----------------|
| `get(index)` | $O(1)$ |
| `indexOf(element)` | $O(n)$ |
| `insert(index, element)` | $O(n)$ (shifting) |
| `erase(index)` | $O(n)$ (shifting) |

*Table 2. Time complexity of each operation in the array representation*

### 2.5 Insert Operation

Inserting at position $k$ requires shifting elements $k, k+1, \ldots, n-1$ one position to the right:

```cpp
// Insert element at index k
for (int i = size - 1; i >= k; i--)
    arr[i + 1] = arr[i];  // Shift right
arr[k] = element;
size++;
```

Worst case (insert at 0): $O(n)$ shifts. Best case (insert at end): $O(1)$. In the code, `arr` and `size` correspond to `element` and `listSize`, respectively.

```text
listSize = 5    [a][b][c][d][e][ ][ ][ ]
insert(1, g)
listSize = 6    [a][g][b][c][d][e][ ][ ]
```

*Figure 2. The array and listSize before and after insert(1, g)*

`insert(1, g)` shifts the elements b, c, d, and e from index 1 to the end one position to the right, puts g into `element[1]`, and increases `listSize` to 6. Erasing an element (`erase`) does the opposite: it shifts the elements after the erased position one position to the left and decreases `listSize` by 1.

### 2.6 Dynamic Arrays

If we do not know how many elements will be in the list, we must pick an initial length for the array and dynamically increase it as needed. The current length of the array `element[]` is stored in the variable `arrayLength`.

When the array is full, allocate a **new array of double the size** and copy elements:
- Individual worst case: $O(n)$
- Amortized cost per insertion: $O(1)$

### 2.7 Space Complexity

The space required to run a program to completion depends on the size of the input $n$. An array `element[n]` of size $n$ uses space proportional to $n$.

```text
int i;                  // O(1)
create B[n];            // O(n)
for i = 1 to n
    B[i] = A[i];
// Total: O(n + 1) = O(n)
```

The integer variable `i` uses $O(1)$ space and the array `B` uses $O(n)$, so the total space is $O(n + 1) = O(n)$. The loop itself uses no extra space.

```text
int i, j;               // O(2)
create B[n, n];         // O(n^2)
for i = 1 to n
    for j = 1 to n
        B[i, j] = A[i];
// Total: O(n^2 + 2) = O(n^2)
```

The two-dimensional array `B[n, n]` holds $n^2$ elements, so the total space is $O(n^2 + 2) = O(n^2)$. With 4-byte integer elements, it is $4n^2$ bytes.

---

<br>

## 3. Linked Representation

### 3.1 Node Structure

The linked representation represents data as follows.

1. Each element is represented in a **cell** or **node**.
2. Each node keeps explicit information about the location of other relevant nodes.
3. This explicit information about the location of another node is called a **link** or **pointer**.

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

> **[Computer Programming]** A C++ template (`template <typename T>`) takes a type as a parameter so that the same code works for many types; `new` creates an object on the heap (free store) at run time and returns its address, and `delete` returns that memory. The linked representation creates a node with `new` whenever one is needed and returns an unused node with `delete`, so these two operations are the basis of a dynamic structure whose size is not fixed in advance.

### 3.2 Difference from Array Representation

In the array representation, the location of an element is computed by the mapping formula, so no location information is stored. In the linked representation, the location of the next element is stored explicitly in each node as a link. So the linked representation can place elements anywhere in memory, but accessing the $i$-th element requires following the links from the first node.

### 3.3 Advantages over Arrays

- Dynamic size (no pre-allocation)
- Efficient insertion/deletion at known positions (given the preceding node): $O(1)$
- No wasted space from unused capacity

### 3.4 Disadvantages

- No random access: $O(n)$ to reach element $i$
- Extra memory for pointers
- Cache-unfriendly (nodes scattered in memory)

> **[Computer Architecture]** A cache is a small, fast memory that holds recently accessed addresses and their neighboring data in units of blocks. An array at consecutive addresses lets neighboring elements share a block once it is fetched (spatial locality), but nodes scattered across memory need a different block at every link that is followed, so a linked list is often slower than an array even for the same $O(n)$ traversal.

---

<br>

## 4. Singly Linked Lists

### 4.1 Structure

Representing $L = (e_1, e_2, \ldots, e_n)$ as a singly linked list puts each element $e_i$ in a separate node, and each node has exactly one link field that is used to locate the next element in the linear list. The last node, $e_n$, has no node to link to, so its link field is `NULL`. This structure is also called a **chain**.

```text
head -> [data|next] -> [data|next] -> [data|next] -> nullptr
```

*Figure 3. Structure of a singly linked list (chain)*

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

### 4.3 The Chain Class and Its Operations

Implementing a chain as a class uses a node class `ChainNode` and a chain class `Chain`. The link field of a node is named `link` and plays the same role as `next` in the `Node` of Section 3.1. `first` points to the first node, and `listSize` is the number of elements.

```cpp
template <class T>
class ChainNode {
public:
    T data;               // data field
    ChainNode<T>* link;   // link field
};

template <class T>
class Chain {
public:
    Chain() { first = NULL; listSize = 0; }
    ~Chain();
    int Length() const;
    bool Find(int k, T& x) const;
    int Search(const T& x) const;
    void Insert(int k, const T& x);
    bool Delete(int k, T& x);
private:
    void checkIndex(int Index) const;
    ChainNode<T>* first;  // pointer to the first node
    int listSize;         // number of elements
};
```

**Destructor `~Chain`.** The destructor returns the memory of all nodes of the chain. The following is the destructor of a chain without a head node (Section 4.4). `next` temporarily stores the address of the node that `first->link` points to; the first node is deleted, and the next node becomes the new first node. The time complexity is $O(n)$, where $n$ is the length of the chain.

```cpp
template <class T>
Chain<T>::~Chain()
{
    ChainNode<T> *next;    // holds a pointer to the next node
    while (first->link) {
        next = first->link;  // next temporarily stores the address of the node that first->link points to
        delete first;        // the first node is deleted
        first = next;        // then the next node becomes the new first node
    }
}
```

> **Note:** **Error in the loop condition.** The condition `first->link` above repeats only while the first node has a next node, so it never deletes the last node, and if the chain is empty (`first` is `NULL`) it dereferences a null pointer. Running it on a chain of 3 nodes deletes only 2. The implementation with the condition corrected to `first != NULL` is as follows.

```cpp
// Corrected implementation: deletes up to the last node and is safe for an empty chain
template <class T>
Chain<T>::~Chain()
{
    ChainNode<T> *next;
    while (first != NULL) {
        next = first->link;
        delete first;
        first = next;
    }
}
```

**`Length`.** Counts the nodes from the first node until `NULL` is reached. The time complexity is $O(n)$.

```cpp
template <class T>
int Chain<T>::Length() const
{
    ChainNode<T> *current = first;
    int len = 0;
    while (current) {
        len++;
        current = current->link;
    }
    return len;
}
```

**`checkIndex`.** Verifies that `Index` is between 0 and `listSize-1`. If the condition `Index < 0 || Index >= listSize` is true, the index does not exist; if it is false, the index exists. The time complexity is $O(1)$.

```cpp
template <class T>
void Chain<T>::checkIndex(int Index) const
{ // Verify that Index is between 0 and listSize-1.
    if (Index < 0 || Index >= listSize)
    {
        cout << "This index does not exist";   // Print
    }
}
```

**`Find`.** If the element at index `k` exists, stores its value in `x`. It follows the links `k` times from the first node, so the time complexity is $O(k)$.

```cpp
template <class T>
bool Chain<T>::Find(int k, T& x) const
{ // Set x to the element at index k in the list if it exists
  // Throw illegal index exception if no such element exists
    checkIndex(k);

    // move to desired node
    ChainNode<T>* current = first;
    for (int i = 0; i < k; i++)
        current = current->link;   // move to the next node
    x = current->data;             // save the data of the node at index k in x
    return true;                   // should return true if the element exists, false otherwise
}
```

> **Note:** **`Find` continues after the range check.** Contrary to the comment, `checkIndex` throws no exception; it only prints a message and does not stop `Find`, so for an out-of-range `k`, `Find` keeps running the loop and dereferences a `NULL` `current`. The implementation in which `checkIndex` returns the result of the check, so that `Find` returns `false` when no such element exists as its comment says, is as follows.

```cpp
// Corrected implementation: returns false when out of range
template <class T>
bool Chain<T>::checkIndex(int Index) const
{
    if (Index < 0 || Index >= listSize) {
        cout << "This index does not exist" << endl;
        return false;
    }
    return true;
}

template <class T>
bool Chain<T>::Find(int k, T& x) const
{
    if (!checkIndex(k)) return false;
    ChainNode<T>* current = first;
    for (int i = 0; i < k; i++)
        current = current->link;
    x = current->data;
    return true;
}
```

To use this implementation, also change `checkIndex` in the class declaration to `bool checkIndex(int Index) const;`.

**`Search`.** Locates the value `x` and returns its position (index), or -1 if it is not found. The time complexity is $O(n)$. The difference is that `Find` finds the value of the element at a given position `k` ($O(k)$), while `Search` finds the position of a given value `x`.

```cpp
template <class T>
int Chain<T>::Search(const T& x) const
{ // Locate x and return its position if found else return -1
  // search the chain for x
    ChainNode<T>* current = first;
    int index = 0; // index of current
    while (current != NULL && current->data != x)
    { // move to the next node
        current = current->link;
        index++;
    }
    // make sure we found matching element
    if (current == NULL)
        return -1;
    else
        return index;
}
```

**`Delete`.** To delete the fourth element from the chain, we locate the third and fourth nodes, link the third node to the fifth, and free the fourth node so that it becomes available for reuse.

```text
Before:   first -> [20] -> [10] -> [30] -> [80] -> [11] -> NULL
After:    first -> [20] -> [10] -> [30] ---------> [11] -> NULL    ([80] is freed)
```

*Figure 4. Deleting the fourth element 80 from a chain*

The following implements this process for an index `k` (the fourth element is `k = 3`). Deleting the first node has no preceding node, so it changes `first`.

```cpp
template <class T>
bool Chain<T>::Delete(int k, T& x)
{ // store the element at index k in x and delete it
    if (!checkIndex(k)) return false;
    ChainNode<T>* del;
    if (k == 0) {                    // delete the first node
        del = first;
        first = first->link;
    }
    else {
        ChainNode<T>* p = first;     // locate the node before the one to delete
        for (int i = 1; i < k; i++)
            p = p->link;
        del = p->link;
        p->link = del->link;         // link the preceding node to the node after the deleted one
    }
    x = del->data;
    delete del;                      // free the node so that it becomes available for reuse
    listSize--;
    return true;
}
```

**`Insert`.** To insert an element following the $k$th element in the chain, we locate the $k$th node, make the new node's link point to the $k$th node's link, and then make the $k$th node's link point to the new node. If $k = 0$, the new node becomes the first node, so the new node's link points to the old first node and `first` points to the new node. The new element is placed after $k$ elements, so its index becomes $k$.

```text
k = 0:   first -> [new] -> [e1] -> [e2] -> ...
k > 0:   first -> ... -> [kth node] -> [new] -> [(k+1)th node] -> ...
```

*Figure 5. Results of inserting at the front of a chain (k = 0) and after the kth node (k > 0)*

```cpp
template <class T>
void Chain<T>::Insert(int k, const T& x)
{ // insert x at index k (place it after k elements)
    if (k < 0 || k > listSize) {
        cout << "Bad insert index" << endl;
        return;
    }
    ChainNode<T>* newNode = new ChainNode<T>;
    newNode->data = x;
    if (k == 0) {                    // insert at the front
        newNode->link = first;
        first = newNode;
    }
    else {
        ChainNode<T>* p = first;     // locate the kth node (index k-1)
        for (int i = 1; i < k; i++)
            p = p->link;
        newNode->link = p->link;     // new node's link points to kth node's link
        p->link = newNode;           // kth node's link now points to the new node
    }
    listSize++;
}
```

**Program example.** The following program inserts 10, 20, 30, 40, and 50 into a chain in order, prints the length, and then finds the element at index `index`. `Find` and `checkIndex` use the corrected implementation.

```cpp
int main() {
    Chain<int> chain;

    chain.Insert(0, 10); // insert element at index 0
    chain.Insert(1, 20); // insert element at index 1
    chain.Insert(2, 30); // insert element at index 2
    chain.Insert(3, 40); // insert element at index 3
    chain.Insert(4, 50); // insert element at index 4

    cout << "Chain length: " << chain.Length() << endl; // print

    int x;
    int index = 8;
    if (chain.Find(index, x)) {
        cout << "Index#" << index << " Element found: " << x << endl; // print
    }
}
```

If the index is out of the chain length, as with `index = 8`, the output is:

```text
Chain length: 5
This index does not exist
```

If the index is within the chain length, as with `index = 3`, the output is:

```text
Chain length: 5
Index#3 Element found: 40
```

### 4.4 Chain with a Head Node

A chain may have a **head node** at the front that holds no data. Pointer `first` points to the head node, and the head node points to the first node of the chain. `first` always points to the head node, and the head node remains undeleted. If the first node of the chain changes, the link of the head node is changed to the new first node, so insertion and deletion of the first node can be handled in the same way as at any other position.

```text
first       del
  |          |
  v          v
[0|*] --> [3|*] --> [2|*] --> [1|*] --> [2|*] --> [4|*] --> [6|NULL]
head node
```

*Figure 6. A chain with a head node and the destructor's pointer del*

The destructor of a chain with a head node is as follows. Unlike the destructor of the chain without a head node, pointer `del` holds the target node to delete, and `first` remains pointing to the head node until the end.

```cpp
template <class T>
Chain<T>::~Chain()
{
    ChainNode<T> *del = first->link;   // (1) select the target node to delete
    while (first->link) {
        first->link = del->link;       // (2) select a new first node before deleting the target
        delete del;                    // (3) delete the target node
        del = first->link;             // (1) select the next target node to delete
    }
}
```

In Figure 6, the first step selects node 3, pointed to by `del` (1), changes the head node's link to node 2 (2), and deletes node 3 (3). Repeating this deletes all 6 data nodes, after which `first->link` becomes `NULL` and the loop ends. To return the head node itself as well, execute `delete first;` after the loop.

---

<br>

## 5. Doubly Linked Lists

### 5.1 Node Structure

A **doubly linked list** is an ordered sequence of nodes in which each node has two pointers, left and right. The `prev` and `next` of the following `DNode` correspond to left and right, respectively.

```cpp
template <typename T>
struct DNode {
    T data;
    DNode<T>* prev;
    DNode<T>* next;
};
```

```text
       LeftEnd                                                 RightEnd
          |                                                       |
          v                                                       v
NULL <- [left|1|right] <-> [left|2|right] <-> [left|3|right] <-> [left|4|right] -> NULL
```

*Figure 7. A doubly linked list and its two end nodes LeftEnd and RightEnd*

The left-most node (LeftEnd) has a `NULL` left, and the right-most node (RightEnd) has a `NULL` right, so these values distinguish the two end nodes.

### 5.2 Advantages

- Traversal in both directions
- Deletion of a known node in $O(1)$ (no need to find predecessor)
- Useful for undo operations, browser history, etc.

### 5.3 Trade-off

Extra pointer per node (more memory) but bidirectional traversal and simpler deletion.

### 5.4 Circular Doubly Linked Lists

In a **circular doubly linked list**, a head node can be added at the left end, the right end, or both. In a non-empty circular doubly linked list without a head node, the following hold.

- `LeftEnd->left` is a pointer to the right-most node (i.e., it equals RightEnd).
- `RightEnd->right` is a pointer to the left-most node (i.e., it equals LeftEnd).

With a head node at the left end only, the head node's right points to the first data node and its left to the last data node, and the first data node's left and the last data node's right point to the head node. An empty list consists of the head node alone, whose left and right both point to itself.

```text
+-> [head] <-> [ 2 ] <-> [ 7 ] <-> [ 1 ] <-> [ 8 ] <-+
|                                                    |
+----------------------------------------------------+
      (head's left = [8], [8]'s right = head)
```

*Figure 8. A circular doubly linked list with a head node at the left end*

---

<br>

## 6. Circular Lists

### 6.1 Circular Singly Linked List

The last node's `next` pointer points back to the first node instead of `nullptr`.

### 6.2 Use Cases

- Round-robin scheduling
- Circular buffers
- Josephus problem

### 6.3 Circular Lists and Head Nodes

Programs that use chains can be simplified or run faster by doing one or both of the following.

1. Represent the linear list as a **singly linked circular list** (or simply **circular list**) rather than as a chain. All other nodes can be reached from any node.
2. Add an additional node, called the **head node**, at the front. Adding and deleting become simpler.

```text
(a) Circular list
first --> [e1] --> [e2] --> [e3] --> ... --> [en] --+
           ^                                        |
           +----------------------------------------+

(b) Circular list with head node
first --> [head] --> [e1] --> [e2] --> ... --> [en] --+
            ^                                         |
            +-----------------------------------------+

(c) Empty list with head node
first --> [head] --+
            ^      |
            +------+
```

*Figure 9. A circular list, a circular list with a head node, and an empty list*

Circular lists also have disadvantages. The end of the list cannot be recognized by `NULL`, so the condition that ends a traversal must compare with the starting node, and a wrong condition leads to an infinite loop. Also, if the name of the list points to the first node, inserting at the front requires moving to the last node to change its link (Section 6.5).

### 6.4 Deleting the Nodes of a Circular List

The following destructor deletes the nodes of a circular list with a head node one by one. When all data nodes are deleted, the head node's link points to the head node itself, so `del` equals `first` and the loop ends.

```cpp
template <class T>
CircularList<T>::~CircularList()
{
    ChainNode<T> *del = first->link;   // (1) select a target node to delete
    while (del != first) {             // exit when the target node becomes the head node
        first->link = del->link;       // (2) select a new first node before deleting the target
        delete del;                    // (3) delete the target node
        del = first->link;             // (1) select a next target node to delete
    }
}
```

### 6.5 Adding a Node at the Front of a Circular List

Inserting a new node at the front of a circular list requires changing the link field of the last node. If the name (pointer) of the list points to the first node, the whole list must be followed to find the last node, so it is more convenient if the name of the circular list points to the last node. Then the first node is obtained directly as `last->link`.

```text
Name points to the first node:
a --> [x1|*] --> [x2|*] --> [x3|*] --+
       ^                             |
       +-----------------------------+

Name points to the last node:
      [x1|*] --> [x2|*] --> [x3|*] <-- a
       ^                      |
       +----------------------+
```

*Figure 10. The name of a circular list pointing to the first node and to the last node*

```cpp
typedef struct listNode *listPointer;
struct listNode {
    int data;
    listPointer link;
};

void insertFront(listPointer *last, listPointer node)
{ // insert node at the front of a circular list (*last is the last node)
    if (!(*last)) {                 // empty list
        *last = node;
        node->link = node;
    }
    else {
        node->link = (*last)->link;   // (1) the new node points to the current first node
        (*last)->link = node;         // (2) the last node points to the new node
    }
}
```

For an empty list, the new node points to itself and `*last` points to the new node. Otherwise, (1) the new node's link points to the current first node (`(*last)->link`), and (2) the last node's link points to the new node. There is no need to find the last node, so the time complexity is $O(1)$. Inserting 3, 2, and 1 at the front in order gives the list 1, 2, 3, with `last` pointing to 3.

### 6.6 Searching with a Head Node

A circular list with a head node searches with fewer comparisons than a chain. The following two functions count positions from 1 and return 0 when the value is not found.

```cpp
template<class T>
int Chain<T>::Search(const T& x) const
{
    ChainNode<T> *current = first;
    int index = 1; // index of current
    while (current && current->data != x) {
        current = current->link;
        index++;
    }
    if (current) return index;
    return 0;
}
```

```cpp
template<class T>
int CircularList<T>::Search(const T& x) const
{
    ChainNode<T> *current = first->link;
    int index = 1; // index of current
    first->data = x; // put x in head node
    while (current->data != x) {
        current = current->link;
        index++;
    }
    // are we at head?
    return ((current == first) ? 0 : index);
}
```

The chain search tests two things in every iteration: whether `current` is not `NULL` and whether `current->data` differs from `x`. The circular list search puts the value `x` into the `data` of the head node (such a value is called a **sentinel**), so the loop always stops at the head node even if `x` is not in the list. Each iteration therefore needs only one test. If the loop stops at the head node, `x` is not present, so the function returns 0. These two functions differ from the `Search` of Section 4.3 (which counts from 0 and returns -1 on failure) in that they count positions from 1 and return 0 on failure.

---

<br>

## 7. Application of Linked Lists: Polynomials

### 7.1 Polynomial Representation

Each term of a polynomial is represented by one node. A node has three fields, the coefficient (data field 1), the exponent (data field 2), and the link (link field), and the terms are linked in decreasing order of exponent.

```text
a = 3x^14 + 2x^8 + 1
a --> [ 3 | 14 | *] --> [ 2 |  8 | *] --> [ 1 |  0 | NULL]

b = 8x^14 - 3x^10 + 10x^6
b --> [ 8 | 14 | *] --> [-3 | 10 | *] --> [10 |  6 | NULL]
```

*Figure 11. Linked list representation of the polynomials a and b*

### 7.2 Adding Polynomials

To add two polynomials, we examine their terms starting at the nodes pointed to by `a` and `b`.

1. If the exponents of the two terms are equal, we add the two coefficients and create a new term for the result, and advance both `a` and `b` to their next terms. If the sum of the coefficients is 0, no term is created.
2. If the exponent of the current term in `a` is less than the exponent of the current term in `b`, we create a duplicate term of `b`, attach this term to the result, called `d`, and advance the pointer to the next term in `b`.
3. Take a similar action on `a` if `a->expon > b->expon`.

When one list is exhausted, the remaining terms of the other are attached to `d` in order.

| Step | Current Term of `a` | Current Term of `b` | Comparison | Term Attached to `d` |
|------|------|------|------|------|
| 1 | $3x^{14}$ | $8x^{14}$ | $14 = 14$ | $11x^{14}$ |
| 2 | $2x^8$ | $-3x^{10}$ | $8 < 10$ | $-3x^{10}$ |
| 3 | $2x^8$ | $10x^6$ | $8 > 6$ | $2x^8$ |
| 4 | $1$ | $10x^6$ | $0 < 6$ | $10x^6$ |
| 5 | $1$ | (end) | `b` exhausted | $1$ |

*Table 3. Steps of adding a and b*

The result is $d = 11x^{14} - 3x^{10} + 2x^8 + 10x^6 + 1$. In every step at least one of `a` and `b` advances to its next term, so if `a` and `b` have $m$ and $n$ terms, respectively, the time complexity is $O(m + n)$.

### 7.3 Representation with a Circular List and a Head Node

If the link field of the last node points to the first node in the list (a circular list), all the nodes of a polynomial can be freed more efficiently. Representing the polynomial $\text{ptr} = 3x^{14} + 2x^8 + 1$ as a circular list makes the node of the last term 1 point to the node of the first term $3x^{14}$. For reference, a **chain** is a singly linked list in which the last node has a null link.

Nodes that are no longer in use are freed so that we can reuse them later, and the freed nodes are maintained as a chain. A circular list can be attached to this chain of freed nodes as a whole in constant time, without following it to the last node.

To avoid the special case of the zero polynomial, each polynomial may contain one additional head node. The `expon` and `coef` fields of this node are irrelevant; the figure below stores the exponent -1, which does not clash with any real term.

```text
Zero polynomial:
a --> [ - | -1 | *] --+
        ^             |
        +-------------+

a = 3x^14 + 2x^8 + 1:
a --> [ - | -1 | *] --> [ 3 | 14 | *] --> [ 2 | 8 | *] --> [ 1 | 0 | *] --+
        ^                                                                |
        +----------------------------------------------------------------+
```

*Figure 12. Polynomials represented as circular lists with a head node*

---

<br>

## 8. Linked Stacks and Queues

When several stacks and queues coexist, there is no efficient way to represent them sequentially in an array. With the linked representation, each stack and queue uses only as many nodes as it needs. The direction of the links also makes insertion and deletion of nodes easy for both the stack and the queue.

```text
(a) Linked stack (LIFO)
top --> [ |*] --> [ |*] --> ... --> [ |NULL]

(b) Linked queue (FIFO)
front --> [ |*] --> [ |*] --> ... --> [ |NULL] <-- rear
```

*Figure 13. A linked stack and a linked queue*

A linked stack inserts and deletes at `top`, so the last element in is the first out (last in, first out, LIFO), and a linked queue inserts at `rear` and deletes at `front`, so the first element in is the first out (first in, first out, FIFO). Which of the array and the chain is more efficient depends on how they are used. Both representations can insert into and delete from stacks and queues in $O(1)$ (an array-based queue uses a circular array), but the array uses contiguous memory with good cache performance while its capacity must be fixed in advance or grown, and the chain needs extra link space per node but uses only as many nodes as needed with no size limit. Stacks are covered in detail in Lecture 5 and queues in Lecture 6.

---

<br>

## 9. Comparison: Array vs. Linked List

| Feature | Array | Linked List |
|---------|-------|-------------|
| Access by index | $O(1)$ | $O(n)$ |
| Insert at front | $O(n)$ | $O(1)$ |
| Insert at end | $O(1)$ amortized | $O(1)$ with tail pointer |
| Insert at middle | $O(n)$ | $O(1)$ after finding position |
| Delete at front | $O(n)$ | $O(1)$ |
| Memory overhead | None per element (contiguous), though unused capacity can occur | Extra pointer per node |
| Cache performance | Excellent | Poor |
| Memory allocation | Contiguous block | Scattered |

*Table 4. Comparison of arrays and linked lists*

---

<br>

## 10. Appendix

### 10.1 Iterator Design Pattern

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

### 10.2 Common Interview Questions

1. **Reverse a linked list** (iterative and recursive)
2. **Detect a cycle** (Floyd's tortoise and hare algorithm)
3. **Find the middle element** (two-pointer technique)
4. **Merge two sorted linked lists**

---

<br>

## Summary

| Concept | Key Summary |
|---------|-------------|
| Linear List | It is an ordered collection of elements $(e_1, \ldots, e_n)$, represented with an array or with links. |
| Array | The location is computed by a mapping formula, so direct access is $O(1)$, but insertion and deletion are $O(n)$ because elements are shifted. |
| Mapping formula | Several formulas, such as $i$, $\text{arrayLength} - i - 1$, $(\text{location}(0) + i) \,\%\, \text{arrayLength}$, and $2i$, turn a list location into an array index. |
| Singly linked list | Also called a chain, it allows only sequential access but inserts and deletes in $O(1)$ after a node when that preceding node is known. |
| Head node | It is a front node that holds no data and lets insertion and deletion of the first node be handled like any other position. |
| Doubly linked list | It allows bidirectional traversal and deletes a known node in $O(1)$. |
| Circular list | The last node links back to the first, which is useful for cyclic processes, and insertion at the front is $O(1)$ when the name points to the last node. |
| Polynomial | Each term is a node holding a coefficient and an exponent, and two lists are added in one pass in $O(m + n)$ by comparing exponents. |
| Dynamic array | The doubling strategy gives an amortized cost of $O(1)$ for appending at the end. |

---

<br>

## Self-Check Questions

1. **Mapping formulas:** The list (5, 2, 4, 8, 1) is stored in an array of length 15. In the wrap-around mapping with $\text{location}(0) = 12$, what is the array index of element 8 (location 3)? In the right-to-left mapping, what is the array index of element 4 (location 2)?

   <details>
   <summary>Answer</summary>

   In the wrap-around mapping, $(12 + 3) \,\%\, 15 = 0$, so the index is 0. In the right-to-left mapping, $15 - 2 - 1 = 12$, so the index is 12. Both can be checked in (c) and (b) of Figure 1.

   </details>

2. **Find and Search:** How do `Find` and `Search` of a chain differ, and what is the time complexity of each?

   <details>
   <summary>Answer</summary>

   `Find(k, x)` takes a position (index) `k` and stores the value of that element in `x`; it follows the links `k` times from the first node, so it is $O(k)$. `Search(x)` takes a value `x` and returns the position of that element; in the worst case it compares every node, so it is $O(n)$.

   </details>

3. **Order of insertion steps:** What happens if `newNode->link = p->link;` and `p->link = newNode;` are swapped in the chain's `Insert`?

   <details>
   <summary>Answer</summary>

   If `p->link = newNode;` runs first, `p->link` already points to the new node, so the following `newNode->link = p->link;` makes the new node point to itself. The pointer to the nodes that originally followed `p` is lost, so those nodes become unreachable (a memory leak), and a traversal never ends at the new node but loops forever.

   </details>

4. **Sentinel search:** Why does `Search` of a circular list with a head node need fewer comparisons than `Search` of a chain?

   <details>
   <summary>Answer</summary>

   Putting the value `x` into the `data` of the head node guarantees that the loop stops at the head node even if `x` is not in the list. So there is no need to test whether `current` is `NULL` in each iteration, and the tests per iteration drop from two to one. If the loop stops at the head node, the search has failed.

   </details>

5. **Adding polynomials:** Add $a = 5x^7 + 3x^2 + 1$ and $b = 4x^7 - 3x^2 + 2x$ by the method of Section 7.2.

   <details>
   <summary>Answer</summary>

   The exponents 7 are equal, so $9x^7$ is created. The exponents 2 are equal and the sum of the coefficients is $3 + (-3) = 0$, so no term is created. Next, the exponent 0 of $a$ is less than the exponent 1 of $b$, so $2x$ is attached, and since $b$ is exhausted, the remaining $1$ is attached. The result is $9x^7 + 2x + 1$.

   </details>
