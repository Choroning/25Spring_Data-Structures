# Chapter 04 — Matrices

> **Last Updated:** 2026-03-21

---

## Table of Contents

1. [Arrays and Matrices](#1-arrays-and-matrices)
2. [Row-Major and Column-Major Order](#2-row-major-and-column-major-order)
3. [Special Matrices](#3-special-matrices)
4. [Sparse Matrices](#4-sparse-matrices)
5. [Linked Representation of Sparse Matrices](#5-linked-representation-of-sparse-matrices)
6. [Matrix Operations](#6-matrix-operations)
7. [Summary](#summary)
8. [Appendix](#appendix)

---

## 1. Arrays and Matrices

### 1.1 Multi-dimensional Arrays

A **two-dimensional array** (matrix) `A[m][n]` stores $m \times n$ elements organized in $m$ rows and $n$ columns.

### 1.2 Memory Mapping

Since memory is linear, 2D arrays must be mapped to 1D. The mapping function determines how elements are laid out.

For a 2D array `A[r][c]` with dimensions $m \times n$:

**Row-major order**: $\text{location}(A[i][j]) = \text{base} + (i \cdot n + j) \cdot \text{sizeof}(T)$

**Column-major order**: $\text{location}(A[i][j]) = \text{base} + (j \cdot m + i) \cdot \text{sizeof}(T)$

---

## 2. Row-Major and Column-Major Order

### 2.1 Row-Major (C/C++ Default)

Elements of each row are stored contiguously:

```
A[0][0], A[0][1], ..., A[0][n-1], A[1][0], A[1][1], ..., A[m-1][n-1]
```

### 2.2 Column-Major (Fortran, MATLAB)

Elements of each column are stored contiguously:

```
A[0][0], A[1][0], ..., A[m-1][0], A[0][1], A[1][1], ..., A[m-1][n-1]
```

> **Key Point:** Row-major favors row-wise traversal for cache efficiency; column-major favors column-wise traversal.

---

## 3. Special Matrices

### 3.1 Diagonal Matrix

Only elements on the main diagonal are non-zero: $A[i][j] = 0$ when $i \neq j$.

Storage: Only $n$ elements needed for an $n \times n$ matrix.

$$\text{map}(i) = i \quad \text{(store } A[i][i] \text{ at position } i\text{)}$$

### 3.2 Tridiagonal Matrix

Non-zero elements only on the main diagonal and the two adjacent diagonals.

Storage: $3n - 2$ elements for an $n \times n$ matrix.

### 3.3 Triangular Matrices

**Lower triangular**: $A[i][j] = 0$ when $j > i$

Number of elements: $\frac{n(n+1)}{2}$

Mapping: $\text{map}(i,j) = \frac{i(i+1)}{2} + j$ (row-major lower triangular)

**Upper triangular**: $A[i][j] = 0$ when $j < i$

### 3.4 Symmetric Matrix

$A[i][j] = A[j][i]$ for all $i, j$. Only need to store the lower (or upper) triangular part: $\frac{n(n+1)}{2}$ elements.

---

## 4. Sparse Matrices

### 4.1 Definition

A matrix is **sparse** if a large fraction of its elements are zero. Typically, the number of non-zero elements is $O(n)$ or $O(n \log n)$ for an $n \times n$ matrix, rather than $O(n^2)$.

### 4.2 Array of Triples Representation

Store each non-zero element as a triple $(i, j, \text{value})$:

```cpp
struct MatrixTerm {
    int row;
    int col;
    int value;
};
```

For a matrix with $t$ non-zero elements:
- Space: $O(t)$ instead of $O(m \times n)$
- Access: $O(t)$ to find an element (linear scan)

### 4.3 Transpose of Sparse Matrix

For triples representation, transpose by swapping row and column indices, then sorting by new row order.

**Simple approach**: $O(t \cdot n)$ where $t$ = number of terms, $n$ = number of columns
**Fast transpose**: $O(t + n)$ using column count arrays

---

## 5. Linked Representation of Sparse Matrices

### 5.1 Orthogonal List

Each non-zero element is a node with:
- `row`, `col`, `value`
- `nextInRow` (pointer to next non-zero in same row)
- `nextInCol` (pointer to next non-zero in same column)

Plus arrays of row and column head pointers.

### 5.2 Advantages

- Efficient insertion and deletion of non-zero elements
- Natural representation for operations like addition

---

## 6. Matrix Operations

### 6.1 Sparse Matrix Addition

For two sparse matrices in triple form:
- Merge the sorted triple lists
- Handle overlapping positions by adding values

Time complexity: $O(t_1 + t_2)$

### 6.2 Sparse Matrix Multiplication

Time complexity depends on the representation but generally more efficient than dense multiplication when matrices are sufficiently sparse.

---

## Summary

| Concept | Key Point |
|---------|-----------|
| Row-major order | Rows stored contiguously; C/C++ default |
| Column-major order | Columns stored contiguously; Fortran/MATLAB |
| Diagonal matrix | Store only $n$ elements |
| Triangular matrix | Store $n(n+1)/2$ elements |
| Sparse matrix | Store only non-zero elements; saves space when most are zero |
| Triples representation | $(row, col, value)$ tuples |
| Fast transpose | $O(t + n)$ using auxiliary arrays |

---

## Appendix

### When to Use Sparse Representation

Use sparse representation when the density $d = \frac{\text{non-zeros}}{m \times n}$ is below approximately 0.3 (30%). Above this threshold, the overhead of the sparse structure may exceed the savings.

### Applications of Sparse Matrices

- Finite element analysis
- Network adjacency matrices (social graphs, web link graphs)
- Natural language processing (term-document matrices)
- Scientific computing (PDE discretization)
