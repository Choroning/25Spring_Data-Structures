# Chapter 04 — Quiz

> **Last Updated:** 2026-03-21

---

## Q1. Row-Major Address Calculation

**Question:** Given a 2D array `A[5][8]` stored in row-major order with base address 1000 and each element occupying 4 bytes, find the address of `A[3][5]`.

**Answer:** Address = $1000 + (3 \times 8 + 5) \times 4 = 1000 + 29 \times 4 = 1116$.

**Explanation:** In row-major, $\text{location}(A[i][j]) = \text{base} + (i \times n + j) \times \text{size}$. With $i=3$, $j=5$, $n=8$: $(3 \times 8 + 5) = 29$ elements before `A[3][5]`, each taking 4 bytes.

---

## Q2. Sparse Matrix Representation

**Question:** A $100 \times 100$ matrix has only 50 non-zero elements. Compare the storage required for dense vs. sparse (triples) representation, assuming each integer takes 4 bytes.

**Answer:** Dense: $100 \times 100 \times 4 = 40{,}000$ bytes. Sparse (triples): $50 \times 3 \times 4 = 600$ bytes (plus small overhead for dimensions).

**Explanation:** The sparse representation stores only the non-zero elements as $(row, col, value)$ triples. This saves $40{,}000 - 600 = 39{,}400$ bytes, a 98.5% reduction. The break-even point is when $3t = m \times n$, i.e., $t = 3{,}333$ non-zeros.

---

## Q3. Lower Triangular Mapping

**Question:** For a lower triangular matrix of size $5 \times 5$, stored in row-major order in a 1D array, what is the index in the 1D array for element $A[3][1]$ (0-indexed)?

**Answer:** Index = $\frac{3 \times (3+1)}{2} + 1 = 6 + 1 = 7$.

**Explanation:** For lower triangular row-major storage, the number of elements before row $i$ is $\frac{i(i+1)}{2}$, and the element is at offset $j$ within its row. So the 1D index is $\frac{i(i+1)}{2} + j$.

---

## Q4. Fast Transpose Complexity

**Question:** Explain the fast transpose algorithm for a sparse matrix in triples format and its time complexity.

**Answer:** The fast transpose uses two auxiliary arrays: `rowSize[]` (count of elements in each column of the original, which becomes each row of the transpose) and `rowStart[]` (starting position for each row in the result). It makes two passes over the data. Time: $O(t + n)$ where $t$ = non-zeros, $n$ = columns.

**Explanation:** First pass counts elements per column. Second pass computes prefix sums for starting positions. Third pass places each element directly into its correct position. This avoids the $O(t \times n)$ cost of the simple transpose.

---

## Q5. Symmetric Matrix Storage

**Question:** How many elements need to be stored for a symmetric matrix of size $n \times n$? Write the mapping function for element $A[i][j]$ where $i \geq j$.

**Answer:** $\frac{n(n+1)}{2}$ elements. Mapping: $\text{index}(i,j) = \frac{i(i+1)}{2} + j$ (for $i \geq j$; if $i < j$, use $\text{index}(j,i)$).

**Explanation:** Since $A[i][j] = A[j][i]$, we only store the lower triangular portion. For any access where $i < j$, we swap indices and access $A[j][i]$ instead.
