# Lecture 5 Solutions — Stacks

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-18

---

<br>

## Table of Contents

- [Exercise 1: Stack Operations Trace](#exercise-1-stack-operations-trace)
- [Exercise 2: Infix to Postfix](#exercise-2-infix-to-postfix)
- [Exercise 3: Postfix Evaluation](#exercise-3-postfix-evaluation)
- [Exercise 4: Parentheses Matching](#exercise-4-parentheses-matching)
- [Exercise 5: Array vs. Linked Stack](#exercise-5-array-vs-linked-stack)

---

<br>

## Exercise 1: Stack Operations Trace

**Problem:** Given an initially empty stack, trace the state after the following operations: `push(5)`, `push(3)`, `pop()`, `push(7)`, `push(2)`, `pop()`, `push(8)`. What is the top element?

### Solution

**Answer:** The top element is 8. The stack from bottom to top is [5, 7, 8].

**Explanation:** After `push(5)`: [5]. After `push(3)`: [5, 3]. After `pop()`: [5] (3 removed). After `push(7)`: [5, 7]. After `push(2)`: [5, 7, 2]. After `pop()`: [5, 7] (2 removed). After `push(8)`: [5, 7, 8].

---

<br>

## Exercise 2: Infix to Postfix

**Problem:** Convert the infix expression `A + B * C - D / E` to postfix notation.

### Solution

**Answer:** `A B C * + D E / -`

**Explanation:** Following operator precedence (`*` and `/` before `+` and `-`), first `B * C` becomes `B C *`. Then `A + (B C *)` becomes `A B C * +`. Then `D / E` becomes `D E /`. Finally, `(A B C * +) - (D E /)` becomes `A B C * + D E / -`. Since `+` and `-` are left-associative operators of equal precedence, the addition on the left is computed first.

---

<br>

## Exercise 3: Postfix Evaluation

**Problem:** Evaluate the postfix expression `6 2 3 + - 3 8 2 / + * 2 ^ 3 +`.

### Solution

**Answer:** 52.

**Explanation:** Step by step: `2 3 +` = 5; `6 5 -` = 1; `8 2 /` = 4; `3 4 +` = 7; `1 7 *` = 7; `7 2 ^` = 49; `49 3 +` = 52. Here `^` is exponentiation, and each operator uses the value popped first from the stack as its right operand.

---

<br>

## Exercise 4: Parentheses Matching

**Problem:** Determine if the following expressions have balanced parentheses: (a) `{[()]}` (b) `{[(])}` (c) `((()))`

### Solution

**Answer:** (a) is balanced. (b) is not balanced. (c) is balanced.

**Explanation:** (a) Each closing bracket matches the most recent unmatched opening bracket of the same type. (b) `]` encounters `(` on the stack instead of `[`, which is a mismatch. (c) All parentheses match correctly.

---

<br>

## Exercise 5: Array vs. Linked Stack

**Problem:** Compare array-based and linked stacks in terms of memory usage for a stack that fluctuates between 10 and 1000 elements.

### Solution

**Answer:** A linked stack uses memory proportional to the current number of elements plus pointer overhead. An array-based stack may keep capacity for 1000+ elements even when only 10 are present. For fluctuating sizes, the linked stack wastes less total memory, though each element uses more memory due to the pointer.

**Explanation:** If the stack grows to 1000 and then shrinks to 10, the array-based stack still holds memory for 1000 (or 1024 after doubling). The linked stack releases nodes as they are popped. However, each linked node uses extra bytes for the pointer (8 bytes on 64-bit systems).
