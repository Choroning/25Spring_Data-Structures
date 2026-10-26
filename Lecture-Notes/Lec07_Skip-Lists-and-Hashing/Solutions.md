# Lecture 7 Solutions — Skip Lists and Hashing

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-26

---

<br>

## Table of Contents

- [Exercise 1: Skip List Search Path](#exercise-1-skip-list-search-path)
- [Exercise 2: Skip List Level Assignment](#exercise-2-skip-list-level-assignment)
- [Exercise 3: Hash Table Linear Probing](#exercise-3-hash-table-linear-probing)
- [Exercise 4: Chaining vs. Open Addressing](#exercise-4-chaining-vs-open-addressing)
- [Exercise 5: Skip List Average-Case Analysis](#exercise-5-skip-list-average-case-analysis)

---

<br>

## Exercise 1: Skip List Search Path

**Problem:** In a skip list with levels 0-2 containing elements {20, 24, 30, 40, 60, 75, 80} where level 2 has {40, 80}, level 1 has {24, 40, 60, 80}, and level 0 has all elements (Figure 1), trace the search path for key 75.

```text
Level 2:  H ───────────────────────> 40 ────────────────> 80 ──> T
Level 1:  H ─────────> 24 ─────────> 40 ──> 60 ─────────> 80 ──> T
Level 0:  H ──> 20 ──> 24 ──> 30 ──> 40 ──> 60 ──> 75 ──> 80 ──> T
```

*Figure 1. Skip list of Exercise 1*

### Solution

**Answer:** Start at the level 2 head: compare with 40 (go right), then compare with 80 (80 > 75, drop down). At level 1, continuing from 40: compare with 60 (go right), then compare with 80 (80 > 75, drop down). At level 0, continuing from 60: compare with 75 (found). Total comparisons: 5.

**Explanation:** Skip list search begins at the highest level and moves right while the next key is less than the target. When the next key exceeds the target or is the tail, the search drops down one level. At a lower level the search continues from the node where it stopped on the level above, so 20, 24, 30, and 40 are not compared again at level 0. Skipping over elements at higher levels in this way achieves $O(\log n)$ expected search time.

---

<br>

## Exercise 2: Skip List Level Assignment

**Problem:** In a skip list with $p = 1/2$, what is the probability that a newly inserted element is assigned level 3? How many levels are expected for $n = 16$ elements?

### Solution

**Answer:** The probability of reaching the level 3 chain is $(1/2)^3 = 1/8$. For $n = 16$, the number of levels is $\lfloor \log_2 16 \rfloor + 1 = 5$ (level 0 through level 4).

**Explanation:** Each element is promoted to the next level with probability $p = 1/2$. The probability of reaching the level $i$ chain is $p^i = (1/2)^i$. For the level to be exactly 3, the element must also not be promoted to level 4, so when the highest level is unbounded that probability is $(1/2)^3 \times (1/2) = 1/16$. The number of levels is $\lfloor \log_{1/p} n \rfloor + 1$ and the highest level is level $\lfloor \log_{1/p} n \rfloor$; for $p = 1/2$ and $n$ a power of 2, the number of levels is $\log_2 n + 1$. This is the number of levels of the regular structure; with randomly chosen levels, the actual number of levels may differ from it.

---

<br>

## Exercise 3: Hash Table Linear Probing

**Problem:** Given a hash table of size 11 with hash function $h(k) = k \mod 11$ and linear probing, insert the keys 20, 31, 24, 9, 35, 42. Show the final state of the table.

### Solution

**Answer:**
- $h(20) = 9$ → bucket 9
- $h(31) = 9$ → collision, probe to bucket 10
- $h(24) = 2$ → bucket 2
- $h(9) = 9$ → collision at 9, 10; probe to bucket 0
- $h(35) = 2$ → collision at 2; probe to bucket 3
- $h(42) = 9$ → collision at 9, 10, 0; probe to bucket 1

Final table: [0]=9, [1]=42, [2]=24, [3]=35, [4]-[8]=empty, [9]=20, [10]=31.

```text
 [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9]  [10]
  9   42   24   35    -    -    -    -    -   20    31
```

*Figure 2. Final hash table of Exercise 3*

**Explanation:** Linear probing resolves collisions by trying $h_i(k) = (h(k) + i) \mod m$ for $i = 0, 1, 2, \ldots$, wrapping from bucket 10 back to bucket 0. This creates clusters of occupied buckets (primary clustering), which increases the average probe length for subsequent insertions. In this example, too, buckets 9, 10, and 0 form a run of occupied buckets, so 42 finds the empty bucket 1 only on the fourth probe, and buckets 9 through 3 then form one cluster.

---

<br>

## Exercise 4: Chaining vs. Open Addressing

**Problem:** A hash table has $n = 100$ elements and $m = 200$ buckets (load factor $\alpha = 0.5$). Compare the expected number of probes for a successful search using linear probing vs. chaining.

### Solution

**Answer:** Linear probing: $\frac{1}{2}(1 + \frac{1}{1-\alpha}) = \frac{1}{2}(1 + \frac{1}{0.5}) = \frac{1}{2}(1 + 2) = 1.5$ probes. Chaining: $1 + \frac{\alpha}{2} = 1 + 0.25 = 1.25$ probes.

**Explanation:** Chaining slightly outperforms linear probing because it does not suffer from primary clustering. As $\alpha$ increases, the performance gap widens significantly. At $\alpha = 0.9$, linear probing requires $\frac{1}{2}(1 + \frac{1}{0.1}) = 5.5$ probes, while chaining requires only $1 + \frac{0.9}{2} = 1.45$.

---

<br>

## Exercise 5: Skip List Average-Case Analysis

**Problem:** Derive the expected search time of a skip list using backward analysis. Let $C(i)$ be the expected cost of climbing $i$ levels. Write the recurrence and solve it for $p = 1/2$.

### Solution

**Answer:** At each node during backward traversal, with probability $1-p$ the node has no higher pointer (cost $1 + C(i)$), and with probability $p$ the node has a higher pointer (cost $1 + C(i-1)$). The recurrence is as follows.

$$C(i) = (1-p)(1+C(i)) + p(1+C(i-1))$$

Simplifying gives $pC(i) = 1 + pC(i-1)$, that is, $C(i) = \frac{1}{p} + C(i-1)$. Solving with $C(0) = 0$ yields $C(i) = i/p$. For $p = 1/2$, substituting $i = \log_2 n$, which corresponds to the number of the top level, gives $C(\log_2 n) = 2\log_2 n = O(\log n)$.

**Explanation:** The backward analysis traces the search path in reverse (up and to the left). The recurrence captures the expected number of steps to climb $i$ levels. Since each level takes $1/p$ expected steps and the climb to the top level covers $\log_{1/p} n$ levels, the total expected time is $\frac{\log_{1/p} n}{p} = O(\log n)$.
