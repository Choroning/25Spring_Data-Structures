/**
 * @file    InsertFront-and-InsertRear.cpp
 * @brief   InsertFront and InsertRear of a circular linked list with a head node
 * @author  Cheolwon Park
 * @date    2025-05-07
 *
 * Member functions of the class template CircularList<T>, where `head` points
 * to the head node. This file is not compiled on its own: Test-Driver.cpp
 * includes it inside the class definition.
 */

void InsertFront(const T& item) {
    ChainNode<T>* newNode = new ChainNode<T>(item);

    // (1-1) The Link of newNode points out the original first node.
    newNode->link = head->link;

    // (1-2) The newNode will be a new first node.
    head->link = newNode;
}

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
