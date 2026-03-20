# Chapter 03 — Quiz

> **Last Updated:** 2026-03-21

---

## Q1. Array Insert Complexity

**Question:** What is the time complexity of inserting an element at position 0 of an array-based list with $n$ elements? Explain why.

**Answer:** $O(n)$.

**Explanation:** Inserting at position 0 requires shifting all $n$ existing elements one position to the right to make room for the new element. Each shift is an $O(1)$ operation, and there are $n$ shifts, so the total is $O(n)$.

---

## Q2. Linked List Advantages

**Question:** Give two advantages and two disadvantages of a singly linked list compared to an array.

**Answer:**
- Advantages: (1) Dynamic size -- no need to pre-allocate a fixed capacity. (2) $O(1)$ insertion/deletion at the front without shifting.
- Disadvantages: (1) No random access -- accessing the $i$-th element requires $O(n)$ traversal. (2) Extra memory for storing next pointers.

**Explanation:** The choice between array and linked list depends on the dominant operations. If frequent random access is needed, arrays are better. If frequent insertions/deletions at arbitrary positions are needed, linked lists may be preferable.

---

## Q3. Doubly Linked List Deletion

**Question:** Why can a doubly linked list delete a known node in $O(1)$, while a singly linked list requires $O(n)$?

**Answer:** In a doubly linked list, each node has a `prev` pointer, so we can directly access the predecessor to update its `next` pointer. In a singly linked list, we must traverse from the head to find the predecessor, which takes $O(n)$.

**Explanation:** Deletion requires updating the predecessor's `next` pointer to bypass the deleted node. With a `prev` pointer, this is immediate. Without it, a linear scan is needed.

---

## Q4. Circular Linked List

**Question:** In a circular singly linked list, how do you detect that you have traversed all nodes?

**Answer:** Start from any node and continue traversing until you reach the starting node again.

**Explanation:** Since the last node's `next` points back to the first node, the traversal forms a cycle. By comparing the current node with the starting node, we can detect when a full traversal is complete: `do { ... curr = curr->next; } while (curr != start);`

---

## Q5. Dynamic Array Amortized Cost

**Question:** Explain why the amortized cost of inserting at the end of a dynamic array (which doubles in size when full) is $O(1)$.

**Answer:** When the array is full, we allocate a new array of double the size and copy all $n$ elements, costing $O(n)$. However, this doubling happens only after $n$ insertions. The total cost of $n$ insertions is $n + n/2 + n/4 + \cdots + 1 \leq 2n = O(n)$. Thus the amortized cost per insertion is $O(n)/n = O(1)$.

**Explanation:** Using the aggregate method, the sum of copy costs over all doublings forms a geometric series that converges to $2n$, making the average cost per operation constant.
