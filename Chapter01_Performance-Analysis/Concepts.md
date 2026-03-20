# Chapter 01 — Performance Analysis

> **Last Updated:** 2026-03-21

---

## Table of Contents

1. [Introduction to Performance Analysis](#1-introduction-to-performance-analysis)
2. [Space Complexity](#2-space-complexity)
3. [Time Complexity](#3-time-complexity)
4. [Performance Measurement](#4-performance-measurement)
5. [Practical Profiling Techniques](#5-practical-profiling-techniques)
6. [Summary](#summary)
7. [Appendix](#appendix)

---

## 1. Introduction to Performance Analysis

### 1.1 What is Performance?

Performance of a program is measured by two key resources:

- **Space** (memory) used by the program
- **Time** (CPU cycles / wall-clock time) consumed during execution

Performance analysis helps us predict the behavior of a program **before** running it, while performance measurement gives us **empirical** data from actual execution.

### 1.2 Why Analyze Performance?

- Compare alternative algorithms for the same problem
- Predict scalability as input size grows
- Identify bottlenecks before deployment
- Make informed design decisions

> **Key Point:** Performance analysis is an *a priori* estimate; performance measurement is an *a posteriori* test.

---

## 2. Space Complexity

### 2.1 Components of Space

The total space $S(P)$ needed by a program $P$ consists of:

$$S(P) = c + S_p(\text{instance characteristics})$$

Where:
- $c$ = **fixed part**: code space, simple variables, constants
- $S_p$ = **variable part**: depends on the particular problem instance (input size, recursion depth, dynamic allocations)

### 2.2 Fixed vs. Variable Space

| Component | Fixed | Variable |
|-----------|-------|----------|
| Instruction space | Yes | No |
| Simple variables | Yes | No |
| Dynamically allocated memory | No | Yes |
| Recursion stack space | No | Yes |

### 2.3 Example: Array Sum

```cpp
// Space complexity analysis
int sum(int a[], int n) {
    int total = 0;          // 1 int
    for (int i = 0; i < n; i++)  // 1 int (i)
        total += a[i];
    return total;
}
// S_p = 0 (no extra space proportional to n)
// Total: O(1) extra space (ignoring input array)
```

### 2.4 Recursive Space

```cpp
int recursiveSum(int a[], int n) {
    if (n == 0) return 0;
    return a[n-1] + recursiveSum(a, n-1);
}
// Each recursive call uses stack space
// Depth of recursion = n
// S_p = O(n)
```

> **Key Point:** Recursive algorithms can have significantly higher space complexity due to the call stack.

---

## 3. Time Complexity

### 3.1 Operation Counts

Time complexity is estimated by counting the number of **key operations** as a function of input size $n$.

Key operations include:
- Comparisons
- Arithmetic operations
- Data movements (assignments)
- Function calls

### 3.2 Step Count Method

A **program step** is a syntactically or semantically meaningful segment of a program that has an execution time independent of the instance characteristics.

```cpp
// Step count example: Matrix Addition
void matrixAdd(int A[][MAX], int B[][MAX], int C[][MAX], int n) {
    for (int i = 0; i < n; i++)         // n+1 times
        for (int j = 0; j < n; j++)     // n(n+1) times
            C[i][j] = A[i][j] + B[i][j]; // n^2 times
}
// Total steps: n+1 + n(n+1) + n^2 = 2n^2 + 2n + 1
// Time complexity: O(n^2)
```

### 3.3 Best, Worst, and Average Cases

For a given input size $n$:
- **Best case**: minimum number of steps over all possible inputs of size $n$
- **Worst case**: maximum number of steps (most commonly used)
- **Average case**: expected number of steps (requires probability distribution)

```cpp
// Sequential search example
int sequentialSearch(int a[], int n, int x) {
    for (int i = 0; i < n; i++)
        if (a[i] == x) return i;
    return -1;
}
// Best case:   O(1)    — found at first position
// Worst case:  O(n)    — not found or at last position
// Average case: O(n/2) = O(n)
```

---

## 4. Performance Measurement

### 4.1 Wall-Clock Timing

```cpp
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();
// ... code to measure ...
auto end = std::chrono::high_resolution_clock::now();

auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
std::cout << "Time: " << duration.count() << " microseconds" << std::endl;
```

### 4.2 CPU Time vs. Wall-Clock Time

| Metric | Description | Use Case |
|--------|-------------|----------|
| Wall-clock time | Total elapsed real time | End-user experience |
| CPU time | Time spent by CPU on the process | Algorithm comparison |
| User time | CPU time in user mode | Pure computation |
| System time | CPU time in kernel mode | I/O operations |

### 4.3 Measurement Best Practices

1. **Run multiple iterations** to reduce variance
2. **Warm up** the cache before timing
3. **Disable optimizations** (or measure with them) consistently
4. **Use large enough inputs** to get meaningful measurements
5. **Account for system load** and background processes

---

## 5. Practical Profiling Techniques

### 5.1 Using `clock()` for CPU Time

```cpp
#include <ctime>

clock_t start = clock();
// ... code to measure ...
clock_t end = clock();
double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
```

### 5.2 Empirical Complexity Determination

By measuring runtime at different input sizes, you can empirically determine the growth rate:

| n | T(n) | T(n)/n | T(n)/n^2 | T(n)/n*log(n) |
|---|------|--------|----------|---------------|
| 1000 | 0.01s | 1e-5 | 1e-8 | 1.4e-6 |
| 2000 | 0.04s | 2e-5 | 1e-8 | 2.6e-6 |
| 4000 | 0.16s | 4e-5 | 1e-8 | 4.8e-6 |

If $T(n)/n^2$ remains roughly constant, the algorithm is $O(n^2)$.

---

## Summary

| Concept | Key Point |
|---------|-----------|
| Space complexity | $S(P) = c + S_p$; fixed + variable parts |
| Time complexity | Count key operations as function of $n$ |
| Step count | Assign steps to each statement and sum |
| Best/Worst/Average | Different bounds for different input distributions |
| Performance measurement | Use `chrono` or `clock()` for empirical timing |
| Profiling | Multiple runs, large inputs, consistent methodology |

---

## Appendix

### Common Pitfalls in Performance Analysis

1. **Ignoring constants**: While $O$-notation hides constants, they matter in practice for moderate $n$
2. **Confusing amortized and worst-case**: Some operations are expensive occasionally but cheap on average
3. **Cache effects**: Memory access patterns significantly affect real-world performance
4. **Compiler optimizations**: May eliminate dead code or reorder operations

### Interview Questions

1. **Q:** What is the difference between time complexity and space complexity?
   **A:** Time complexity measures the number of operations as a function of input size; space complexity measures the memory required.

2. **Q:** Why do we typically focus on worst-case analysis?
   **A:** It provides a guarantee on the maximum resources needed, which is critical for real-time systems and reliability.

3. **Q:** Can an algorithm with higher time complexity be faster in practice?
   **A:** Yes, for small inputs, an $O(n^2)$ algorithm with small constants can outperform an $O(n \log n)$ algorithm with large constants.
