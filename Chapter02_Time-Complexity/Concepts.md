# Chapter 02 — Time Complexity

> **Last Updated:** 2026-03-21

---

## Table of Contents

1. [Asymptotic Notation](#1-asymptotic-notation)
2. [Big-O Notation](#2-big-o-notation)
3. [Big-Omega Notation](#3-big-omega-notation)
4. [Theta Notation](#4-theta-notation)
5. [Little-o and Little-omega](#5-little-o-and-little-omega)
6. [Common Growth Rates](#6-common-growth-rates)
7. [Complexity Analysis Techniques](#7-complexity-analysis-techniques)
8. [Summary](#summary)
9. [Appendix](#appendix)

---

## 1. Asymptotic Notation

### 1.1 Motivation

Exact step counts are tedious and platform-dependent. Asymptotic notation provides a **machine-independent** way to describe the growth rate of functions.

We focus on **how the running time scales** as $n \to \infty$, ignoring constant factors and lower-order terms.

### 1.2 Notation Overview

| Notation | Meaning | Analogy |
|----------|---------|---------|
| $O(g(n))$ | Upper bound | $\leq$ |
| $\Omega(g(n))$ | Lower bound | $\geq$ |
| $\Theta(g(n))$ | Tight bound | $=$ |
| $o(g(n))$ | Strict upper bound | $<$ |
| $\omega(g(n))$ | Strict lower bound | $>$ |

---

## 2. Big-O Notation

### 2.1 Definition

$f(n) = O(g(n))$ if there exist positive constants $c$ and $n_0$ such that:

$$f(n) \leq c \cdot g(n) \quad \text{for all } n \geq n_0$$

Big-O gives an **asymptotic upper bound** on the growth rate.

### 2.2 Examples

- $3n + 2 = O(n)$ because $3n + 2 \leq 4n$ for $n \geq 2$ (choose $c = 4$, $n_0 = 2$)
- $10n^2 + 4n + 2 = O(n^2)$ because $10n^2 + 4n + 2 \leq 11n^2$ for $n \geq 5$
- $6 \cdot 2^n + n^2 = O(2^n)$ because $6 \cdot 2^n + n^2 \leq 7 \cdot 2^n$ for sufficiently large $n$

### 2.3 Properties

1. **Transitivity**: If $f = O(g)$ and $g = O(h)$, then $f = O(h)$
2. **Sum Rule**: $O(f + g) = O(\max(f, g))$
3. **Product Rule**: $O(f \cdot g) = O(f) \cdot O(g)$
4. **Constant factors**: $O(c \cdot f) = O(f)$ for any constant $c > 0$

> **Key Point:** Big-O describes the *worst-case* upper bound. It tells us the function grows *no faster than* $g(n)$.

---

## 3. Big-Omega Notation

### 3.1 Definition

$f(n) = \Omega(g(n))$ if there exist positive constants $c$ and $n_0$ such that:

$$f(n) \geq c \cdot g(n) \quad \text{for all } n \geq n_0$$

### 3.2 Examples

- $3n + 2 = \Omega(n)$ because $3n + 2 \geq 3n$ for $n \geq 1$
- $n^2 - 5n = \Omega(n^2)$ because $n^2 - 5n \geq \frac{1}{2}n^2$ for $n \geq 10$

> **Key Point:** Big-Omega provides a *lower bound*. The function grows *at least as fast as* $g(n)$.

---

## 4. Theta Notation

### 4.1 Definition

$f(n) = \Theta(g(n))$ if there exist positive constants $c_1$, $c_2$, and $n_0$ such that:

$$c_1 \cdot g(n) \leq f(n) \leq c_2 \cdot g(n) \quad \text{for all } n \geq n_0$$

Equivalently, $f(n) = \Theta(g(n))$ if and only if $f(n) = O(g(n))$ **and** $f(n) = \Omega(g(n))$.

### 4.2 Examples

- $3n + 2 = \Theta(n)$ since $3n \leq 3n+2 \leq 4n$ for $n \geq 2$
- $n^2 / 2 - 3n = \Theta(n^2)$

---

## 5. Little-o and Little-omega

### 5.1 Little-o

$f(n) = o(g(n))$ means $\lim_{n \to \infty} \frac{f(n)}{g(n)} = 0$.

Example: $n = o(n^2)$, $\log n = o(n)$

### 5.2 Little-omega

$f(n) = \omega(g(n))$ means $\lim_{n \to \infty} \frac{f(n)}{g(n)} = \infty$.

Example: $n^2 = \omega(n)$

---

## 6. Common Growth Rates

### 6.1 Growth Rate Hierarchy

$$O(1) < O(\log n) < O(\sqrt{n}) < O(n) < O(n \log n) < O(n^2) < O(n^3) < O(2^n) < O(n!)$$

### 6.2 Practical Impact

| Complexity | $n = 10$ | $n = 100$ | $n = 1000$ | $n = 10^6$ |
|------------|----------|-----------|------------|------------|
| $O(1)$ | 1 | 1 | 1 | 1 |
| $O(\log n)$ | 3.3 | 6.6 | 10 | 20 |
| $O(n)$ | 10 | 100 | 1000 | $10^6$ |
| $O(n \log n)$ | 33 | 664 | 10000 | $2 \times 10^7$ |
| $O(n^2)$ | 100 | 10000 | $10^6$ | $10^{12}$ |
| $O(2^n)$ | 1024 | $10^{30}$ | - | - |

### 6.3 Identifying Complexity from Code

```cpp
// O(1) - No loops, direct computation
int getFirst(int arr[]) { return arr[0]; }

// O(log n) - Halving the problem each iteration
while (n > 1) { n /= 2; count++; }

// O(n) - Single loop proportional to n
for (int i = 0; i < n; i++) { /* ... */ }

// O(n log n) - Loop with logarithmic inner work
for (int i = 0; i < n; i++)
    for (int j = 1; j < n; j *= 2) { /* ... */ }

// O(n^2) - Nested loops both proportional to n
for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) { /* ... */ }
```

---

## 7. Complexity Analysis Techniques

### 7.1 Recurrence Relations

Many recursive algorithms have time complexity described by recurrences:

$$T(n) = aT(n/b) + f(n)$$

**Master Theorem**: Given $T(n) = aT(n/b) + \Theta(n^d)$:

1. If $d < \log_b a$: $T(n) = \Theta(n^{\log_b a})$
2. If $d = \log_b a$: $T(n) = \Theta(n^d \log n)$
3. If $d > \log_b a$: $T(n) = \Theta(n^d)$

### 7.2 Examples

**Merge Sort**: $T(n) = 2T(n/2) + \Theta(n)$
- $a = 2$, $b = 2$, $d = 1$
- $\log_2 2 = 1 = d$ (Case 2)
- $T(n) = \Theta(n \log n)$

**Binary Search**: $T(n) = T(n/2) + \Theta(1)$
- $a = 1$, $b = 2$, $d = 0$
- $\log_2 1 = 0 = d$ (Case 2)
- $T(n) = \Theta(\log n)$

### 7.3 Amortized Analysis

Some operations are occasionally expensive but cheap on average. **Amortized analysis** gives the average cost per operation over a sequence.

Example: Dynamic array `push_back`:
- Usually $O(1)$ (just append)
- Occasionally $O(n)$ (when resizing)
- Amortized cost: $O(1)$ per operation

---

## Summary

| Concept | Key Point |
|---------|-----------|
| Big-O | Upper bound: $f(n) \leq c \cdot g(n)$ for large $n$ |
| Big-Omega | Lower bound: $f(n) \geq c \cdot g(n)$ for large $n$ |
| Theta | Tight bound: both $O$ and $\Omega$ |
| Growth hierarchy | $1 < \log n < n < n\log n < n^2 < 2^n < n!$ |
| Master Theorem | Solves $T(n) = aT(n/b) + \Theta(n^d)$ recurrences |
| Amortized analysis | Average cost over a sequence of operations |

---

## Appendix

### Proving Big-O Formally

**Claim**: $2n^2 + 3n + 1 = O(n^2)$

**Proof**: Choose $c = 6$ and $n_0 = 1$.
For $n \geq 1$: $2n^2 + 3n + 1 \leq 2n^2 + 3n^2 + n^2 = 6n^2$. QED.

### Comparison of Sorting Algorithm Complexities

| Algorithm | Best | Average | Worst | Space |
|-----------|------|---------|-------|-------|
| Bubble Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ |
| Insertion Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ |
| Merge Sort | $O(n\log n)$ | $O(n\log n)$ | $O(n\log n)$ | $O(n)$ |
| Quick Sort | $O(n\log n)$ | $O(n\log n)$ | $O(n^2)$ | $O(\log n)$ |
| Heap Sort | $O(n\log n)$ | $O(n\log n)$ | $O(n\log n)$ | $O(1)$ |
