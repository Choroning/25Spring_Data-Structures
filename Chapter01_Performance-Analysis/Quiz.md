# Chapter 01 — Quiz

> **Last Updated:** 2026-03-21

---

## Q1. Space Complexity Definition

**Question:** Define space complexity of a program. What are the two components that make up the total space requirement?

**Answer:** Space complexity $S(P)$ is the total amount of memory required by a program $P$. It consists of a fixed part $c$ (instruction space, simple variables, constants) and a variable part $S_p$ that depends on the instance characteristics (input size, recursion depth, dynamic memory).

**Explanation:** $S(P) = c + S_p(\text{instance characteristics})$. The fixed part is independent of the input, while the variable part grows with the problem size.

---

## Q2. Step Count for Loop

**Question:** Determine the step count for the following code fragment:
```cpp
for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        x += 2;
```

**Answer:** The total step count is $2n^2 + 2n + 1$.

**Explanation:** The outer loop test executes $n+1$ times, the inner loop test executes $n(n+1)$ times, and the assignment `x += 2` executes $n^2$ times. Summing: $(n+1) + n(n+1) + n^2 = 2n^2 + 2n + 1$.

---

## Q3. Recursive Space Complexity

**Question:** What is the space complexity of a recursive function that computes the sum of an array of size $n$?

**Answer:** $S_p = O(n)$.

**Explanation:** Each recursive call adds a frame to the call stack containing the return address, parameters, and local variables. Since the recursion depth is $n$, the variable space is proportional to $n$.

---

## Q4. Best, Worst, Average Case

**Question:** For sequential search on an unsorted array of $n$ elements, state the best-case, worst-case, and average-case time complexities.

**Answer:** Best case: $O(1)$, Worst case: $O(n)$, Average case: $O(n)$.

**Explanation:** Best case occurs when the target is at the first position (1 comparison). Worst case when the target is at the last position or not present ($n$ comparisons). Average case assumes uniform probability, requiring $n/2$ comparisons on average, which is $O(n)$.

---

## Q5. Performance Measurement

**Question:** Explain the difference between wall-clock time and CPU time. Which is more appropriate for comparing algorithm performance?

**Answer:** Wall-clock time is the total elapsed real time (includes I/O waits, context switches). CPU time is only the time the CPU spends executing the process. CPU time is more appropriate for algorithm comparison because it excludes external factors.

**Explanation:** Wall-clock time can vary significantly due to system load, while CPU time more accurately reflects the computational work performed by the algorithm.
