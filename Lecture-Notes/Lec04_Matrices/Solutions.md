# Lecture 4 Solutions — Matrices

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Table of Contents

- [Exercise 1: Row-Major Address Calculation](#exercise-1-row-major-address-calculation)
- [Exercise 2: Sparse Matrix Representation](#exercise-2-sparse-matrix-representation)
- [Exercise 3: Lower Triangular Mapping](#exercise-3-lower-triangular-mapping)
- [Exercise 4: Fast Transpose Complexity](#exercise-4-fast-transpose-complexity)
- [Exercise 5: Symmetric Matrix Storage](#exercise-5-symmetric-matrix-storage)

---

<br>

## Exercise 1: Row-Major Address Calculation

**Problem:** Given a 2D array `A[5][8]` stored in row-major order with base address 1000 and each element occupying 4 bytes, find the address of `A[3][5]`.

### Solution

**Answer:** The address is $1000 + (3 \times 8 + 5) \times 4 = 1000 + 29 \times 4 = 1116$.

**Explanation:** In row-major, $\text{location}(A[i][j]) = \text{base} + (i \times n + j) \times \text{size}$. With $i=3$, $j=5$, $n=8$, there are $(3 \times 8 + 5) = 29$ elements before `A[3][5]`, each taking 4 bytes.

---

<br>

## Exercise 2: Sparse Matrix Representation

**Problem:** A $100 \times 100$ matrix has only 50 non-zero elements. Compare the storage required for dense vs. sparse (triples) representation, assuming each integer takes 4 bytes.

### Solution

**Answer:** The dense representation needs $100 \times 100 \times 4 = 40{,}000$ bytes. The sparse (triples) representation needs $50 \times 3 \times 4 = 600$ bytes, plus a small overhead for recording the dimensions of the matrix.

**Explanation:** The sparse representation stores only the non-zero elements as $(row, col, value)$ triples. This saves $40{,}000 - 600 = 39{,}400$ bytes, a 98.5% reduction. The break-even point is when $3t = m \times n$, i.e., $t = 10{,}000 / 3 \approx 3{,}333$ non-zeros. With more non-zero elements than this, the triples representation uses more space than the dense one.

---

<br>

## Exercise 3: Lower Triangular Mapping

**Problem:** For a lower triangular matrix of size $5 \times 5$, stored in row-major order in a 1D array, what is the index in the 1D array for element $A[3][1]$ (0-indexed)?

### Solution

**Answer:** The index is $\frac{3 \times (3+1)}{2} + 1 = 6 + 1 = 7$.

**Explanation:** For lower triangular row-major storage, the number of elements before row $i$ is $\frac{i(i+1)}{2}$, and the element is at offset $j$ within its row. So the 1D index is $\frac{i(i+1)}{2} + j$. Counting directly, row 0 has 1 element (index 0), row 1 has 2 (indices 1, 2), and row 2 has 3 (indices 3-5), so row 3 starts at index 6 and $A[3][1]$ is at the next index, 7.

---

<br>

## Exercise 4: Fast Transpose Complexity

**Problem:** Explain the fast transpose algorithm for a sparse matrix in triples format and its time complexity.

### Solution

**Answer:** The fast transpose uses two auxiliary arrays. `rowSize[]` is the count of elements in each column of the original (which becomes each row of the transpose), and `rowStart[]` is the starting position for each row in the result. It scans the term array twice (counting and placing) and the array of column size once (prefix sums). Time: $O(t + n)$ where $t$ = non-zeros, $n$ = columns.

**Explanation:** The first pass scans the terms and counts elements per column. The second pass scans the columns and computes prefix sums for starting positions. The third pass scans the terms again and places each element directly into its correct position. This avoids the $O(t \times n)$ cost of the simple transpose, which scans all terms for every column. Lecture 4, Section 5.3 gives an implementation and an example.

---

<br>

## Exercise 5: Symmetric Matrix Storage

**Problem:** How many elements need to be stored for a symmetric matrix of size $n \times n$? Write the mapping function for element $A[i][j]$ where $i \geq j$.

### Solution

**Answer:** $\frac{n(n+1)}{2}$ elements need to be stored. The mapping is $\text{index}(i,j) = \frac{i(i+1)}{2} + j$ (for $i \geq j$; if $i < j$, use $\text{index}(j,i)$; indices are counted from 0).

**Explanation:** Since $A[i][j] = A[j][i]$, we only store the lower triangular portion. For any access where $i < j$, we swap indices and access $A[j][i]$ instead.
