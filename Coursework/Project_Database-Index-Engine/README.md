# Term Project — Database Index Engine (B+ Tree)

[Repository Guide](../../README.md) | [English](README.md) | [한국어](README.ko.md)

> **Last Updated:** 2026-10-26

---

## Overview

This term project implements a B+ tree index engine in C++. The B+ tree is the standard data structure used in relational databases (MySQL InnoDB, PostgreSQL, SQLite) for indexing because it minimizes disk I/O by maximizing the branching factor and keeping all data in leaf nodes linked for sequential access.

## Features

In the bounds below, $n$ is the number of keys and $M$ is the order of the tree (the template parameter `ORDER`): an internal node has at most $M$ children and $M-1$ keys.

- **Point query:** Search for a single key in $O(\log_M n)$.
- **Range query:** Retrieve all keys in $[low, high]$ in $O(\log_M n + k)$ via the leaf linked list, where $k$ is the number of keys returned.
- **Insert:** Insert a key-value pair with automatic node splitting in $O(\log_M n)$.
- **Delete:** Remove a key with underflow handling in $O(\log_M n)$.
- **Configurable order:** A template parameter allows tuning the branching factor.

## File Structure

| File | Description |
|:-----|:------------|
| `BPlusTree.h` | B+ tree class declaration (template, order-parameterized) |
| `BPlusTree.cpp` | B+ tree implementation (insert, delete, search, range query) |
| `main.cpp` | Demo driver with basic operations and performance benchmarks |

## Build and Run

```bash
g++ -std=c++17 -O2 -o index_engine BPlusTree.cpp main.cpp
./index_engine
```

## Design Decisions

1. **Template order parameter:** It allows compile-time tuning of the branching factor.
2. **Leaf linked list:** It supports efficient range queries and sequential scans.
3. **Copy-up for leaf splits:** The first key of the new leaf is copied up to the parent.
4. **Push-up for internal splits:** The middle key is pushed up to the parent.

## Complexity

| Operation | Time | Notes |
|:----------|:-----|:------|
| Search | $O(\log_M n)$ | Single key lookup |
| Insert | $O(\log_M n)$ | With potential splits |
| Delete | $O(\log_M n)$ | With potential merges |
| Range query | $O(\log_M n + k)$ | $k$ = number of results |

## References

- **CMU 15-445: Database Systems.** Andy Pavlo's course on B+ tree implementation and buffer pool management (https://15445.courses.cs.cmu.edu/)
- **Stanford CS245: Principles of Data-Intensive Systems.** B+ tree indexing in the context of modern database engines (https://cs245.stanford.edu/)
- Sahni, S. *Data Structures, Algorithms, and Applications in C++*, Chapters 10-11
