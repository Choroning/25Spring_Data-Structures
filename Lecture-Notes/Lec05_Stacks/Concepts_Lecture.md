# Lecture 5 — Stacks

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-18

> **Learning Objectives:**
> 1. Define a stack as a restricted linear list and explain its LIFO behavior
> 2. Implement stacks using arrays and linked lists
> 3. Apply stacks to parenthesis matching and expression evaluation
> 4. Solve the Towers of Hanoi recursively and solve the recurrence for its number of moves
> 5. Analyze time complexity of stack operations

---

<br>

## Table of Contents

- [1. Stack ADT](#1-stack-adt)
  - [1.1 Definition](#11-definition)
  - [1.2 Core Operations](#12-core-operations)
  - [1.3 Relation to Linear Lists](#13-relation-to-linear-lists)
- [2. Array-Based Stack](#2-array-based-stack)
  - [2.1 Implementation](#21-implementation)
  - [2.2 Dynamic Resizing](#22-dynamic-resizing)
  - [2.3 Two Stacks in One Array](#23-two-stacks-in-one-array)
  - [2.4 Advantages/Disadvantages](#24-advantagesdisadvantages)
- [3. Linked Stack](#3-linked-stack)
  - [3.1 Which End of the Chain Is the Stack Top](#31-which-end-of-the-chain-is-the-stack-top)
  - [3.2 Implementation](#32-implementation)
  - [3.3 Advantages/Disadvantages](#33-advantagesdisadvantages)
- [4. Applications of Stacks](#4-applications-of-stacks)
  - [4.1 Parentheses Matching](#41-parentheses-matching)
  - [4.2 Function Call Stack](#42-function-call-stack)
  - [4.3 Undo Operations](#43-undo-operations)
  - [4.4 Tower of Hanoi](#44-tower-of-hanoi)
- [5. Expression Evaluation](#5-expression-evaluation)
  - [5.1 Infix, Prefix, and Postfix](#51-infix-prefix-and-postfix)
  - [5.2 Infix to Postfix Conversion](#52-infix-to-postfix-conversion)
  - [5.3 Postfix Evaluation](#53-postfix-evaluation)
- [6. Appendix](#6-appendix)
  - [6.1 Stack vs. Queue](#61-stack-vs-queue)
  - [6.2 Common Interview Problems](#62-common-interview-problems)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Stack ADT

### 1.1 Definition

A **stack** is a linear list where insertions and deletions are made at one end called the **top**. The other end is called the **bottom**.

- It follows the **LIFO** (Last In, First Out) principle, in which the element added last leaves first.
- It is also known as a pushdown list.

A stack of cups or the coins stacked in a taxi driver's coin box are examples of a stack. Cups and coins are added only on top and removed only from the top, so the one added last comes out first.

```text
          +-----+
top --->  |  C  |  <--- push and pop happen here
          +-----+
          |  B  |
          +-----+
bottom -> |  A  |
          +-----+
```

*Figure 1. Top and bottom of a stack after pushing A, B, and C in order*

### 1.2 Core Operations

| Operation | Description | Complexity |
|-----------|-------------|------------|
| `push(x)` | Insert element $x$ at the top | $O(1)$ |
| `pop()` | Remove and return the top element | $O(1)$ |
| `top()` | Return the top element without removing | $O(1)$ |
| `empty()` | Check if the stack is empty | $O(1)$ |
| `size()` | Return the number of elements | $O(1)$ |

*Table 1. Core stack operations and their time complexity*

> **Key Point:** With a fixed-size array or a linked list, all stack operations are $O(1)$, which is what makes stacks efficient. In an implementation that doubles a full array, push is amortized $O(1)$ (Section 2.2).

### 1.3 Relation to Linear Lists

A stack is a restricted version of a linear list (the array list or linked list of Lecture 3), and all stack operations can be performed as linear list operations. If we designate the left end of the list as the stack bottom and the right end as the stack top, the following holds.

- The stack push operation is equivalent to inserting at the right end of the linear list.
- The stack pop operation is equivalent to deleting from the right end of the linear list.

---

<br>

## 2. Array-Based Stack

### 2.1 Implementation

Use an array with a variable `topIndex` tracking the top:
- `topIndex = -1` means the stack is empty.
- `push(x)` increments `topIndex` and stores at `array[topIndex]`.
- `pop()` returns `array[topIndex]` and decrements `topIndex`.

Since a stack is a restricted version of a linear list, the array-based representation of a linear list can be used as it is. With `length` elements, the top of the stack is `element[length-1]` and the bottom is `element[0]`, so `topIndex = length - 1`. The following implementation includes the resizing of Section 2.2.

```cpp
#include <iostream>
#include <stdexcept>

template <class T>
class ArrayStack {
    T* stack;          // element array; stack[0] is the bottom
    int capacity;      // array length
    int topIndex;      // index of the top element, -1 when empty
public:
    ArrayStack(int initialCapacity = 4)
        : stack(new T[initialCapacity]), capacity(initialCapacity), topIndex(-1) {}
    ~ArrayStack() { delete[] stack; }

    bool empty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }

    void push(const T& x) {
        if (topIndex == capacity - 1) {          // full: double the array
            T* bigger = new T[2 * capacity];
            for (int i = 0; i < capacity; i++) bigger[i] = stack[i];
            delete[] stack;
            stack = bigger;
            capacity *= 2;
        }
        stack[++topIndex] = x;                   // increment, then store
    }

    T top() const {
        if (empty()) throw std::underflow_error("Stack is empty");
        return stack[topIndex];
    }

    T pop() {
        if (empty()) throw std::underflow_error("Stack is empty");
        return stack[topIndex--];                // return, then decrement
    }
};

int main() {
    ArrayStack<int> s(2);
    for (int i = 1; i <= 5; i++) s.push(i * 10);  // capacity grows 2 -> 4 -> 8
    std::cout << s.size() << " " << s.top() << "\n";
    std::cout << s.pop() << " ";                   // removes 50
    std::cout << s.pop() << "\n";                  // removes 40
    std::cout << s.size() << " " << s.top() << "\n";
}
```

`push` moves the elements to an array of twice the size only when the array is full, then increments `topIndex` and stores in that cell. `pop` returns the top element and then decrements `topIndex`, and calling `top` or `pop` on an empty stack throws an exception. The output is as follows.

```text
5 50
50 40
3 30
```

### 2.2 Dynamic Resizing

When the array is full, double its size (amortized $O(1)$ push).

Starting from capacity 1, $n$ pushes copy 1, 2, 4, ... elements each time the array grows, so the total number of copies is less than $2n$. The average cost of one push is therefore constant. The particular push that grows the array, however, copies every element and takes $O(n)$ time.

### 2.3 Two Stacks in One Array

An array-based representation of a stack can waste space when multiple stacks are to coexist. Each stack needs its own array of maximum size, and when one stack is full it cannot use the free space of another. An exception is when only two stacks are to coexist, and the two stacks are placed in one array as follows.

- Fix the bottom of one stack at position 0.
- Fix the bottom of the other stack at position `MaxSize-1`.
- The two stacks grow toward the middle of the array.

```text
index   0   1   2   3   4   5   6   7   8   9
      +---+---+---+---+---+---+---+---+---+---+
      | a | b | c |   |   |   |   | y | x | w |
      +---+---+---+---+---+---+---+---+---+---+
        ^       ^                   ^       ^
     bottom1   top1 -->       <-- top2   bottom2
```

*Figure 2. Two stacks growing from both ends of one array toward the middle*

In the figure, a, b, c were pushed onto stack 1 and w, x, y onto stack 2 in order. If `top1` and `top2` are the top positions of stacks 1 and 2, the array is full only when `top1 + 1 == top2`. Either stack can therefore use every free cell of the array.

### 2.4 Advantages/Disadvantages

- **Advantage:** The elements are in contiguous memory, which is cache-friendly, and the implementation is simple.
- **Disadvantage:** It may waste space if the capacity is much larger than the actual size, and the waste grows when multiple stacks coexist (Section 2.3).

---

<br>

## 3. Linked Stack

### 3.1 Which End of the Chain Is the Stack Top

Multiple stacks can be represented efficiently using one chain (linked list) for each stack. We must then decide which end of the chain is the stack top. Let $n$ be the number of nodes in the chain.

1. If the right end of the chain is the stack top, push and pop are implemented with the chain operations `insert(n, x)` and `erase(n-1)`. Finding the last node and the node before it in a singly linked chain requires following the links from the first node, so this takes $O(n)$ time. Even if a tail pointer makes push $O(1)$, pop must still find the previous node that becomes the new last node, so it remains $O(n)$.
2. If the left end of the chain is the stack top, push and pop are implemented with `insert(0, x)` and `erase(0)`, which change only the first node and take $O(1)$ time.

Therefore the left end (head) of the chain is used as the stack top.

```text
(a) top = right end: insert(n, x) and erase(n-1) take O(n)

    firstNode                               top
        |                                    |
        v                                    v
      [ a ] ---> [ b ] ---> [ c ] ---> [ d ] ---> NULL

(b) top = left end: insert(0, x) and erase(0) take O(1)

       top
        |
        v
      [ d ] ---> [ c ] ---> [ b ] ---> [ a ] ---> NULL
```

*Figure 3. The right end of the chain as the top versus the left end as the top*

### 3.2 Implementation

Use a singly linked list where the top of the stack is the head:
- `push(x)` inserts a new node at the head in $O(1)$.
- `pop()` removes the head node in $O(1)$.

```cpp
#include <iostream>
#include <stdexcept>

template <class T>
class LinkedStack {
    struct Node {
        T data;
        Node* next;
    };
    Node* topNode = nullptr;   // left end of the chain is the stack top
public:
    bool empty() const { return topNode == nullptr; }

    void push(const T& x) {            // insert(0, x): O(1)
        topNode = new Node{x, topNode};
    }

    T pop() {                          // erase(0): O(1)
        if (empty()) throw std::underflow_error("Stack is empty");
        Node* p = topNode;
        T x = p->data;
        topNode = p->next;
        delete p;
        return x;
    }

    ~LinkedStack() { while (!empty()) pop(); }
};

int main() {
    LinkedStack<char> s;
    s.push('a'); s.push('b'); s.push('c');
    while (!s.empty()) std::cout << s.pop();
    std::cout << "\n";
}
```

`push` sets the `next` of the new node to the current top and moves the top pointer to the new node. `pop` takes the value of the top node, moves the top pointer to the next node, and frees the old top node. Pushing a, b, c in order and popping them all prints them in LIFO order as follows.

```text
cba
```

### 3.3 Advantages/Disadvantages

- **Advantage:** No capacity is reserved in advance, so no space is wasted on empty cells, and it is a truly dynamic structure whose size follows the number of elements.
- **Disadvantage:** Each element carries extra pointer overhead, and the nodes are scattered in memory, which gives poor cache locality.

---

<br>

## 4. Applications of Stacks

### 4.1 Parentheses Matching

**Parenthesis matching** is the problem of matching the left and right parentheses in a character string. Character positions are counted from 0. For example, the characters of `(a*(b+c)+d)` by position are as follows.

| Position | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|:-----|:--|:--|:--|:--|:--|:--|:--|:--|:--|:--|:--|
| Character | `(` | `a` | `*` | `(` | `b` | `+` | `c` | `)` | `+` | `d` | `)` |

*Table 2. Characters by position in the parenthesis matching example*

The left parentheses are at positions 0 and 3 and the right parentheses at positions 7 and 10; 3 matches 7, and 0 matches 10. Some parentheses may have no match. In `(a+b))*((c+d)`, (0, 4) is a pair, the right parenthesis at position 5 has no matching left parenthesis, (8, 12) is a pair, and the left parenthesis at position 7 has no matching right parenthesis.

The output consists of the pairs $(u, v)$ such that the left parenthesis at position $u$ is matched with the right parenthesis at position $v$. A stack implements this as follows.

1. Scan the expression from left to right.
2. When a left parenthesis is encountered, push its position onto the stack.
3. When a right parenthesis is encountered, pop the position of the matching left parenthesis from the stack and output the pair. If the stack is empty, this right parenthesis has no match.
4. After the scan, the left parentheses at the positions left on the stack have no match.

The most recent left parenthesis is matched first by the next right parenthesis, so a stack, a LIFO structure, fits. The output for the expression `(((a+b)*c+d-e)/(f+g)-(h+j)*(k-1))/(m-n)` is (2, 6) (1, 13) (15, 19) (21, 25) (27, 31) (0, 32) (34, 38), and the stack and output change at each parenthesis as follows.

| Parenthesis read (position) | Action | Stack (bottom → top) | Output |
|:-----|:-----|:-----|:-----|
| `(` (0) | push 0 | 0 | |
| `(` (1) | push 1 | 0 1 | |
| `(` (2) | push 2 | 0 1 2 | |
| `)` (6) | pop 2 | 0 1 | (2, 6) |
| `)` (13) | pop 1 | 0 | (1, 13) |
| `(` (15) | push 15 | 0 15 | |
| `)` (19) | pop 15 | 0 | (15, 19) |
| `(` (21) | push 21 | 0 21 | |
| `)` (25) | pop 21 | 0 | (21, 25) |
| `(` (27) | push 27 | 0 27 | |
| `)` (31) | pop 27 | 0 | (27, 31) |
| `)` (32) | pop 0 | (empty) | (0, 32) |
| `(` (34) | push 34 | 34 | |
| `)` (38) | pop 34 | (empty) | (34, 38) |

*Table 3. Stack and output during parenthesis matching of a long expression*

The following code implements this algorithm and applies it to the two expressions above.

```cpp
#include <iostream>
#include <stack>
#include <string>

// Print matched pairs (u, v) and unmatched positions.
void printMatchedPairs(const std::string& expr) {
    std::stack<int> s;                       // positions of left parentheses
    for (int i = 0; i < (int)expr.size(); i++) {
        if (expr[i] == '(') {
            s.push(i);                       // remember where '(' was seen
        } else if (expr[i] == ')') {
            if (s.empty()) {
                std::cout << "No match for right parenthesis at " << i << "\n";
            } else {
                std::cout << "(" << s.top() << ", " << i << ")\n";
                s.pop();                     // matched, so remove it
            }
        }
    }
    while (!s.empty()) {                     // left parentheses never closed
        std::cout << "No match for left parenthesis at " << s.top() << "\n";
        s.pop();
    }
}

int main() {
    printMatchedPairs("(((a+b)*c+d-e)/(f+g)-(h+j)*(k-1))/(m-n)");
    std::cout << "--\n";
    printMatchedPairs("(a+b))*((c+d)");
}
```

The output is as follows.

```text
(2, 6)
(1, 13)
(15, 19)
(21, 25)
(27, 31)
(0, 32)
(34, 38)
--
(0, 4)
No match for right parenthesis at 5
(8, 12)
No match for left parenthesis at 7
```

When there are several kinds of brackets, push the opening bracket character instead of its position, and on a closing bracket compare its kind with the opening bracket on top. The following function checks if brackets `()`, `[]`, `{}` are properly nested:

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

On a closing bracket, it returns `false` if the stack is empty or the opening bracket on top is of a different kind. After the full scan, the stack must be empty for every opening bracket to have found its match, and then it returns `true`.

### 4.2 Function Call Stack

The runtime system uses a stack to manage function calls:
- On a call, it pushes an activation record holding the parameters, local variables, and return address.
- On return, it pops that activation record.
- Each recursive call stacks its own activation record, so recursion is supported naturally.

### 4.3 Undo Operations

Text editors, browsers, and many applications use stacks for undo functionality. The most recent action must be undone first, so a LIFO structure fits.

### 4.4 Tower of Hanoi

Classic recursive problem solved elegantly with stacks:

$$T(n) = 2T(n-1) + 1 = 2^n - 1 \text{ moves}$$

The **Towers of Hanoi** problem moves $n$ disks stacked on tower A to tower C. Initially the disks are on A with larger disks below, and the following rules must be kept.

- Move 1 disk at a time, using any of towers A, B, and C.
- A larger disk cannot be placed on top of a smaller one.

```text
    |           |           |
   =1=          |           |
  ==2==         |           |
 ===3===        |           |
---------   ---------   ---------
    A           B           C
```

*Figure 4. Initial state with 3 disks stacked on tower A*

Disk 1 is the smallest and disk 3 the largest. The 3-disk problem is solved by the following seven moves.

| Move | Disk moved | From → To |
|:-----|:-----|:-----|
| 1 | Disk 1 | A → C |
| 2 | Disk 2 | A → B |
| 3 | Disk 1 | C → B |
| 4 | Disk 3 | A → C |
| 5 | Disk 1 | B → A |
| 6 | Disk 2 | B → C |
| 7 | Disk 1 | A → C |

*Table 4. The seven moves that solve the 3-disk Towers of Hanoi*

On each tower, disks are added and removed only at the top, so they are removed in a LIFO manner. Each tower can therefore be represented as a stack.

**Recursive solution:** Moving $n > 0$ disks from A to C splits into the following three steps.

1. Move the top $n-1$ disks from A to B, using C as the helper tower. This is the same problem of size $n-1$.
2. Move the largest disk left on A to C.
3. Move the $n-1$ disks on B from B to C, using A as the helper tower.

```cpp
#include <iostream>

// Move the top n disks from tower x to tower y, using tower z as a helper.
void towersOfHanoi(int n, char x, char y, char z) {
    if (n > 0) {
        towersOfHanoi(n - 1, x, z, y);   // top n-1 disks: x -> z
        std::cout << "Move top disk from tower " << x
                  << " to top of tower " << y << "\n";
        towersOfHanoi(n - 1, z, y, x);   // top n-1 disks: z -> y
    }
}

int main() {
    towersOfHanoi(3, 'A', 'C', 'B');
}
```

The output for $n = 3$ is as follows, which matches the moves of Table 4.

```text
Move top disk from tower A to top of tower C
Move top disk from tower A to top of tower B
Move top disk from tower C to top of tower B
Move top disk from tower A to top of tower C
Move top disk from tower B to top of tower A
Move top disk from tower B to top of tower C
Move top disk from tower A to top of tower C
```

**Number of moves:** Let $T(n)$ be the number of moves for $n$ disks. Steps 1 and 3 take $T(n-1)$ moves each and step 2 takes 1, so $T(n) = T(n-1) + 1 + T(n-1) = 2T(n-1) + 1$ with $T(0) = 0$. Unrolling it repeatedly gives the following.

$$T(n) = 2T(n-1) + 1 = 2(2T(n-2) + 1) + 1 = 2^2 T(n-2) + 2^1 + 2^0$$

$$T(n) = 2^k T(n-k) + 2^{k-1} + 2^{k-2} + \cdots + 2^2 + 2^1 + 2^0$$

Substituting $k = n$ and using $T(0) = 0$ gives $T(n) = 2^{n-1} + \cdots + 2^1 + 2^0 = 2^n - 1$. This is the minimum number of moves required to solve the problem, and the time complexity is exponential, $O(2^n)$.

**64 disks:** Moving 64 disks requires $2^{64} - 1 \approx 1.8 \times 10^{19}$ moves. According to legend, the priests of Brahma are moving 64 gold disks, and the world will come to an end when they complete their task. At 1 disk move per minute, with about 525,600 minutes in a year, this takes $1.8 \times 10^{19} / 525{,}600 \approx 3.5 \times 10^{13}$ years. Even a computer making $10^9$ moves per second needs about $1.8 \times 10^{10}$ seconds, that is, about 585 years. Each additional disk roughly doubles the number of moves, so the running time also roughly doubles.

---

<br>

## 5. Expression Evaluation

### 5.1 Infix, Prefix, and Postfix

| Type | Example | Description |
|------|---------|-------------|
| Infix | `A + B * C` | Operators between operands |
| Prefix (Polish) | `+ A * B C` | Operators before operands |
| Postfix (Reverse Polish) | `A B C * +` | Operators after operands |

*Table 5. Three notations for expressions*

Postfix notation fixes the order of evaluation without parentheses or precedence rules, so an expression can be evaluated with one stack in a single left-to-right scan.

### 5.2 Infix to Postfix Conversion

Algorithm using a stack for operators:

1. Scan left to right.
2. If operand, output it.
3. If `(`, push onto stack.
4. If `)`, pop and output until `(` is found, then discard the `(`.
5. If operator, pop and output operators while the top is not `(` and has higher or equal precedence, then push the current operator.
6. At the end of the input, pop and output all remaining operators.

> **Caution:** Popping operators of equal precedence in step 5 is the rule for left-associative operators (`+`, `-`, `*`, `/`). When the right-associative exponent `^` arrives, only operators of strictly higher precedence must be popped. Only then is `A ^ B ^ C` read as `A ^ (B ^ C)` and converted to `A B C ^ ^`.

Converting `A * (B + C) - D` proceeds as follows.

| Symbol read | Action | Stack (bottom → top) | Output |
|:-----|:-----|:-----|:-----|
| `A` | output | (empty) | `A` |
| `*` | push | `*` | `A` |
| `(` | push | `* (` | `A` |
| `B` | output | `* (` | `A B` |
| `+` | push because the top is `(` | `* ( +` | `A B` |
| `C` | output | `* ( +` | `A B C` |
| `)` | pop and output until `(` | `*` | `A B C +` |
| `-` | pop `*`, which has higher precedence, then push | `-` | `A B C + *` |
| `D` | output | `-` | `A B C + * D` |
| (end) | pop the remaining operators | (empty) | `A B C + * D -` |

*Table 6. Converting an infix expression with parentheses to postfix*

### 5.3 Postfix Evaluation

1. Scan left to right.
2. If operand, push onto stack.
3. If operator, pop two operands, apply operator, push result. The value popped first is the right operand, and the value popped second is the left operand.
4. When the scan ends, the single value left on the stack is the result.

The order of the operands matters for subtraction and division. For example, `8 2 -` pops 2 first and 8 second, so it gives $8 - 2 = 6$. Evaluating `2 3 4 + * 5 -` proceeds as follows.

| Symbol read | Action | Stack (bottom → top) |
|:-----|:-----|:-----|
| `2` | push | 2 |
| `3` | push | 2 3 |
| `4` | push | 2 3 4 |
| `+` | pop 4 and 3, push $3 + 4 = 7$ | 2 7 |
| `*` | pop 7 and 2, push $2 \times 7 = 14$ | 14 |
| `5` | push | 14 5 |
| `-` | pop 5 and 14, push $14 - 5 = 9$ | 9 |

*Table 7. Evaluating a postfix expression with a stack*

The 9 left on the stack after the scan is the result, which equals the value of the infix expression $2 \times (3 + 4) - 5$.

---

<br>

## 6. Appendix

### 6.1 Stack vs. Queue

| Feature | Stack | Queue |
|---------|-------|-------|
| Order | LIFO | FIFO |
| Insert | push (top) | enqueue (rear) |
| Remove | pop (top) | dequeue (front) |
| Use case | Undo, recursion, DFS | Scheduling, BFS |

*Table 8. Comparison of stacks and queues*

Queues are covered in Lecture 6.

### 6.2 Common Interview Problems

1. **Min Stack:** Design a stack that supports `getMin()` in $O(1)$.
2. **Evaluate Reverse Polish Notation:** Evaluate a postfix expression, which uses the algorithm of Section 5.3 directly.
3. **Valid Parentheses** (LeetCode #20): Decide whether several kinds of brackets are properly nested, which is the problem of Section 4.1.
4. **Daily Temperatures:** A problem solved with a monotonic stack.

---

<br>

## Summary

| Concept | Key Summary |
|---------|-------------|
| Stack | A LIFO data structure that inserts and deletes only at the top, and all operations are $O(1)$ with a fixed-size array or a linked list. |
| Relation to linear lists | A stack is a restricted linear list that inserts and deletes only at the right end. |
| Array-based | It uses `topIndex` and doubles the array when full, which keeps push amortized $O(1)$. |
| Two stacks in one array | Using the two ends of an array as the bottoms of two stacks lets them share the free cells without waste. |
| Linked | It uses the linked list head as the top and has no capacity limit. |
| Parentheses matching | Opening brackets or their positions are pushed and popped on closing brackets to form pairs. |
| Tower of Hanoi | Each tower is represented as a stack, and moving $n$ disks requires at least $2^n - 1$ moves. |
| Expression evaluation | Infix is converted to postfix, which is then evaluated with a stack. |
| Recursion | The function call stack is an implicit stack. |

---

<br>

## Self-Check Questions

1. **Two stacks in one array:** Two stacks are placed in an array of size 10 (`MaxSize = 10`) as in Section 2.3. After pushing 4 elements onto stack 1 and 5 elements onto stack 2, find `top1` and `top2`, the condition for the array to be full, and the number of elements that can still be pushed.

   <details>
   <summary>Answer</summary>

   Stack 1 uses positions 0-3, so `top1 = 3`, and stack 2 uses 5 cells downward from position 9 (positions 5-9), so `top2 = 5`. The array is full when `top1 + 1 == top2`. Now `top1 + 1 = 4 < 5`, so one more element can be pushed into position 4 by either stack. After that the condition holds and the array is full.

   </details>

2. **Top of a linked stack:** If the right end of a singly linked chain of $n$ nodes is used as the stack top, which chain operations do push and pop become, and how long do they take? What changes if a tail pointer is added?

   <details>
   <summary>Answer</summary>

   Push becomes `insert(n, x)` and pop becomes `erase(n-1)`, and both take $O(n)$ because they follow the links to the last node. With a tail pointer, push becomes $O(1)$, but pop still takes $O(n)$ because it must find the previous node that becomes the new tail after the deletion. With the left end as the top, `insert(0, x)` and `erase(0)` are both $O(1)$.

   </details>

3. **Tracing parenthesis matching:** For `(a-b)*(c+d/(e-f))/(g+h)`, write the pairs $(u, v)$ that the algorithm of Section 4.1 outputs, in output order.

   <details>
   <summary>Answer</summary>

   The parenthesis positions are `(` 0, `)` 4, `(` 6, `(` 11, `)` 15, `)` 16, `(` 18, `)` 22. The algorithm pushes 0 and pops it at position 4 to output (0, 4), pushes 6 and 11 and pops 11 at position 15 to output (11, 15), pops 6 at position 16 to output (6, 16), and pushes 18 and pops it at position 22 to output (18, 22). The output is therefore (0, 4) (11, 15) (6, 16) (18, 22).

   </details>

4. **Towers of Hanoi:** Find the minimum number of moves for 5 disks. Roughly how long would a computer making $10^9$ moves per second take to move 64 disks?

   <details>
   <summary>Answer</summary>

   $T(5) = 2^5 - 1 = 31$ moves. Checking with the recurrence, $T(1) = 1$, $T(2) = 3$, $T(3) = 7$, $T(4) = 15$, and $T(5) = 31$. Moving 64 disks needs $2^{64} - 1 \approx 1.8 \times 10^{19}$ moves, so it takes $1.8 \times 10^{19} / 10^9 = 1.8 \times 10^{10}$ seconds, that is, about 585 years.

   </details>

5. **Associativity:** Convert `A ^ B ^ C` and `A - B - C` to postfix notation, and explain how step 5 of Section 5.2 treats the two cases differently.

   <details>
   <summary>Answer</summary>

   `A ^ B ^ C` becomes `A B C ^ ^`. When the second `^` arrives, the `^` on top has equal precedence but is right-associative, so it is not popped and the new `^` is pushed, and both `^` are output at the end. `A - B - C` becomes `A B - C -`. When the second `-` arrives, the `-` on top has equal precedence and is left-associative, so it is popped and output first, and then the new `-` is pushed. Therefore `A - B` is computed first.

   </details>
