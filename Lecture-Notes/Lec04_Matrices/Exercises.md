# Lecture 4 Exercises — Matrices

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Exercise 1: Row-Major Address Calculation

**Problem:** Given a 2D array `A[5][8]` stored in row-major order with base address 1000 and each element occupying 4 bytes, find the address of `A[3][5]`.

**[Solution](Solutions.md#exercise-1-row-major-address-calculation)**

---

<br>

## Exercise 2: Sparse Matrix Representation

**Problem:** A $100 \times 100$ matrix has only 50 non-zero elements. Compare the storage required for dense vs. sparse (triples) representation, assuming each integer takes 4 bytes.

**[Solution](Solutions.md#exercise-2-sparse-matrix-representation)**

---

<br>

## Exercise 3: Lower Triangular Mapping

**Problem:** For a lower triangular matrix of size $5 \times 5$, stored in row-major order in a 1D array, what is the index in the 1D array for element $A[3][1]$ (0-indexed)?

**[Solution](Solutions.md#exercise-3-lower-triangular-mapping)**

---

<br>

## Exercise 4: Fast Transpose Complexity

**Problem:** Explain the fast transpose algorithm for a sparse matrix in triples format and its time complexity.

**[Solution](Solutions.md#exercise-4-fast-transpose-complexity)**

---

<br>

## Exercise 5: Symmetric Matrix Storage

**Problem:** How many elements need to be stored for a symmetric matrix of size $n \times n$? Write the mapping function for element $A[i][j]$ where $i \geq j$.

**[Solution](Solutions.md#exercise-5-symmetric-matrix-storage)**
