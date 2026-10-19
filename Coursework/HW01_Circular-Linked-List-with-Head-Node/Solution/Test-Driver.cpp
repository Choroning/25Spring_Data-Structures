/**
 * @file    Test-Driver.cpp
 * @brief   Test driver for InsertFront and InsertRear (HW1)
 * @author  Cheolwon Park
 * @date    2026-10-19
 * @note    Test driver that only compiles and runs the submitted functions.
 *          It is not part of the submitted homework; the full program used
 *          for the submission was not kept. The output format follows the
 *          screenshots of the submission.
 *
 * Build and run from this folder, then enter the value to search for:
 *     g++ -std=c++17 -Wall -Wextra -pedantic -o hw1 Test-Driver.cpp
 *     ./hw1
 */

#include <initializer_list>
#include <iostream>

template <class T> class CircularList;

/**
 * @class ChainNode
 * @brief Node with a data field and a link field
 */
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

/**
 * @class CircularList
 * @brief Singly linked circular list with a head node
 *
 * `head` points to the head node, which holds no element. The link of the
 * last node points back to the head node, so an empty list is a head node
 * whose link points to itself.
 */
template <class T>
class CircularList {
public:
    CircularList() {
        head = new ChainNode<T>();
        head->link = head;              // empty list: the head node points to itself
    }

    /** @brief Delete the nodes from the first one, then the head node */
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

    // The submitted functions, included unchanged
#include "InsertFront-and-InsertRear.cpp"

    /** @brief Print the elements from the first node, separated by "->" */
    void Print() const {
        for (ChainNode<T>* cur = head->link; cur != head; cur = cur->link) {
            std::cout << cur->data;
            if (cur->link != head) std::cout << "->";
        }
        std::cout << '\n';
    }

    /**
     * @brief  Search with the head node as a sentinel (Lecture 3, Section 6.6)
     * @return Position of the first node holding x, counted from 1, or 0 if x is absent
     */
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

private:
    ChainNode<T>* head;                 // pointer to the head node
};

int main() {
    CircularList<int> list;

    std::cout << "Inserting nodes using operation 'InsertFront':\n\n";
    for (int x : {1, 2, 3}) {
        list.InsertFront(x);
        list.Print();
        std::cout << '\n';
    }

    std::cout << "\nInserting nodes using operation 'InsertRear':\n\n";
    for (int x : {2, 4, 6}) {
        list.InsertRear(x);
        list.Print();
        std::cout << "\n\n";
    }

    std::cout << "\nPrint a Circular Linked List:\n\n";
    list.Print();
    std::cout << "\n\n";

    int target;
    std::cout << "Which data is searching for? : ";
    if (!(std::cin >> target)) {
        std::cout << "\nInput is not an integer.\n\n";
        return 1;
    }

    int index = list.Search(target);
    if (index != 0)
        std::cout << target << " is at the index " << index << "\n\n";
    else
        std::cout << "There's no data you want to search!\n\n";

    return 0;                           // the destructor of list runs here
}
