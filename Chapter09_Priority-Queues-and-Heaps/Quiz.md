# Chapter 09 — Quiz

> **Last Updated:** 2026-03-21

---

## Q1. Max Heap Insert Trace

**Question:** Given a max heap `[-, 20, 15, 7, 6, 9, 2, 6, 5, 1]`, insert the element 25. Show the heap after insertion.

**Answer:** Place 25 at position 10: `[-, 20, 15, 7, 6, 9, 2, 6, 5, 1, 25]`. Bubble up: 25 > parent 9 (pos 5) -> swap. 25 > parent 15 (pos 2) -> swap. 25 > parent 20 (pos 1) -> swap. Final: `[-, 25, 20, 7, 6, 15, 2, 6, 5, 1, 9]`.

**Explanation:** Heap insert places the new element at the end (next available position in the complete binary tree) and bubbles it up by repeatedly comparing with its parent and swapping if larger. Time: $O(\log n) = O(\log 10) = O(4)$.

---

## Q2. Max Heap Delete Trace

**Question:** Given a max heap `[-, 20, 15, 7, 6, 9, 2, 6, 5, 1, 8]`, perform deleteMax. Show the heap after deletion.

**Answer:** Remove root 20. Last element is 8 (pos 10). Place 8 at root. Trickle down: compare children 15 and 7, pick 15. 8 < 15 -> swap. Compare children 6 and 9, pick 9. 8 < 9 -> swap. 8 has child at pos 10 (previously removed, heapSize is now 9). Final: `[-, 15, 9, 7, 6, 8, 2, 6, 5, 1]`.

**Explanation:** DeleteMax removes the root, replaces it with the last element, and trickles it down. At each level, the element is compared with the larger child and swapped if smaller. Time: $O(\log n)$.

---

## Q3. Heap Initialization

**Question:** Build a max heap from the array `[-, 3, 1, 6, 5, 2, 4]` using the bottom-up initialization algorithm. Show each step.

**Answer:** $n = 6$, start at $\lfloor 6/2 \rfloor = 3$.
- Position 3 (value 6): children are at 6 (value 4). 6 > 4, no swap. Array: `[-, 3, 1, 6, 5, 2, 4]`.
- Position 2 (value 1): children are 5 (pos 4) and 2 (pos 5). Larger child = 5. 1 < 5, swap. Array: `[-, 3, 5, 6, 1, 2, 4]`.
- Position 1 (value 3): children are 5 (pos 2) and 6 (pos 3). Larger child = 6. 3 < 6, swap. Array: `[-, 6, 5, 3, 1, 2, 4]`. Continue trickle: pos 3, children are empty or value 4. 3 < 4, swap. Final: `[-, 6, 5, 4, 1, 2, 3]`.

**Explanation:** Bottom-up initialization starts at the rightmost internal node and applies trickle-down at each. This is $O(n)$ because most nodes are near the bottom and require few swaps.

---

## Q4. Is This a Heap?

**Question:** Determine whether each of the following is a valid max heap: (a) `[-, 14, 12, 7, 10, 8, 6]` (b) `[-, 9, 6, 5]` with 6 having only a right child (c) `[-, 30, 25]` with 25 as left child only.

**Answer:** (a) Yes — complete binary tree and every parent >= children. (b) No — not a complete binary tree (6 should have a left child before a right child). (c) Yes — complete binary tree (with 2 nodes, node 2 is left child) and 30 >= 25.

**Explanation:** A max heap requires two properties: (1) it is a complete binary tree (all levels full except possibly the last, filled from left), and (2) every node's value >= its children's values. Both conditions must hold.

---

## Q5. Leftist Tree Merge

**Question:** Explain why leftist trees are preferred over heaps when frequent merge operations are needed. What is the time complexity of merging two leftist trees of sizes $m$ and $n$?

**Answer:** Merging two heaps requires $O((m+n) \log(m+n))$: essentially dump both arrays together and re-heapify, or insert elements from one heap into the other. Leftist tree merge follows only the right paths of both trees, which have length at most $\lfloor \log_2(n+1) \rfloor$, giving $O(\log m + \log n)$ time.

**Explanation:** The leftist property ($s(\text{left}) \geq s(\text{right})$) ensures the right path is short. Since merge only traverses right paths and then adjusts by swapping children, the total work is proportional to the sum of right path lengths, which is logarithmic in the tree sizes.
