/**
 * @file    Push-and-Pop.cpp
 * @brief   push and pop of a linked queue in two representations (type 1 and type 2)
 * @author  Cheolwon Park
 * @date    2025-05-14
 *
 * Member functions of the class template Queue<T>, which has the members
 * `type`, `front`, `rear`, and `queueSize`. In type 1 the links run from the
 * front to the rear; in type 2 they run from the rear to the front. This file
 * is not compiled on its own: Test-Driver.cpp includes it inside the class
 * definition.
 */

void push(const T& item)
{
    Node<T>* newNode = new Node<T>(item);

    // (1-1) Program an operation push for type1 (20 Points)
    if (type == 1) {
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->link = newNode;
            rear       = newNode;
        }
    }


    // (1-2) Program an operation push for type2 (10 Points)
    else {
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            newNode->link = rear;
            rear          = newNode;
        }
    }

    queueSize++;
}

T pop()
{
    T popData;

    // (2-1) Program an operation pop for type1 (20 Points)
    if (type == 1) {
        if (front == nullptr) return T();

        Node<T>* popNode = front;
        popData          = popNode->data;

        front = front->link;
        if (front == nullptr)
            rear = nullptr;

        delete popNode;
    }

    // (2-2) Program an operation pop for type2 (30 Points)
    else {
        if (front == nullptr) return T();

        popData = front->data;

        if (front == rear) {
            delete front;
            front = rear = nullptr;
        } else {
            Node<T>* prev = rear;
            while (prev->link != front)
                prev = prev->link;

            delete front;
            front      = prev;
            front->link = nullptr;
        }
    }

    queueSize--;
    return popData;
}
