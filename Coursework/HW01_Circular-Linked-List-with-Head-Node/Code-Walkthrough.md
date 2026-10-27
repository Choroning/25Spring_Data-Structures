# HW1 Code Walkthrough — Circular Linked List with Head Node

[Repository Guide](../../README.md) | [English](Code-Walkthrough.md) | [한국어](Code-Walkthrough.ko.md)

> **Last Updated:** 2026-10-27

> **Learning Objectives:**
> 1. Explain the link that each statement of `InsertFront` and `InsertRear` changes
> 2. Explain how `CircularList<T>` in the test driver creates the head node and frees the nodes
> 3. Explain how an `#include` inside the class definition turns the solution functions into member functions
> 4. Trace the state of the list and the output in execution order

---

## Table of Contents

- [1. File Layout](#1-file-layout)
- [2. InsertFront](#2-insertfront)
- [3. InsertRear](#3-insertrear)
- [4. Driver Headers and ChainNode](#4-driver-headers-and-chainnode)
- [5. Constructor and Destructor](#5-constructor-and-destructor)
- [6. Including the Solution Functions and Print](#6-including-the-solution-functions-and-print)
- [7. Search](#7-search)
- [8. main](#8-main)
- [9. Execution Trace](#9-execution-trace)
- [10. Complexity](#10-complexity)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. File Layout

The companion document [HW1 Assignment Explanation](Assignment-Explanation.md) covers the requirements, design, testing, and written answers. This document reads the two files in `Solution` from beginning to end. All line numbers refer to the respective file. `InsertFront-and-InsertRear.cpp` (38 lines) holds the two solution functions, and `Test-Driver.cpp` (133 lines) is a test driver that runs them.

| File | Lines | Part | Kind |
|:-----|:-----|:-----|:-----|
| `InsertFront-and-InsertRear.cpp` | 1-10 | Doxygen header | File description comment |
| `InsertFront-and-InsertRear.cpp` | 12-20 | `InsertFront` | Solution code |
| `InsertFront-and-InsertRear.cpp` | 22-38 | `InsertRear` | Solution code |
| `Test-Driver.cpp` | 1-19 | Header comment, `#include`, forward declaration | Test driver |
| `Test-Driver.cpp` | 21-36 | `ChainNode<T>` | Test driver |
| `Test-Driver.cpp` | 38-96 | `CircularList<T>` (includes the solution functions at line 68) | Test driver |
| `Test-Driver.cpp` | 98-133 | `main` | Test driver |

*Table 1. Layout of the two files*

---

<br>

## 2. InsertFront

```cpp
void InsertFront(const T& item) {
    ChainNode<T>* newNode = new ChainNode<T>(item);

    // (1-1) The Link of newNode points out the original first node.
    newNode->link = head->link;

    // (1-2) The newNode will be a new first node.
    head->link = newNode;
}
```

Line 13 dynamically allocates a new node whose data is `item`. The constructor of `ChainNode<T>` sets the link to `nullptr`, but the value is never used because it is overwritten right away. Line 16 copies the link of the head node, that is, the address of the original first node, into the link of the new node, and line 19 changes the link of the head node to the new node. Because line 16 first moves the address of the original first node into the new node, the list is not lost when line 19 overwrites `head->link`. The comments (1-1) and (1-2) are the comments of the handout's skeleton code without the points.

---

<br>

## 3. InsertRear

```cpp
void InsertRear(const T& item) {
    ChainNode<T>* newNode = new ChainNode<T>(item);

    // (2-1) The first node is stored at the *cur pointer.
    ChainNode<T>* cur = head->link;

    // (2-2) We will find the last node through the while loop, and the last node is stored at the *cur pointer.
    while (cur->link != head) {
        cur = cur->link;
    }

    // (2-3) The newNode will be inserted after the last node.
    cur->link = newNode;

    // (2-4) The last node should always point out the head node.
    newNode->link = head;
}
```

After line 23 allocates the new node, line 26 initializes `cur` to the first node (`head->link`). The handout's skeleton code only declared `ChainNode<T>* cur;`, and the solution merges the declaration and the assignment of (2-1) into one line. The loop on lines 29-31 advances one node at a time while the node after `cur` is not the head node, so when it ends, `cur` points to the node whose link is the head node, that is, the last node. On the empty list, `cur` is the head node itself and the loop does not run. Line 34 links the new node after the last node, and line 37 sets the link of the new node to the head node, closing the circle.

---

<br>

## 4. Driver Headers and ChainNode

Lines 1-14 of `Test-Driver.cpp` are the Doxygen header, which states that the file was written for testing and gives the build commands. `<initializer_list>` on line 16 is the header for using a brace list in a range-based for statement such as `for (int x : {1, 2, 3})` in `main`, and `<iostream>` on line 17 is the header for input and output. Line 19 is a forward declaration of `CircularList`. It is needed because the `friend` declaration on line 27 refers to `CircularList<T>` before it is defined.

```cpp
template <class T>
class ChainNode {
    friend class CircularList<T>;

public:
    ChainNode(const T& data = T(), ChainNode<T>* link = nullptr)
        : data(data), link(link) {}

private:
    T data;
    ChainNode<T>* link;
};
```

`ChainNode<T>` on lines 25-36 has the same two fields as the node of Lecture 3, Section 4.3. The fields are `private` and `CircularList<T>` is declared a `friend`, so only the member functions of the list class (including the two solution functions) can access `data` and `link`. Both constructor parameters have default values, so a node can be created with data only, as in `new ChainNode<T>(item)`, or with no arguments, as for the head node.

---

<br>

## 5. Constructor and Destructor

```cpp
CircularList() {
    head = new ChainNode<T>();
    head->link = head;              // empty list: the head node points to itself
}
```

The constructor on lines 49-52 allocates the head node and makes its link point to itself, creating the empty list (Figure 2 of the [Assignment Explanation](Assignment-Explanation.md)).

```cpp
~CircularList() {
    ChainNode<T>* del = head->link; // node to delete
    while (del != head) {
        head->link = del->link;     // the next node becomes the first node
        std::cout << "Node<" << del->data << "> is deleted\n";
        delete del;
        del = head->link;
    }
    delete head;
    std::cout << "\nDestructor is executed successfully!\n" << std::endl;
}
```

The destructor on lines 55-65 is the destructor of Lecture 3, Section 6.4 with the deletion messages and the freeing of the head node added. It makes `del` point to the first node, then repeatedly moves the link of the head node to the node after `del` and deletes `del`, until `del` becomes the head node. Since the next node is moved into `head->link` before a node is deleted, the link of a freed node is never read. When all data nodes are gone, the link of the head node points to itself, the loop ends, and line 63 frees the head node. Deletion proceeds in turn from the first node, so the output order matches the list order.

---

<br>

## 6. Including the Solution Functions and Print

Lines 67-68 `#include` the file `InsertFront-and-InsertRear.cpp` inside the class definition. The preprocessor replaces the line with the contents of the file, so the two solution functions become member functions defined in the class, and `T`, `ChainNode<T>`, and `head` inside them refer to the parameter of the class template, the node class, and the member variable. This way the solution file compiles as member functions as it is. In exchange, `InsertFront-and-InsertRear.cpp` does not compile on its own, and only `Test-Driver.cpp` is compiled.

```cpp
void Print() const {
    for (ChainNode<T>* cur = head->link; cur != head; cur = cur->link) {
        std::cout << cur->data;
        if (cur->link != head) std::cout << "->";
    }
    std::cout << '\n';
}
```

`Print` on lines 71-77 traverses from the first node up to just before returning to the head node and prints the data. It appends `->` only when the next node is not the head node, so no arrow follows the last element. On the empty list the loop does not run and only an empty line is printed. Ending the loop by comparing with `head` rather than with `NULL` is how a circular list is traversed.

---

<br>

## 7. Search

```cpp
int Search(const T& x) const {
    ChainNode<T>* cur = head->link;
    int index = 1;                  // position of cur
    head->data = x;                 // the loop stops at the head node at the latest
    while (cur->data != x) {
        cur = cur->link;
        index++;
    }
    return (cur == head) ? 0 : index;
}
```

`Search` on lines 83-92 is the same sentinel search as `CircularList<T>::Search` in Lecture 3, Section 6.6. Line 86 stores the target in the `data` of the head node, so even when the value is not in the list, the loop stops at the head node at the latest. Each iteration therefore checks only `cur->data != x`. If the loop stops at the head node, the value is absent and the function returns 0; otherwise it returns the position counted from 1. Line 86 is allowed even though the function is `const`, because in a `const` member function the pointer `head` itself becomes constant, not the head node it points to.

---

<br>

## 8. main

Creating the local variable `list` on line 99 makes the constructor prepare an empty list. Lines 101-106 insert 1, 2, and 3 with `InsertFront` and lines 108-113 insert 2, 4, and 6 with `InsertRear`, printing the list each time, and lines 115-117 print the completed list again. Lines 119-124 read the value to search for, and if the input is not an integer, the program prints a message and returns 1. Lines 126-130 print the position if the result of `Search` is not 0, and the message that the value is absent if it is 0. When `main` ends on line 132, the destructor of `list` runs and prints the node deletion messages and the completion message.

---

<br>

## 9. Execution Trace

The run of Section 4.1 of the [Assignment Explanation](Assignment-Explanation.md) (search value 2) traces step by step as follows.

| Step | Call | List or result after the call | Loop iterations of `InsertRear` |
|:-----|:-----|:-----|-----:|
| 1 | `InsertFront(1)` | `1` | - |
| 2 | `InsertFront(2)` | `2->1` | - |
| 3 | `InsertFront(3)` | `3->2->1` | - |
| 4 | `InsertRear(2)` | `3->2->1->2` | 2 |
| 5 | `InsertRear(4)` | `3->2->1->2->4` | 3 |
| 6 | `InsertRear(6)` | `3->2->1->2->4->6` | 4 |
| 7 | `Search(2)` | Compares with nodes 3 and 2, stops at 2, position 2 | - |
| 8 | Destructor | Deletes in the order 3, 2, 1, 2, 4, 6, then frees the head node | - |

*Table 2. State at each step of the run that searches for 2*

When 9 is searched for, step 7 finds that it differs from all six data nodes, so `cur` reaches the head node, where it equals the sentinel, and `Search` returns 0.

---

<br>

## 10. Complexity

With $n$ data nodes, the time complexity of each function is as follows.

| Function | Time complexity | Reason |
|:-----|:-----|:-----|
| `InsertFront` | $O(1)$ | It changes only two links |
| `InsertRear` | $O(n)$ | It moves $n - 1$ times to find the last node |
| `Print` | $O(n)$ | It visits each data node once |
| `Search` | $O(n)$ | If the value is absent, it compares $n + 1$ times, with the $n$ data nodes and the head node |
| Destructor | $O(n)$ | It frees each data node once |

*Table 3. Time complexity of each function*

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| File layout | `InsertFront-and-InsertRear.cpp` holds the two solution functions, and `Test-Driver.cpp` is the test driver that runs them. |
| `InsertFront` | It first moves the address of the original first node into the new node and then changes the link of the head node to the new node. |
| `InsertRear` | It starts `cur` at the first node, moves it to the node whose link is the head node, links the new node after it, and closes the circle. |
| `#include` inside the class | It pastes the bodies of the solution functions into the class definition so that they compile as member functions. |
| Constructor and destructor | The constructor creates a head node that points to itself, and the destructor deletes the nodes in turn from the first one and then frees the head node. |
| `Search` | It is a sentinel search that stores the target in the head node, counts positions from 1, and returns 0 when the value is not found. |

---

<br>

## Self-Check Questions

1. **Default argument of the constructor:** Without the default value `T()` for `data` in the constructor of `ChainNode<T>`, which line of the driver fails to compile?

   <details>
   <summary>Answer</summary>

   It is line 50 of the constructor, `head = new ChainNode<T>();`. The head node must be created without data, and without the default value no constructor can be called with no arguments. The lines of the solution functions that pass an argument, such as `new ChainNode<T>(item)`, still compile.

   </details>

2. **Order in the destructor:** What goes wrong if `delete del;` runs before `head->link = del->link;` in the destructor's loop?

   <details>
   <summary>Answer</summary>

   The `link` of a node that has already been freed is read (use after free). Since this is undefined behavior, the address of the next node may be corrupted, so some nodes may not be freed or the program may terminate abnormally. The next node must be moved into `head->link` first.

   </details>

3. **Arrows in Print:** How does the output change if `Print` prints `->` every time, without the check `if (cur->link != head)`?

   <details>
   <summary>Answer</summary>

   An arrow also follows the last element, as in `3->2->1->`. The check uses the property of the circular structure that the node after the last node is the head node to omit the arrow only after the last element.

   </details>

4. **Search without a sentinel:** If line 86 is deleted, how does `Search` behave for a value in the list and for a value not in the list?

   <details>
   <summary>Answer</summary>

   For a value in the list the loop stops at that node, so the result is the same. For a value not in the list, if it also differs from the `data` of the head node (the `T()` set by the constructor, that is, 0), the loop passes the head node and keeps going around forever. If the target is 0, the loop stops at the head node and returns 0, which is correct only by chance. Without a sentinel, the check `cur != head` must be added to the loop condition.

   </details>
