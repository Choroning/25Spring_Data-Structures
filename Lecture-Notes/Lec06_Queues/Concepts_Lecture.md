# Lecture 6 — Queues

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-18

> **Learning Objectives:**
> 1. Define a queue as a FIFO linear list and compare it with a stack
> 2. Implement queues using arrays and linked lists
> 3. Apply circular array technique for efficient queue operations
> 4. Compare the methods that distinguish a full circular queue from an empty one
> 5. Distinguish queue variants (deque, priority queue)

---

<br>

## Table of Contents

- [1. Queue ADT](#1-queue-adt)
  - [1.1 Definition](#11-definition)
  - [1.2 Core Operations](#12-core-operations)
- [2. Array-Based Queue](#2-array-based-queue)
  - [2.1 Simple Array Queue](#21-simple-array-queue)
  - [2.2 Modified Formula](#22-modified-formula)
  - [2.3 Shifting a Queue](#23-shifting-a-queue)
- [3. Circular Queue](#3-circular-queue)
  - [3.1 Concept](#31-concept)
  - [3.2 Implementation Details](#32-implementation-details)
  - [3.3 Full vs. Empty Distinction](#33-full-vs-empty-distinction)
  - [3.4 Add Operation (Enqueue)](#34-add-operation-enqueue)
  - [3.5 Remove Operation (Dequeue)](#35-remove-operation-dequeue)
- [4. Linked Queue](#4-linked-queue)
  - [4.1 Two Ways to Assign the Ends of the Chain](#41-two-ways-to-assign-the-ends-of-the-chain)
  - [4.2 Implementation](#42-implementation)
  - [4.3 Advantages](#43-advantages)
- [5. Double-Ended Queue (Deque)](#5-double-ended-queue-deque)
- [6. Applications of Queues](#6-applications-of-queues)
  - [6.1 CPU Scheduling](#61-cpu-scheduling)
  - [6.2 Breadth-First Search (BFS)](#62-breadth-first-search-bfs)
  - [6.3 Buffer Management](#63-buffer-management)
- [7. Appendix](#7-appendix)
  - [7.1 Circular Queue vs. Linear Queue](#71-circular-queue-vs-linear-queue)
  - [7.2 Queue Variants](#72-queue-variants)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Queue ADT

### 1.1 Definition

A **queue** is a linear list where:
- Additions (insertions, push, enqueue) are done at the **rear** only.
- Removals (deletions, pop, dequeue) are done at the **front** only.

This follows the **FIFO** (First In, First Out) principle.

Like a stack, a queue is a special kind of linear list; one end is called the front, and the other end is called the rear. A line at a bus stop is an example of a queue. The person who came first boards the bus first from the head of the line (the front), and a newcomer joins the end of the line (the rear).

```text
            +---+---+---+---+
  pop <---  | A | B | C | D |  <--- push
            +---+---+---+---+
              ^           ^
            front        rear
```

*Figure 1. A queue that deletes at the front and inserts at the rear*

> **Key Point:** In stacks, push and pop are all made at top (LIFO). In queues, push is at rear and pop is at front (FIFO).

### 1.2 Core Operations

| Operation | Description | Complexity |
|-----------|-------------|------------|
| `push(x)` / `enqueue(x)` | Insert element at rear | $O(1)$ |
| `pop()` / `dequeue()` | Remove element from front | $O(1)$ |
| `front()` | Return front element | $O(1)$ |
| `back()` | Return rear element | $O(1)$ |
| `empty()` | Check if queue is empty | $O(1)$ |
| `size()` | Return number of elements | $O(1)$ |

*Table 1. Core queue operations and their time complexity*

The times in the table hold for an implementation with a circular array (Section 3) or a linked list (Section 4). With a simple array representation, pop can take $O(n)$, as Section 2 shows.

---

<br>

## 2. Array-Based Queue

### 2.1 Simple Array Queue

Using `front` at the left end and `rear` at the right end:
- `front` always equals zero.
- `push(x)` is `array[++rear] = x` and takes $O(1)$.
- `pop()` shifts all elements left and takes $O(n)$.

This is inefficient because `pop()` requires $O(n)$ shifts.

This representation stores the $i$-th element of the queue ($i$ from 1) by the simple formula $\text{location}(i) = i - 1$. That is, the first element is in `queue[0]`, the second element is in `queue[1]`, and so on. `front` always equals zero, `rear` is the location of the last element, and the queue size is `rear + 1`.

```text
(a) initial         front=0, rear=2   | A | B | C |   |   |
(b) after pop()     front=0, rear=1   | B | C |   |   |   |
(c) after push(D)   front=0, rear=2   | B | C | D |   |   |
                                       [0] [1] [2] [3] [4]
```

*Figure 2. Pop and push in an array queue that uses the simple formula*

This queue can be derived from the array linear list (`ArrayLinearList`) of Lecture 3. With the left end of the list as the front and the right end as the rear, the operations are as follows.

| Queue operation | Array linear list operation | Time |
|:-----|:-----|:-----|
| `Queue.empty()` | `ArrayLinearList.empty()` | $O(1)$ |
| `x = Queue.front()` | `ArrayLinearList.get(0)` | $O(1)$ |
| `x = Queue.back()` | `ArrayLinearList.get(length - 1)` | $O(1)$ |
| `Queue.push(x)` | `ArrayLinearList.insert(length, x)` | $O(1)$ |
| `Queue.pop()` | `ArrayLinearList.erase(0)` | $O(\text{length})$ |

*Table 2. Queue operations derived from the array linear list and their times*

Pop takes $O(\text{length})$ because after the first element is erased, every remaining element must shift one position left. Performing every operation in $O(1)$ time requires an array representation customized for queues.

### 2.2 Modified Formula

Use a modified location formula where `front` can move right:
$$\text{location}(i) = \text{location}(1) + i - 1$$

- `pop()` increments `front` by 1 and takes $O(1)$.
- Problem: when `rear = MaxSize - 1` and `front > 0`, space is wasted at the front.

Here $\text{location}(1)$ is the array position of the first element. With this formula the queue behaves as follows.

1. There is no need to shift the whole queue one position left each time an element is deleted.
2. Instead, each deletion causes `front` to move right by 1.
3. `front` is $\text{location}(1)$, `rear` is the location of the last element, and an empty queue has `rear < front`.

```text
             front       rear
               |           |
               v           v
+-----+-----+-----+-----+-----+-----+
|     |     |  B  |  C  |  D  |     |
+-----+-----+-----+-----+-----+-----+
 Q(0)  Q(1)  Q(2)  Q(3)  Q(4)  Q(5)
```

*Figure 3. A queue whose first element is at Q(2) under the modified formula*

In the figure, $\text{location}(1) = 2$, so the second element is at $\text{location}(2) = 2 + 2 - 1 = 3$, that is, C in Q(3). Deleting B and C moves `front` to 4 and leaves only D (`front = rear = 4`), and deleting D as well gives `front = 5 > rear = 4`, an empty queue.

### 2.3 Shifting a Queue

When `rear = MaxSize - 1` and `front > 0`, no more elements can be added even though there are empty cells at the front of the array. To continue adding to the queue, all elements must be moved to the left end of the array, which is called **shifting** the queue.

```text
(a) before shift   |   |   |   | A | B | C | D | E |
(b) after shift    | A | B | C | D | E |   |   |   |
```

*Figure 4. Shifting a queue that reached the right end of the array to the left end*

But shifting increases the worst-case add time from $\Theta(1)$ to $\Theta(n)$. A better method is therefore needed, and that is the circular queue of Section 3.

---

<br>

## 3. Circular Queue

### 3.1 Concept

Treat the array as **circular** using the modulo operation:

$$\text{location}(i) = (\text{location}(1) + i - 1) \% \text{MaxSize}$$

Both add and delete operations become $O(1)$.

This is called a **circular queue**, and it provides worst-case add and delete times of $\Theta(1)$. It uses the same 1D array `queue[]` but views the array as a circle in which position 0 follows the last position.

```text
          [2] ----> [3]
           ^          |
           |          v
          [1]        [4]
           ^          |
           |          v
          [0] <---- [5]
```

*Figure 5. An array of size 6 viewed as a clockwise circle*

A circular queue with 3 elements may, for example, be configured in the following two ways.

| Configuration | `front` | Positions of the elements | `rear` |
|:-----|:-----|:-----|:-----|
| Configuration 1 | 1 | A at [2], B at [3], C at [4] | 4 |
| Configuration 2 | 4 | A at [5], B at [0], C at [1] | 1 |

*Table 3. Two possible configurations of a circular queue with 3 elements*

In configuration 2 the elements continue from the end of the array, [5], to [0]. Viewed as a circle, A, B, and C are consecutive in the clockwise direction.

### 3.2 Implementation Details

- **Moving clockwise:** `rear = (rear + 1) % queue.length` moves one position.
- Use integer variables `theFront` and `theBack`:
  - `theFront` is one position counterclockwise from the first element.
  - `theBack` gives the position of the last element.
- Initialize `front = rear = 0`.

Figures and code use `front` and `rear` for `theFront` and `theBack`. Moving clockwise is the same as incrementing `rear` and setting `rear = 0` when `rear == queue.length`. Note that `front` was the position of the first element in Section 2.2, but in a circular queue `front` points one position before the first element. In configuration 1 of Table 3, the first element A is at [2], and `front` is 1, one position before it.

### 3.3 Full vs. Empty Distinction

- When the queue becomes full through additions: `front == rear`.
- When the queue becomes empty through removals: `front == rear`.

We **cannot distinguish** between full and empty using only `front` and `rear`.

Starting from configuration 2 of Table 3, three deletions empty the queue as follows.

| Operation | `front` | `rear` | Remaining elements (positions) |
|:-----|:-----|:-----|:-----|
| Start | 4 | 1 | A [5], B [0], C [1] |
| `pop()` removes A | 5 | 1 | B [0], C [1] |
| `pop()` removes B | 0 | 1 | C [1] |
| `pop()` removes C | 1 | 1 | (none) |

*Table 4. Emptying a circular queue*

Starting from the same configuration and filling all six cells gives the following.

| Operation | `front` | `rear` | Elements (positions) |
|:-----|:-----|:-----|:-----|
| Start | 4 | 1 | A [5], B [0], C [1] |
| `push(D)` | 4 | 2 | A [5], B [0], C [1], D [2] |
| `push(E)` | 4 | 3 | A [5], B [0], C [1], D [2], E [3] |
| `push(F)` | 4 | 4 | A [5], B [0], C [1], D [2], E [3], F [4] |

*Table 5. Filling all six cells of a circular queue*

When a series of removals empties the queue, `front = rear`, and a newly constructed queue is also empty, so it is initialized with `front = rear = 0`. But when a series of additions fills the queue, `front = rear` as well. A method to tell the two states apart is therefore needed.

**Solution:** Waste one slot. The queue is full when `(rear + 1) % capacity == front`. This means a maximum of $\text{capacity} - 1$ elements.

This method is one way of not letting the queue get full. The methods that distinguish the two states are as follows.

1. **Do not let the queue get full.** Refusing an addition that would make the queue full gives the one-slot method above, and increasing the array size instead means the queue never reaches the full state.
2. **Define a boolean variable `lastOperationIsAdd`.** Set it to `true` after each add operation and to `false` after each delete operation. The queue is empty iff `(front == rear) && !lastOperationIsAdd`, and full iff `(front == rear) && lastOperationIsAdd`.
3. **Define a variable `NumElements`.** Increment it after each add operation and decrement it after each delete operation (never below 0). The queue is empty iff `(front == rear) && NumElements == 0`, and full iff `(front == rear) && NumElements != 0`, which is the same as `NumElements == capacity`.

| Method | Empty condition | Full condition | Elements that can be stored |
|:-----|:-----|:-----|:-----|
| Waste one slot | `front == rear` | `(rear + 1) % capacity == front` | `capacity - 1` |
| Increase the array size | `front == rear` | Grow the array before it gets full | As many as memory allows |
| `lastOperationIsAdd` | `front == rear && !lastOperationIsAdd` | `front == rear && lastOperationIsAdd` | `capacity` |
| `NumElements` | `NumElements == 0` | `NumElements == capacity` | `capacity` |

*Table 6. Comparison of methods that distinguish a full queue from an empty one*

### 3.4 Add Operation (Enqueue)

To add an element, first move `rear` one position clockwise, then put the element into `queue[rear]`.

```cpp
void push(const T& element) {
    int newRear = (rear + 1) % capacity;
    if (newRear == front)
        throw std::overflow_error("Queue is full");
    rear = newRear;
    queue[rear] = element;
}
```

This code uses the one-slot method. If the position `rear` would move to equals `front`, it treats the queue as full and throws an exception. In configuration 1 of Table 3 (`front = 1`, `rear = 4`), `push(D)` makes `rear` 5 and puts D into [5].

### 3.5 Remove Operation (Dequeue)

To remove an element, first move `front` one position clockwise, then extract the element from `queue[front]`.

```cpp
T pop() {
    if (front == rear)
        throw std::underflow_error("Queue is empty");
    front = (front + 1) % capacity;
    return queue[front];
}
```

Since `front` points one position before the first element, the position reached by moving `front` once is exactly the first element. In configuration 1 of Table 3, `pop()` makes `front` 2 and extracts A.

---

<br>

## 4. Linked Queue

### 4.1 Two Ways to Assign the Ends of the Chain

A queue can be represented using a chain (linked list), with two variables, `front` and `rear`, to keep track of the two ends of the queue. There are two ways to assign the ends of the chain to the ends of the queue.

1. Assign the head of the chain (`firstNode`) as the front and the tail (`lastNode`) as the rear.
2. Assign the head of the chain as the rear and the tail as the front.

A queue that received a, b, c, d, e in order looks as follows under the two options.

```text
(a) head = front, tail = rear

  front                                         rear
    |                                             |
    v                                             v
  [ a ] ---> [ b ] ---> [ c ] ---> [ d ] ---> [ e ] ---> NULL

(b) head = rear, tail = front

  rear                                          front
    |                                             |
    v                                             v
  [ e ] ---> [ d ] ---> [ c ] ---> [ b ] ---> [ a ] ---> NULL
```

*Figure 6. Two ways to assign the head and tail of a chain to the front and rear of a queue*

The times of push and pop under the two options are as follows.

- **Push (add at the rear):** In (a), link the new node after `rear` and move `rear`; in (b), make the new node point to the current `rear` and move `rear`. Both take $O(1)$.
- **Pop (delete at the front):** In (a), moving `front` to the next node takes $O(1)$. In (b), after deleting the `front` node we need the previous node that becomes the new front, but the links point toward the front, so that node cannot be reached from `front`. All $n$ nodes must be scanned starting from `rear`, which takes $\Theta(n)$.

| Option | Push (rear) | Pop (front) |
|:-----|:-----|:-----|
| (a) head = front, tail = rear | $O(1)$ | $O(1)$ |
| (b) head = rear, tail = front | $O(1)$ | $\Theta(n)$ |

*Table 7. Time complexity of the two ways to assign the ends of the chain*

Option (a), with the head as the front and the tail as the rear, is therefore better.

### 4.2 Implementation

Use a singly linked list with both `front` and `rear` pointers:
- `enqueue` inserts at the rear in $O(1)$.
- `dequeue` removes from the front in $O(1)$.

```cpp
struct Node {
    T data;
    Node* next;
};
Node* frontNode;
Node* rearNode;
```

The following member functions implement push and pop on this structure (an empty queue has `frontNode == nullptr`).

```cpp
void push(const T& element) {
    Node* p = new Node{element, nullptr};
    if (frontNode == nullptr) frontNode = p;        // empty queue: p is also the front
    else rearNode->next = p;                        // link after the current rear
    rearNode = p;
}

T pop() {
    if (frontNode == nullptr) throw std::underflow_error("Queue is empty");
    Node* p = frontNode;
    T x = p->data;
    frontNode = p->next;                            // the next node becomes the front
    if (frontNode == nullptr) rearNode = nullptr;   // the queue became empty
    delete p;
    return x;
}
```

Pushing onto an empty queue makes the new node both the front and the rear, and popping the last element sets both `frontNode` and `rearNode` to `nullptr`. Without handling these two boundary cases, the next push onto the empty queue would use a `rearNode` that points to a freed node.

### 4.3 Advantages

- There is no size limitation because the list uses dynamic memory.
- No slot needs to be left empty as in a circular array, so no cell is wasted.

---

<br>

## 5. Double-Ended Queue (Deque)

A **deque** allows insertion and deletion at both ends:
- It provides `pushFront`, `pushBack`, `popFront`, and `popBack`.
- With a circular array or a doubly linked list, all operations are $O(1)$.

With a singly linked list, `popBack` must find the previous node that becomes the new tail, so it takes $O(n)$. Since a deque can use both ends, it can serve as either a stack or a queue.

---

<br>

## 6. Applications of Queues

### 6.1 CPU Scheduling

- In round-robin scheduling, processes take turns using the CPU. A process that has used up its time slice returns to the rear of the queue.
- The ready queue holds the processes waiting for execution in order of arrival.

### 6.2 Breadth-First Search (BFS)

```text
enqueue(start)
while queue is not empty:
    node = dequeue()
    for each neighbor of node:
        if not visited:
            mark visited
            enqueue(neighbor)
```

A queue removes the vertex discovered first before the others, so breadth-first search visits vertices in order of their closeness to the start vertex.

> **Note:** The pseudocode above does not mark the start vertex as visited. When a neighbor connected to the start vertex is processed, the start vertex therefore looks unvisited and can enter the queue again. The start vertex must be marked before it is enqueued, and the corrected pseudocode is as follows.

```text
mark start visited
enqueue(start)
while queue is not empty:
    node = dequeue()
    for each neighbor of node:
        if not visited:
            mark visited
            enqueue(neighbor)
```

### 6.3 Buffer Management

- Print job spooling processes the jobs that arrive at a printer in order of arrival.
- A keyboard input buffer passes characters to a program in the order they were typed.
- Network packet buffering keeps arriving packets in order until they can be processed.

---

<br>

## 7. Appendix

### 7.1 Circular Queue vs. Linear Queue

| Property | Linear Queue | Circular Queue |
|----------|-------------|----------------|
| Pop | $O(n)$ or wastes space | $O(1)$ |
| Space utilization | May leave gaps at front | Reuses freed space |
| Full detection | `rear == capacity - 1` | `(rear+1) % cap == front` |
| Implementation | Simple | Requires modulo arithmetic |

*Table 8. Comparison of linear and circular queues*

### 7.2 Queue Variants

- **Priority Queue:** Elements are dequeued by priority rather than by order of arrival (Lecture 9).
- **Circular Buffer:** It has a fixed size and overwrites the oldest data when full.
- **Message Queue:** An operating system technique for inter-process communication.

---

<br>

## Summary

| Concept | Key Summary |
|---------|-------------|
| Queue | A FIFO data structure that inserts at the rear and removes from the front. |
| Simple array queue | `front` is fixed at 0, so pop requires $O(n)$ shifting. |
| Modified formula | `front` moves right, so pop becomes $O(1)$, but reaching the end of the array forces a shift, so an add takes $\Theta(n)$ in the worst case. |
| Circular array queue | Modulo arithmetic makes the array circular and all operations $O(1)$, and the one-slot method keeps one slot empty. |
| Full vs. empty | Both have `front == rear`, so one of the one-slot method (capacity - 1 elements), `lastOperationIsAdd`, or an element counter tells them apart. |
| Linked queue | With the head of the chain as the front and the tail as the rear, push and pop are both $O(1)$ in a truly dynamic structure. |
| Deque | A double-ended queue that can insert and remove at both ends. |

---

<br>

## Self-Check Questions

1. **Modified formula:** A non-circular queue using the modified formula is stored in an array of size 6 (Q(0)-Q(5)), with `front = 3` and `rear = 5`. Find the number of elements and $\text{location}(2)$. What is needed to push a new element, and how long does it take?

   <details>
   <summary>Answer</summary>

   The number of elements is `rear - front + 1 = 5 - 3 + 1 = 3`. Since $\text{location}(1) = 3$, $\text{location}(2) = 3 + 2 - 1 = 4$. Because `rear = MaxSize - 1 = 5` and `front > 0`, no element can be added as it is; the 3 elements must be moved to Q(0)-Q(2), making `front = 0` and `rear = 2`, and then the new element goes into Q(3). The shift is proportional to the number of elements, so this push takes $\Theta(n)$.

   </details>

2. **The `lastOperationIsAdd` method:** A circular queue of capacity 4 starts with `front = rear = 0` and `lastOperationIsAdd = false`. After four pushes, give `front`, `rear`, the flag, and the state of the queue. What happens after four more pops?

   <details>
   <summary>Answer</summary>

   Four pushes move `rear` to 1, 2, 3, 0, so `front = rear = 0` and the flag is `true`. Since `front == rear && lastOperationIsAdd`, all four cells are filled and the queue is full. Four pops then move `front` to 1, 2, 3, 0, so again `front = rear = 0`, and the flag is `false`, so the queue is empty.

   </details>

3. **Number of elements that can be stored:** For a circular queue of capacity 6, give the maximum number of elements and the full condition under the one-slot method and under the `NumElements` method.

   <details>
   <summary>Answer</summary>

   The one-slot method stores at most $6 - 1 = 5$ elements and treats the queue as full when `(rear + 1) % 6 == front`. The `NumElements` method uses all six cells and stores 6 elements, and the queue is full when `NumElements == 6` (that is, `front == rear` and `NumElements != 0`). In exchange, it must maintain one more variable for the element count.

   </details>

4. **Assigning a linked queue:** Explain why pop takes $\Theta(n)$ when the head of the chain is the rear and the tail is the front. What changes with a doubly linked list?

   <details>
   <summary>Answer</summary>

   Under this assignment the links point from the rear toward the front, so after the front node is deleted, the previous node that becomes the new front cannot be reached from the front node. Finding that node requires scanning all nodes from the rear, which takes $\Theta(n)$. With a doubly linked list, each node also has a link in the opposite direction, so the new front is found directly and pop takes $O(1)$, at the cost of one more pointer per node. With a singly linked list, using the head as the front avoids the problem.

   </details>

5. **Breadth-first search:** Run breadth-first search from A with the corrected pseudocode of Section 6.2 on the undirected graph with edges A-B, A-C, B-D, C-D, D-E. Processing neighbors in alphabetical order, give the order in which vertices leave the queue.

   <details>
   <summary>Answer</summary>

   Mark A and enqueue it (queue: A). Dequeue A, then mark and enqueue B and C (queue: B, C). Dequeue B; A is already visited, so only D is enqueued (queue: C, D). Dequeue C; A and D are already visited (queue: D). Dequeue D and enqueue E (queue: E). Dequeue E; its neighbor D is already visited. The order is therefore A, B, C, D, E.

   </details>
