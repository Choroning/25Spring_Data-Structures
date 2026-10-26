# Lecture 2 — Time Complexity

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-26

> **Learning Objectives:**
> 1. Classify algorithms by time complexity classes
> 2. Analyze nested loops and recursive time complexity
> 3. Compare growth rates of common complexity functions
> 4. Prove asymptotic relations between two functions using the definitions and limits

---

## Table of Contents

- [1. Asymptotic Notation](#1-asymptotic-notation)
  - [1.1 Motivation](#11-motivation)
  - [1.2 Notation Overview](#12-notation-overview)
  - [1.3 Graphical Meaning](#13-graphical-meaning)
- [2. Big-O Notation](#2-big-o-notation)
  - [2.1 Definition](#21-definition)
  - [2.2 Examples](#22-examples)
  - [2.3 An Example Where Big-O Fails](#23-an-example-where-big-o-fails)
  - [2.4 Properties](#24-properties)
- [3. Big-Omega Notation](#3-big-omega-notation)
  - [3.1 Definition](#31-definition)
  - [3.2 Examples](#32-examples)
- [4. Theta Notation](#4-theta-notation)
  - [4.1 Definition](#41-definition)
  - [4.2 Examples](#42-examples)
  - [4.3 Relationship Among O, Omega, and Theta](#43-relationship-among-o-omega-and-theta)
- [5. Little-o and Little-omega](#5-little-o-and-little-omega)
  - [5.1 Little-o](#51-little-o)
  - [5.2 Little-omega](#52-little-omega)
- [6. Characteristics of Complexity Order](#6-characteristics-of-complexity-order)
- [7. Comparing Orders with Limits](#7-comparing-orders-with-limits)
  - [7.1 L'Hôpital's Rule and the Limit Test](#71-lhôpitals-rule-and-the-limit-test)
  - [7.2 Proof Examples](#72-proof-examples)
- [8. Common Growth Rates](#8-common-growth-rates)
  - [8.1 Growth Rate Hierarchy](#81-growth-rate-hierarchy)
  - [8.2 Practical Impact](#82-practical-impact)
  - [8.3 Identifying Complexity from Code](#83-identifying-complexity-from-code)
- [9. Analyzing the Complexity of Loops](#9-analyzing-the-complexity-of-loops)
  - [9.1 From Step Counts to Asymptotic Complexity](#91-from-step-counts-to-asymptotic-complexity)
  - [9.2 Single Loops](#92-single-loops)
  - [9.3 Nested Loops](#93-nested-loops)
  - [9.4 Sequences of Statements](#94-sequences-of-statements)
  - [9.5 Examples by Loop Type](#95-examples-by-loop-type)
- [10. Complexity Analysis Techniques](#10-complexity-analysis-techniques)
  - [10.1 Recurrence Relations](#101-recurrence-relations)
  - [10.2 Examples](#102-examples)
  - [10.3 Amortized Analysis](#103-amortized-analysis)
- [11. Appendix](#11-appendix)
  - [11.1 Proving Big-O Formally](#111-proving-big-o-formally)
  - [11.2 Comparison of Sorting Algorithm Complexities](#112-comparison-of-sorting-algorithm-complexities)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

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

*Table 1. Kinds of asymptotic notation and their meanings*

### 1.3 Graphical Meaning

The three notations can be understood by how the graphs of the two functions are positioned relative to each other after $n_0$.

| Notation | Relation for $n \ge n_0$ | Meaning |
|----------|------|------|
| $f(n) = O(g(n))$ | The graph of $f(n)$ lies below $c \cdot g(n)$ | $f(n)$ grows no faster than $g(n)$ |
| $f(n) = \Omega(g(n))$ | The graph of $f(n)$ lies above $c \cdot g(n)$ | $f(n)$ grows no slower than $g(n)$ |
| $f(n) = \Theta(g(n))$ | The graph of $f(n)$ lies between $c_1 \cdot g(n)$ and $c_2 \cdot g(n)$ | $f(n)$ grows asymptotically at the same rate as $g(n)$ |

*Table 2. Relations of the three notations seen graphically*

In these notations, $f(n)$ is the function being analyzed (e.g., the running time of an algorithm), and $g(n)$ is a reference function that bounds $f(n)$. For example, if $f(n)$ is an algorithm's running time and $g(n)$ is some time complexity function, then $f(n)$ is $O(g(n))$ if $f(n)$ is less than or equal to $c \cdot g(n)$ for every input size $n$ from $n_0$ on. Asymptotic notation analyzes an algorithm's running time by identifying its behavior as the input size increases.

> **Note:** **Set notation.** Since $O(g(n))$ is a set of functions, $f(n) = O(g(n))$ is also written $f(n) \in O(g(n))$. The equals sign here denotes membership, not a symmetric relation, so it is never written in reverse as $O(g(n)) = f(n)$. Some texts swap the roles, writing the analyzed function as $g(n)$ and the reference function as $f(n)$ in $g(n) \in O(f(n))$, so check which one is the reference function.

---

<br>

## 2. Big-O Notation

### 2.1 Definition

$f(n) = O(g(n))$ (read as "f(n) is Big-O of g(n)") if there exist positive constants $c$ and $n_0$ such that:

$$f(n) \leq c \cdot g(n) \quad \text{for all } n \geq n_0$$

Big-O gives an **asymptotic upper bound** on the growth rate. $f(n)$ is the complexity of the algorithm being evaluated, and $g(n)$ is the reference complexity it is compared with. If the time complexity of an algorithm is $O(g(n))$, then for sufficiently large input sizes $n$ the computing time of the algorithm, apart from a constant factor, cannot be slower than $g(n)$. In other words, $g(n)$ is an upper bound.

For example, $f(n) = O(n^2)$ means that $f(n)$ ultimately (for all $n$ greater than some $n_0$) takes values less than or equal to some quadratic function $cn^2$. On a graph $f(n)$ lies below $cn^2$, and we can say that $f(n)$ is ultimately no worse than (grows no faster than) $cn^2$.

### 2.2 Examples

- $3n + 2 = O(n)$ because $3n + 2 \leq 4n$ for $n \geq 2$ (choose $c = 4$, $n_0 = 2$)
- $10n^2 + 4n + 2 = O(n^2)$ because $10n^2 + 4n + 2 \leq 11n^2$ for $n \geq 5$
- $6 \cdot 2^n + n^2 = O(2^n)$ because $6 \cdot 2^n + n^2 \leq 7 \cdot 2^n$ for sufficiently large $n$ ($n^2 \le 2^n$ for $n \ge 4$, so $n_0 = 4$)

**$n^2 + 10n = O(n^2)$.** For all integers $n \ge 10$, $10n \le n^2$, so $n^2 + 10n \le 2n^2$ holds. Thus, if we select $c = 2$ and $n_0 = 10$, $n^2 + 10n = O(n^2)$ by the definition of Big-O. Also, for all integers $n \ge 1$, $10n \le 10n^2$, so $n^2 + 10n \le 11n^2$ holds, and selecting $c = 11$ and $n_0 = 1$ gives the same conclusion. As this shows, the $c$ and $n_0$ satisfying the definition are not unique.

| $n$ | 1 | 5 | 9 | 10 | 11 | 15 |
|---|---|---|---|---|---|---|
| $n^2 + 10n$ | 11 | 75 | 171 | 200 | 231 | 375 |
| $2n^2$ | 2 | 50 | 162 | 200 | 242 | 450 |

*Table 3. Comparison of the values of $n^2 + 10n$ and $2n^2$*

For $n < 10$, $n^2 + 10n$ is larger, but the two values become equal at $n = 10$, and after that $n^2 + 10n$ stays beneath $2n^2$.

The following can also be checked with the definition.

- $5n^2 = O(n^2)$: with $c = 5$, $5n^2 \le 5n^2$ for all $n \ge 1$ (in fact, for all $n \ge 0$).
- $T(n) = \dfrac{n(n-1)}{2} = O(n^2)$: since $\dfrac{n(n-1)}{2} \le \dfrac{n^2}{2}$ for all $n \ge 0$, take $c = \dfrac{1}{2}$ and $n_0 = 1$.
- $n^2 = O(n^2 + 10n)$: since $n^2 \le 1 \cdot (n^2 + 10n)$ for all $n \ge 0$, take $c = 1$ and $n_0 = 1$.
- $n = O(n^2)$: since $n \le 1 \cdot n^2$ for all integers $n \ge 1$, take $c = 1$ and $n_0 = 1$.

### 2.3 An Example Where Big-O Fails

$n^3 \ne O(n^2)$. Suppose there were $c$ and $n_0$ such that $n^3 \le c \cdot n^2$ for all $n \ge n_0$. Dividing both sides by $n^2$ gives $n \le c$, but however large $c$ is chosen, there exists an $n$ that is at least $n_0$ and greater than $c$. Therefore no such $c$ and $n_0$ exist.

> **Caution:** For small $n$ the inequality can hold by chance. With $c$ fixed at 5, $2^3 = 8 \le 5 \times 2^2 = 20$ is true at $n = 2$, but at $n = 10$, $10^3 = 1000 \le 5 \times 10^2 = 500$ is false. Big-O must hold for all $n$ from $n_0$ on, so it cannot be proved by trying a few values. In the form $n \le c$, whatever $c$ is chosen, an $n$ greater than $c$ breaks the inequality, so the relation is always false.

### 2.4 Properties

1. **Transitivity**: If $f = O(g)$ and $g = O(h)$, then $f = O(h)$
2. **Sum Rule**: $O(f + g) = O(\max(f, g))$
3. **Product Rule**: $O(f \cdot g) = O(f) \cdot O(g)$
4. **Constant factors**: $O(c \cdot f) = O(f)$ for any constant $c > 0$

> **Key Point:** Big-O describes an *upper bound* of a function. It tells us the function grows *no faster than* $g(n)$. It is often used for the worst-case running time, but it applies equally to best-case or average-case functions.

---

<br>

## 3. Big-Omega Notation

### 3.1 Definition

$f(n) = \Omega(g(n))$ if there exist positive constants $c$ and $n_0$ such that:

$$f(n) \geq c \cdot g(n) \quad \text{for all } n \geq n_0$$

### 3.2 Examples

- $3n + 2 = \Omega(n)$ because $3n + 2 \geq 3n$ for $n \geq 1$
- $n^2 - 5n = \Omega(n^2)$ because $n^2 - 5n \geq \frac{1}{2}n^2$ for $n \geq 10$

> **Key Point:** Big-Omega provides a *lower bound*. The function grows *at least as fast as* $g(n)$.

---

<br>

## 4. Theta Notation

### 4.1 Definition

$f(n) = \Theta(g(n))$ if there exist positive constants $c_1$, $c_2$, and $n_0$ such that:

$$c_1 \cdot g(n) \leq f(n) \leq c_2 \cdot g(n) \quad \text{for all } n \geq n_0$$

Equivalently, $f(n) = \Theta(g(n))$ if and only if $f(n) = O(g(n))$ **and** $f(n) = \Omega(g(n))$.

### 4.2 Examples

- $3n + 2 = \Theta(n)$ since $3n \leq 3n+2 \leq 4n$ for $n \geq 2$
- $n^2 / 2 - 3n = \Theta(n^2)$ since $\frac{1}{4}n^2 \le n^2/2 - 3n \le \frac{1}{2}n^2$ for $n \ge 12$ ($c_1 = 1/4$, $c_2 = 1/2$, $n_0 = 12$)

### 4.3 Relationship Among O, Omega, and Theta

$O(n^2)$, $\Omega(n^2)$, and $\Theta(n^2)$ are each sets of functions. The following table shows which sets several functions belong to.

| Function | $O(n^2)$ | $\Omega(n^2)$ | $\Theta(n^2)$ |
|----------|------|------|------|
| $3\lg n + 8$ | Yes | No | No |
| $5n + 7$ | Yes | No | No |
| $2n \lg n$ | Yes | No | No |
| $4n^2$ | Yes | Yes | Yes |
| $6n^2 + 9$ | Yes | Yes | Yes |
| $5n^2 + 2n$ | Yes | Yes | Yes |
| $4n^3 + 3n^2$ | No | Yes | No |
| $6n^6 + n^4$ | No | Yes | No |
| $2^n + 4n$ | No | Yes | No |

*Table 4. Membership of example functions in $O(n^2)$, $\Omega(n^2)$, and $\Theta(n^2)$*

$\Theta(n^2) = O(n^2) \cap \Omega(n^2)$. The functions $4n^2$, $6n^2 + 9$, and $5n^2 + 2n$ in $\Theta(n^2)$ share the same upper bound and lower bound of order $n^2$, and this bound cannot be made any tighter.

> **Caution:** A running time of $\Theta(g(n))$ only means that the algorithm's upper and lower bounds have the same order; it does not mean that the algorithm is optimal. An algorithm is optimal when its upper bound matches the lower bound of the problem itself (Lecture 1, Section 4.4). For example, the comparison count $n(n-1)/2$ of bubble sort is $\Theta(n^2)$, but the lower bound for comparison-based sorting is $\Omega(n \log n)$, so bubble sort is not optimal.

---

<br>

## 5. Little-o and Little-omega

### 5.1 Little-o

$f(n) = o(g(n))$ means $\lim_{n \to \infty} \frac{f(n)}{g(n)} = 0$.

Example: $n = o(n^2)$, $\log n = o(n)$

In terms of inequalities, $f(n) = o(g(n))$ when for **every** positive constant $c$ there exists an $n_0$ such that $f(n) \le c \cdot g(n)$ for all $n \ge n_0$ (this matches the limit definition when $g(n)$ is positive for sufficiently large $n$). The differences between Big-O and little-o are as follows.

1. **Big-O**: true as long as the comparison is satisfied for **at least one** positive real value $c$.
2. **Little-o**: true only if the comparison is satisfied for **all** positive real values $c$.

If $f(n) = o(g(n))$, the performance of $f(n)$ is much better than that of $g(n)$ (it grows much more slowly).

### 5.2 Little-omega

$f(n) = \omega(g(n))$ means $\lim_{n \to \infty} \frac{f(n)}{g(n)} = \infty$.

Example: $n^2 = \omega(n)$

---

<br>

## 6. Characteristics of Complexity Order

The following properties are used to compare the orders of functions. "A iff B" (A if and only if B) means that A and B are necessary and sufficient conditions for each other, so both directions hold. "A if B", on the other hand, only means that A is true when B is true; when A is true, B can be true or false.

- **Duality:** $f(n) = O(g(n))$ iff $g(n) = \Omega(f(n))$.
- **Symmetry:** $f(n) = \Theta(g(n))$ iff $g(n) = \Theta(f(n))$.
- **Logarithms:** If $a > 1$ and $b > 1$, $\log_a n = \Theta(\log_b n)$ is always true. All logarithmic complexity functions are in the same class, so they are normally written $\Theta(\log n)$ without the base.
- **Exponentials:** If $b > a > 0$, $a^n = o(b^n)$. Unlike logarithmic functions, exponential complexity functions are not all in the same class.
- **Factorial:** If $a > 0$, $a^n = o(n!)$. In other words, $n!$ is worse than any exponential time complexity function.

Listing complexity classes from best to worst gives the following ($k > j > 2$, $b > a > 1$).

$$\Theta(\lg n),\ \Theta(n),\ \Theta(n \lg n),\ \Theta(n^2),\ \Theta(n^j),\ \Theta(n^k),\ \Theta(a^n),\ \Theta(b^n),\ \Theta(n!)$$

If the class of a complexity function $f(n)$ is to the left of the class of $g(n)$, then $f(n) = o(g(n))$.

**Sum property.** If $f(n) = O(h(n))$, $g(n) = \Theta(h(n))$, $c > 0$, and $d > 0$, then $c \cdot f(n) + d \cdot g(n) = \Theta(h(n))$. In other words, when terms are added, the term of the highest order determines the class, and adding terms of the same or lower order or multiplying by positive constant coefficients does not change the class. For example, $3\lg n + 5n^2 = \Theta(n^2)$.

Exponential functions such as $2^n$ and $10^n$ increase much more steeply than $\log n$, $n$, $n \log n$, $n^2$, and $n^3$. For example, at $n = 11$, $n^3 = 1331$, but $2^n = 2048$ and $10^n = 10^{11}$.

---

<br>

## 7. Comparing Orders with Limits

### 7.1 L'Hôpital's Rule and the Limit Test

**L'Hôpital's rule:** If $\lim_{n \to \infty} f(n) = \lim_{n \to \infty} g(n) = \infty$ and the limit on the right exists, then:

$$\lim_{n \to \infty} \frac{f(n)}{g(n)} = \lim_{n \to \infty} \frac{f'(n)}{g'(n)}$$

> **[Calculus]** L'Hôpital's rule is the calculus theorem that computes the limit of an indeterminate form such as $\infty/\infty$ or $0/0$ as the ratio of the derivatives of the numerator and the denominator. Complexity functions are defined on integers $n$, but the rule is applied by extending them, like $n^2$, $\lg n$, and $2^n$, to functions differentiable in a real $x$, and when the limit as $x \to \infty$ exists, the limit as the integer $n \to \infty$ equals it.

This rule is very important for comparing complexity orders. Computing the limit of the ratio of two functions decides their relation as follows.

| $\lim_{n \to \infty} f(n)/g(n)$ | Conclusion |
|------|------|
| $0$ | $f(n) = o(g(n))$ (so $f(n) = O(g(n))$ but $f(n) \ne \Theta(g(n))$) |
| A constant $c$ with $0 < c < \infty$ | $f(n) = \Theta(g(n))$ |
| $\infty$ | $f(n) = \omega(g(n))$ (so $f(n) = \Omega(g(n))$ but $f(n) \ne \Theta(g(n))$) |

*Table 5. Deciding asymptotic relations from the limit value*

> **Caution:** The limit test works only in the direction from the limit value to the relation. $f(n) = O(g(n))$ does not imply $\lim f(n)/g(n) = 0$ (if $f = g$, the limit is 1), and a relation can hold even when the limit does not exist. For example, the function that equals $n$ for even $n$ and $2n$ for odd $n$ has no limit of $f(n)/n$, which alternates between 1 and 2, yet it is $\Theta(n)$ because $n \le f(n) \le 2n$.

### 7.2 Proof Examples

**$\dfrac{n^2}{2} = o(n^3)$:**

$$\lim_{n \to \infty} \frac{n^2/2}{n^3} = \lim_{n \to \infty} \frac{1}{2n} = 0$$

**If $b > a > 0$, then $a^n = o(b^n)$:** since $0 < a/b < 1$,

$$\lim_{n \to \infty} \frac{a^n}{b^n} = \lim_{n \to \infty} \left(\frac{a}{b}\right)^n = 0$$

**$\lg n = o(n)$:** apply L'Hôpital's rule ($\lg n = \log_2 n$ and $(\lg n)' = \frac{1}{n \ln 2}$).

$$\lim_{n \to \infty} \frac{\lg n}{n} = \lim_{n \to \infty} \frac{1/(n \ln 2)}{1} = 0$$

**If $a > 1$ and $b > 1$, then $\log_a n = \Theta(\log_b n)$:** since $(\log_a f(n))' = \dfrac{f'(n)}{f(n) \ln a}$,

$$\lim_{n \to \infty} \frac{\log_a n}{\log_b n} = \lim_{n \to \infty} \frac{1/(n \ln a)}{1/(n \ln b)} = \frac{\ln b}{\ln a} = \frac{\log b}{\log a} > 0$$

Since the limit is a positive constant, the two functions are in the same class. The change-of-base formula $\log_a n = \log_b n / \log_b a$ also shows directly that their ratio is a constant.

**$f(n) = \log n^2$, $g(n) = \log n + 5$:** applying L'Hôpital's rule,

$$\lim_{n \to \infty} \frac{\log n^2}{\log n + 5} = \lim_{n \to \infty} \frac{2/n}{1/n} = 2$$

and since $0 < 2 < \infty$, $f(n) = \Theta(g(n))$. Note that $\log n + 5$ is different from $\log(n + 5)$. Since $\log n^2 = 2\log n$, the same conclusion also follows directly.

---

<br>

## 8. Common Growth Rates

### 8.1 Growth Rate Hierarchy

$$O(1) < O(\log n) < O(\sqrt{n}) < O(n) < O(n \log n) < O(n^2) < O(n^3) < O(2^n) < O(n!)$$

### 8.2 Practical Impact

| Complexity | $n = 10$ | $n = 100$ | $n = 1000$ | $n = 10^6$ |
|------------|----------|-----------|------------|------------|
| $O(1)$ | 1 | 1 | 1 | 1 |
| $O(\log n)$ | 3.3 | 6.6 | 10 | 20 |
| $O(n)$ | 10 | 100 | 1000 | $10^6$ |
| $O(n \log n)$ | 33 | 664 | 10000 | $2 \times 10^7$ |
| $O(n^2)$ | 100 | 10000 | $10^6$ | $10^{12}$ |
| $O(2^n)$ | 1024 | $10^{30}$ | - | - |

*Table 6. Approximate values of complexity functions by input size (logarithms base 2)*

### 8.3 Identifying Complexity from Code

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

<br>

## 9. Analyzing the Complexity of Loops

### 9.1 From Step Counts to Asymptotic Complexity

The following function computes the sum of all numbers in an array `A` of $N$ integers.

```cpp
// Input: int A[N], array of N integers
// Output: Sum of all numbers in array A
int Sum(int A[], int N) {
    int s = 0;                      // (1)
    for (int i = 0; i < N; i++)     // (2) i = 0, (3) i < N, (4) i++
        s = s + A[i];               // (5) assignment, (6) addition, (7) access A[i]
    return s;                       // (8)
}
```

Counting (1), (2), and (8) once each and (3) through (7) once per iteration, $N$ times, gives a total of $5N + 3$ steps. The **complexity function** of this algorithm is $f(N) = 5N + 3$.

| $N$ | Steps |
|---|---|
| 10 | 53 |
| 100 | 503 |
| 1,000 | 5,003 |
| 1,000,000 | 5,000,003 |

*Table 7. Step counts of the function Sum for different values of N*

As $N$ grows, the number of steps of this function grows in linear proportion to $N$.

> **Note:** **Counting the last test.** Strictly, the test `i < N` in (3) executes $N+1$ times, including the last test in which the condition becomes false, so the total is $5N + 4$ steps. The conclusion (linear growth) is the same.

The $+3$ and the coefficient 5 in $5N + 3$ do not matter, for the following reasons.

- As $N$ gets large, the $+3$ becomes insignificant.
- The 5 is inaccurate, as different operations require varying amounts of time, and it has no significant importance.

What is fundamental is that the time is **linear** in $N$. **Asymptotic complexity** concentrates on the highest order term as $N$ gets large: drop lower order terms such as $+3$, and drop the constant coefficient of the highest order term. The $5N + 3$ time bound is then said to **grow asymptotically** like $N$. **Asymptotic** describes a formula becoming increasingly exact as a variable approaches a limit, usually infinity. Asymptotic complexity gives an approximation of the complexity of the algorithm, ignoring many machine-dependent details and concentrating on the bigger picture.

### 9.2 Single Loops

A loop is analyzed in two parts. How many iterations are performed? How many steps per iteration? The complexity of a loop is the number of iterations times the complexity of the body.

```cpp
int sum = 0, j;
for (j = 0; j < N; j++)
    sum = sum + j;
```

The loop executes $N$ times ($j = 0, \ldots, N-1$) with 4 steps per iteration (test, addition, assignment, increment), and the initializations `sum = 0` and `j = 0` before the loop take 2 steps, so there are $4N + 2$ steps in total. The coefficient 4 is a constant, so it can be ignored as $4 = O(1)$, and the total time is $N \cdot O(1) = O(N \cdot 1) = O(N)$.

```cpp
int sum = 0, j;
for (j = 0; j < 100; j++)
    sum = sum + j;
```

This loop executes 100 times regardless of $N$ with $4 = O(1)$ steps per iteration, so the total time is $100 \cdot O(1) = O(100 \cdot 1) = O(100) = O(1)$.

### 9.3 Nested Loops

Treat nested loops just like a single loop and evaluate each level of nesting as needed.

```cpp
int j, k;
for (j = 0; j < N; j++)
    for (k = N; k > 0; k--)
        sum += k + j;
```

Start with the outer loop. It performs $N$ iterations, and the time per iteration requires evaluating the inner loop. The inner loop uses $O(N)$ time, so the total time is $N \cdot O(N) = O(N \cdot N) = O(N^2)$.

When the number of iterations of one loop depends on the counter of the other, analyze the inner and outer loops together.

```cpp
int j, k;
for (j = 0; j < N; j++)
    for (k = 0; k < j; k++)
        sum += k + j;   // sum = sum + (k + j)
```

The inner loop runs $j$ times, so the total number of iterations of the inner loop is:

$$0 + 1 + 2 + \cdots + (N-1) = \frac{N(N-1)}{2} = O(N^2)$$

### 9.4 Sequences of Statements

For a sequence of statements, compute their complexity functions individually and add them up.

```cpp
for (j = 0; j < N; j++)
    for (k = 0; k < j; k++)
        sum = sum + j * k;
for (l = 0; l < N; l++)
    sum = sum - l;
cout << "sum is now " << sum;
```

The first nested loop is $O(N^2)$, the second loop is $O(N)$, and the final print statement is $O(1)$. The upper bound (worst case) of the time complexity of this program is therefore $O(N^2) + O(N) + O(1) = O(N^2)$.

### 9.5 Examples by Loop Type

For `for`, `while`, and `do-while` loops, the complexity is determined by the number of iterations in the loop times the complexity of the body.

| Code | Complexity |
|------|------------|
| `for (int i = 0; i < n; i++) sum = sum - i;` | $O(n)$ |
| `for (int i = 0; i < n * n; i++) sum = sum + i;` | $O(n^2)$ |
| `i = 1; while (i < n) { sum = sum + i; i = i * 2; }` | $O(\log n)$ |
| `for (int i = 0; i < 100000; i++) sum = sum + i;` | $O(1)$ |

*Table 8. Complexity of loops by type*

In the `while` loop, `i` doubles each time. Counting the iterations for several $n$ gives the following.

| $n$ | Values of `i` Tested | Iterations |
|---|---|---|
| 2 | 1 (1 < 2 true), 2 (2 < 2 false) | 1 |
| 4 | 1, 2 (true), 4 (4 < 4 false) | 2 |
| 8 | 1, 2, 4 (true), 8 (8 < 8 false) | 3 |
| 16 | 1, 2, 4, 8 (true), 16 (16 < 16 false) | 4 |

*Table 9. Iterations of the doubling while loop*

Since `i` grows as $1, 2, 2^2, 2^3, \ldots$, the loop iterates $k = \log_2 n$ times when $n = 2^k$. For general $n \ge 1$, the number of iterations is $\lceil \log_2 n \rceil$.

---

<br>

## 10. Complexity Analysis Techniques

### 10.1 Recurrence Relations

Many recursive algorithms have time complexity described by recurrences:

$$T(n) = aT(n/b) + f(n)$$

**Master Theorem**: Given $T(n) = aT(n/b) + \Theta(n^d)$ for constants $a \ge 1$, $b > 1$, and $d \ge 0$:

1. If $d < \log_b a$: $T(n) = \Theta(n^{\log_b a})$
2. If $d = \log_b a$: $T(n) = \Theta(n^d \log n)$
3. If $d > \log_b a$: $T(n) = \Theta(n^d)$

> **[Algorithms]** The recurrence $T(n) = aT(n/b) + f(n)$ is the running time of a divide-and-conquer algorithm that recursively solves $a$ subproblems of size $n/b$ and spends $f(n)$ time dividing and combining. With $f(n) = \Theta(n^d)$, depth $i$ of the recursion tree costs about $a^i (n/b^i)^d = n^d (a/b^d)^i$, so the leaves determine the total cost when the cost grows with depth ($d < \log_b a$), all $\log_b n$ levels contribute equally when it stays the same ($d = \log_b a$), and the root determines it when the cost shrinks ($d > \log_b a$), which gives the three cases of the Master Theorem.

### 10.2 Examples

**Merge Sort**: $T(n) = 2T(n/2) + \Theta(n)$
- $a = 2$, $b = 2$, $d = 1$
- $\log_2 2 = 1 = d$ (Case 2)
- $T(n) = \Theta(n \log n)$

**Binary Search**: $T(n) = T(n/2) + \Theta(1)$
- $a = 1$, $b = 2$, $d = 0$
- $\log_2 1 = 0 = d$ (Case 2)
- $T(n) = \Theta(\log n)$

### 10.3 Amortized Analysis

Some operations are occasionally expensive but cheap when averaged over many operations. **Amortized analysis** gives the average cost per operation over a sequence. Unlike average-case analysis (Section 3.5 of Lecture 1), which assumes a probability distribution of the inputs, this average holds even for the worst-case sequence of operations.

Example: Dynamic array `push_back` (Section 2.6 of Lecture 3):
- Usually $O(1)$ (just append)
- Occasionally $O(n)$ (when a full array is copied into a new array of twice the size)
- Amortized cost: $O(1)$ per operation

---

<br>

## 11. Appendix

### 11.1 Proving Big-O Formally

**Claim**: $2n^2 + 3n + 1 = O(n^2)$

**Proof**: Choose $c = 6$ and $n_0 = 1$.
For $n \geq 1$: $2n^2 + 3n + 1 \leq 2n^2 + 3n^2 + n^2 = 6n^2$. QED.

### 11.2 Comparison of Sorting Algorithm Complexities

| Algorithm | Best | Average | Worst | Space |
|-----------|------|---------|-------|-------|
| Bubble Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ |
| Insertion Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ |
| Merge Sort | $O(n\log n)$ | $O(n\log n)$ | $O(n\log n)$ | $O(n)$ |
| Quick Sort | $O(n\log n)$ | $O(n\log n)$ | $O(n^2)$ | $O(\log n)$ |
| Heap Sort | $O(n\log n)$ | $O(n\log n)$ | $O(n\log n)$ | $O(1)$ |

*Table 10. Time and space complexities of sorting algorithms*

The best case $O(n)$ of bubble sort assumes an implementation that stops when a pass makes no exchange. The space $O(\log n)$ of quick sort is the average recursion depth; recursing first on the smaller of the two parts and handling the larger part with a loop keeps it $O(\log n)$ even in the worst case.

---

<br>

## Summary

| Concept | Key Summary |
|---------|-------------|
| Big-O | It is an upper bound satisfying $f(n) \leq c \cdot g(n)$ for large $n$. |
| Big-Omega | It is a lower bound satisfying $f(n) \geq c \cdot g(n)$ for large $n$. |
| Theta | It is a tight bound satisfying both $O$ and $\Omega$, and $\Theta(g) = O(g) \cap \Omega(g)$. |
| Little-o | It is a strict upper bound that holds for every positive constant $c$, equivalent to $\lim f/g = 0$. |
| Growth hierarchy | Growth becomes faster in the order $1 < \log n < n < n\log n < n^2 < 2^n < n!$. |
| Limit test | If $\lim f/g$ is 0 the relation is $o$, if it is a positive constant $\Theta$, and if it is infinity $\omega$; L'Hôpital's rule helps compute the limit. |
| Loop analysis | Multiply the iteration count by the body complexity, add the complexities of sequential statements, and keep only the highest order term. |
| Master Theorem | It solves recurrences of the form $T(n) = aT(n/b) + \Theta(n^d)$ by comparing $d$ with $\log_b a$. |
| Amortized analysis | It gives the average cost per operation over a whole sequence of operations. |

---

<br>

## Self-Check Questions

1. **Limit test:** For $f(n) = 3n^2 + 5n$ and $g(n) = n^2$, use a limit to decide the asymptotic relation between the two functions.

   <details>
   <summary>Answer</summary>

   $\lim_{n \to \infty} (3n^2 + 5n)/n^2 = \lim_{n \to \infty} (3 + 5/n) = 3$. Since the limit is a constant with $0 < 3 < \infty$, $f(n) = \Theta(g(n))$, that is, $3n^2 + 5n = \Theta(n^2)$.

   </details>

2. **Base of logarithms:** Are $\log_2 n$ and $\log_{10} n$ in the same complexity class?

   <details>
   <summary>Answer</summary>

   Yes. By the change-of-base formula, $\log_2 n / \log_{10} n = \log_2 10 \approx 3.32$, a positive constant independent of $n$, so $\log_2 n = \Theta(\log_{10} n)$. That is why the base of the logarithm is omitted in complexities and written $\Theta(\log n)$.

   </details>

3. **Comparing exponentials:** Is $2^n = \Theta(3^n)$?

   <details>
   <summary>Answer</summary>

   No. $\lim_{n \to \infty} 2^n / 3^n = \lim_{n \to \infty} (2/3)^n = 0$, so $2^n = o(3^n)$. $2^n = O(3^n)$ holds but $2^n = \Omega(3^n)$ does not, so the relation is not $\Theta$. Unlike logarithms, exponential functions with different bases belong to different classes.

   </details>

4. **Sequence of statements:** Find how many times `sum++` executes in the following code and its time complexity.

   ```cpp
   for (int i = 0; i < n; i++)
       for (int j = 0; j < 10; j++)
           sum++;
   for (int k = 1; k < n; k *= 2)
       sum++;
   ```

   <details>
   <summary>Answer</summary>

   In the first nested loop, the inner loop runs 10 times regardless of $n$, so it executes $10n$ times, which is $O(n)$. In the second loop, `k` doubles each time, so it executes $\lceil \log_2 n \rceil$ times, which is $O(\log n)$. The total is $10n + \lceil \log_2 n \rceil$ times (e.g., 1007 times for $n = 100$), and the time complexity is $O(n) + O(\log n) = O(n)$.

   </details>

5. **Theta and optimality:** If a comparison-based sorting algorithm has a worst-case running time of $\Theta(n^2)$, is it optimal?

   <details>
   <summary>Answer</summary>

   No. $\Theta(n^2)$ only means that its running time grows exactly quadratically. The lower bound for comparison-based sorting is $\Omega(n \log n)$, and heap sort achieves it with $O(n \log n)$, so an algorithm whose worst case is $\Theta(n^2)$ is not optimal.

   </details>
