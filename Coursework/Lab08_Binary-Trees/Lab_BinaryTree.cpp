/**
 * @file    Lab_BinaryTree.cpp
 * @brief   Binary tree with all four traversals and expression tree evaluation
 * @author  Cheolwon Park
 * @date    2025-05-26
 */

#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>

// ============================================================
// Part 1: General Binary Tree with Four Traversals
// ============================================================

/**
 * @class BinaryTree
 * @brief Linked representation of a binary tree with traversal methods
 */
template <typename T>
class BinaryTree {
public:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    BinaryTree() : root(nullptr) {}

    ~BinaryTree() { destroy(root); }

    /**
     * @brief Preorder traversal: root, left, right - O(n)
     */
    void preorder(Node* node) const {
        if (!node) return;
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    /**
     * @brief Inorder traversal: left, root, right - O(n)
     */
    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    /**
     * @brief Postorder traversal: left, right, root - O(n)
     */
    void postorder(Node* node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }

    /**
     * @brief Level-order traversal using a queue - O(n)
     */
    void levelOrder() const {
        if (!root) return;
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            std::cout << current->data << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

    /**
     * @brief Compute the height of the tree - O(n)
     */
    int height(Node* node) const {
        if (!node) return 0;
        int leftH = height(node->left);
        int rightH = height(node->right);
        return 1 + std::max(leftH, rightH);
    }

    /**
     * @brief Count the number of nodes - O(n)
     */
    int size(Node* node) const {
        if (!node) return 0;
        return 1 + size(node->left) + size(node->right);
    }

private:
    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

// ============================================================
// Part 2: Expression Tree
// ============================================================

/**
 * @class ExpressionTree
 * @brief Binary tree for arithmetic expressions with evaluation
 *
 * Internal nodes are operators, leaf nodes are operands (integers).
 * Supports building from postfix and evaluation.
 */
class ExpressionTree {
private:
    struct Node {
        std::string data;
        Node* left;
        Node* right;
        Node(const std::string& val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root_;

    bool isOperator(const std::string& token) const {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    /**
     * @brief Recursively evaluate the expression tree
     */
    double evaluate(Node* node) const {
        if (!node) return 0;

        // Leaf node: operand
        if (!node->left && !node->right) {
            return std::stod(node->data);
        }

        double leftVal = evaluate(node->left);
        double rightVal = evaluate(node->right);

        if (node->data == "+") return leftVal + rightVal;
        if (node->data == "-") return leftVal - rightVal;
        if (node->data == "*") return leftVal * rightVal;
        if (node->data == "/") {
            if (rightVal == 0) throw std::runtime_error("Division by zero");
            return leftVal / rightVal;
        }

        throw std::runtime_error("Unknown operator: " + node->data);
    }

    void inorderParen(Node* node) const {
        if (!node) return;
        if (isOperator(node->data)) std::cout << "(";
        inorderParen(node->left);
        std::cout << node->data;
        inorderParen(node->right);
        if (isOperator(node->data)) std::cout << ")";
    }

    void preorderPrint(Node* node) const {
        if (!node) return;
        std::cout << node->data << " ";
        preorderPrint(node->left);
        preorderPrint(node->right);
    }

    void postorderPrint(Node* node) const {
        if (!node) return;
        postorderPrint(node->left);
        postorderPrint(node->right);
        std::cout << node->data << " ";
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    ExpressionTree() : root_(nullptr) {}
    ~ExpressionTree() { destroy(root_); }

    /**
     * @brief Build expression tree from a postfix expression string
     * @param postfix Space-separated postfix expression (e.g., "3 5 + 2 * 7 -")
     */
    void buildFromPostfix(const std::string& postfix) {
        destroy(root_);
        root_ = nullptr;

        std::stack<Node*> stk;
        std::istringstream iss(postfix);
        std::string token;

        while (iss >> token) {
            if (isOperator(token)) {
                Node* node = new Node(token);
                node->right = stk.top(); stk.pop();
                node->left = stk.top(); stk.pop();
                stk.push(node);
            } else {
                stk.push(new Node(token));
            }
        }

        if (!stk.empty()) {
            root_ = stk.top();
            stk.pop();
        }
    }

    double evaluate() const { return evaluate(root_); }

    void printPrefix() const {
        std::cout << "Prefix:  ";
        preorderPrint(root_);
        std::cout << std::endl;
    }

    void printInfix() const {
        std::cout << "Infix:   ";
        inorderParen(root_);
        std::cout << std::endl;
    }

    void printPostfix() const {
        std::cout << "Postfix: ";
        postorderPrint(root_);
        std::cout << std::endl;
    }
};

// ============================================================
// Main: Demonstrate binary tree and expression tree
// ============================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Binary Tree Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // Build a sample binary tree manually
    //         A
    //        / \
    //       B   C
    //      / \   \
    //     D   E   F
    using Node = BinaryTree<char>::Node;
    BinaryTree<char> bt;
    bt.root = new Node('A');
    bt.root->left = new Node('B');
    bt.root->right = new Node('C');
    bt.root->left->left = new Node('D');
    bt.root->left->right = new Node('E');
    bt.root->right->right = new Node('F');

    std::cout << "\nTree structure:" << std::endl;
    std::cout << "        A" << std::endl;
    std::cout << "       / \\" << std::endl;
    std::cout << "      B   C" << std::endl;
    std::cout << "     / \\   \\" << std::endl;
    std::cout << "    D   E   F" << std::endl;

    std::cout << "\nPreorder:    ";
    bt.preorder(bt.root);
    std::cout << std::endl;

    std::cout << "Inorder:     ";
    bt.inorder(bt.root);
    std::cout << std::endl;

    std::cout << "Postorder:   ";
    bt.postorder(bt.root);
    std::cout << std::endl;

    std::cout << "Level-order: ";
    bt.levelOrder();
    std::cout << std::endl;

    std::cout << "Height: " << bt.height(bt.root) << std::endl;
    std::cout << "Size:   " << bt.size(bt.root) << std::endl;

    // Expression Tree demonstration
    std::cout << "\n========================================" << std::endl;
    std::cout << "   Expression Tree Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // Expression: 3 + ((5 + 9) * 2) = 3 + 28 = 31
    // Postfix: 3 5 9 + 2 * +
    ExpressionTree et1;
    et1.buildFromPostfix("3 5 9 + 2 * +");

    std::cout << "\nExpression: 3 + ((5 + 9) * 2)" << std::endl;
    et1.printPrefix();
    et1.printInfix();
    et1.printPostfix();
    std::cout << "Result: " << et1.evaluate() << std::endl;

    // Expression: (a*b) + (c/d) with numeric values
    // (6 * 3) + (8 / 2) = 18 + 4 = 22
    // Postfix: 6 3 * 8 2 / +
    ExpressionTree et2;
    et2.buildFromPostfix("6 3 * 8 2 / +");

    std::cout << "\nExpression: (6 * 3) + (8 / 2)" << std::endl;
    et2.printPrefix();
    et2.printInfix();
    et2.printPostfix();
    std::cout << "Result: " << et2.evaluate() << std::endl;

    // Expression: 3 5 + 2 * 7 -  =>  (3+5)*2 - 7 = 9
    ExpressionTree et3;
    et3.buildFromPostfix("3 5 + 2 * 7 -");

    std::cout << "\nExpression: ((3 + 5) * 2) - 7" << std::endl;
    et3.printPrefix();
    et3.printInfix();
    et3.printPostfix();
    std::cout << "Result: " << et3.evaluate() << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
