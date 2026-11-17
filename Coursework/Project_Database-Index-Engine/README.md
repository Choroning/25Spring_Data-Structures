# Term Project — Database Index Engine (B+ Tree)

[Repository Guide](../../README.md) | [English](README.md) | [한국어](README.ko.md)

> **Last Updated:** 2026-11-18

---

## Overview

This term project implements a B+ tree index engine in C++. The B+ tree is the standard data structure used in relational databases (MySQL InnoDB, PostgreSQL, SQLite) for indexing because it minimizes disk I/O by maximizing the branching factor and keeping all data in leaf nodes linked for sequential access.

## Features

In the bounds below, $n$ is the number of keys and $M$ is the order of the tree (the template parameter `ORDER`): an internal node has at most $M$ children and $M-1$ keys.

- **Point query:** Search for a single key in $O(\log_M n)$.
- **Range query:** Retrieve all keys in $[low, high]$ in $O(\log_M n + k)$ via the leaf linked list, where $k$ is the number of keys returned.
- **Insert:** Insert a key-value pair, splitting nodes automatically when they overflow. The target leaf is found in $O(\log_M n)$, but a split looks up the parent node by traversing the whole tree from the root, so an insertion that causes a split takes $O(n)$ time.
- **Delete:** Remove a key from its leaf in $O(\log_M n)$. Nodes that underflow are neither redistributed nor merged.
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
| Insert | $O(\log_M n)$ without a split, $O(n)$ with a split | The parent lookup traverses the whole tree |
| Delete | $O(\log_M n)$ | Underflow is not handled |
| Range query | $O(\log_M n + k)$ | $k$ = number of results |

> **Note:** **Differences from a full implementation.** This implementation simplifies two parts to keep the structure intuitive. First, a split finds the parent node by traversing the whole tree from the root. A full implementation records the nodes passed on the way down from the root to the leaf in a stack, or keeps a parent pointer in each node, and obtains the parent in $O(1)$. Then, even when splits propagate from the leaf to the root, only one node is split on each level, so if the cost of processing one node is taken as constant, the whole insertion takes $O(\log_M n)$. Second, it does not handle underflow, in which a node is left with fewer keys than the minimum after a deletion. In a full implementation, every internal node other than the root must have at least $\lceil M/2 \rceil$ children, and every leaf other than the root must have at least $\lceil (M-1)/2 \rceil$ keys. When a node underflows, one key is moved from an adjacent sibling that has more keys than the minimum, and the separator key in the parent is updated (redistribution; for internal nodes, the separator key in the parent moves down and a key of the sibling moves up into its place). If no sibling can lend a key, the node is merged with a sibling, and one separator key and one child pointer are removed from the parent. Merging leaves also fixes the `next` pointers of the leaf linked list, and merging internal nodes moves the separator key of the parent down into the merged node. If the merge makes the parent underflow, the same handling repeats toward the root, and when the root is left with a single child, that child becomes the new root and the height decreases by 1. This handling also processes a constant number of nodes for each node on the path, so deletion remains $O(\log_M n)$. Without it, nodes gradually empty and space utilization drops, and because the height never decreases, $n$ in the time complexities of this implementation must be read as the largest number of keys the tree has ever held, not the current number of keys.

## References

- "Project #1 - Buffer Pool," *CMU 15-445/645: Intro to Database Systems*, Carnegie Mellon University, Fall 2022. https://15445.courses.cs.cmu.edu/fall2022/project1/
- "Project #2 - B+Tree," *CMU 15-445/645: Intro to Database Systems*, Carnegie Mellon University, Fall 2022. https://15445.courses.cs.cmu.edu/fall2022/project2/
- M. Zaharia, "Data Storage & Indexes," lecture slides, *CS 245: Principles of Data-Intensive Systems*, Stanford University, Winter 2021. https://cs245.stanford.edu/slides/05-Storage-Formats-p2.pdf
- S. Sahni, *Data Structures, Algorithms, and Applications in C++*. Boston, MA, USA: WCB/McGraw-Hill, 1998, Sec. 11.4.
