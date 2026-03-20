# Chapter 05 — Quiz

> **Last Updated:** 2026-03-21

---

## Q1. Stack Operations Trace

**Question:** Given an initially empty stack, trace the state after the following operations: `push(5)`, `push(3)`, `pop()`, `push(7)`, `push(2)`, `pop()`, `push(8)`. What is the top element?

**Answer:** The top element is 8. Stack from bottom to top: [5, 7, 8].

**Explanation:** After `push(5)`: [5]. After `push(3)`: [5, 3]. After `pop()`: [5] (3 removed). After `push(7)`: [5, 7]. After `push(2)`: [5, 7, 2]. After `pop()`: [5, 7] (2 removed). After `push(8)`: [5, 7, 8].

---

## Q2. Infix to Postfix

**Question:** Convert the infix expression `A + B * C - D / E` to postfix notation.

**Answer:** `A B C * + D E / -`

**Explanation:** Following operator precedence (* and / before + and -): First, `B * C` becomes `B C *`. Then `A + (B C *)` becomes `A B C * +`. Then `D / E` becomes `D E /`. Finally, `(A B C * +) - (D E /)` becomes `A B C * + D E / -`.

---

## Q3. Postfix Evaluation

**Question:** Evaluate the postfix expression `6 2 3 + - 3 8 2 / + * 2 ^ 3 +`.

**Answer:** 52.

**Explanation:** Step by step: `2 3 +` = 5; `6 5 -` = 1; `8 2 /` = 4; `3 4 +` = 7; `1 7 *` = 7; `7 2 ^` = 49; `49 3 +` = 52.

---

## Q4. Parentheses Matching

**Question:** Determine if the following expressions have balanced parentheses: (a) `{[()]}` (b) `{[(])}` (c) `((()))`

**Answer:** (a) Balanced. (b) Not balanced. (c) Balanced.

**Explanation:** (a) Each closing bracket matches the most recent unmatched opening bracket of the same type. (b) `]` encounters `(` on the stack instead of `[` -- mismatch. (c) All parentheses match correctly.

---

## Q5. Array vs. Linked Stack

**Question:** Compare array-based and linked stacks in terms of memory usage for a stack that fluctuates between 10 and 1000 elements.

**Answer:** A linked stack uses memory proportional to the current number of elements plus pointer overhead. An array-based stack may allocate capacity for 1000+ elements even when only 10 are present. For fluctuating sizes, the linked stack wastes less total memory, though each element uses more memory due to the pointer.

**Explanation:** If the stack grows to 1000 and then shrinks to 10, the array-based stack still holds memory for 1000 (or 1024 after doubling). The linked stack releases nodes as they are popped. However, each linked node uses extra bytes for the pointer (8 bytes on 64-bit systems).
