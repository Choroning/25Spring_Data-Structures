# Chapter 05 — Stacks

> **Last Updated:** 2026-03-21

---

## Table of Contents

1. [Stack ADT](#1-stack-adt)
2. [Array-Based Stack](#2-array-based-stack)
3. [Linked Stack](#3-linked-stack)
4. [Applications of Stacks](#4-applications-of-stacks)
5. [Expression Evaluation](#5-expression-evaluation)
6. [Summary](#summary)
7. [Appendix](#appendix)

---

## 1. Stack ADT

### 1.1 Definition

A **stack** is a linear list where insertions and deletions are made at one end called the **top**.

- **LIFO** (Last In, First Out) principle
- Also known as a pushdown list

### 1.2 Core Operations

| Operation | Description | Complexity |
|-----------|-------------|------------|
| `push(x)` | Insert element $x$ at the top | $O(1)$ |
| `pop()` | Remove and return the top element | $O(1)$ |
| `top()` | Return the top element without removing | $O(1)$ |
| `empty()` | Check if the stack is empty | $O(1)$ |
| `size()` | Return the number of elements | $O(1)$ |

> **Key Point:** All stack operations are $O(1)$ — this is what makes stacks efficient.

---

## 2. Array-Based Stack

### 2.1 Implementation

Use an array with a variable `topIndex` tracking the top:
- `topIndex = -1` means the stack is empty
- `push(x)`: increment `topIndex`, store at `array[topIndex]`
- `pop()`: return `array[topIndex]`, decrement `topIndex`

### 2.2 Dynamic Resizing

When the array is full, double its size (amortized $O(1)$ push).

### 2.3 Advantages/Disadvantages

- **Advantage**: Cache-friendly, simple implementation
- **Disadvantage**: May waste space if capacity is much larger than actual size

---

## 3. Linked Stack

### 3.1 Implementation

Use a singly linked list where the top of the stack is the head:
- `push(x)`: insert new node at head — $O(1)$
- `pop()`: remove head node — $O(1)$

### 3.2 Advantages/Disadvantages

- **Advantage**: No wasted space, truly dynamic
- **Disadvantage**: Extra pointer overhead per element, poor cache locality

---

## 4. Applications of Stacks

### 4.1 Parentheses Matching

Check if brackets `()`, `[]`, `{}` are properly nested:

```cpp
bool isBalanced(const std::string& expr) {
    std::stack<char> s;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') s.push(c);
        else if (c == ')' || c == ']' || c == '}') {
            if (s.empty()) return false;
            char top = s.top(); s.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{'))
                return false;
        }
    }
    return s.empty();
}
```

### 4.2 Function Call Stack

The runtime system uses a stack to manage function calls:
- Push activation record on call
- Pop on return
- Supports recursion naturally

### 4.3 Undo Operations

Text editors, browsers, and many applications use stacks for undo functionality.

### 4.4 Tower of Hanoi

Classic recursive problem solved elegantly with stacks:

$$T(n) = 2T(n-1) + 1 = 2^n - 1 \text{ moves}$$

---

## 5. Expression Evaluation

### 5.1 Infix, Prefix, and Postfix

| Type | Example | Description |
|------|---------|-------------|
| Infix | `A + B * C` | Operators between operands |
| Prefix (Polish) | `+ A * B C` | Operators before operands |
| Postfix (Reverse Polish) | `A B C * +` | Operators after operands |

### 5.2 Infix to Postfix Conversion

Algorithm using a stack for operators:

1. Scan left to right
2. If operand, output it
3. If `(`, push onto stack
4. If `)`, pop and output until `(` is found
5. If operator, pop and output operators with higher or equal precedence, then push

### 5.3 Postfix Evaluation

1. Scan left to right
2. If operand, push onto stack
3. If operator, pop two operands, apply operator, push result

---

## Summary

| Concept | Key Point |
|---------|-----------|
| Stack | LIFO data structure; all ops $O(1)$ |
| Array-based | Uses `topIndex`; may need resizing |
| Linked | Uses linked list head as top; no capacity limit |
| Parentheses matching | Push opening, pop on closing |
| Expression evaluation | Convert infix to postfix, then evaluate |
| Recursion | Function call stack is implicitly a stack |

---

## Appendix

### Stack vs. Queue

| Feature | Stack | Queue |
|---------|-------|-------|
| Order | LIFO | FIFO |
| Insert | push (top) | enqueue (rear) |
| Remove | pop (top) | dequeue (front) |
| Use case | Undo, recursion, DFS | Scheduling, BFS |

### Common Interview Problems

1. **Min Stack**: Design a stack that supports `getMin()` in $O(1)$
2. **Evaluate Reverse Polish Notation**
3. **Valid Parentheses** (LeetCode #20)
4. **Daily Temperatures** (monotonic stack)
