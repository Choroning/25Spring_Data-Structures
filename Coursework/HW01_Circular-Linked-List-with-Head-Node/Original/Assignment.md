# HW1 Assignment Handout — Circular Linked List with Head Node

[Repository Guide](../../../README.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **Last Updated:** 2026-10-19

Data Structures Programming Homework #1, Circular Linked List with Head Node. The homework has four problems worth 100 points in total. Problems 1 and 2 fill in the bodies of member functions of a circular linked list that has a head node.

---

<br>

## Problem 1. InsertFront (20 points)

Program the operation `InsertFront` of a circular linked list with a head node.

```cpp
void InsertFront(const T& item) {
    ChainNode<T>* newNode = new ChainNode<T>(item);

    // (1-1) The Link of newNode points out the original first node. (10 points)

    // (1-2) The newNode will be a new first node. (10 points)

}
```

---

<br>

## Problem 2. InsertRear (50 points)

Program the operation `InsertRear` of a circular linked list with a head node.

```cpp
void InsertRear(const T& item) {
    ChainNode<T>* newNode = new ChainNode<T>(item);

    ChainNode<T>* cur; // (2-1) The first node is stored at the *cur pointer. (10 points)

    // (2-2) We will find the last node through the while loop, and the last node is stored at the *cur pointer. (20 points)

    // (2-3) The newNode will be inserted after the last node. (10 points)

    // (2-4) The last node should always point out the head node. (10 points)

}
```

---

<br>

## Problem 3. Execution Screenshots (20 points)

Run the program with the completed code and capture screenshots of the results. The handout gives the output of two runs as examples. The first run enters 4 at the search prompt.

```text
Inserting nodes using operation 'InsertFront':

1

2->1

3->2->1


Inserting nodes using operation 'InsertRear':

3->2->1->2

3->2->1->2->4

3->2->1->2->4->6


Print a Circular Linked List:

3->2->1->2->4->6


Which data is searching for? : 4

4 is at the index 5

Node<3> is deleted
Node<2> is deleted
Node<1> is deleted
Node<2> is deleted
Node<4> is deleted
Node<6> is deleted

Destructor is executed successfully!
```

The second run enters 9, which is not in the list. The output up to the list printout is the same as in the first run, and the rest reads as follows.

```text
Which data is searching for? : 9

There's no data you want to search!

Node<3> is deleted
Node<2> is deleted
Node<1> is deleted
Node<2> is deleted
Node<4> is deleted
Node<6> is deleted

Destructor is executed successfully!
```

---

<br>

## Problem 4. Questions about the Head Node (10 points)

Explain the following questions about the head node for a circular linked list.

1. Explain the pros of using a head node for a circular linked list.
2. Explain the difference between putting the head node at the front and putting the head node at the rear.
