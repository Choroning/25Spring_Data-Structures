/**
 * @file    Lab_BinarySearchTree.cpp
 * @brief   Binary search tree with insert, search, delete, and inorder traversal
 * @author  Cheolwon Park
 * @date    2025-06-09
 */

#include <iostream>
#include <queue>
#include <stdexcept>

/**
 * @class BST
 * @brief Linked representation of a binary search tree
 *
 * BST property: for every node, left subtree keys < node key < right subtree keys.
 * All keys are distinct. Inorder traversal produces sorted output.
 *
 * Operations:
 * - Search: O(h)
 * - Insert: O(h)
 * - Delete: O(h)   (three cases: leaf, degree 1, degree 2)
 * - Inorder: O(n)
 *
 * where h is the height (best O(log n), worst O(n)).
 */
template <typename T>
class BST {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        Node(const T& k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root_;
    int size_;

    /**
     * @brief Recursive search - O(h)
     */
    Node* search(Node* node, const T& key) const {
        if (!node || node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    /**
     * @brief Recursive insert - O(h)
     */
    Node* insert(Node* node, const T& key) {
        if (!node) {
            size_++;
            return new Node(key);
        }
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        // Duplicate keys are ignored
        return node;
    }

    /**
     * @brief Find the node with the minimum key in a subtree
     */
    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    /**
     * @brief Find the node with the maximum key in a subtree
     */
    Node* findMax(Node* node) const {
        while (node && node->right) node = node->right;
        return node;
    }

    /**
     * @brief Recursive delete - O(h)
     *
     * Three cases:
     * 1. Leaf: simply remove
     * 2. Degree 1: replace with the single child
     * 3. Degree 2: replace with inorder successor (smallest in right subtree)
     */
    Node* remove(Node* node, const T& key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            // Found the node to delete

            // Case 1 & 2: Node has 0 or 1 child
            if (!node->left) {
                Node* rightChild = node->right;
                delete node;
                size_--;
                return rightChild;
            }
            if (!node->right) {
                Node* leftChild = node->left;
                delete node;
                size_--;
                return leftChild;
            }

            // Case 3: Node has 2 children
            // Replace with inorder successor (smallest in right subtree)
            Node* successor = findMin(node->right);
            node->key = successor->key;
            node->right = remove(node->right, successor->key);
        }
        return node;
    }

    /**
     * @brief Inorder traversal (left, root, right) - produces sorted output
     */
    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        std::cout << node->key << " ";
        inorder(node->right);
    }

    /**
     * @brief Preorder traversal (root, left, right)
     */
    void preorder(Node* node) const {
        if (!node) return;
        std::cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }

    /**
     * @brief Compute tree height
     */
    int height(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(height(node->left), height(node->right));
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    /**
     * @brief Print tree structure with indentation
     */
    void printTree(Node* node, std::string prefix, bool isLeft) const {
        if (!node) return;
        std::cout << prefix;
        std::cout << (isLeft ? "|-- " : "\\-- ");
        std::cout << node->key << std::endl;
        printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
        printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
    }

public:
    BST() : root_(nullptr), size_(0) {}
    ~BST() { destroy(root_); }

    void insert(const T& key) { root_ = insert(root_, key); }

    bool search(const T& key) const { return search(root_, key) != nullptr; }

    void remove(const T& key) { root_ = remove(root_, key); }

    T findMin() const {
        Node* minNode = findMin(root_);
        if (!minNode) throw std::underflow_error("BST is empty");
        return minNode->key;
    }

    T findMax() const {
        Node* maxNode = findMax(root_);
        if (!maxNode) throw std::underflow_error("BST is empty");
        return maxNode->key;
    }

    void inorder() const {
        inorder(root_);
        std::cout << std::endl;
    }

    void preorder() const {
        preorder(root_);
        std::cout << std::endl;
    }

    /**
     * @brief Level-order traversal using a queue
     */
    void levelOrder() const {
        if (!root_) return;
        std::queue<Node*> q;
        q.push(root_);
        while (!q.empty()) {
            Node* node = q.front(); q.pop();
            std::cout << node->key << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        std::cout << std::endl;
    }

    int height() const { return height(root_); }
    int size() const { return size_; }
    bool empty() const { return root_ == nullptr; }

    void printTree() const {
        if (!root_) {
            std::cout << "(empty)" << std::endl;
            return;
        }
        printTree(root_, "", false);
    }
};

// ============================================================
// Main: Demonstrate BST operations
// ============================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Binary Search Tree Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    BST<int> bst;

    // Insert operations
    std::cout << "\n--- Insert Operations ---" << std::endl;
    int keys[] = {20, 10, 40, 6, 15, 30, 25, 35, 8, 18};
    for (int k : keys) {
        bst.insert(k);
        std::cout << "Inserted " << k << std::endl;
    }

    std::cout << "\nTree structure:" << std::endl;
    bst.printTree();

    std::cout << "\nInorder (sorted):  ";
    bst.inorder();

    std::cout << "Preorder:          ";
    bst.preorder();

    std::cout << "Level-order:       ";
    bst.levelOrder();

    std::cout << "Height: " << bst.height() << std::endl;
    std::cout << "Size:   " << bst.size() << std::endl;
    std::cout << "Min:    " << bst.findMin() << std::endl;
    std::cout << "Max:    " << bst.findMax() << std::endl;

    // Search operations
    std::cout << "\n--- Search Operations ---" << std::endl;
    int searchKeys[] = {15, 25, 7, 40, 100};
    for (int k : searchKeys) {
        std::cout << "Search " << k << ": "
                  << (bst.search(k) ? "FOUND" : "NOT FOUND") << std::endl;
    }

    // Delete operations - all three cases
    std::cout << "\n--- Delete Case 1: Leaf (delete 8) ---" << std::endl;
    bst.remove(8);
    bst.printTree();

    std::cout << "\n--- Delete Case 2: Degree 1 (delete 6, has no right child after 8 removed) ---" << std::endl;
    bst.remove(6);
    bst.printTree();

    std::cout << "\n--- Delete Case 3: Degree 2 (delete 20, root) ---" << std::endl;
    bst.remove(20);
    std::cout << "After deleting root 20 (replaced by inorder successor 25):" << std::endl;
    bst.printTree();

    std::cout << "\nInorder after deletions: ";
    bst.inorder();

    std::cout << "Height: " << bst.height() << std::endl;
    std::cout << "Size:   " << bst.size() << std::endl;

    // Worst-case: sorted insertion
    std::cout << "\n--- Worst Case: Sorted Insertion ---" << std::endl;
    BST<int> skewedBST;
    for (int i = 1; i <= 7; i++) {
        skewedBST.insert(i);
    }
    std::cout << "Inserting 1,2,3,4,5,6,7 produces a right-skewed tree:" << std::endl;
    skewedBST.printTree();
    std::cout << "Height (should be 7): " << skewedBST.height() << std::endl;

    // Duplicate insertion test
    std::cout << "\n--- Duplicate Insertion ---" << std::endl;
    BST<int> dupTest;
    dupTest.insert(10);
    dupTest.insert(10); // Should be ignored
    std::cout << "After inserting 10 twice, size = " << dupTest.size() << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
