/**
 * @file    Lab_LeftistTree.cpp
 * @brief   Leftist tree (min leftist heap) with merge, insert, and deleteMin
 * @author  Cheolwon Park
 * @date    2025-06-02
 */

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

/**
 * @class LeftistTree
 * @brief Min leftist tree implementation
 *
 * A leftist tree is a binary tree where:
 * - Every node satisfies the min-tree property (parent <= children)
 * - s(left) >= s(right) for every node (leftist property)
 *
 * s-value = shortest path from node to an external (null) node.
 * All operations reduce to the merge operation.
 */
class LeftistTree {
private:
    struct Node {
        int key;
        int sValue; // Shortest path to external node
        Node* left;
        Node* right;

        Node(int k) : key(k), sValue(1), left(nullptr), right(nullptr) {}
    };

    Node* root_;

    /**
     * @brief Merge two leftist trees - O(log m + log n)
     *
     * The fundamental operation. Recursively merges along right paths,
     * then adjusts to maintain the leftist property.
     */
    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        // Ensure h1 has the smaller root (min leftist tree)
        if (h1->key > h2->key) {
            std::swap(h1, h2);
        }

        // Recursively merge h2 with the right subtree of h1
        h1->right = merge(h1->right, h2);

        // Maintain leftist property: s(left) >= s(right)
        if (!h1->left || (h1->right && h1->left->sValue < h1->right->sValue)) {
            std::swap(h1->left, h1->right);
        }

        // Update s-value
        h1->sValue = (h1->right ? h1->right->sValue : 0) + 1;

        return h1;
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void inorderPrint(Node* node, int depth) const {
        if (!node) return;
        inorderPrint(node->right, depth + 1);
        for (int i = 0; i < depth; i++) std::cout << "    ";
        std::cout << node->key << "(s=" << node->sValue << ")" << std::endl;
        inorderPrint(node->left, depth + 1);
    }

    int countNodes(Node* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    bool verifyLeftist(Node* node) const {
        if (!node) return true;

        int leftS = node->left ? node->left->sValue : 0;
        int rightS = node->right ? node->right->sValue : 0;

        if (leftS < rightS) return false;

        // Verify min-tree property
        if (node->left && node->key > node->left->key) return false;
        if (node->right && node->key > node->right->key) return false;

        return verifyLeftist(node->left) && verifyLeftist(node->right);
    }

public:
    LeftistTree() : root_(nullptr) {}
    ~LeftistTree() { destroy(root_); }

    /**
     * @brief Insert a new key - O(log n)
     *
     * Creates a single-node leftist tree and merges it with the current tree.
     */
    void insert(int key) {
        Node* newNode = new Node(key);
        root_ = merge(root_, newNode);
    }

    /**
     * @brief Remove and return the minimum element - O(log n)
     *
     * Removes the root and merges its left and right subtrees.
     */
    int deleteMin() {
        if (!root_)
            throw std::underflow_error("Leftist tree is empty");

        int minKey = root_->key;
        Node* oldRoot = root_;
        root_ = merge(root_->left, root_->right);
        delete oldRoot;
        return minKey;
    }

    /**
     * @brief Return the minimum element without removing - O(1)
     */
    int findMin() const {
        if (!root_)
            throw std::underflow_error("Leftist tree is empty");
        return root_->key;
    }

    /**
     * @brief Merge another leftist tree into this one - O(log m + log n)
     *
     * After merging, the other tree becomes empty.
     */
    void mergeWith(LeftistTree& other) {
        root_ = merge(root_, other.root_);
        other.root_ = nullptr;
    }

    bool empty() const { return root_ == nullptr; }
    int size() const { return countNodes(root_); }

    void display() const {
        if (!root_) {
            std::cout << "(empty)" << std::endl;
            return;
        }
        inorderPrint(root_, 0);
    }

    bool isValid() const { return verifyLeftist(root_); }
};

// ============================================================
// Main: Demonstrate leftist tree operations
// ============================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Leftist Tree Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // Build first leftist tree
    std::cout << "\n--- Building Leftist Tree 1 ---" << std::endl;
    LeftistTree lt1;
    int keys1[] = {10, 5, 20, 3, 15, 8};
    for (int k : keys1) {
        lt1.insert(k);
        std::cout << "Inserted " << k << ", min = " << lt1.findMin() << std::endl;
    }

    std::cout << "\nTree 1 structure:" << std::endl;
    lt1.display();
    std::cout << "Valid leftist tree: " << (lt1.isValid() ? "YES" : "NO") << std::endl;
    std::cout << "Size: " << lt1.size() << std::endl;

    // Build second leftist tree
    std::cout << "\n--- Building Leftist Tree 2 ---" << std::endl;
    LeftistTree lt2;
    int keys2[] = {7, 12, 1, 25};
    for (int k : keys2) {
        lt2.insert(k);
    }

    std::cout << "Tree 2 structure:" << std::endl;
    lt2.display();

    // Merge two trees
    std::cout << "\n--- Merging Tree 1 and Tree 2 ---" << std::endl;
    lt1.mergeWith(lt2);
    std::cout << "Merged tree structure:" << std::endl;
    lt1.display();
    std::cout << "Min: " << lt1.findMin() << std::endl;
    std::cout << "Size: " << lt1.size() << std::endl;
    std::cout << "Valid: " << (lt1.isValid() ? "YES" : "NO") << std::endl;

    // DeleteMin operations
    std::cout << "\n--- DeleteMin Operations ---" << std::endl;
    while (!lt1.empty()) {
        int min = lt1.deleteMin();
        std::cout << "Deleted min: " << min;
        if (!lt1.empty()) {
            std::cout << ", next min: " << lt1.findMin();
        }
        std::cout << std::endl;
    }

    // Verify the elements come out in sorted order
    std::cout << "\n--- Verify: Insert and Extract (should be sorted) ---" << std::endl;
    LeftistTree lt3;
    int unsorted[] = {42, 17, 3, 88, 25, 1, 56, 9};
    for (int k : unsorted) lt3.insert(k);

    std::cout << "Sorted output: ";
    while (!lt3.empty()) {
        std::cout << lt3.deleteMin() << " ";
    }
    std::cout << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
