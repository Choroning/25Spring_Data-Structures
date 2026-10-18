# Lecture 4 — Matrices

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-18

> **Learning Objectives:**
> 1. Explain the memory representation of 1D and 2D arrays and compute their space overhead
> 2. Compute the location of an element under row-major and column-major mapping
> 3. Define matrix transpose, addition, and multiplication and implement matrix operations using 2D arrays
> 4. Store diagonal, tridiagonal, triangular, and symmetric matrices compactly in a 1D array
> 5. Represent sparse matrices with arrays or linked structures for efficiency
> 6. Analyze the time and space complexity of matrix operations

---

<br>

## Table of Contents

- [1. Arrays and Matrices](#1-arrays-and-matrices)
  - [1.1 Tabular Data and Matrices](#11-tabular-data-and-matrices)
  - [1.2 Multi-dimensional Arrays](#12-multi-dimensional-arrays)
  - [1.3 Memory Representation of a 1D Array](#13-memory-representation-of-a-1d-array)
  - [1.4 Memory Mapping](#14-memory-mapping)
  - [1.5 Array-of-Arrays Representation](#15-array-of-arrays-representation)
  - [1.6 Irregular 2D Arrays](#16-irregular-2d-arrays)
- [2. Row-Major and Column-Major Order](#2-row-major-and-column-major-order)
  - [2.1 Row-Major (C/C++ Default)](#21-row-major-cc-default)
  - [2.2 Column-Major (Fortran, MATLAB)](#22-column-major-fortran-matlab)
  - [2.3 Both Mappings of the Same Array](#23-both-mappings-of-the-same-array)
  - [2.4 Generalized Mapping Functions](#24-generalized-mapping-functions)
- [3. Matrices](#3-matrices)
  - [3.1 Definition of a Matrix](#31-definition-of-a-matrix)
  - [3.2 Transpose, Addition, and Multiplication](#32-transpose-addition-and-multiplication)
  - [3.3 Shortcomings of a 2D Array for a Matrix](#33-shortcomings-of-a-2d-array-for-a-matrix)
- [4. Special Matrices](#4-special-matrices)
  - [4.1 Square Matrices and Kinds of Special Matrices](#41-square-matrices-and-kinds-of-special-matrices)
  - [4.2 Diagonal Matrix](#42-diagonal-matrix)
  - [4.3 Tridiagonal Matrix](#43-tridiagonal-matrix)
  - [4.4 Triangular Matrices](#44-triangular-matrices)
  - [4.5 Symmetric Matrix](#45-symmetric-matrix)
- [5. Sparse Matrices](#5-sparse-matrices)
  - [5.1 Definition](#51-definition)
  - [5.2 Array of Triples Representation](#52-array-of-triples-representation)
  - [5.3 Transpose of Sparse Matrix](#53-transpose-of-sparse-matrix)
- [6. Linked Representation of Sparse Matrices](#6-linked-representation-of-sparse-matrices)
  - [6.1 Row Chain Representation](#61-row-chain-representation)
  - [6.2 Orthogonal List](#62-orthogonal-list)
  - [6.3 Advantages](#63-advantages)
- [7. Matrix Operations](#7-matrix-operations)
  - [7.1 Sparse Matrix Addition](#71-sparse-matrix-addition)
  - [7.2 Sparse Matrix Multiplication](#72-sparse-matrix-multiplication)
- [8. Appendix](#8-appendix)
  - [8.1 When to Use Sparse Representation](#81-when-to-use-sparse-representation)
  - [8.2 Applications of Sparse Matrices](#82-applications-of-sparse-matrices)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Arrays and Matrices

### 1.1 Tabular Data and Matrices

Data is often available in tabular form, and tabular data is usually represented in arrays. A **matrix** is a typical example of tabular data and is often represented as a 2-dimensional array, which is a data structure. A matrix and a C++ 2D array differ in the following two ways.

1. Matrices are normally indexed beginning at 1 rather than 0.
2. Matrices support operations such as addition, multiplication, and transpose, which C++ 2D arrays do not support.

Using a customized representation instead of a plain multidimensional array can reduce time and space. The sections below cover row-major and column-major mapping of multidimensional arrays (Sections 1-2), matrices and their operations (Section 3), and special matrices such as diagonal, tridiagonal, triangular, symmetric, and sparse matrices (Sections 4-7).

### 1.2 Multi-dimensional Arrays

A **two-dimensional array** (matrix) `A[m][n]` stores $m \times n$ elements organized in $m$ rows and $n$ columns.

In C++, the 2D array declared as `int a[3][4];` holds $3 \times 4 = 12$ values of type `int`, so with 4-byte `int` the elements alone need $12 \times 4 = 48$ bytes. The array can be shown as the table below. Each horizontal line is a **row**, and each vertical line is a **column**.

| | Column 0 | Column 1 | Column 2 | Column 3 |
|:--|:--|:--|:--|:--|
| Row 0 | `a[0][0]` | `a[0][1]` | `a[0][2]` | `a[0][3]` |
| Row 1 | `a[1][0]` | `a[1][1]` | `a[1][2]` | `a[1][3]` |
| Row 2 | `a[2][0]` | `a[2][1]` | `a[2][2]` | `a[2][3]` |

*Table 1. Elements of a 3 × 4 2D array with their row and column numbers*

### 1.3 Memory Representation of a 1D Array

The elements of the 1D array `x = [a, b, c, d]` are placed one after another in contiguous memory locations. If `start` is the location of the first element, the location of element `x[i]` is as follows.

$$\text{location}(x[i]) = \text{start} + i$$

Here locations are counted in elements; as a byte address the location is $\text{start} + i \times \text{sizeof}(T)$. For example, if `start` points to memory cell 4, then `x[0]` is in cell $4 + 0 = 4$ and `x[3]` is in cell $4 + 3 = 7$.

```text
cell     0   1   2   3   4   5   6   7   8   9
       +---+---+---+---+---+---+---+---+---+---+
memory |   |   |   |   | a | b | c | d |   |   |
       +---+---+---+---+---+---+---+---+---+---+
                         ^
                         |
                       start
```

*Figure 1. 1D array x = [a, b, c, d] in contiguous memory*

The **space overhead** of a representation is the memory needed in addition to the elements; here it is the 4 bytes that store `start`. The space needed for the elements themselves is not counted as overhead.

> **Note:** Here and below, all overhead calculations assume a 32-bit environment where a pointer and an `int` each take 4 bytes. In a 64-bit environment a pointer usually takes 8 bytes, so the overhead spent on pointers doubles.

### 1.4 Memory Mapping

Since memory is linear, 2D arrays must be mapped to 1D. The mapping function determines how elements are laid out.

For element `A[i][j]` (indices from 0) of a 2D array `A` with dimensions $m \times n$, the addresses under the two mappings are as follows.

**Row-major order:** $\text{location}(A[i][j]) = \text{base} + (i \cdot n + j) \cdot \text{sizeof}(T)$

**Column-major order:** $\text{location}(A[i][j]) = \text{base} + (j \cdot m + i) \cdot \text{sizeof}(T)$

Here $\text{base}$ is the byte address of `A[0][0]`, and $\text{sizeof}(T)$ is the number of bytes in one element. Section 2 covers both mappings in detail.

### 1.5 Array-of-Arrays Representation

Consider a 3 × 4 array `x[3][4]` whose elements are a through l. Row 0 is [a, b, c, d], row 1 is [e, f, g, h], and row 2 is [i, j, k, l].

C++ views a 2D array as a 1D array of rows. That is, `x` is a 1D array [row 0, row 1, row 2] whose elements are three rows, and each row is a 1D array of four elements. Keeping each row as a separate 1D array and storing the start address of each row in a pointer array whose length is the number of rows is called the **array-of-arrays representation**.

```text
  x                 [0]   [1]   [2]   [3]
+------+          +-----+-----+-----+-----+
| x[0] | -------> |  a  |  b  |  c  |  d  |
+------+          +-----+-----+-----+-----+
| x[1] | -------> |  e  |  f  |  g  |  h  |
+------+          +-----+-----+-----+-----+
| x[2] | -------> |  i  |  j  |  k  |  l  |
+------+          +-----+-----+-----+-----+
```

*Figure 2. A 3 × 4 array stored in the array-of-arrays representation*

This representation requires four blocks of contiguous memory of sizes 3, 4, 4, and 4. One is a pointer array whose size is the number of rows, and the other blocks, as many as the rows, are row arrays whose size is the number of columns. The space overhead is the row pointer array, the extra memory needed to keep the rows separate, which is (number of rows) × 4 bytes = 3 × 4 bytes = 12 bytes. Including the elements, the total memory is $(3 \times 4) + (3 \times 4 \times 4) = 12 + 48 = 60$ bytes.

> **Caution:** A C++ array declared with fixed sizes, such as `int x[3][4];`, is actually one block of 12 elements in row-major order and stores no row pointers. In that case `x[i]` is not a stored pointer but an address computed from the start address. The array-of-arrays representation, in which the row pointers occupy memory of their own, corresponds to a dynamic 2D array created as `int** x` with a pointer array from `new int*[3]` and each row allocated by `new int[4]`.

### 1.6 Irregular 2D Arrays

An **irregular 2D array** is a 2D array in which the rows are not required to have the same length. Because the array-of-arrays representation allocates each row separately, each row can have a different length. The figure below stores 1 through 10 in order in four rows of lengths 1, 2, 3, and 4.

```text
x[0] ---> | 1 |
x[1] ---> | 2 | 3 |
x[2] ---> | 4 | 5 | 6 |
x[3] ---> | 7 | 8 | 9 | 10 |
```

*Figure 3. Irregular 2D array with row lengths 1, 2, 3, and 4*

This array can be created in C++ as follows.

```cpp
int** x = new int*[4];          // array of 4 row pointers
int value = 1;
for (int i = 0; i < 4; i++) {
    x[i] = new int[i + 1];      // row i has i + 1 elements
    for (int j = 0; j <= i; j++)
        x[i][j] = value++;      // stores 1, 2, ..., 10 row by row
}
```

---

<br>

## 2. Row-Major and Column-Major Order

### 2.1 Row-Major (C/C++ Default)

Elements of each row are stored contiguously:

```text
A[0][0], A[0][1], ..., A[0][n-1], A[1][0], A[1][1], ..., A[m-1][n-1]
```

**Row-major mapping** converts a 2D array into a 1D array `y` by collecting its elements row by row. Within a row, elements are collected from left to right, and rows are collected from top to bottom. Mapping the 3 × 4 array `x` of Section 1.5 in row-major order gives `y[12] = {a, b, c, d, e, f, g, h, i, j, k, l}`.

```text
index   0  1  2  3    4  5  6  7    8  9 10 11
y       a  b  c  d    e  f  g  h    i  j  k  l
        \- row 0 -/   \- row 1 -/   \- row 2 -/
```

*Figure 4. 1D array from the row-major mapping of a 3 × 4 array*

In an array with $m$ rows and $n$ columns, the position of element `x[i][j]` is found as follows (indices from 0).

1. Each row has $n$ elements (the number of columns).
2. Row $i$ is preceded by the $i$ rows from row $0$ through row $i-1$, so there are $i \times n$ elements to the left of `x[i][0]`. For example, with 4 columns there are $2 \times 4 = 8$ elements to the left of `x[2][0]`.
3. Within its row, `x[i][j]` is preceded by $j$ elements, so `x[i][j]` is at the following position, counted from 1.

$$\text{map}(i, j) = i \times n + (j + 1)$$

For example, with $n = 4$, $\text{map}(1, 0) = 1 \times 4 + (0 + 1) = 5$, so `x[1][0]` (e) is the fifth element of the 1D array, and $\text{map}(2, 2) = 2 \times 4 + (2 + 1) = 11$, so `x[2][2]` (k) is the eleventh element. As a 1D index counted from 0 the position is $i \times n + j$, and the address formula of Section 1.4 multiplies this index by the element size and adds it to the base address.

The space overhead of row-major mapping is 8 bytes: 4 bytes for `start`, the start of the 1D array, plus 4 bytes for the number of columns $n$ (the number of elements in each row). A 3 × 4 `int` array needs contiguous memory of size $3 \times 4 = 12$ elements, that is, $12 \times 4 = 48$ bytes, so the total memory is $8 + 48 = 56$ bytes. The overhead is smaller than in the array-of-arrays representation (60 bytes) and the gap grows with the number of rows, but this mapping requires one contiguous block large enough for all elements. The array-of-arrays representation can instead be allocated as several small blocks the size of one row.

### 2.2 Column-Major (Fortran, MATLAB)

Elements of each column are stored contiguously:

```text
A[0][0], A[1][0], ..., A[m-1][0], A[0][1], A[1][1], ..., A[m-1][n-1]
```

**Column-major mapping** collects elements column by column. Within a column, elements are collected from top to bottom, and columns are collected from left to right. Mapping the 3 × 4 array `x` of Section 1.5 in column-major order gives `y[12] = {a, e, i, b, f, j, c, g, k, d, h, l}`.

> **Key Point:** Row-major favors row-wise traversal for cache efficiency; column-major favors column-wise traversal.

### 2.3 Both Mappings of the Same Array

Writing the row-major position $6i + j$ in each element `a[i][j]` of `int a[3][6];` gives the following.

| | Column 0 | Column 1 | Column 2 | Column 3 | Column 4 | Column 5 |
|:--|:--|:--|:--|:--|:--|:--|
| Row 0 | 0 | 1 | 2 | 3 | 4 | 5 |
| Row 1 | 6 | 7 | 8 | 9 | 10 | 11 |
| Row 2 | 12 | 13 | 14 | 15 | 16 | 17 |

*Table 2. Row-major position written in each element of a 3 × 6 array*

The two mappings place these elements in the 1D array in the following orders.

- Row-major mapping places them in the order (0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17).
- Column-major mapping places them in the order (0 6 12 1 7 13 2 8 14 3 9 15 4 10 16 5 11 17).

### 2.4 Generalized Mapping Functions

For $u_1 \times u_2$ and $u_1 \times u_2 \times u_3$ arrays with indices starting at 0, the row-major mapping functions are as follows. The value is the 1D position of the element, counted from 0.

$$\text{map}(i_1, i_2) = i_1 u_2 + i_2$$

$$\text{map}(i_1, i_2, i_3) = i_1 u_2 u_3 + i_2 u_3 + i_3$$

In the 2D formula, $u_2$ is the number of elements in each row (the number of columns). In the 3D formula, $i_1 u_2 u_3$ counts the elements in the $i_1$ preceding $u_2 \times u_3$ planes, and $i_2 u_3$ counts the elements in the $i_2$ preceding rows of the same plane. If the indices start at 1, substitute each index minus 1.

For the 3 × 6 array of Section 2.3, $\text{map}(i_1, i_2) = 6 i_1 + i_2$, so $\text{map}(2, 3) = 6 \times 2 + 3 = 15$, which equals the value written in `a[2][3]` in Table 2.

In column-major mapping the columns become the outer unit, so the two indices swap roles.

$$\text{map}(i_1, i_2) = i_2 u_1 + i_1$$

For the 3 × 6 array, column-major $\text{map}(2, 3) = 3 \times 3 + 2 = 11$, which agrees with 15 being at position 11 (counted from 0) of the column-major order in Section 2.3.

---

<br>

## 3. Matrices

### 3.1 Definition of a Matrix

An $m \times n$ **matrix** is a table with $m$ rows and $n$ columns. $M(i, j)$ denotes the element in row $i$ and column $j$, and matrix indices are counted from 1 ($1 \le i \le m$, $1 \le j \le n$). Common matrix operations are transpose, addition, and multiplication.

### 3.2 Transpose, Addition, and Multiplication

**Transpose:** The result of transposing an $m \times n$ matrix $M$ is an $n \times m$ matrix $M^T$ with the following property.

$$M^T(j, i) = M(i, j), \quad 1 \le i \le m, \ 1 \le j \le n$$

**Addition:** The sum of matrices is only defined for matrices that have the same dimensions. The sum of two $m \times n$ matrices $A$ and $B$ is an $m \times n$ matrix $C$ with the following property.

$$C(i, j) = A(i, j) + B(i, j), \quad 1 \le i \le m, \ 1 \le j \le n$$

**Multiplication:** The product of matrices $A$ and $B$ is only defined when the number of columns in $A$ equals the number of rows in $B$. If $A$ is an $m \times n$ matrix and $B$ is an $n \times q$ matrix, $A \times B$ is an $m \times q$ matrix $C$ with the following property.

$$C(i, j) = \sum_{k=1}^{n} A(i, k) \times B(k, j), \quad 1 \le i \le m, \ 1 \le j \le q$$

That is, $C(i, j)$ is the sum of the products of the elements at the same position $k$ in row $i$ of $A$ and column $j$ of $B$. For example, if row 1 of $A$ is (1, 2) and column 1 of $B$ is (5, 7), then $C(1, 1) = 1 \times 5 + 2 \times 7 = 19$.

With 2D arrays, transpose and addition compute each element once and take $O(mn)$ time each, and multiplication performs $n$ multiplications and additions for each of the $mq$ elements of $C$, so it takes $O(mnq)$ time. The following example implements multiplication with 2D arrays indexed from 0.

```cpp
#include <iostream>

const int M = 2, N = 2, Q = 2;

// c = a * b for an M x N matrix a and an N x Q matrix b (0-based arrays)
void multiply(const int a[M][N], const int b[N][Q], int c[M][Q]) {
    for (int i = 0; i < M; i++)
        for (int j = 0; j < Q; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++)
                sum += a[i][k] * b[k][j];   // row i of a times column j of b
            c[i][j] = sum;
        }
}

int main() {
    int a[M][N] = {{1, 2}, {3, 4}};
    int b[N][Q] = {{5, 6}, {7, 8}};
    int c[M][Q];
    multiply(a, b, c);
    for (int i = 0; i < M; i++)
        std::cout << c[i][0] << " " << c[i][1] << "\n";
}
```

The innermost loop multiplies row $i$ of $A$ by column $j$ of $B$ and sums the products, and the two outer loops fill every element of the result. The output is as follows.

```text
19 22
43 50
```

### 3.3 Shortcomings of a 2D Array for a Matrix

- C++ array indices are 0, 1, ..., n-1, so they are off by 1 from matrix indices, which start at 1.
- C++ arrays do not support matrix operations such as addition, transpose, and multiplication. Even if `x` and `y` are 2D arrays, C++ does not allow `x + y`, `x - y`, or `x * y`.
- Object-oriented support of all matrix operations therefore requires a separate matrix class. Such a class can accept indices starting at 1, convert them to positions in an internal 1D array, and provide `+`, `-`, and `*` through operator overloading.

---

<br>

## 4. Special Matrices

### 4.1 Square Matrices and Kinds of Special Matrices

A **square matrix** has the same number of rows and columns. Commonly used special square matrices are the following ($n \times n$ matrices, indices from 1).

| Kind | Definition | Elements that may be nonzero |
|:-----|:-----|:-----|
| Diagonal matrix | $M(i, j) = 0$ when $i \ne j$ | Elements with $i = j$ |
| Tridiagonal matrix | $M(i, j) = 0$ when $\vert i - j \vert > 1$ | Elements with $\vert i - j \vert \le 1$ |
| Lower triangular matrix | $M(i, j) = 0$ when $i < j$ | Elements with $i \ge j$ |
| Upper triangular matrix | $M(i, j) = 0$ when $i > j$ | Elements with $i \le j$ |
| Symmetric matrix | $M(i, j) = M(j, i)$ for all $i$ and $j$ | All elements |

*Table 3. Definitions of special square matrices*

The figure below gives a $4 \times 4$ example of each kind: (a) is diagonal, (b) tridiagonal, (c) lower triangular, (d) upper triangular, and (e) symmetric. All examples in this section use these matrices.

```text
   (a)          (b)          (c)          (d)          (e)
2 0 0 0      2 1 0 0      2 0 0 0      2 1 3 0      2 4 6 0
0 1 0 0      3 1 3 0      5 1 0 0      0 1 3 8      4 1 9 5
0 0 4 0      0 5 2 7      0 3 1 0      0 0 1 6      6 9 4 7
0 0 0 6      0 0 9 0      4 2 7 0      0 0 0 0      0 5 7 0
```

*Figure 5. Examples of 4 × 4 special matrices*

These special matrices are of interest because a more efficient implementation can be provided for each kind. Diagonal and tridiagonal matrices can be stored in a representation that is $O(n)$ instead of a 2D array with $O(n^2)$ space complexity, and triangular and symmetric matrices can also cut the storage nearly in half. Careful design of the operations that store and retrieve elements can also reduce time.

### 4.2 Diagonal Matrix

Only elements on the main diagonal may be non-zero: $A[i][j] = 0$ when $i \neq j$.

Storage: Only $n$ elements needed for an $n \times n$ matrix.

$$\text{map}(i) = i \quad \text{(store } A[i][i] \text{ at position } i\text{)}$$

With matrix indices starting at 1, the two ways to represent an $n \times n$ diagonal matrix $D$ compare as follows.

1. The naive way keeps a 2D array `T d[n][n]` and stores $D(i, j)$ in `d[i-1][j-1]`. It requires $n^2 \times \text{sizeof}(T)$ bytes of memory.
2. The better way keeps a 1D array `T d[n]`, reads $D(i, j)$ from `d[i-1]` when $i = j$, and returns 0 when $i \ne j$. It requires only $n \times \text{sizeof}(T)$ bytes of memory.

Written with indices from 0, the second way is the same as $\text{map}(i) = i$ above.

### 4.3 Tridiagonal Matrix

Non-zero elements may occur only on the main diagonal and the two adjacent diagonals. The three diagonals are as follows.

- The main diagonal consists of the elements with $i = j$.
- The diagonal below the main diagonal consists of the elements with $i = j + 1$ (for example, $M(4, 3)$ with $4 = 3 + 1$).
- The diagonal above the main diagonal consists of the elements with $i = j - 1$ (for example, $M(1, 2)$ with $1 = 2 - 1$).

Storage: $3n - 2$ elements for an $n \times n$ matrix.

The main diagonal has $n$ elements and each adjacent diagonal has $n - 1$, so the total is $(n - 1) + n + (n - 1) = 3n - 2$. The matrix can therefore be stored in a 1D array `T t[3n-2]`, which has $3 \times 4 - 2 = 10$ cells when $n = 4$. Mapping the matrix of Figure 5 (b) by row, by column, and by diagonal gives the following.

| Mapping | 1D array `t` |
|:-----|:-----|
| By row | [2, 1, 3, 1, 3, 5, 2, 7, 9, 0] |
| By column | [2, 3, 1, 1, 5, 3, 2, 9, 7, 0] |
| By diagonal (below, main, above) | [3, 5, 9, 2, 1, 2, 0, 1, 3, 7] |

*Table 4. The tridiagonal matrix of Figure 5 (b) mapped in three ways*

The position formulas of the mappings are as follows (elements with $\vert i - j \vert \le 1$, matrix indices from 1, indices of `t` from 0).

- In the mapping by row, row 1 has 2 elements, rows 2 through $i-1$ have 3 each, and the first stored element of row $i$ is in column $i-1$. Simplifying, $T(i, j)$ is in `t[2i + j - 3]`.
- In the mapping by diagonal, an element of the lower diagonal ($i = j + 1$) is in `t[i - 2]`, an element of the main diagonal is in `t[n + i - 2]`, and an element of the upper diagonal ($i = j - 1$) is in `t[2n + i - 2]`.

For example, $T(2, 3) = 3$ is in `t[2 × 2 + 3 - 3] = t[4]` by row and in `t[2 × 4 + 2 - 2] = t[8]` by diagonal, and both positions hold 3 in Table 4.

### 4.4 Triangular Matrices

**Lower triangular**: $A[i][j] = 0$ when $j > i$

**Upper triangular**: $A[i][j] = 0$ when $j < i$

In the figure below, x marks the region that may be nonzero. (a) is a lower triangular matrix, and (b) is an upper triangular matrix.

```text
   (a)             (b)
x 0 0 0 0       x x x x x
x x 0 0 0       0 x x x x
x x x 0 0       0 0 x x x
x x x x 0       0 0 0 x x
x x x x x       0 0 0 0 x
```

*Figure 6. Regions that may be nonzero in lower and upper triangular matrices*

Number of elements: $\frac{n(n+1)}{2}$

The rows of the nonzero region hold 1, 2, ..., $n$ elements ($n$, ..., 1 for an upper triangular matrix), so the region has $1 + 2 + \cdots + n = \sum_{i=1}^{n} i = \frac{n(n+1)}{2}$ elements. Both triangular matrices may therefore be represented using a 1D array `T t[n(n+1)/2]`. Mapping the lower triangular matrix of Figure 5 (c) gives the following.

| Mapping | 1D array `t` |
|:-----|:-----|
| By row | [2, 5, 1, 0, 3, 1, 4, 2, 7, 0] |
| By column | [2, 5, 0, 4, 1, 3, 2, 1, 7, 0] |

*Table 5. The lower triangular matrix of Figure 5 (c) mapped by row and by column*

Mapping: $\text{map}(i,j) = \frac{i(i+1)}{2} + j$ (row-major lower triangular)

This formula uses indices counted from 0. With matrix indices counted from 1, the formula is derived as follows. When a lower triangular matrix is stored by row, rows 1 through $i-1$ hold $1 + 2 + \cdots + (i - 1) = \frac{i(i-1)}{2}$ elements, and $L(i, j)$ is the $j$-th element of row $i$, so its offset within the row is $j - 1$.

$$L(i, j) = \begin{cases} 0 & i < j \\ t\left[\frac{i(i-1)}{2} + j - 1\right] & i \ge j \end{cases}$$

In code this reads as follows.

```cpp
if (i >= j) return t[i * (i - 1) / 2 + j - 1]; else return 0;
```

Substituting indices from 0, $i' = i - 1$ and $j' = j - 1$, for $i$ and $j$ gives $\frac{(i'+1)i'}{2} + j'$, which is the formula above for indices from 0. Retrieving two elements of the matrix of Figure 5 (c) gives the following.

- The element in row 4, column 3, $L(4, 3)$ (C++ index `a[3][2]`), is `t[4 × (4 - 1) / 2 + 3 - 1] = t[12 / 2 + 2] = t[8] = 7`.
- The element in row 3, column 2, $L(3, 2)$ (C++ index `a[2][1]`), is `t[3 × (3 - 1) / 2 + 2 - 1] = t[3 × 2 / 2 + 1] = t[4] = 3`.

An upper triangular matrix stored by column has the same shape as a lower triangular matrix stored by row. Mapping the upper triangular matrix of Figure 5 (d) by column gives [2, 1, 1, 3, 3, 1, 0, 8, 6, 0]. Columns 1 through $j-1$ hold $\frac{j(j-1)}{2}$ elements and the offset within column $j$ is $i - 1$, which gives the following formula.

$$U(i, j) = \begin{cases} 0 & i > j \\ t\left[\frac{j(j-1)}{2} + i - 1\right] & i \le j \end{cases}$$

For example, $U(2, 3)$ is `t[3 × 2 / 2 + 2 - 1] = t[4] = 3`.

### 4.5 Symmetric Matrix

$A[i][j] = A[j][i]$ for all $i, j$. Only need to store the lower (or upper) triangular part: $\frac{n(n+1)}{2}$ elements.

An $n \times n$ symmetric matrix can be represented using a 1D array of size $n(n+1)/2$ by storing either the lower or the upper triangle, using one of the triangular matrix methods of Section 4.4. The elements that are not stored are computed from those that are stored. If the lower triangle is stored by row, $M(i, j)$ with $i \ge j$ is read from `t[i(i-1)/2 + j - 1]`, and $M(i, j)$ with $i < j$ equals $M(j, i)$ and is read from `t[j(j-1)/2 + i - 1]`. For example, storing the lower triangle of the matrix of Figure 5 (e) by row gives [2, 4, 1, 6, 9, 4, 0, 5, 7, 0], and the unstored $M(1, 3)$ is found as $M(3, 1)$ = `t[3 + 0] = t[3] = 6`.

---

<br>

## 5. Sparse Matrices

### 5.1 Definition

A **sparse matrix** is a matrix most of whose elements are zero, and a matrix that is not sparse is a **dense matrix**. The boundary between the two is not precisely defined. Typically an $n \times n$ matrix is considered sparse if the number of non-zero elements is $O(n)$ or $O(n \log n)$ rather than $O(n^2)$.

By this criterion, diagonal matrices (at most $n$ non-zero elements) and tridiagonal matrices (at most $3n - 2$) are sparse, and triangular matrices, which may have up to $n(n+1)/2$ non-zero elements, more than half of all elements, are classified as dense. A sparse matrix can be represented with an array (Section 5.2) or a linked list (Section 6).

### 5.2 Array of Triples Representation

Store each non-zero element as a triple $(i, j, \text{value})$:

```cpp
struct MatrixTerm {
    int row;
    int col;
    int value;
};
```

The non-zero elements are mapped into a 1D array in row-major order. The values alone cannot reconstruct the matrix structure, so the row and column each element comes from are recorded as well. For example, the following $4 \times 8$ matrix has 9 non-zero elements.

```text
0 0 0 2 0 0 1 0
0 6 0 0 7 0 0 3
0 0 0 9 0 8 0 0
0 4 5 0 0 0 0 0
```

*Figure 7. A 4 × 8 sparse matrix with 9 non-zero elements*

Representing this matrix as an array of triples `a[]` in row-major order gives the following (row and column numbers from 1).

| Cell of `a[]` | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|:-----|:--|:--|:--|:--|:--|:--|:--|:--|:--|
| `row` | 1 | 1 | 2 | 2 | 2 | 3 | 3 | 4 | 4 |
| `col` | 4 | 7 | 2 | 5 | 8 | 4 | 6 | 2 | 3 |
| `value` | 2 | 1 | 6 | 7 | 3 | 9 | 8 | 4 | 5 |

*Table 6. Row-major array of triples representing the sparse matrix of Figure 7*

For a matrix with $t$ non-zero elements:
- Space is $O(t)$ instead of $O(m \times n)$.
- Finding an element takes $O(t)$ time with a linear scan. If the terms are sorted in row-major order, binary search on (`row`, `col`) reduces this to $O(\log t)$.

### 5.3 Transpose of Sparse Matrix

For triples representation, transpose by swapping row and column indices, then sorting by new row order. The transpose must also be in row-major order, so the terms of the original matrix must be rearranged in column order.

- **Simple approach:** For each column from 1 to $n$ in turn, scan all $t$ terms and move the terms in that column as (`col`, `row`, `value`). The time is $O(t \cdot n)$ (where $t$ = number of terms, $n$ = number of columns).
- **Fast transpose:** Transpose in $O(t + n)$ using column count arrays.

Fast transpose uses two auxiliary arrays. `rowSize[j]` is the number of terms in column $j$ of the original matrix, which becomes the number of terms in row $j$ of the transpose. `rowStart[j]` is the cell of the result array where row $j$ of the transpose starts. The algorithm consists of the following three steps.

1. Scan the $t$ terms once, counting the terms in each column to fill `rowSize`.
2. Scan the $n$ columns once, computing `rowStart` by prefix sums: `rowStart[1] = 0` and `rowStart[j] = rowStart[j-1] + rowSize[j-1]`.
3. Scan the $t$ terms again, putting each term (`row`, `col`, `value`) as (`col`, `row`, `value`) into cell `rowStart[col]` of the result and incrementing `rowStart[col]` by 1.

For the matrix of Figure 7, steps 1 and 2 give the following.

| Original column $j$ (row of the transpose) | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|:-----|:--|:--|:--|:--|:--|:--|:--|:--|
| `rowSize[j]` | 0 | 2 | 1 | 2 | 1 | 1 | 1 | 1 |
| `rowStart[j]` | 0 | 0 | 2 | 3 | 5 | 6 | 7 | 8 |

*Table 7. rowSize and rowStart computed in the fast transpose of the matrix of Figure 7*

The following code implements the three steps and transposes the matrix of Figure 7.

```cpp
#include <iostream>
#include <vector>

struct MatrixTerm {
    int row;
    int col;
    int value;
};

// a: terms of a rows x cols matrix in row-major order (1-based indices)
// returns the terms of the transpose in row-major order
std::vector<MatrixTerm> fastTranspose(const std::vector<MatrixTerm>& a, int cols) {
    std::vector<int> rowSize(cols + 1, 0);   // rowSize[j]: terms in column j of a
    std::vector<int> rowStart(cols + 1, 0);  // rowStart[j]: first slot of row j in b
    std::vector<MatrixTerm> b(a.size());

    for (const MatrixTerm& t : a)            // pass 1 over the terms: count
        rowSize[t.col]++;
    rowStart[1] = 0;
    for (int j = 2; j <= cols; j++)          // pass over the columns: prefix sums
        rowStart[j] = rowStart[j - 1] + rowSize[j - 1];
    for (const MatrixTerm& t : a) {          // pass 2 over the terms: place
        int k = rowStart[t.col]++;
        b[k] = {t.col, t.row, t.value};
    }
    return b;
}

int main() {
    std::vector<MatrixTerm> a = {
        {1, 4, 2}, {1, 7, 1}, {2, 2, 6}, {2, 5, 7}, {2, 8, 3},
        {3, 4, 9}, {3, 6, 8}, {4, 2, 4}, {4, 3, 5}};
    for (const MatrixTerm& t : fastTranspose(a, 8))
        std::cout << "(" << t.row << ", " << t.col << ", " << t.value << ") ";
    std::cout << "\n";
}
```

The output is as follows, with the terms of the transpose in row-major order.

```text
(2, 2, 6) (2, 4, 4) (3, 4, 5) (4, 1, 2) (4, 3, 9) (5, 2, 7) (6, 3, 8) (7, 1, 1) (8, 2, 3)
```

The term array is scanned twice ($O(t)$) and the array of column size once ($O(n)$), so the total time is $O(t + n)$.

---

<br>

## 6. Linked Representation of Sparse Matrices

A shortcoming of the 1D array representation of a sparse matrix is that the number of non-zero terms of the sparse matrix must be known when the array is created. When the number of terms in the result cannot be known in advance, as in the sum of two matrices, the array must be allocated generously or reallocated. A linked representation overcomes this shortcoming.

### 6.1 Row Chain Representation

Each row keeps a chain that links its non-zero terms in column order. Each node of a chain stores (`col`, `value`, `link`). Each row that has non-zero terms gets a header node, which stores the row number, a pointer to the first node of that row's chain, and a pointer to the next header node. The header nodes also form a chain in row order, and `first` points to the first header node.

```text
first
  |
  v
[1|*]--->[4|2|*]--->[7|1|0]
  |
  v
[2|*]--->[2|6|*]--->[5|7|*]--->[8|3|0]
  |
  v
[3|*]--->[4|9|*]--->[6|8|0]
  |
  v
[4|*]--->[2|4|*]--->[3|5|0]
```

*Figure 8. Row chain structure representing the sparse matrix of Figure 7*

In the figure, the left column holds the header nodes [row number|pointer to the row chain], and the downward arrows are the links to the next header node. The nodes on the right are [`col`|`value`|`link`], and 0 means a null pointer. The header node of row 4 is the last header, so its link to the next header is null.

### 6.2 Orthogonal List

Each non-zero element is a node with:
- `row`, `col`, `value`
- `nextInRow` (pointer to next non-zero in same row)
- `nextInCol` (pointer to next non-zero in same column)

Plus arrays of row and column head pointers.

The row chain representation of Section 6.1 can be followed only along rows, but an orthogonal list can also follow the elements of the same column in turn. It therefore suits operations that traverse columns, such as transpose and multiplication.

### 6.3 Advantages

- Non-zero elements can be inserted and deleted efficiently. Unlike the array representation, no other terms need to be moved.
- It is a natural representation for operations like addition. The number of non-zero terms need not be known in advance, so it suits operations whose number of result terms is unknown.

---

<br>

## 7. Matrix Operations

This section shows how to perform the matrix operations of Section 3 on sparse matrix representations.

### 7.1 Sparse Matrix Addition

For two sparse matrices in triple form:
- Merge the sorted triple lists.
- Handle overlapping positions by adding values.

Time complexity: $O(t_1 + t_2)$

Concretely, keep the term arrays of the two matrices, which must have the same dimensions, sorted in row-major order, and compare the positions (`row`, `col`) of the two current terms from the front. Copy the term whose position comes first into the result and move to the next term of that array. If the positions are equal, add the two values, and if the sum is 0, do not put it in the result. Storing a 0 would break the principle that the representation stores only non-zero elements. Each term is examined only once, so with $t_1$ and $t_2$ terms in the two matrices the time is $O(t_1 + t_2)$.

For example, if the terms of $A$ are (1, 2, 3), (2, 1, 4) and the terms of $B$ are (1, 2, -3), (2, 3, 5), the sum at position (1, 2) is $3 + (-3) = 0$ and is dropped, so the result is (2, 1, 4), (2, 3, 5).

### 7.2 Sparse Matrix Multiplication

Time complexity depends on the representation but generally more efficient than dense multiplication when matrices are sufficiently sparse.

Computing $C(i, j)$ only requires multiplying the terms in row $i$ of $A$ and column $j$ of $B$ whose column number in $A$ equals the row number in $B$. An array of triples is easy to read in turn only row by row, so a common method transposes $B$ first and reads the columns of $B$ as rows.

---

<br>

## 8. Appendix

### 8.1 When to Use Sparse Representation

Use sparse representation when the density $d = \frac{\text{non-zeros}}{m \times n}$ is below approximately 0.3 (30%). Above this threshold, the overhead of the sparse structure may exceed the savings.

This criterion is an approximate value from the break-even point $3t = mn$, that is, $d = 1/3$, when each integer element is stored as a triple of three integers. The actual threshold depends on the sizes of elements and indices and on the pointer overhead of a linked representation.

### 8.2 Applications of Sparse Matrices

- The matrices of the systems of equations in finite element analysis are sparse because only adjacent elements have non-zero entries between them.
- Network adjacency matrices (social graphs, web link graphs) are mostly zero because they have far fewer edges than the number of vertices allows.
- Term-document matrices in natural language processing are mostly zero because each document contains only part of the whole vocabulary.
- In scientific computing, discretizing partial differential equations (PDEs) yields sparse matrices in which each grid point is connected only to its neighbors.

---

<br>

## Summary

| Concept | Key Summary |
|---------|-------------|
| Array-of-arrays representation | Each row is a separate 1D array linked from a row pointer array, and the space overhead is (number of rows) × 4 bytes. |
| Row-major order | Rows are stored contiguously, which is the C/C++ default, and with $n$ columns `A[i][j]` is at position $i \cdot n + j$ counted from 0. |
| Column-major order | Columns are stored contiguously, as in Fortran and MATLAB. |
| Matrix operations | Addition is defined only for the same dimensions, and multiplication only when the columns of the first matrix match the rows of the second. |
| Diagonal matrix | Only $n$ elements are stored. |
| Tridiagonal matrix | Only the $3n - 2$ elements on the three diagonals are stored. |
| Triangular matrix | $n(n+1)/2$ elements are stored, and when a lower triangular matrix is stored by row, $L(i, j)$ is in `t[i(i-1)/2 + j - 1]`. |
| Symmetric matrix | Only one triangle is stored, and the other elements are found from $M(i, j) = M(j, i)$. |
| Sparse matrix | Only non-zero elements are stored, which saves space when most are zero. |
| Triples representation | Non-zero elements are stored as $(row, col, value)$ tuples in row-major order. |
| Fast transpose | The transpose is computed in $O(t + n)$ time using auxiliary arrays. |
| Linked representation | The number of non-zero terms need not be known in advance, and terms are easy to insert and delete. |

---

<br>

## Self-Check Questions

1. **Column-major mapping:** When `int a[3][6]` is mapped in column-major order, find the 1D position (counted from 0) of `a[1][4]`. If the start address is 2000 and an `int` takes 4 bytes, what is the address of this element?

   <details>
   <summary>Answer</summary>

   The column-major mapping function is $\text{map}(i_1, i_2) = i_2 u_1 + i_1$ with $u_1 = 3$ rows, so the position is $4 \times 3 + 1 = 13$. The $4 \times 3 = 12$ elements of columns 0 through 3 come first, and within column 4 one more element, `a[0][4]`, comes before it. The address is $2000 + 13 \times 4 = 2052$.

   </details>

2. **Space overhead:** With 4-byte pointers and `int`, find the space overhead and the total memory needed to store `int x[5][10]` in the array-of-arrays representation and in row-major mapping.

   <details>
   <summary>Answer</summary>

   The elements need $5 \times 10 \times 4 = 200$ bytes. The overhead of the array-of-arrays representation is the 5 row pointers, $5 \times 4 = 20$ bytes, so the total is 220 bytes. The overhead of row-major mapping is the 8 bytes that store `start` and the number of columns, so the total is 208 bytes. The overhead of row-major mapping stays constant regardless of the number of rows.

   </details>

3. **Tridiagonal matrix:** When a $5 \times 5$ tridiagonal matrix is stored by row, find the size of the 1D array and the cell (counted from 0) where $T(4, 5)$ is stored.

   <details>
   <summary>Answer</summary>

   The size is $3n - 2 = 3 \times 5 - 2 = 13$. Substituting $i = 4$ and $j = 5$ in the row-major position formula $2i + j - 3$ gives $8 + 5 - 3 = 10$, so it is stored in `t[10]`. Counting directly, row 1 has 2 elements (cells 0, 1), rows 2 and 3 have 3 each (cells 2-7), and $T(4, 3)$, $T(4, 4)$, $T(4, 5)$ of row 4 occupy cells 8, 9, 10.

   </details>

4. **Zeros in sparse matrix addition:** When adding two sparse matrices represented as arrays of triples, how should a sum of 0 at a shared position be handled, and why?

   <details>
   <summary>Answer</summary>

   The term is not put in the result. The triples representation saves space on the premise that it stores only non-zero elements, and the time of later operations depends on the number of terms $t$. Storing a term whose sum is 0 wastes space and makes the number of terms larger than necessary, which also slows later operations such as transpose and addition.

   </details>

5. **Row-major mapping of an upper triangular matrix:** When an $n \times n$ upper triangular matrix is stored by row, derive the formula for the cell (counted from 0) that stores $U(i, j)$ ($i \le j$, indices from 1), and find the cell and value of $U(2, 4)$ for the matrix of Figure 5 (d).

   <details>
   <summary>Answer</summary>

   Row $k$ of an upper triangular matrix has $n - k + 1$ elements, so rows 1 through $i-1$ hold $n + (n - 1) + \cdots + (n - i + 2) = \frac{(i-1)(2n-i+2)}{2}$ elements. The first stored element of row $i$ is in column $i$, so the offset within the row is $j - i$ and the cell is $\frac{(i-1)(2n-i+2)}{2} + (j - i)$. With $n = 4$, $i = 2$, $j = 4$ this is $\frac{1 \times 8}{2} + 2 = 6$. Storing Figure 5 (d) by row gives [2, 1, 3, 0, 1, 3, 8, 1, 6, 0], so `t[6] = 8`.

   </details>
