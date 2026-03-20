/**
 * @file    Lab_ArrayStack.cpp
 * @brief   Array-based stack ADT with dynamic resizing and applications
 * @author  Cheolwon Park
 * @date    2025-04-07
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>

/**
 * @class ArrayStack
 * @brief Template-based stack using a dynamic array
 */
template <typename T>
class ArrayStack {
private:
    T* data_;
    int topIndex_;
    int capacity_;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i <= topIndex_; i++)
            newData[i] = data_[i];
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

public:
    explicit ArrayStack(int capacity = 16)
        : topIndex_(-1), capacity_(capacity) {
        data_ = new T[capacity_];
    }

    ArrayStack(const ArrayStack& other)
        : topIndex_(other.topIndex_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (int i = 0; i <= topIndex_; i++)
            data_[i] = other.data_[i];
    }

    ArrayStack& operator=(const ArrayStack& other) {
        if (this != &other) {
            delete[] data_;
            topIndex_ = other.topIndex_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            for (int i = 0; i <= topIndex_; i++)
                data_[i] = other.data_[i];
        }
        return *this;
    }

    ~ArrayStack() { delete[] data_; }

    bool empty() const { return topIndex_ == -1; }
    int size() const { return topIndex_ + 1; }

    /**
     * @brief Push an element onto the top of the stack - O(1) amortized
     */
    void push(const T& element) {
        if (topIndex_ + 1 == capacity_)
            resize(2 * capacity_);
        data_[++topIndex_] = element;
    }

    /**
     * @brief Remove and return the top element - O(1)
     * @throws std::underflow_error if stack is empty
     */
    T pop() {
        if (empty())
            throw std::underflow_error("Stack underflow");
        return data_[topIndex_--];
    }

    /**
     * @brief Return the top element without removing - O(1)
     */
    const T& top() const {
        if (empty())
            throw std::underflow_error("Stack is empty");
        return data_[topIndex_];
    }

    void clear() { topIndex_ = -1; }

    void print(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << ": ";
        std::cout << "Stack(top -> bottom): [";
        for (int i = topIndex_; i >= 0; i--) {
            if (i < topIndex_) std::cout << ", ";
            std::cout << data_[i];
        }
        std::cout << "]" << std::endl;
    }
};

// ============================================================
// Application: Parentheses Matching
// ============================================================

bool isBalanced(const std::string& expr) {
    ArrayStack<char> stack;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stack.empty()) return false;
            char t = stack.pop();
            if ((c == ')' && t != '(') ||
                (c == ']' && t != '[') ||
                (c == '}' && t != '{'))
                return false;
        }
    }
    return stack.empty();
}

// ============================================================
// Application: Infix to Postfix Conversion
// ============================================================

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

std::string infixToPostfix(const std::string& infix) {
    ArrayStack<char> stack;
    std::string postfix;

    for (char c : infix) {
        if (c == ' ') continue;

        if (std::isalnum(c)) {
            postfix += c;
            postfix += ' ';
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.pop();
                postfix += ' ';
            }
            if (!stack.empty()) stack.pop(); // Remove '('
        } else { // Operator
            while (!stack.empty() && stack.top() != '(' &&
                   precedence(stack.top()) >= precedence(c)) {
                postfix += stack.pop();
                postfix += ' ';
            }
            stack.push(c);
        }
    }

    while (!stack.empty()) {
        postfix += stack.pop();
        postfix += ' ';
    }

    return postfix;
}

// ============================================================
// Application: Postfix Expression Evaluation
// ============================================================

double evaluatePostfix(const std::string& postfix) {
    ArrayStack<double> stack;
    std::istringstream iss(postfix);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            stack.push(std::stod(token));
        } else {
            double b = stack.pop();
            double a = stack.pop();
            switch (token[0]) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
                case '^': stack.push(std::pow(a, b)); break;
            }
        }
    }
    return stack.top();
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Array Stack Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // Basic operations
    std::cout << "\n--- Basic Operations ---" << std::endl;
    ArrayStack<int> stack;
    for (int i = 1; i <= 5; i++) {
        stack.push(i * 10);
        std::cout << "Pushed " << i * 10 << std::endl;
    }
    stack.print("Current stack");

    std::cout << "Top: " << stack.top() << std::endl;
    std::cout << "Popped: " << stack.pop() << std::endl;
    std::cout << "Popped: " << stack.pop() << std::endl;
    stack.print("After two pops");

    // Parentheses matching
    std::cout << "\n--- Parentheses Matching ---" << std::endl;
    std::string exprs[] = {"{[()]}", "{[(])}", "((()))", "(()", "}{", ""};
    for (const auto& e : exprs) {
        std::cout << "  \"" << e << "\" -> "
                  << (isBalanced(e) ? "Balanced" : "Not balanced") << std::endl;
    }

    // Infix to postfix
    std::cout << "\n--- Infix to Postfix ---" << std::endl;
    std::string infixExprs[] = {
        "A+B*C",
        "(A+B)*C",
        "A+B*C-D/E",
        "A*(B+C)/D"
    };
    for (const auto& e : infixExprs) {
        std::cout << "  Infix:   " << e << std::endl;
        std::cout << "  Postfix: " << infixToPostfix(e) << std::endl;
    }

    // Postfix evaluation
    std::cout << "\n--- Postfix Evaluation ---" << std::endl;
    std::string postfixExprs[] = {
        "3 4 + 2 *",    // (3+4)*2 = 14
        "5 1 2 + 4 * + 3 -",  // 5+((1+2)*4)-3 = 14
        "2 3 ^ 1 -"     // 2^3-1 = 7
    };
    for (const auto& e : postfixExprs) {
        std::cout << "  \"" << e << "\" = " << evaluatePostfix(e) << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
