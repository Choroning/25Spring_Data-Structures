/**
 * @file    BPlusTree.h
 * @brief   B+ tree header: insert, delete, search, range query
 * @author  Cheolwon Park
 * @date    2025-06-16
 */

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

/**
 * @class BPlusTree
 * @brief B+ tree index structure for database-style key lookups
 *
 * Properties:
 * - All data resides in leaf nodes (internal nodes hold only keys for routing)
 * - Leaf nodes are linked for efficient range queries
 * - Order M: internal nodes have at most M children and M-1 keys
 * - Each internal node (except root) has at least ceil(M/2) children
 * - Each leaf node holds at most M-1 key-value pairs
 *
 * Time complexity:
 * - Search: O(log_M n)
 * - Insert: O(log_M n)
 * - Delete: O(log_M n)
 * - Range query: O(log_M n + k) where k is the number of results
 */
template <int ORDER = 4>
class BPlusTree {
public:
    struct Node {
        bool isLeaf;
        std::vector<int> keys;
        std::vector<Node*> children;  // Internal nodes only
        std::vector<int> values;      // Leaf nodes only (stores values)
        Node* next;                   // Leaf linked list pointer

        Node(bool leaf) : isLeaf(leaf), next(nullptr) {}
    };

private:
    Node* root_;
    int size_;

    /**
     * @brief Find the leaf node where a key should reside
     */
    Node* findLeaf(int key) const;

    /**
     * @brief Insert into a leaf node, splitting if necessary
     */
    void insertIntoLeaf(Node* leaf, int key, int value);

    /**
     * @brief Insert into parent after a child split
     */
    void insertIntoParent(Node* left, int key, Node* right);

    /**
     * @brief Split a full leaf node
     */
    void splitLeaf(Node* leaf);

    /**
     * @brief Split a full internal node
     */
    void splitInternal(Node* node);

    /**
     * @brief Find the parent of a given node
     */
    Node* findParent(Node* current, Node* child) const;

    /**
     * @brief Remove a key from a leaf node
     */
    bool removeFromLeaf(Node* leaf, int key);

    /**
     * @brief Fix underflow after deletion
     */
    void fixUnderflow(Node* node);

    /**
     * @brief Print tree structure recursively
     */
    void printNode(Node* node, int level) const;

    /**
     * @brief Destroy the tree recursively
     */
    void destroy(Node* node);

public:
    BPlusTree();
    ~BPlusTree();

    /**
     * @brief Search for a key - O(log_M n)
     * @return Pointer to the value if found, nullptr otherwise
     */
    int* search(int key);

    /**
     * @brief Insert a key-value pair - O(log_M n)
     */
    void insert(int key, int value);

    /**
     * @brief Delete a key - O(log_M n)
     * @return true if key was found and deleted
     */
    bool remove(int key);

    /**
     * @brief Range query: find all keys in [low, high] - O(log_M n + k)
     * @return Vector of (key, value) pairs in the range
     */
    std::vector<std::pair<int, int>> rangeQuery(int low, int high) const;

    /**
     * @brief Display the tree structure
     */
    void display() const;

    int size() const { return size_; }
    bool empty() const { return size_ == 0; }
};

#endif // BPLUSTREE_H
