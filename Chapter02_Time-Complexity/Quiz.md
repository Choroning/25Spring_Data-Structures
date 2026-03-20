# Chapter 02 — Quiz

> **Last Updated:** 2026-03-21

---

## Q1. Big-O Proof

**Question:** Prove that $5n^2 + 3n = O(n^2)$.

**Answer:** Choose $c = 6$ and $n_0 = 3$. For all $n \geq 3$: $5n^2 + 3n \leq 5n^2 + n^2 = 6n^2$ (since $3n \leq n^2$ for $n \geq 3$). Therefore $5n^2 + 3n = O(n^2)$.

**Explanation:** To prove Big-O, we must find constants $c$ and $n_0$ such that $f(n) \leq c \cdot g(n)$ for all $n \geq n_0$. We bounded $3n$ by $n^2$ (valid for $n \geq 3$).

---

## Q2. Asymptotic Comparison

**Question:** Rank the following in increasing order of growth rate: $n^2$, $2^n$, $n \log n$, $n!$, $\log n$, $n$.

**Answer:** $\log n < n < n \log n < n^2 < 2^n < n!$

**Explanation:** Logarithmic growth is the slowest, followed by linear, then linearithmic. Polynomial growth ($n^2$) is dominated by exponential ($2^n$), which is dominated by factorial ($n!$).

---

## Q3. Master Theorem

**Question:** Use the Master Theorem to solve $T(n) = 4T(n/2) + n$.

**Answer:** $T(n) = \Theta(n^2)$.

**Explanation:** Here $a = 4$, $b = 2$, $d = 1$. We compute $\log_b a = \log_2 4 = 2$. Since $d = 1 < 2 = \log_b a$, this is Case 1 of the Master Theorem: $T(n) = \Theta(n^{\log_b a}) = \Theta(n^2)$.

---

## Q4. Code Complexity

**Question:** What is the time complexity of the following code?
```cpp
for (int i = 1; i < n; i *= 2)
    for (int j = 0; j < i; j++)
        sum++;
```

**Answer:** $O(n)$.

**Explanation:** The outer loop runs $\log n$ times ($i = 1, 2, 4, \ldots, n$). The inner loop runs $i$ times for each value of $i$. The total number of operations is $1 + 2 + 4 + \cdots + n = 2n - 1 = O(n)$ (geometric series).

---

## Q5. Theta Notation

**Question:** Is it correct to say $n^2 + 5n = \Theta(n^2)$? Prove your answer.

**Answer:** Yes, $n^2 + 5n = \Theta(n^2)$.

**Explanation:** We need constants $c_1, c_2, n_0$ such that $c_1 n^2 \leq n^2 + 5n \leq c_2 n^2$. For the lower bound: $n^2 + 5n \geq n^2 = 1 \cdot n^2$ (choose $c_1 = 1$). For the upper bound: $n^2 + 5n \leq n^2 + 5n^2 = 6n^2$ for $n \geq 1$ (choose $c_2 = 6$, $n_0 = 1$).
