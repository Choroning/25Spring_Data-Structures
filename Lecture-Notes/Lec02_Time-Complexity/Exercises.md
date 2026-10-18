# Lecture 2 Exercises — Time Complexity

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Exercise 1: Big-O Proof

**Problem:** Prove that $5n^2 + 3n = O(n^2)$.

**[Solution](Solutions.md#exercise-1-big-o-proof)**

---

<br>

## Exercise 2: Asymptotic Comparison

**Problem:** Rank the following in increasing order of growth rate: $n^2$, $2^n$, $n \log n$, $n!$, $\log n$, $n$.

**[Solution](Solutions.md#exercise-2-asymptotic-comparison)**

---

<br>

## Exercise 3: Master Theorem

**Problem:** Use the Master Theorem to solve $T(n) = 4T(n/2) + n$.

**[Solution](Solutions.md#exercise-3-master-theorem)**

---

<br>

## Exercise 4: Code Complexity

**Problem:** What is the time complexity of the following code?

```cpp
for (int i = 1; i < n; i *= 2)
    for (int j = 0; j < i; j++)
        sum++;
```

**[Solution](Solutions.md#exercise-4-code-complexity)**

---

<br>

## Exercise 5: Theta Notation

**Problem:** Is it correct to say $n^2 + 5n = \Theta(n^2)$? Prove your answer.

**[Solution](Solutions.md#exercise-5-theta-notation)**
