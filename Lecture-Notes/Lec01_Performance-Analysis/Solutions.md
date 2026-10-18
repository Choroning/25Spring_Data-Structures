# Lecture 1 Solutions — Performance Analysis

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Table of Contents

- [Exercise 1: Space Complexity Definition](#exercise-1-space-complexity-definition)
- [Exercise 2: Step Count for Loop](#exercise-2-step-count-for-loop)
- [Exercise 3: Recursive Space Complexity](#exercise-3-recursive-space-complexity)
- [Exercise 4: Best, Worst, Average Case](#exercise-4-best-worst-average-case)
- [Exercise 5: Performance Measurement](#exercise-5-performance-measurement)

---

<br>

## Exercise 1: Space Complexity Definition

**Problem:** Define space complexity of a program. What are the two components that make up the total space requirement?

### Solution

**Answer:** Space complexity $S(P)$ is the total amount of memory required by a program $P$. It consists of a fixed part $c$ (instruction space, simple variables, constants) and a variable part $S_p$ that depends on the instance characteristics (input size, recursion depth, dynamic memory).

**Explanation:** $S(P) = c + S_p(\text{instance characteristics})$. The fixed part is independent of the input, while the variable part grows with the problem size.

---

<br>

## Exercise 2: Step Count for Loop

**Problem:** Determine the step count for the following code fragment:

```cpp
for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        x += 2;
```

### Solution

**Answer:** The total step count is $2n^2 + 2n + 1$.

**Explanation:** Loop-header tests are counted up to and including the last test, in which the condition becomes false. The outer loop test executes $n+1$ times, the inner loop test executes $n(n+1)$ times, and the assignment `x += 2` executes $n^2$ times. Summing: $(n+1) + n(n+1) + n^2 = 2n^2 + 2n + 1$.

---

<br>

## Exercise 3: Recursive Space Complexity

**Problem:** What is the space complexity of a recursive function that computes the sum of an array of size $n$?

### Solution

**Answer:** $S_p = O(n)$.

**Explanation:** Each recursive call adds a frame to the call stack containing the return address, parameters, and local variables. Since the recursion depth is $n$, the variable space is proportional to $n$.

---

<br>

## Exercise 4: Best, Worst, Average Case

**Problem:** For sequential search on an unsorted array of $n$ elements, state the best-case, worst-case, and average-case time complexities.

### Solution

**Answer:** Best case: $O(1)$, Worst case: $O(n)$, Average case: $O(n)$.

**Explanation:** Best case occurs when the target is at the first position (1 comparison). Worst case when the target is at the last position or not present ($n$ comparisons). Average case assumes the target is present and equally likely to be at each position, requiring $(1 + 2 + \cdots + n)/n = (n+1)/2$, or about $n/2$, comparisons on average, which is $O(n)$.

---

<br>

## Exercise 5: Performance Measurement

**Problem:** Explain the difference between wall-clock time and CPU time. Which is more appropriate for comparing algorithm performance?

### Solution

**Answer:** Wall-clock time is the total elapsed real time (includes I/O waits, context switches). CPU time is only the time the CPU spends executing the process. CPU time is more appropriate for algorithm comparison because it excludes external factors.

**Explanation:** Wall-clock time can vary significantly due to system load, while CPU time more accurately reflects the computational work performed by the algorithm.
