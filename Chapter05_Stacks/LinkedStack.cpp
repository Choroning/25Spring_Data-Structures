/**
 * @file    LinkedStack.cpp
 * @brief   Linked list-based stack ADT implementation
 * @author  Cheolwon Park
 * @date    2025-04-07
 */

#include <iostream>
#include <stdexcept>
#include <string>

/**
 * @class LinkedStack
 * @brief Template-based stack using a singly linked list
 */
template <typename T>
class LinkedStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* topNode_;
    int size_;

public:
    LinkedStack() : topNode_(nullptr), size_(0) {}

    ~LinkedStack() { clear(); }

    LinkedStack(const LinkedStack& other) : topNode_(nullptr), size_(0) {
        if (other.topNode_ == nullptr) return;
        // Copy in correct order using a temporary stack
        Node* curr = other.topNode_;
        LinkedStack<T> temp;
        while (curr) {
            temp.push(curr->data);
            curr = curr->next;
        }
        // Reverse by pushing again
        while (!temp.empty()) {
            push(temp.pop());
        }
    }

    bool empty() const { return topNode_ == nullptr; }
    int size() const { return size_; }

    /**
     * @brief Push element onto top - O(1)
     */
    void push(const T& element) {
        topNode_ = new Node(element, topNode_);
        size_++;
    }

    /**
     * @brief Pop and return top element - O(1)
     * @throws std::underflow_error if stack is empty
     */
    T pop() {
        if (empty())
            throw std::underflow_error("Stack underflow");
        Node* temp = topNode_;
        T value = temp->data;
        topNode_ = topNode_->next;
        delete temp;
        size_--;
        return value;
    }

    /**
     * @brief Peek at top element without removing - O(1)
     */
    const T& top() const {
        if (empty())
            throw std::underflow_error("Stack is empty");
        return topNode_->data;
    }

    /**
     * @brief Clear all elements
     */
    void clear() {
        while (topNode_) {
            Node* temp = topNode_;
            topNode_ = topNode_->next;
            delete temp;
        }
        size_ = 0;
    }

    void print(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << ": ";
        std::cout << "Stack(top -> bottom): [";
        Node* curr = topNode_;
        bool first = true;
        while (curr) {
            if (!first) std::cout << ", ";
            std::cout << curr->data;
            curr = curr->next;
            first = false;
        }
        std::cout << "]" << std::endl;
    }
};

// ============================================================
// Application: Decimal to Binary Conversion
// ============================================================

std::string decimalToBinary(int n) {
    if (n == 0) return "0";
    LinkedStack<int> stack;
    bool negative = n < 0;
    if (negative) n = -n;

    while (n > 0) {
        stack.push(n % 2);
        n /= 2;
    }

    std::string result = negative ? "-" : "";
    while (!stack.empty()) {
        result += std::to_string(stack.pop());
    }
    return result;
}

// ============================================================
// Application: String Reversal
// ============================================================

std::string reverseString(const std::string& s) {
    LinkedStack<char> stack;
    for (char c : s) stack.push(c);

    std::string reversed;
    while (!stack.empty()) reversed += stack.pop();
    return reversed;
}

// ============================================================
// Application: Tower of Hanoi
// ============================================================

void towerOfHanoi(int n, char from, char to, char aux, int& moveCount) {
    if (n == 1) {
        moveCount++;
        std::cout << "    Move disk 1 from " << from << " to " << to << std::endl;
        return;
    }
    towerOfHanoi(n - 1, from, aux, to, moveCount);
    moveCount++;
    std::cout << "    Move disk " << n << " from " << from << " to " << to << std::endl;
    towerOfHanoi(n - 1, aux, to, from, moveCount);
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Linked Stack Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // Basic operations
    std::cout << "\n--- Basic Operations ---" << std::endl;
    LinkedStack<int> stack;

    for (int i = 1; i <= 6; i++) {
        stack.push(i);
        std::cout << "Pushed " << i << std::endl;
    }
    stack.print("Stack");
    std::cout << "Size: " << stack.size() << std::endl;
    std::cout << "Top: " << stack.top() << std::endl;

    std::cout << "\nPopping all: ";
    while (!stack.empty()) {
        std::cout << stack.pop() << " ";
    }
    std::cout << std::endl;

    // String stack
    std::cout << "\n--- String Stack ---" << std::endl;
    LinkedStack<std::string> strStack;
    strStack.push("Hello");
    strStack.push("World");
    strStack.push("Data");
    strStack.push("Structures");
    strStack.print("String stack");

    // Decimal to binary
    std::cout << "\n--- Decimal to Binary ---" << std::endl;
    int values[] = {0, 1, 10, 42, 255, 1024};
    for (int v : values) {
        std::cout << "  " << v << " -> " << decimalToBinary(v) << std::endl;
    }

    // String reversal
    std::cout << "\n--- String Reversal ---" << std::endl;
    std::string strings[] = {"Hello", "Stack", "Data Structures"};
    for (const auto& s : strings) {
        std::cout << "  \"" << s << "\" -> \"" << reverseString(s) << "\"" << std::endl;
    }

    // Tower of Hanoi
    std::cout << "\n--- Tower of Hanoi (3 disks) ---" << std::endl;
    int moveCount = 0;
    towerOfHanoi(3, 'A', 'C', 'B', moveCount);
    std::cout << "  Total moves: " << moveCount
              << " (2^3 - 1 = " << (1 << 3) - 1 << ")" << std::endl;

    // Copy test
    std::cout << "\n--- Copy Test ---" << std::endl;
    LinkedStack<int> orig;
    orig.push(1); orig.push(2); orig.push(3);
    orig.print("Original");

    LinkedStack<int> copy(orig);
    copy.print("Copy");

    copy.push(99);
    orig.print("Original (unchanged)");
    copy.print("Copy (modified)");

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
