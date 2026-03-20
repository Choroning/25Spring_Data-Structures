/**
 * @file    BPlusTree.cpp
 * @brief   B+ tree implementation: insert, delete, search, range query
 * @author  Cheolwon Park
 * @date    2025-06-16
 */

#include "BPlusTree.h"
#include <cassert>

// ============================================================
// Constructor / Destructor
// ============================================================

template <int ORDER>
BPlusTree<ORDER>::BPlusTree() : root_(nullptr), size_(0) {}

template <int ORDER>
BPlusTree<ORDER>::~BPlusTree() {
    destroy(root_);
}

template <int ORDER>
void BPlusTree<ORDER>::destroy(Node* node) {
    if (!node) return;
    if (!node->isLeaf) {
        for (auto* child : node->children) {
            destroy(child);
        }
    }
    delete node;
}

// ============================================================
// Search
// ============================================================

template <int ORDER>
typename BPlusTree<ORDER>::Node* BPlusTree<ORDER>::findLeaf(int key) const {
    if (!root_) return nullptr;

    Node* current = root_;
    while (!current->isLeaf) {
        int i = 0;
        while (i < static_cast<int>(current->keys.size()) && key >= current->keys[i]) {
            i++;
        }
        current = current->children[i];
    }
    return current;
}

template <int ORDER>
int* BPlusTree<ORDER>::search(int key) {
    Node* leaf = findLeaf(key);
    if (!leaf) return nullptr;

    for (int i = 0; i < static_cast<int>(leaf->keys.size()); i++) {
        if (leaf->keys[i] == key) {
            return &leaf->values[i];
        }
    }
    return nullptr;
}

// ============================================================
// Insert
// ============================================================

template <int ORDER>
void BPlusTree<ORDER>::insert(int key, int value) {
    // Empty tree: create root as leaf
    if (!root_) {
        root_ = new Node(true);
        root_->keys.push_back(key);
        root_->values.push_back(value);
        size_++;
        return;
    }

    Node* leaf = findLeaf(key);

    // Check for duplicate
    for (int i = 0; i < static_cast<int>(leaf->keys.size()); i++) {
        if (leaf->keys[i] == key) {
            leaf->values[i] = value; // Update existing
            return;
        }
    }

    insertIntoLeaf(leaf, key, value);
    size_++;
}

template <int ORDER>
void BPlusTree<ORDER>::insertIntoLeaf(Node* leaf, int key, int value) {
    // Find insertion position
    auto it = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
    int pos = it - leaf->keys.begin();
    leaf->keys.insert(it, key);
    leaf->values.insert(leaf->values.begin() + pos, value);

    // Check if leaf overflows
    if (static_cast<int>(leaf->keys.size()) >= ORDER) {
        splitLeaf(leaf);
    }
}

template <int ORDER>
void BPlusTree<ORDER>::splitLeaf(Node* leaf) {
    int mid = leaf->keys.size() / 2;

    Node* newLeaf = new Node(true);
    newLeaf->keys.assign(leaf->keys.begin() + mid, leaf->keys.end());
    newLeaf->values.assign(leaf->values.begin() + mid, leaf->values.end());

    leaf->keys.resize(mid);
    leaf->values.resize(mid);

    // Maintain linked list
    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    int newKey = newLeaf->keys[0]; // Copy up the first key of the new leaf

    insertIntoParent(leaf, newKey, newLeaf);
}

template <int ORDER>
void BPlusTree<ORDER>::insertIntoParent(Node* left, int key, Node* right) {
    // If left is root, create new root
    if (left == root_) {
        Node* newRoot = new Node(false);
        newRoot->keys.push_back(key);
        newRoot->children.push_back(left);
        newRoot->children.push_back(right);
        root_ = newRoot;
        return;
    }

    Node* parent = findParent(root_, left);

    // Find position in parent
    auto it = std::lower_bound(parent->keys.begin(), parent->keys.end(), key);
    int pos = it - parent->keys.begin();
    parent->keys.insert(it, key);
    parent->children.insert(parent->children.begin() + pos + 1, right);

    // Check if parent overflows
    if (static_cast<int>(parent->keys.size()) >= ORDER) {
        splitInternal(parent);
    }
}

template <int ORDER>
void BPlusTree<ORDER>::splitInternal(Node* node) {
    int mid = node->keys.size() / 2;
    int pushUpKey = node->keys[mid];

    Node* newNode = new Node(false);
    newNode->keys.assign(node->keys.begin() + mid + 1, node->keys.end());
    newNode->children.assign(node->children.begin() + mid + 1, node->children.end());

    node->keys.resize(mid);
    node->children.resize(mid + 1);

    insertIntoParent(node, pushUpKey, newNode);
}

template <int ORDER>
typename BPlusTree<ORDER>::Node* BPlusTree<ORDER>::findParent(Node* current, Node* child) const {
    if (!current || current->isLeaf) return nullptr;

    for (auto* c : current->children) {
        if (c == child) return current;
        Node* result = findParent(c, child);
        if (result) return result;
    }
    return nullptr;
}

// ============================================================
// Delete
// ============================================================

template <int ORDER>
bool BPlusTree<ORDER>::remove(int key) {
    Node* leaf = findLeaf(key);
    if (!leaf) return false;

    if (!removeFromLeaf(leaf, key)) return false;

    size_--;

    // If root is empty
    if (root_->keys.empty()) {
        if (root_->isLeaf) {
            delete root_;
            root_ = nullptr;
        } else if (root_->children.size() == 1) {
            Node* oldRoot = root_;
            root_ = root_->children[0];
            delete oldRoot;
        }
    }

    return true;
}

template <int ORDER>
bool BPlusTree<ORDER>::removeFromLeaf(Node* leaf, int key) {
    auto it = std::find(leaf->keys.begin(), leaf->keys.end(), key);
    if (it == leaf->keys.end()) return false;

    int pos = it - leaf->keys.begin();
    leaf->keys.erase(it);
    leaf->values.erase(leaf->values.begin() + pos);
    return true;
}

// ============================================================
// Range Query
// ============================================================

template <int ORDER>
std::vector<std::pair<int, int>> BPlusTree<ORDER>::rangeQuery(int low, int high) const {
    std::vector<std::pair<int, int>> result;

    Node* leaf = findLeaf(low);
    if (!leaf) return result;

    // Walk through leaves using linked list
    while (leaf) {
        for (int i = 0; i < static_cast<int>(leaf->keys.size()); i++) {
            if (leaf->keys[i] >= low && leaf->keys[i] <= high) {
                result.push_back({leaf->keys[i], leaf->values[i]});
            }
            if (leaf->keys[i] > high) return result;
        }
        leaf = leaf->next;
    }

    return result;
}

// ============================================================
// Display
// ============================================================

template <int ORDER>
void BPlusTree<ORDER>::display() const {
    if (!root_) {
        std::cout << "(empty tree)" << std::endl;
        return;
    }
    printNode(root_, 0);

    // Print leaf chain
    std::cout << "Leaf chain: ";
    Node* leaf = root_;
    while (leaf && !leaf->isLeaf) leaf = leaf->children[0];
    while (leaf) {
        std::cout << "[";
        for (int i = 0; i < static_cast<int>(leaf->keys.size()); i++) {
            if (i > 0) std::cout << ",";
            std::cout << leaf->keys[i];
        }
        std::cout << "] -> ";
        leaf = leaf->next;
    }
    std::cout << "NULL" << std::endl;
}

template <int ORDER>
void BPlusTree<ORDER>::printNode(Node* node, int level) const {
    if (!node) return;

    std::string indent(level * 4, ' ');
    std::cout << indent << (node->isLeaf ? "Leaf" : "Internal") << "[";
    for (int i = 0; i < static_cast<int>(node->keys.size()); i++) {
        if (i > 0) std::cout << ",";
        std::cout << node->keys[i];
    }
    std::cout << "]" << std::endl;

    if (!node->isLeaf) {
        for (auto* child : node->children) {
            printNode(child, level + 1);
        }
    }
}

// Explicit template instantiation
template class BPlusTree<3>;
template class BPlusTree<4>;
template class BPlusTree<5>;
