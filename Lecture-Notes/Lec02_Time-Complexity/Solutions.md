# Lecture 2 Solutions — Time Complexity

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Table of Contents

- [Exercise 1: Big-O Proof](#exercise-1-big-o-proof)
- [Exercise 2: Asymptotic Comparison](#exercise-2-asymptotic-comparison)
- [Exercise 3: Master Theorem](#exercise-3-master-theorem)
- [Exercise 4: Code Complexity](#exercise-4-code-complexity)
- [Exercise 5: Theta Notation](#exercise-5-theta-notation)

---

<br>

## Exercise 1: Big-O Proof

**Problem:** Prove that $5n^2 + 3n = O(n^2)$.

### Solution

**Answer:** Choose $c = 6$ and $n_0 = 3$. For all $n \geq 3$: $5n^2 + 3n \leq 5n^2 + n^2 = 6n^2$ (since $3n \leq n^2$ for $n \geq 3$). Therefore $5n^2 + 3n = O(n^2)$.

**Explanation:** To prove Big-O, we must find constants $c$ and $n_0$ such that $f(n) \leq c \cdot g(n)$ for all $n \geq n_0$. We bounded $3n$ by $n^2$ (valid for $n \geq 3$).

---

<br>

## Exercise 2: Asymptotic Comparison

**Problem:** Rank the following in increasing order of growth rate: $n^2$, $2^n$, $n \log n$, $n!$, $\log n$, $n$.

### Solution

**Answer:** $\log n < n < n \log n < n^2 < 2^n < n!$

**Explanation:** Logarithmic growth is the slowest, followed by linear, then linearithmic. Polynomial growth ($n^2$) is dominated by exponential ($2^n$), which is dominated by factorial ($n!$).

---

<br>

## Exercise 3: Master Theorem

**Problem:** Use the Master Theorem to solve $T(n) = 4T(n/2) + n$.

### Solution

**Answer:** $T(n) = \Theta(n^2)$.

**Explanation:** Here $a = 4$, $b = 2$, $d = 1$. We compute $\log_b a = \log_2 4 = 2$. Since $d = 1 < 2 = \log_b a$, this is Case 1 of the Master Theorem: $T(n) = \Theta(n^{\log_b a}) = \Theta(n^2)$.

---

<br>

## Exercise 4: Code Complexity

**Problem:** What is the time complexity of the following code?

```cpp
for (int i = 1; i < n; i *= 2)
    for (int j = 0; j < i; j++)
        sum++;
```

### Solution

**Answer:** $O(n)$.

**Explanation:** In the outer loop, $i$ takes the values $1, 2, 4, \ldots, 2^{k-1}$ while it is less than $n$ ($2^{k-1} < n \le 2^k$), so the outer loop runs $k = \lceil \log_2 n \rceil$ times ($n \ge 2$). The inner loop runs $i$ times for each value of $i$. The total number of operations is the geometric series $1 + 2 + 4 + \cdots + 2^{k-1} = 2^k - 1$, and since $2^{k-1} < n$, $2^k - 1 < 2n$, which is $O(n)$. When $n$ is a power of 2, it is exactly $n - 1$ (e.g., 1 + 2 + 4 = 7 for $n = 8$).

---

<br>

## Exercise 5: Theta Notation

**Problem:** Is it correct to say $n^2 + 5n = \Theta(n^2)$? Prove your answer.

### Solution

**Answer:** Yes, $n^2 + 5n = \Theta(n^2)$.

**Explanation:** We need constants $c_1, c_2, n_0$ such that $c_1 n^2 \leq n^2 + 5n \leq c_2 n^2$. For the lower bound: $n^2 + 5n \geq n^2 = 1 \cdot n^2$ (choose $c_1 = 1$). For the upper bound: $n^2 + 5n \leq n^2 + 5n^2 = 6n^2$ for $n \geq 1$ (choose $c_2 = 6$, $n_0 = 1$).
