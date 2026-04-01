# Chapter 07 — Skip Lists and Hashing

> **Last Updated:** 2026-04-01
>
> Carrano & Henry, Data Structures and Abstractions with Java 4th Ed. Ch 7

> **Prerequisites**: [Programming Language] Java. [Data Structures] Arrays, linked lists (Ch 3-6).
>
> **Learning Objectives**:
> 1. Explain skip list structure and probabilistic balancing
> 2. Implement hash tables with collision resolution strategies
> 3. Analyze expected time complexity of hashing operations

---

## Table of Contents

- [1. Dictionary ADT](#1-dictionary-adt)
  - [1.1 Definition](#11-definition)
  - [1.2 Dictionary Operations](#12-dictionary-operations)
  - [1.3 Dictionary with Duplicates](#13-dictionary-with-duplicates)
  - [1.4 Accessing Dictionary Elements](#14-accessing-dictionary-elements)
  - [1.5 Dictionary as an Ordered Linear List](#15-dictionary-as-an-ordered-linear-list)
- [2. Skip Lists](#2-skip-lists)
  - [2.1 Motivation](#21-motivation)
  - [2.2 Structure and Levels](#22-structure-and-levels)
  - [2.3 Search Operation](#23-search-operation)
  - [2.4 Insertion and Deletion](#24-insertion-and-deletion)
  - [2.5 Worst-Case Time Complexity](#25-worst-case-time-complexity)
  - [2.6 Average-Case Time Complexity](#26-average-case-time-complexity)
- [3. Hashing](#3-hashing)
  - [3.1 Ideal Hashing](#31-ideal-hashing)
  - [3.2 Hash Functions](#32-hash-functions)
  - [3.3 Collision Resolution — Open Addressing](#33-collision-resolution--open-addressing)
  - [3.4 Collision Resolution — Chaining](#34-collision-resolution--chaining)
  - [3.5 Performance Comparison](#35-performance-comparison)
- [Summary](#summary)
- [Appendix](#appendix)

---

<br>

## 1. Dictionary ADT

### 1.1 Definition

A **dictionary** is a collection of elements where each element has a field called a **key**. Every element is stored as a **(key, value)** pair, and every key is usually distinct (unique).

> **Key Point:** A dictionary is an abstract data type that maps keys to values, supporting efficient lookup, insertion, and deletion.

### 1.2 Dictionary Operations

Typical dictionary operations include:

1. **empty()** — Determine whether the dictionary is empty
2. **size()** — Return the number of (key, value) pairs
3. **insert(key, value)** — Insert a new pair into the dictionary
4. **search(key)** — Find the pair with a specified key
5. **delete(key)** — Remove the pair with a specified key

### 1.3 Dictionary with Duplicates

In some applications, keys are **not** required to be distinct. A word dictionary is a common example:

- Pairs are of the form `(word, meaning)`
- A single word may have multiple entries (e.g., "rank" can mean a position in society, an official grade, or the act of ordering)

### 1.4 Accessing Dictionary Elements

There are two access patterns:

| Access Type | Description |
|:-----------|:------------|
| **Random Access** | Retrieve any element by performing a search on its key |
| **Sequential Access** | Retrieve elements one by one in ascending order of the key field using `Begin()` and `Next()` |

### 1.5 Dictionary as an Ordered Linear List

Given $L = (e_1, e_2, e_3, \ldots, e_n)$ where each $e_i$ is a pair `(key, value)`:

| Representation | Search Time |
|:--------------|:------------|
| Unsorted array | $O(n)$ |
| Sorted array | $O(\log n)$ — binary search |
| Unsorted chain | $O(n)$ |
| Sorted chain | $O(n)$ |

> **Key Point:** Sorted arrays allow $O(\log n)$ search via binary search, but sorted chains still require $O(n)$ since we cannot index into the middle. Skip lists solve this problem.

---

<br>

## 2. Skip Lists

### 2.1 Motivation

- Binary search on a **sorted array** achieves $O(\log n)$, but insertion/deletion is $O(n)$ due to shifting
- A **sorted chain** allows $O(1)$ insertion/deletion once the position is found, but search is $O(n)$

**Question:** How can we improve the search performance of a sorted chain?

**Answer:** By adding **additional forward pointers** to some nodes — these augmented chains are called **skip lists**.

### 2.2 Structure and Levels

A skip list is built on multiple levels of sorted chains:

- **Level 0** chain includes **all elements**
- **Level 1** chain includes every **2nd** element
- **Level 2** chain includes every **4th** element
- **Level $i$** chain includes every $2^i$-th element

An element is called a **level $i$ element** if and only if it appears in chains for levels 0 through $i$.

```
Level 2:  H ──────────────────> 40 ──────────────────> 80 ──> T
Level 1:  H ──────> 24 ──────> 40 ──────> 60 ──────> 80 ──> T
Level 0:  H ──> 20 ──> 24 ──> 30 ──> 40 ──> 60 ──> 75 ──> 80 ──> T
```

> **Key Point:** The number of levels for $n$ elements is $\lfloor \log_{1/p} n \rfloor + 1 = \lfloor \log_p n \rfloor + 1$. With $p = 1/2$ and 8 elements: $\log_2 8 = 3$ levels.

### 2.3 Search Operation

To search for key $k$, start at the **highest level** of the head node and traverse right:

1. At the current level, move right while the next node's key is less than $k$
2. If the next node's key equals $k$, the element is found
3. If the next node's key exceeds $k$ (or is tail), drop down one level
4. Repeat until found or level 0 is exhausted

**Example:** Searching for 77 in a 3-level skip list requires at most $\log_2 n = 3$ comparisons:

1. Start at level 2: compare with 40 (go right), compare with 80 (drop down)
2. At level 1: compare with 60 (go right), compare with 80 (drop down)
3. At level 0: compare with 75 (go right), compare with 80 → 77 not found or insert here

### 2.4 Insertion and Deletion

**Insertion:**
- When a new element is inserted, its level is assigned with probability $p^i$ (typically $p = 1/2$)
- The probability that a new element is a level $i$ element is $1/2^i$
- After determining the level, update the forward pointers at each affected level

**Deletion:**
- Locate the element using the search procedure
- Remove it from all levels in which it appears
- Update the forward pointers of predecessor nodes at each level

> **Key Point:** Insertions and deletions require $O(n)$ work in the worst case to maintain the skip list structure, but expected time is $O(\log n)$.

### 2.5 Worst-Case Time Complexity

If all elements are at **level 0 only** (no higher-level pointers), the skip list degenerates into a simple sorted linked list. In this case:

$$T_{\text{worst}}(n) = \Theta(n)$$

### 2.6 Average-Case Time Complexity

To analyze the **expected** search time, we trace the search path **backwards** (traveling up and to the left):

Let $C(i)$ be the expected cost of climbing $i$ levels backward. At each node:

- **Case 1** (probability $1 - p$): The node has no higher-level pointer → cost is $C(i) + 1$
- **Case 2** (probability $p$): The node has a higher-level pointer → cost is $C(i-1) + 1$

$$C(i) = (1-p)(1 + C(i)) + p(1 + C(i-1))$$

Solving the recurrence with $C(0) = 0$:

$$C(i) = \frac{i}{p}$$

Since the maximum level $i = \log_p n = \log n$:

$$\Theta(C(i)) = \Theta\left(\frac{\log N}{p}\right) = \Theta(\log N) = O(\log N)$$

> **Exam Tip:** The average-case analysis is a classic recurrence problem. Remember: with $p = 1/2$, the average search time is $O(\log n)$ — essentially equivalent to binary search on a sorted array, but with efficient insertion/deletion.

---

<br>

## 3. Hashing

### 3.1 Ideal Hashing

**Ideal hashing** (or direct addressing) uses the key itself as the array index:

- Store element with key $k$ in `table[k]`
- Search, insert, and delete are all $O(1)$

**Limitation:** If the key range is enormous (e.g., 9-digit student IDs), the table would require $10^9$ slots, which is impractical.

### 3.2 Hash Functions

A **hash function** $h(k)$ maps keys to a smaller range of table indices $[0, m-1]$:

$$h: K \rightarrow \{0, 1, 2, \ldots, m-1\}$$

**Common hash functions:**

| Function | Formula | Notes |
|:---------|:--------|:------|
| Division | $h(k) = k \mod m$ | Choose $m$ as a prime not close to a power of 2 |
| Multiplication | $h(k) = \lfloor m(kA \mod 1) \rfloor$ | $A \approx 0.6180$ (golden ratio) |
| Folding | Split key into parts, add them | Good for string keys |

> **Key Point:** A **collision** occurs when two different keys map to the same index: $h(k_1) = h(k_2)$ where $k_1 \neq k_2$. Collision resolution is the central challenge in hashing.

### 3.3 Collision Resolution — Open Addressing

In open addressing, all elements are stored within the hash table itself. When a collision occurs, probe for the next available slot:

**Linear Probing:**
$$h_i(k) = (h(k) + i) \mod m, \quad i = 0, 1, 2, \ldots$$

- Simple but suffers from **primary clustering** — long chains of occupied cells form

**Quadratic Probing:**
$$h_i(k) = (h(k) + i^2) \mod m, \quad i = 0, 1, 2, \ldots$$

- Reduces primary clustering but may cause **secondary clustering**

**Double Hashing:**
$$h_i(k) = (h_1(k) + i \cdot h_2(k)) \mod m$$

- Uses a second hash function to determine the probe step
- Best distribution among open addressing methods

### 3.4 Collision Resolution — Chaining

In **separate chaining**, each table slot holds a pointer to a linked list of all elements that hash to that index:

```
Index 0: → [20] → [40] → NULL
Index 1: → [31] → NULL
Index 2: → [12] → [52] → NULL
...
```

- No clustering problems
- Table can hold more elements than its size (load factor $\alpha > 1$ is possible)
- Each chain can be a sorted or unsorted linked list

### 3.5 Performance Comparison

Let $\alpha = n/m$ be the **load factor** (ratio of elements to table size):

| Method | Successful Search | Unsuccessful Search |
|:-------|:-----------------|:-------------------|
| Linear Probing | $\frac{1}{2}\left(1 + \frac{1}{1-\alpha}\right)$ | $\frac{1}{2}\left(1 + \frac{1}{(1-\alpha)^2}\right)$ |
| Quadratic / Double | $-\frac{1}{\alpha}\ln(1-\alpha)$ | $\frac{1}{1-\alpha}$ |
| Chaining | $1 + \frac{\alpha}{2}$ | $1 + \alpha$ |

> **Key Point:** Chaining generally outperforms open addressing when the load factor is high. For low load factors ($\alpha < 0.5$), all methods perform similarly.

---

<br>

## Summary

| Concept | Key Point |
|:--------|:----------|
| Dictionary ADT | Collection of (key, value) pairs with search, insert, delete |
| Skip List | Multi-level linked list with $O(\log n)$ expected search/insert/delete |
| Skip List Levels | Level $i$ includes every $2^i$-th element; total levels = $\lfloor \log_2 n \rfloor + 1$ |
| Skip List Worst Case | $\Theta(n)$ — degenerates to a linked list |
| Skip List Average Case | $O(\log n)$ — derived from backward analysis recurrence |
| Hash Function | Maps keys to table indices; collisions must be resolved |
| Open Addressing | Linear, quadratic, or double hashing probing within the table |
| Chaining | Each slot holds a linked list of colliding elements |
| Load Factor $\alpha$ | $n/m$; higher values increase collision frequency |

---

<br>

## Appendix

### Real-World Applications

- **Hash Maps** (C++ `unordered_map`, Java `HashMap`, Python `dict`) use chaining or open addressing internally
- **Skip Lists** are used in Redis (sorted sets), LevelDB, and concurrent data structures
- **Bloom Filters** extend hashing for probabilistic membership testing

### Interview Tips

- Know the difference between open addressing and chaining
- Be able to analyze collision probability and expected probe lengths
- Skip lists are a common alternative to balanced BSTs in system design
