# Chapter 07 — Quiz

> **Last Updated:** 2026-03-21

---

## Q1. Skip List Search Path

**Question:** In a skip list with levels 0-2 containing elements {20, 24, 30, 40, 60, 75, 80} where level 2 has {40, 80}, level 1 has {24, 40, 60, 80}, and level 0 has all elements, trace the search path for key 75.

**Answer:** Start at level 2 head: compare with 40 (go right), compare with 80 (80 > 75, drop down). At level 1: compare with 60 (go right), compare with 80 (80 > 75, drop down). At level 0: compare with 75 (found). Total comparisons: 5.

**Explanation:** Skip list search begins at the highest level and moves right while the next key is less than the target. When the next key exceeds the target or is the tail, we drop down one level. This achieves $O(\log n)$ expected search time by skipping over elements at higher levels.

---

## Q2. Skip List Level Assignment

**Question:** In a skip list with $p = 1/2$, what is the probability that a newly inserted element is assigned level 3? How many levels are expected for $n = 16$ elements?

**Answer:** The probability of being level 3 is $(1/2)^3 = 1/8$. For $n = 16$, the expected number of levels is $\lfloor \log_2 16 \rfloor + 1 = 5$.

**Explanation:** Each element is promoted to the next level with probability $p = 1/2$. The probability of reaching level $i$ is $p^i = (1/2)^i$. The maximum level is $\lfloor \log_{1/p} n \rfloor + 1$, which for $p = 1/2$ gives $\log_2 n + 1$.

---

## Q3. Hash Table Linear Probing

**Question:** Given a hash table of size 11 with hash function $h(k) = k \mod 11$ and linear probing, insert the keys: 20, 31, 24, 9, 35, 42. Show the final state of the table.

**Answer:**
- $h(20) = 9$ -> slot 9
- $h(31) = 9$ -> collision, probe to slot 10
- $h(24) = 2$ -> slot 2
- $h(9) = 9$ -> collision at 9, 10; probe to slot 0
- $h(35) = 2$ -> collision at 2; probe to slot 3
- $h(42) = 9$ -> collision at 9, 10, 0; probe to slot 1

Final table: [0]=9, [1]=42, [2]=24, [3]=35, [4..8]=empty, [9]=20, [10]=31.

**Explanation:** Linear probing resolves collisions by trying $h_i(k) = (h(k) + i) \mod m$ for $i = 0, 1, 2, \ldots$. This creates clusters of occupied cells (primary clustering), which increases the average probe length for subsequent insertions.

---

## Q4. Chaining vs. Open Addressing

**Question:** A hash table has $n = 100$ elements and $m = 200$ slots (load factor $\alpha = 0.5$). Compare the expected number of probes for a successful search using linear probing vs. chaining.

**Answer:** Linear probing: $\frac{1}{2}(1 + \frac{1}{1-\alpha}) = \frac{1}{2}(1 + \frac{1}{0.5}) = \frac{1}{2}(1 + 2) = 1.5$ probes. Chaining: $1 + \frac{\alpha}{2} = 1 + 0.25 = 1.25$ probes.

**Explanation:** Chaining slightly outperforms linear probing because it does not suffer from primary clustering. As $\alpha$ increases, the performance gap widens significantly. At $\alpha = 0.9$, linear probing requires 5.5 probes while chaining requires only 1.45.

---

## Q5. Skip List Average-Case Analysis

**Question:** Derive the expected search time of a skip list using backward analysis. Let $C(i)$ be the expected cost of climbing $i$ levels. Write the recurrence and solve it for $p = 1/2$.

**Answer:** At each node during backward traversal: with probability $1-p$, the node has no higher pointer (cost $1 + C(i)$); with probability $p$, the node has a higher pointer (cost $1 + C(i-1)$). Recurrence: $C(i) = (1-p)(1+C(i)) + p(1+C(i-1))$. Solving with $C(0) = 0$ yields $C(i) = i/p$. For $p = 1/2$: $C(\log_2 n) = 2\log_2 n = O(\log n)$.

**Explanation:** The backward analysis traces the search path in reverse (up and to the left). The recurrence captures the expected number of steps to climb $i$ levels. Since each level takes $1/p$ expected steps and there are $\log_{1/p} n$ levels, the total expected time is $\frac{\log n}{p} = O(\log n)$.
