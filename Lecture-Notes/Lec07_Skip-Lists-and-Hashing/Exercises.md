# Lecture 7 Exercises — Skip Lists and Hashing

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-18

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

**[Solution](Solutions.md#exercise-1-skip-list-search-path)**

---

<br>

## Exercise 2: Skip List Level Assignment

**Problem:** In a skip list with $p = 1/2$, what is the probability that a newly inserted element is assigned level 3? How many levels are expected for $n = 16$ elements?

**[Solution](Solutions.md#exercise-2-skip-list-level-assignment)**

---

<br>

## Exercise 3: Hash Table Linear Probing

**Problem:** Given a hash table of size 11 with hash function $h(k) = k \mod 11$ and linear probing, insert the keys 20, 31, 24, 9, 35, 42. Show the final state of the table.

**[Solution](Solutions.md#exercise-3-hash-table-linear-probing)**

---

<br>

## Exercise 4: Chaining vs. Open Addressing

**Problem:** A hash table has $n = 100$ elements and $m = 200$ buckets (load factor $\alpha = 0.5$). Compare the expected number of probes for a successful search using linear probing vs. chaining.

**[Solution](Solutions.md#exercise-4-chaining-vs-open-addressing)**

---

<br>

## Exercise 5: Skip List Average-Case Analysis

**Problem:** Derive the expected search time of a skip list using backward analysis. Let $C(i)$ be the expected cost of climbing $i$ levels. Write the recurrence and solve it for $p = 1/2$.

**[Solution](Solutions.md#exercise-5-skip-list-average-case-analysis)**
