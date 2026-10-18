/**
 * @file    Lab_LinkedList.cpp
 * @brief   Template-based singly and doubly linked list with iterator support
 * @author  Cheolwon Park
 * @date    2025-03-24
 */

#include <iostream>
#include <stdexcept>

// ============================================================
// Singly Linked List
// ============================================================

/**
 * @class SinglyLinkedList
 * @brief A template-based singly linked list with full operation set
 */
template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* head_;
    int size_;

public:
    // ---- Iterator ----
    class Iterator {
    private:
        Node* current_;
    public:
        Iterator(Node* node) : current_(node) {}
        T& operator*() { return current_->data; }
        const T& operator*() const { return current_->data; }
        Iterator& operator++() { current_ = current_->next; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; current_ = current_->next; return tmp; }
        bool operator==(const Iterator& other) const { return current_ == other.current_; }
        bool operator!=(const Iterator& other) const { return current_ != other.current_; }
    };

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }

    // ---- Constructor / Destructor ----
    SinglyLinkedList() : head_(nullptr), size_(0) {}

    ~SinglyLinkedList() { clear(); }

    SinglyLinkedList(const SinglyLinkedList& other) : head_(nullptr), size_(0) {
        Node* curr = other.head_;
        Node* tail = nullptr;
        while (curr) {
            Node* newNode = new Node(curr->data);
            if (!head_) head_ = newNode;
            else tail->next = newNode;
            tail = newNode;
            size_++;
            curr = curr->next;
        }
    }

    // ---- Core Operations ----

    bool empty() const { return size_ == 0; }
    int size() const { return size_; }

    /**
     * @brief Insert at the front of the list - O(1)
     */
    void pushFront(const T& value) {
        head_ = new Node(value, head_);
        size_++;
    }

    /**
     * @brief Insert at the back of the list - O(n)
     */
    void pushBack(const T& value) {
        Node* newNode = new Node(value);
        if (!head_) {
            head_ = newNode;
        } else {
            Node* curr = head_;
            while (curr->next) curr = curr->next;
            curr->next = newNode;
        }
        size_++;
    }

    /**
     * @brief Insert at a specific index - O(n)
     */
    void insert(int index, const T& value) {
        if (index < 0 || index > size_)
            throw std::out_of_range("Insert index out of range");

        if (index == 0) {
            pushFront(value);
            return;
        }

        Node* curr = head_;
        for (int i = 0; i < index - 1; i++)
            curr = curr->next;

        curr->next = new Node(value, curr->next);
        size_++;
    }

    /**
     * @brief Remove from the front - O(1)
     */
    T popFront() {
        if (empty()) throw std::underflow_error("List is empty");
        Node* temp = head_;
        T value = temp->data;
        head_ = head_->next;
        delete temp;
        size_--;
        return value;
    }

    /**
     * @brief Remove element at a specific index - O(n)
     */
    T erase(int index) {
        if (index < 0 || index >= size_)
            throw std::out_of_range("Erase index out of range");

        if (index == 0) return popFront();

        Node* curr = head_;
        for (int i = 0; i < index - 1; i++)
            curr = curr->next;

        Node* temp = curr->next;
        T value = temp->data;
        curr->next = temp->next;
        delete temp;
        size_--;
        return value;
    }

    /**
     * @brief Get element at index - O(n)
     */
    T& get(int index) {
        if (index < 0 || index >= size_)
            throw std::out_of_range("Index out of range");
        Node* curr = head_;
        for (int i = 0; i < index; i++)
            curr = curr->next;
        return curr->data;
    }

    /**
     * @brief Search for an element - O(n)
     */
    int indexOf(const T& value) const {
        Node* curr = head_;
        int idx = 0;
        while (curr) {
            if (curr->data == value) return idx;
            curr = curr->next;
            idx++;
        }
        return -1;
    }

    /**
     * @brief Reverse the linked list in-place - O(n)
     */
    void reverse() {
        Node* prev = nullptr;
        Node* curr = head_;
        while (curr) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        head_ = prev;
    }

    /**
     * @brief Clear all elements
     */
    void clear() {
        while (head_) {
            Node* temp = head_;
            head_ = head_->next;
            delete temp;
        }
        size_ = 0;
    }

    void print(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << ": ";
        Node* curr = head_;
        std::cout << "[";
        while (curr) {
            std::cout << curr->data;
            if (curr->next) std::cout << " -> ";
            curr = curr->next;
        }
        std::cout << "]" << std::endl;
    }
};

// ============================================================
// Doubly Linked List
// ============================================================

/**
 * @class DoublyLinkedList
 * @brief A template-based doubly linked list with sentinel nodes
 */
template <typename T>
class DoublyLinkedList {
private:
    struct DNode {
        T data;
        DNode* prev;
        DNode* next;
        DNode(const T& d = T(), DNode* p = nullptr, DNode* n = nullptr)
            : data(d), prev(p), next(n) {}
    };

    DNode* header_;   // Sentinel before first element
    DNode* trailer_;  // Sentinel after last element
    int size_;

public:
    // ---- Iterator ----
    class Iterator {
    private:
        DNode* current_;
    public:
        Iterator(DNode* node) : current_(node) {}
        T& operator*() { return current_->data; }
        Iterator& operator++() { current_ = current_->next; return *this; }
        Iterator& operator--() { current_ = current_->prev; return *this; }
        bool operator==(const Iterator& other) const { return current_ == other.current_; }
        bool operator!=(const Iterator& other) const { return current_ != other.current_; }
    };

    Iterator begin() { return Iterator(header_->next); }
    Iterator end() { return Iterator(trailer_); }

    // ---- Constructor / Destructor ----
    DoublyLinkedList() : size_(0) {
        header_ = new DNode();
        trailer_ = new DNode();
        header_->next = trailer_;
        trailer_->prev = header_;
    }

    ~DoublyLinkedList() {
        clear();
        delete header_;
        delete trailer_;
    }

    // ---- Core Operations ----

    bool empty() const { return size_ == 0; }
    int size() const { return size_; }

    T& front() { return header_->next->data; }
    T& back() { return trailer_->prev->data; }

    /**
     * @brief Insert before a given node - O(1)
     */
    void insertBefore(DNode* node, const T& value) {
        DNode* newNode = new DNode(value, node->prev, node);
        node->prev->next = newNode;
        node->prev = newNode;
        size_++;
    }

    void pushFront(const T& value) { insertBefore(header_->next, value); }
    void pushBack(const T& value) { insertBefore(trailer_, value); }

    /**
     * @brief Remove a given node - O(1)
     */
    T removeNode(DNode* node) {
        T value = node->data;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size_--;
        return value;
    }

    T popFront() {
        if (empty()) throw std::underflow_error("List is empty");
        return removeNode(header_->next);
    }

    T popBack() {
        if (empty()) throw std::underflow_error("List is empty");
        return removeNode(trailer_->prev);
    }

    void clear() {
        while (!empty()) popFront();
    }

    void print(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << ": ";
        DNode* curr = header_->next;
        std::cout << "[";
        while (curr != trailer_) {
            std::cout << curr->data;
            if (curr->next != trailer_) std::cout << " <-> ";
            curr = curr->next;
        }
        std::cout << "]" << std::endl;
    }
};

// ============================================================
// Main: Demonstration
// ============================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Linked List Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // --- Singly Linked List ---
    std::cout << "\n=== Singly Linked List ===" << std::endl;
    SinglyLinkedList<int> sll;

    sll.pushBack(10);
    sll.pushBack(20);
    sll.pushBack(30);
    sll.pushFront(5);
    sll.print("After pushes");

    sll.insert(2, 15);
    sll.print("After insert(2, 15)");

    std::cout << "get(0) = " << sll.get(0) << std::endl;
    std::cout << "indexOf(20) = " << sll.indexOf(20) << std::endl;

    sll.erase(0);
    sll.print("After erase(0)");

    sll.reverse();
    sll.print("After reverse");

    std::cout << "Iterator: ";
    for (int x : sll) std::cout << x << " ";
    std::cout << std::endl;

    // --- Doubly Linked List ---
    std::cout << "\n=== Doubly Linked List ===" << std::endl;
    DoublyLinkedList<std::string> dll;

    dll.pushBack("Alpha");
    dll.pushBack("Beta");
    dll.pushBack("Gamma");
    dll.pushFront("Omega");
    dll.print("After pushes");

    std::cout << "Front: " << dll.front() << std::endl;
    std::cout << "Back: " << dll.back() << std::endl;

    dll.popFront();
    dll.print("After popFront");

    dll.popBack();
    dll.print("After popBack");

    std::cout << "Iterator: ";
    for (auto& s : dll) std::cout << s << " ";
    std::cout << std::endl;

    // --- Copy test ---
    std::cout << "\n=== Copy Test ===" << std::endl;
    SinglyLinkedList<int> original;
    for (int i = 1; i <= 5; i++) original.pushBack(i);
    original.print("Original");

    SinglyLinkedList<int> copied(original);
    copied.print("Copied");

    copied.pushBack(99);
    original.print("Original after modifying copy");
    copied.print("Copy after pushBack(99)");

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
