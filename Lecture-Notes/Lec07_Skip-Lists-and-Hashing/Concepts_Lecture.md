# Lecture 7 — Skip Lists and Hashing

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-18

> **Learning Objectives:**
> 1. Explain the operations of the dictionary ADT and the search time of each linear list representation
> 2. Explain skip list structure and probabilistic balancing
> 3. Trace the search path of a skip list and derive its average search time with a recurrence
> 4. Implement hash tables with collision resolution strategies
> 5. Analyze the expected time complexity of hashing operations and choose the number of buckets

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
  - [3.3 Collisions and Overflows](#33-collisions-and-overflows)
  - [3.4 Collision Resolution: Open Addressing](#34-collision-resolution-open-addressing)
  - [3.5 Collision Resolution: Chaining](#35-collision-resolution-chaining)
  - [3.6 Performance Comparison](#36-performance-comparison)
  - [3.7 Hash Table Design](#37-hash-table-design)
- [4. Appendix](#4-appendix)
  - [4.1 Real-World Applications](#41-real-world-applications)
  - [4.2 Interview Tips](#42-interview-tips)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Dictionary ADT

### 1.1 Definition

A **dictionary** is a collection of elements where each element has a field called a **key**. Every element is stored as a **(key, value)** pair, and keys are usually distinct (unique).

> **Key Point:** A dictionary is an abstract data type that maps keys to values, supporting efficient lookup, insertion, and deletion.

A typical application of a dictionary is the collection of student records in a class. The key is the student number, the value is the list of that student's assignment and exam marks, and all student numbers are distinct. A dictionary keyed by name supports operations such as retrieving the element whose key is a given name or updating that element.

### 1.2 Dictionary Operations

Typical dictionary operations include the following.

1. **empty()**: Determine whether the dictionary is empty.
2. **size()**: Return the number of (key, value) pairs.
3. **insert(key, value)**: Insert a new pair into the dictionary.
4. **search(key)**: Find the pair with a specified key.
5. **delete(key)**: Remove the pair with a specified key.

### 1.3 Dictionary with Duplicates

In some applications, keys are **not** required to be distinct. A word dictionary is a common example.

- Pairs are of the form `(word, meaning)`.
- A single word may have two or more entries. For example, the word rank has several entries such as (rank, a relative position in a society), (rank, an official position or grade), and (rank, to give a particular order or position to).

### 1.4 Accessing Dictionary Elements

There are two access patterns.

| Access Type | Description |
|:-----------|:------------|
| **Random Access** | Retrieve any element by performing a search on its key |
| **Sequential Access** | Retrieve elements one by one in ascending order of the key field using `Begin()` and `Next()` |

*Table 1. Two ways to access dictionary elements*

In sequential access, `Begin()` retrieves the element with the smallest key, and `Next()` retrieves the next element.

### 1.5 Dictionary as an Ordered Linear List

A dictionary can be represented as a linear list $L = (e_1, e_2, e_3, \ldots, e_n)$. Each $e_i$ is a pair `(key, value)`, and the list is represented as an array or a chain (the linked list of Lecture 3).

| Representation | Search Time |
|:--------------|:------------|
| Unsorted array | $O(n)$ |
| Sorted array | $O(\log n)$ (binary search) |
| Unsorted chain | $O(n)$ |
| Sorted chain | $O(n)$ |

*Table 2. Dictionary search time by linear list representation*

> **Key Point:** Sorted arrays allow $O(\log n)$ search via binary search, but sorted chains still require $O(n)$ since a middle node cannot be accessed directly. Skip lists solve this problem.

---

<br>

## 2. Skip Lists

### 2.1 Motivation

- Binary search on a **sorted array** achieves $O(\log n)$, but insertion and deletion are $O(n)$ because elements must be shifted.
- A **sorted chain** allows $O(1)$ insertion and deletion once the position is found, but search is $O(n)$.

**Question:** How can we improve the search performance of a sorted chain?

**Answer:** Put **additional forward pointers** in some of the nodes. A chain augmented with forward pointers in this way is called a **skip list**.

A skip list uses a randomization technique to decide where and how many additional forward pointers to put. As a result, insertion and deletion perform better than on a sorted array, and the expected time of search, insertion, and deletion is $O(\log n)$. The worst-case time, however, is $\Theta(n)$ (Sections 2.4 and 2.5).

### 2.2 Structure and Levels

A skip list is built by adding forward pointers to a sorted chain with a head node and a tail node. The head node is where the chains of all levels start, and the tail node is where the chains of all levels end. The chain of each level is built as follows.

- The **level 0** chain includes **all elements**.
- The **level 1** chain includes one element out of **every 2**.
- The **level 2** chain includes one element out of **every 4**.
- The **level $i$** chain includes one element out of every $2^i$. For example, the level 3 chain includes every $2^3 = 8$th element.

> **Definition:** An element is a **level $i$ element** if it is in the chains for levels 0 through $i$. Since a level 3 element is also in the chains for levels 0-2, the level of an element is taken to be the number of the highest chain that contains it.

```text
Level 2:  H ───────────────────────> 40 ───────────────────────> T
Level 1:  H ─────────> 24 ─────────> 40 ─────────> 75 ─────────> T
Level 0:  H ──> 20 ──> 24 ──> 30 ──> 40 ──> 60 ──> 75 ──> 80 ──> T
```

*Figure 1. Skip list linking 7 elements in the regular structure*

In Figure 1, H and T are the head and tail nodes. The level 1 chain includes the 2nd, 4th, and 6th elements 24, 40, and 75, and the level 2 chain includes the 4th element 40. Thus 40 is a level 2 element, 24 and 75 are level 1 elements, and the rest are level 0 elements.

In general, a fraction $p$ of the elements in the level $i-1$ chain are also in the level $i$ chain. The regular structure of Figure 1 is the case $p = 1/2$.

> **Key Point:** The number of levels of a skip list holding $n$ elements is $\lfloor \log_{1/p} n \rfloor + 1$. Since levels are numbered from 0, the highest level is level $\lfloor \log_{1/p} n \rfloor$. With $p = 1/2$ and 8 elements, $\log_2 8 = 3$, so there are 4 levels, level 0 through level 3; with 9 elements there are $\lfloor \log_2 9 \rfloor + 1 = \lfloor 3.17 \rfloor + 1 = 4$ levels.

### 2.3 Search Operation

To search for key $k$, start at the **highest level** of the head node and traverse right.

1. At the current level, move right while the next node's key is less than $k$.
2. If the next node's key equals $k$, the element is found.
3. If the next node's key is greater than $k$ or the next node is the tail, drop down one level.
4. Repeat until the element is found or no further progress is possible at level 0. The position where the search stops at level 0 is also where $k$ would be inserted.

**Example 1 (regular structure).** Searching for 77 in the skip list of Figure 1 proceeds as follows. The tail node is treated as larger than every key and is not counted as a key comparison.

1. Level 2: compare with 40 and move right; the next node is the tail, so drop down.
2. Level 1: compare with 75 and move right; the next node is the tail, so drop down.
3. Level 0: compare with 80; since 80 > 77, stop. 77 is not present, and the insertion position is between 75 and 80.

The search stops once at each of levels 2, 1, and 0, three times in all (at 40, at 75, and between 75 and 80). Inserting 77 as a level 0 element gives Figure 2; with 8 elements, the number of levels traversed, 3, equals $\log_2 8$.

```text
Level 2:  H ───────────────────────> 40 ──────────────────────────────> T
Level 1:  H ─────────> 24 ─────────> 40 ─────────> 75 ────────────────> T
Level 0:  H ──> 20 ──> 24 ──> 30 ──> 40 ──> 60 ──> 75 ──> 77 ──> 80 ──> T
```

*Figure 2. Skip list after inserting 77 into Figure 1 as a level 0 element*

In the regular structure there are $\lfloor \log_2 n \rfloor + 1$ levels and the search moves right at most once per level, so each level takes at most 2 key comparisons. The search time is therefore $O(\log n)$.

**Example 2 (effect of the structure).** Figures 3 and 4 are both level 3 skip lists with levels 0 through 3.

```text
Level 3:  H ──> 30 ────────────────────────────────────────────> NIL
Level 2:  H ──> 30 ────────────────────────────────────────────> NIL
Level 1:  H ──> 30 ────────────────────────────────────────────> NIL
Level 0:  H ──> 30 ──> 40 ──> 50 ──> 60 ──> 70 ──> 80 ──> 95 ──> NIL
```

*Figure 3. Level 3 skip list whose upper levels contain only element 30*

```text
Level 3:  H ──> 30 ─────────────────────────────────────> NIL
Level 2:  H ──> 30 ─────────> 50 ───────────────────────> NIL
Level 1:  H ──> 30 ─────────> 50 ─────────> 70 ─────────> NIL
Level 0:  H ──> 30 ──> 40 ──> 50 ──> 60 ──> 70 ──> 90 ──> NIL
```

*Figure 4. Level 3 skip list whose upper levels spread elements evenly*

The number of key comparisons needed to find where a new element 85 goes in the level 0 list is as follows (NIL is the tail).

- Figure 3: compare with 30 at level 3 and move right; at levels 3, 2, and 1 the next node is NIL, so drop down immediately. At level 0 the search passes 40, 50, 60, 70, and 80 and stops at 95, so there are 7 key comparisons in all.
- Figure 4: compare with 30 at level 3, 50 at level 2, and 70 at level 1, moving right each time, and drop down when the next node is NIL. At level 0 the search compares with 90 and stops, so there are 4 key comparisons in all.

When the upper levels barely narrow the search range, as in Figure 3, the search becomes similar to a sequential search of level 0.

### 2.4 Insertion and Deletion

Keeping the regular structure (in which the level $i$ chain contains exactly every $2^i$th element) after an insertion or deletion requires $O(n)$ work, because inserting or removing one element changes the rank of every element after it. A skip list therefore chooses the level of a new element at random.

**Insertion:**
- Choose the level of the new element so that it enters the chains up to level $i$ with probability $p^i$. Typically $p = 1/2$, but $p = 1/3$ or $p = 1/4$ can also be used.
- With $p = 1/2$, the probability that a new element enters the chains up to level $i$ is $1/2^i$. For example, the probability that it reaches the level 2 chain is $1/2^2 = 1/4 = 25\%$.
- After choosing the level, update the forward pointers of the last node met at each level on the search path, linking the new node into the chains from level 0 up to the chosen level.

> **Note:** **Interpreting the probability.** To reach the level $i$ chain, an element must be promoted with probability $p$ at every level from 1 to $i$, so the probability is $p^i$. For its level to be exactly $i$, it must also not be promoted to level $i+1$, so when the highest level is unbounded that probability is $p^i(1-p)$. With $p = 1/2$, the probability of reaching the level 2 chain is 1/4, and the probability that the level is exactly 2 is 1/8.

When levels are chosen at random, the level $i$ chain does not contain exactly every $2^i$th element. Figure 5 links the same elements as Figure 1 with random levels: the level 1 chain contains 24, 40, 60, and 80, and the level 2 chain contains 40 and 80. The search method is the same.

```text
Level 2:  H ───────────────────────> 40 ────────────────> 80 ──> T
Level 1:  H ─────────> 24 ─────────> 40 ──> 60 ─────────> 80 ──> T
Level 0:  H ──> 20 ──> 24 ──> 30 ──> 40 ──> 60 ──> 75 ──> 80 ──> T
```

*Figure 5. Skip list with randomly chosen levels*

**Example 3.** Searching for 77 in Figure 5 proceeds as follows.

1. Start at level 2: compare with 40 (move right), then compare with 80 (drop down).
2. At level 1: compare with 60 (move right), then compare with 80 (drop down).
3. At level 0: compare with 75 (move right), then compare with 80. 77 is not present, and the insertion position is between 75 and 80.

The search goes through 3 levels and makes 6 key comparisons in all.

**Deletion:**
- Locate the element using the search procedure.
- Remove it from the chains of all levels in which it appears.
- Update the forward pointer of the preceding node at each level.
- Since a deletion does not change the levels of other elements, we have no control over the structure that is left following a deletion.

> **Key Point:** Keeping the regular structure requires $O(n)$ work per insertion and deletion. With randomly chosen levels, the expected time of insertion and deletion is $O(\log n)$, but the worst case is $\Theta(n)$.

### 2.5 Worst-Case Time Complexity

At level $i$ every $2^i$th node is linked, so at level 0 all nodes are linked ($2^0 = 1$). If the random levels leave all elements at **level 0 only** (no higher-level pointers), the skip list degenerates into a simple sorted linked list. In this case a search may have to pass every node of level 0, so the following holds.

$$T_{\text{worst}}(n) = \Theta(n)$$

### 2.6 Average-Case Time Complexity

To analyze the **expected** search time, we trace the search path **backwards** (traveling up and to the left). Starting from the search target node X and following the search path in reverse, we move up when the node has a higher-level pointer and move left otherwise, eventually reaching the highest level of the head node. The backward path has the same length as the original search path, so we analyze the cost of climbing instead of the search cost.

Let $C(i)$ be the expected cost of climbing $i$ levels backward. Let $p$ be the probability that a node has a higher-level pointer; it is a constant. At each node there are two cases.

- **Case 1** (probability $1 - p$): The node has no higher-level pointer. After moving one step left (cost 1), $i$ levels still remain to be climbed, so the cost is $C(i) + 1$.
- **Case 2** (probability $p$): The node has a higher-level pointer. After moving one level up (cost 1), the remaining $i-1$ levels must be climbed, so the cost is $C(i-1) + 1$.

$$C(i) = (1-p)(1 + C(i)) + p(1 + C(i-1))$$

Expanding the right side gives $C(i) = 1 + C(i) - p - pC(i) + p + pC(i-1)$, which simplifies to $pC(i) = 1 + pC(i-1)$, that is, $C(i) = \frac{1}{p} + C(i-1)$. Substituting repeatedly gives the following.

$$C(i) = \frac{1}{p} + C(i-1) = \frac{2}{p} + C(i-2) = \frac{3}{p} + C(i-3) = \cdots = \frac{i}{p} + C(0)$$

Solving the recurrence with $C(0) = 0$:

$$C(i) = \frac{i}{p}$$

Since the maximum level is $i = \log_{1/p} n$ ($n$ is the number of nodes), the following holds.

$$\Theta(C(i)) = \Theta\left(\frac{\log_{1/p} n}{p}\right) = \Theta(\log n) = O(\log n)$$

Since $p$ is a constant, the factor $1/p$ and the logarithm base $1/p$ change the result only by a constant factor. Intuitively, with $p = 1/2$ each drop by one level halves the search range as in bisection, so the average search time is proportional to about $\log_2 n$.

> **[Probability and Statistics]** The number of independent trials with success probability $p$ performed until the first success follows a geometric distribution with expected value $1/p$. In the backward search, climbing one level is a sequence of such trials in which each node succeeds (moves up) with probability $p$, so climbing one level takes $1/p$ expected steps and climbing $i$ levels takes $i/p$. This agrees with the solution $C(i) = i/p$ of the recurrence.

> **Note:** **Exam tip.** The average-case analysis is a classic problem of setting up and solving a recurrence. With $p = 1/2$, the average search time is $O(\log n)$, essentially equivalent to binary search on a sorted array, while insertion and deletion are also efficient.

---

<br>

## 3. Hashing

### 3.1 Ideal Hashing

A **hash table** is an alternative method for representing a dictionary. A hash table uses a **hash function** to map keys into positions in the table, and this act is called **hashing**. Hash tables are used in many real-world applications.

In **ideal hashing**, the pair whose key is $k$ is stored in position $h(k)$ of the table, and no two different keys map to the same position. The operations are then as follows.

1. **Search:** Compute $h(k)$ and see whether a pair exists in that position.
2. **Insert:** Compute $h(k)$ and place the pair in that position.
3. **Delete:** Compute $h(k)$ and delete the pair in that position.

In the ideal situation, search, insert, and delete all take $\Theta(1)$.

The simplest way to guarantee ideal hashing is **direct addressing**, which uses the key itself as the array index.

- Store the element with key $k$ in `table[k]`.
- Search, insert, and delete are all $O(1)$.

**Limitation:** If the key range is enormous (e.g., 9-digit student IDs), the table would require $10^9$ buckets, which is impractical.

### 3.2 Hash Functions

Each position of a hash table is called a **bucket**, and for the pair whose key is $k$, the position indicated by $h(k)$ is the **home bucket** of that pair. With $m$ buckets, a **hash function** $h(k)$ maps keys to the table index range $[0, m-1]$.

$$h: K \rightarrow \{0, 1, 2, \ldots, m-1\}$$

A hash function has two parts.

1. Convert the key into an integer if it is not an integer.
2. Map the integer into a home bucket. The result $h(k)$ is an integer in the range $[0, m-1]$.

The most common mapping method is division. The home bucket is computed as `homeBucket = k % divisor`, and since the divisor equals the number of buckets $m$, the home bucket is at least 0 and less than $m$.

**Converting a string to an integer.** Assume that each character is 2 bytes long and an integer is 4 bytes long. Then a 2-character string `s` can be converted into a unique 4-byte integer by the following code.

```cpp
int answer = (int) s[0];
answer = (answer << 16) + (int) s[1];
```

The first line converts the character code of the first character into an integer. The second line shifts that value 16 bits to the left into the upper 2 bytes and adds the code of the second character into the lower 2 bytes. For example, if `s` is `"AB"`, `answer` is $65 \times 2^{16} + 66 = 4259906$. A 4-byte integer holds only as much information as two 2-byte characters, so strings longer than 2 characters cannot have a unique integer representation under this scheme.

**Common hash functions:**

| Function | Formula | Notes |
|:---------|:--------|:------|
| Division | $h(k) = k \mod m$ | Choose $m$ as a prime or a number with no prime factor less than 20 (Section 3.7), and avoid numbers close to a power of 2 |
| Multiplication | $h(k) = \lfloor m(kA \mod 1) \rfloor$ | $A \approx 0.6180$ (the reciprocal of the golden ratio, $(\sqrt{5}-1)/2$) |
| Folding | Split key into parts, add them | Good for string keys |

*Table 3. Common hash functions*

Designing a hash table requires choosing the hash function, the overflow handling method, and the size (number of buckets) of the hash table.

### 3.3 Collisions and Overflows

**Example of ideal hashing.** Store the pairs (22,a), (33,c), (3,d), (72,e), and (85,f) in a hash table `ht[0:7]` with $m = 8$ buckets using the hash function $h(k) = k \mod 8$. The home buckets $22 \mod 8 = 6$, $33 \mod 8 = 1$, $3 \mod 8 = 3$, $72 \mod 8 = 0$, and $85 \mod 8 = 5$ are all different, so every pair goes into its home bucket.

```text
  [0]     [1]     [2]     [3]     [4]     [5]     [6]     [7]
(72,e)  (33,c)     -     (3,d)     -     (85,f)  (22,a)    -
```

*Figure 6. Hash table of the ideal hashing example*

Now insert (25,g): $25 \mod 8 = 1$, but bucket 1 is already occupied by (33,c).

> **Key Point:** A **collision** occurs when two different keys map to the same index: $h(k_1) = h(k_2)$ where $k_1 \neq k_2$. Collision resolution is the central challenge in hashing.

- A **collision** is the situation in which the home bucket of a new pair is already occupied by a pair with a different key.
- Keys that have the same home bucket are called **synonyms** with respect to the hash function. In the example above, 25 and 33 are synonyms with respect to $h(k) = k \mod 8$.
- An **overflow** occurs when there is no space in the home bucket for the new pair. When a bucket can hold only one pair, collisions and overflows occur together.

There are two ways to handle overflows.

1. **Open addressing:** Search the table in some systematic fashion for a bucket that is not full. Methods include linear probing (linear open addressing), quadratic probing, and random probing (Section 3.4).
2. **Chaining:** Eliminate overflows by letting each bucket keep a list of all pairs for which it is the home bucket. The list is implemented as an array linear list or a chain (Section 3.5).

### 3.4 Collision Resolution: Open Addressing

In open addressing, all elements are stored within the hash table itself. When a collision occurs, buckets are probed in a fixed order to find an empty one. In the formulas below, $h_i(k)$ is the bucket examined by the $i$th probe.

**Linear Probing:**
$$h_i(k) = (h(k) + i) \mod m, \quad i = 0, 1, 2, \ldots$$

When a collision occurs, the entry goes into the next available bucket, regarding the table as circular. For this reason linear probing is also called linear open addressing.

- Simple but suffers from **primary clustering**: long runs of consecutive occupied buckets form.

**Example of linear probing.** Inserting the keys 80, 40, and 65 into a table with $m = 11$ buckets and $h(k) = k \mod 11$ puts each into its home bucket, since $80 \mod 11 = 3$, $40 \mod 11 = 7$, and $65 \mod 11 = 10$ ((a) in Figure 7). Next, 58 collides at $58 \mod 11 = 3$ and goes into the next empty bucket 4, and 24 goes into $24 \mod 11 = 2$ (b). Finally, 35 collides at $35 \mod 11 = 2$, and since buckets 3 and 4 are also occupied, it goes into bucket 5 (c).

```text
      [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9]  [10]
(a)    -    -    -   80    -    -    -   40    -    -    65
(b)    -    -   24   80   58    -    -   40    -    -    65
(c)    -    -   24   80   58   35    -   40    -    -    65
```

*Figure 7. Changes of a hash table as keys are inserted with linear probing*

**Search.** The search for key $k$ begins at the home bucket $h(k)$ and examines successive buckets until one of the following happens.

1. A bucket containing an element with key $k$ is reached.
2. An empty bucket is reached.
3. The search returns to the home bucket.

In cases 2 and 3, the table contains no element with key $k$.

**Deletion.** After finding the bucket holding key $k$ by a search and clearing it, do one of the following.

- Move zero or more of the following elements to fill the empty bucket.
- Introduce and use a `NeverUsed` field in each bucket.

If the bucket is only cleared, a later search for an element further along the same cluster stops at the empty bucket and may wrongly conclude that an existing element is absent. The `NeverUsed` field records whether a bucket has ever been used, and a search stops only at a bucket that has never been used.

**Performance of linear probing.** The worst-case search, insert, and delete time is $\Theta(n)$, where $n$ is the number of pairs in the table. This happens when all keys have the same home bucket or the table is full. In the worst case, a hash table and a linear list perform the same, $\Theta(n)$, but on average hashing is much better (Section 3.6).

**Quadratic Probing:**
$$h_i(k) = (h(k) + i^2) \mod m, \quad i = 0, 1, 2, \ldots$$

- Reduces primary clustering but may cause **secondary clustering**, because keys with the same home bucket follow the same probe sequence.

**Random Probing:** Examine, one after another, the buckets at offsets from the home bucket given by a pseudo-random sequence.

**Double Hashing:**
$$h_i(k) = (h_1(k) + i \cdot h_2(k)) \mod m$$

- Uses a second hash function to determine the probe step.
- Gives the best distribution among open addressing methods.

### 3.5 Collision Resolution: Chaining

In **separate chaining**, each bucket holds a pointer to a linked list of all elements that hash to that index. Figure 8 is an example hashed with $h(k) = k \mod 10$.

```text
Index 0: → [20] → [40] → NULL
Index 1: → [31] → NULL
Index 2: → [12] → [52] → NULL
...
```

*Figure 8. Hash table built with separate chaining*

- No clustering problems.
- The table can hold more elements than its number of buckets (load factor $\alpha > 1$ is possible).
- Each chain can be a sorted or unsorted linked list, and an array linear list can be used instead of a chain.

### 3.6 Performance Comparison

Let $\alpha = n/m$ be the **load factor** (ratio of the number of elements to the number of buckets), where $n$ is the number of stored pairs and $m$ is the number of buckets. Expected performance is described by the following two values.

- $S_n$: the average number of buckets examined in a successful search
- $U_n$: the average number of buckets examined in an unsuccessful search

The time to insert and delete is governed by $U_n$. An insertion must go through an unsuccessful search that confirms the key is absent, and a deletion under linear probing examines the following buckets until an empty one appears in order to fill the emptied bucket.

| Method | Successful Search | Unsuccessful Search |
|:-------|:-----------------|:-------------------|
| Linear Probing | $\frac{1}{2}\left(1 + \frac{1}{1-\alpha}\right)$ | $\frac{1}{2}\left(1 + \frac{1}{(1-\alpha)^2}\right)$ |
| Quadratic / Double | $-\frac{1}{\alpha}\ln(1-\alpha)$ | $\frac{1}{1-\alpha}$ |
| Chaining | $1 + \frac{\alpha}{2}$ | $1 + \alpha$ |

*Table 4. Average number of probes by collision resolution method*

All formulas in Table 4 are approximations. The row for quadratic probing and double hashing assumes that the probe sequence is random, and quadratic probing, which has secondary clustering, does slightly worse than these values. In open addressing all elements are inside the table, so $0 \le \alpha \le 1$. Substituting load factors into the linear probing formulas gives the following.

| Load Factor $\alpha$ | $S_n$ (buckets) | $U_n$ (buckets) |
|:-----|:-----|:-----|
| 0.50 | 1.5 | 2.5 |
| 0.75 | 2.5 | 8.5 |
| 0.90 | 5.5 | 50.5 |

*Table 5. Average number of buckets examined by linear probing for each load factor*

> **Key Point:** Chaining generally outperforms open addressing when the load factor is high. For low load factors ($\alpha < 0.5$), all methods perform similarly.

### 3.7 Hash Table Design

In practice, the choice of the divisor $D$ (equal to the number of buckets $m$ in the division method) has a significant effect on the performance of hashing. The best results are obtained when $D$ is a prime or has no prime factors less than 20. There are two methods for determining $D$.

**Method 1.**
1. First, determine what constitutes acceptable performance.
2. Using the formulas for $S_n$ and $U_n$, determine the largest $\alpha$ that can be used.
3. From $n$ and the computed $\alpha$, obtain the smallest permissible $m$.

For example, to store $n = 600$ pairs with linear probing while requiring $S_n \le 2.5$ and $U_n \le 8.5$, Table 5 gives $\alpha \le 0.75$, so $m \ge 600 / 0.75 = 800$. The smallest number of at least 800 that is a prime or has no prime factor less than 20 is the prime 809, so set $D = m = 809$.

**Method 2.**
1. Begin with the largest possible $m$ as determined by the maximum amount of space available.
2. Find the largest $D$ no larger than this value that is a prime or has no prime factors less than 20.

For example, if at most 530 buckets are available, $530 = 2 \times 5 \times 53$ does not qualify, while $529 = 23^2$ has no prime factor less than 20, so $D = 529$.

---

<br>

## 4. Appendix

### 4.1 Real-World Applications

- **Hash maps** (C++ `unordered_map`, Java `HashMap`, Python `dict`) use chaining or open addressing internally.
- **Skip lists** are used in Redis (sorted sets), LevelDB, and concurrent data structures.
- **Bloom filters** are data structures that extend hashing for probabilistic membership testing.

### 4.2 Interview Tips

- Be able to explain the differences between open addressing and chaining (where elements are stored, clustering, and the allowed load factor).
- Be able to analyze collision probability and expected probe lengths.
- Skip lists are a common alternative to balanced binary search trees (Lecture 10) in system design.

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:----------|
| Dictionary ADT | A dictionary is a collection of (key, value) pairs that supports search, insertion, and deletion. |
| Skip List | A skip list is a multi-level linked list that adds forward pointers to a sorted chain and gives $O(\log n)$ expected search, insertion, and deletion time. |
| Skip List Levels | In the regular structure level $i$ includes every $2^i$th element, and the number of levels is $\lfloor \log_{1/p} n \rfloor + 1$, which is $\lfloor \log_2 n \rfloor + 1$ for $p = 1/2$. |
| Level Assignment | The level of a new element is chosen at random so that it enters the chains up to level $i$ with probability $p^i$. |
| Skip List Worst Case | If all elements are at level 0 only, the skip list degenerates into a linked list and takes $\Theta(n)$. |
| Skip List Average Case | The solution $C(i) = i/p$ of the backward-analysis recurrence yields $O(\log n)$. |
| Hash Function | A hash function maps keys to home bucket indices, and collisions must be resolved. |
| Collision and Overflow | A collision is when the home bucket is occupied by a pair with a different key, and an overflow is when the home bucket has no space for the new pair. |
| Open Addressing | Open addressing finds an empty bucket within the table by linear probing, quadratic probing, random probing, or double hashing. |
| Deletion in Linear Probing | After clearing a bucket, elements must be moved or a `NeverUsed` field must be used so that searches do not stop wrongly. |
| Chaining | In chaining, each bucket holds a linked list of the colliding elements. |
| Load Factor $\alpha$ | The load factor is $\alpha = n/m$, and higher values increase collision frequency. |
| Choice of Divisor | The divisor $D$ is chosen as a prime or a number with no prime factor less than 20. |

---

<br>

## Self-Check Questions

1. **Number of levels:** For a skip list holding 100 elements, find the number of levels and the highest level number when $p = 1/2$ and when $p = 1/4$.

   <details>
   <summary>Answer</summary>

   With $p = 1/2$, $\log_2 100 \approx 6.64$, so there are $\lfloor 6.64 \rfloor + 1 = 7$ levels and the highest level is level 6. With $p = 1/4$, $\log_4 100 \approx 3.32$, so there are $3 + 1 = 4$ levels and the highest level is level 3. A smaller $p$ promotes fewer elements to upper levels, so there are fewer levels.

   </details>

2. **Random level assignment:** Explain why a skip list chooses the level of a new element at random instead of keeping the regular structure, and what it pays for this.

   <details>
   <summary>Answer</summary>

   In the regular structure, the level $i$ chain must contain exactly every $2^i$th element. Inserting or deleting one element changes the rank of every element after it, so keeping the structure requires fixing the levels of $O(n)$ nodes. With random levels, only the pointers on the search path change and no other node is touched, so the expected time becomes $O(\log n)$. The price is that performance is guaranteed only probabilistically: with bad luck all elements end up at level 0 and the worst case takes $\Theta(n)$, and the structure left after a deletion cannot be controlled.

   </details>

3. **Collision and overflow:** In the table of Figure 6, suppose each bucket can hold up to 2 pairs. Does inserting (25,g) cause a collision or an overflow? What happens if each bucket can hold only 1 pair?

   <details>
   <summary>Answer</summary>

   $25 \mod 8 = 1$, and bucket 1 holds (33,c), which has a different key, so a collision occurs. 25 and 33 are synonyms. If a bucket can hold 2 pairs, bucket 1 still has space, so no overflow occurs and (25,g) is stored in bucket 1 together with (33,c). If a bucket can hold only 1 pair, the home bucket has no space, so a collision and an overflow occur together and must be handled by open addressing or chaining.

   </details>

4. **Deletion in linear probing:** In the table of Figure 7 (c), what happens to a search for 35 if 58 is deleted by merely clearing bucket 4? Give two ways to prevent this.

   <details>
   <summary>Answer</summary>

   The home bucket of 35 is 2. The search passes bucket 2 (24) and bucket 3 (80) and stops at the empty bucket 4, so it wrongly concludes that 35 is absent even though 35 is in bucket 5. The first way is to move the elements after the cleared bucket. Since the home bucket of 35 in bucket 5 is 2, its probe path 2, 3, 4, 5 contains the cleared bucket 4, so 35 can move to bucket 4, and the moving ends because the next bucket 6 is empty. The second way is to use a `NeverUsed` field. Bucket 4 has been used, so its `NeverUsed` is false, and the search passes bucket 4 and finds 35 in bucket 5.

   </details>

5. **Choosing the number of buckets:** You want to store 1000 pairs with linear probing with $S_n \le 2$ and $U_n \le 5$. Find the largest usable $\alpha$, the smallest number of buckets $m$, and the divisor $D$ by Method 1.

   <details>
   <summary>Answer</summary>

   From $\frac{1}{2}\left(1 + \frac{1}{1-\alpha}\right) \le 2$ we get $\frac{1}{1-\alpha} \le 3$, so $\alpha \le 2/3$. From $\frac{1}{2}\left(1 + \frac{1}{(1-\alpha)^2}\right) \le 5$ we get $(1-\alpha)^2 \ge 1/9$, so again $\alpha \le 2/3$. Thus the largest $\alpha$ is $2/3$, and $m \ge 1000 / (2/3) = 1500$. From 1500 upward, 1500, 1502, 1504, and so on are divisible by 2, 1503 and 1509 by 3, 1505 by 5, 1507 by 11, and 1501 by 19, so they are excluded; 1511 is a prime, so $D = m = 1511$.

   </details>
