/**
 * @file    HuffmanTree.cpp
 * @brief   Huffman tree construction and encoding/decoding implementation
 * @author  Cheolwon Park
 * @date    2025-06-16
 */

#include "HuffmanTree.h"
#include "PriorityQueue.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// ============================================================
// Constructor / Destructor
// ============================================================

HuffmanTree::HuffmanTree() : root_(nullptr) {}

HuffmanTree::~HuffmanTree() {
    destroy(root_);
}

void HuffmanTree::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

// ============================================================
// Build Huffman Tree
// ============================================================

void HuffmanTree::buildFromFrequencies(const std::unordered_map<char, int>& freqMap) {
    destroy(root_);
    root_ = nullptr;
    codeTable_.clear();
    freqTable_ = freqMap;

    if (freqMap.empty()) return;

    // Comparator: lower frequency has higher priority (min-heap)
    auto cmp = [](Node* a, Node* b) { return a->freq < b->freq; };
    MinPriorityQueue<Node*, decltype(cmp)> pq(cmp);

    // Create leaf nodes
    for (const auto& pair : freqMap) {
        pq.insert(new Node(pair.first, pair.second));
    }

    // Special case: single character
    if (pq.size() == 1) {
        Node* only = pq.extractMin();
        root_ = new Node(only->freq, only, nullptr);
        generateCodes(root_, "");
        return;
    }

    // Build tree by repeatedly merging two smallest nodes
    while (pq.size() > 1) {
        Node* left = pq.extractMin();
        Node* right = pq.extractMin();
        Node* parent = new Node(left->freq + right->freq, left, right);
        pq.insert(parent);
    }

    root_ = pq.extractMin();
    generateCodes(root_, "");
}

void HuffmanTree::buildFromText(const std::string& text) {
    std::unordered_map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }
    buildFromFrequencies(freqMap);
}

// ============================================================
// Generate Codes
// ============================================================

void HuffmanTree::generateCodes(Node* node, const std::string& code) {
    if (!node) return;

    // Leaf node: assign code
    if (!node->left && !node->right) {
        codeTable_[node->ch] = code.empty() ? "0" : code;
        return;
    }

    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

// ============================================================
// Encode / Decode
// ============================================================

std::string HuffmanTree::encode(const std::string& text) const {
    std::string encoded;
    for (char c : text) {
        auto it = codeTable_.find(c);
        if (it != codeTable_.end()) {
            encoded += it->second;
        }
    }
    return encoded;
}

std::string HuffmanTree::decode(const std::string& bits) const {
    if (!root_) return "";

    std::string decoded;
    Node* current = root_;

    for (char bit : bits) {
        if (bit == '0')
            current = current->left;
        else
            current = current->right;

        // Reached a leaf
        if (!current->left && !current->right) {
            decoded += current->ch;
            current = root_;
        }
    }

    return decoded;
}

// ============================================================
// Utility
// ============================================================

const std::unordered_map<char, std::string>& HuffmanTree::getCodeTable() const {
    return codeTable_;
}

const std::unordered_map<char, int>& HuffmanTree::getFreqTable() const {
    return freqTable_;
}

double HuffmanTree::compressionRatio(size_t originalBits, size_t compressedBits) {
    if (originalBits == 0) return 0.0;
    return (1.0 - static_cast<double>(compressedBits) / originalBits) * 100.0;
}

void HuffmanTree::display() const {
    std::cout << "\n--- Frequency Table ---" << std::endl;
    // Sort by frequency for display
    std::vector<std::pair<char, int>> freqs(freqTable_.begin(), freqTable_.end());
    std::sort(freqs.begin(), freqs.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    for (const auto& p : freqs) {
        std::string ch;
        if (p.first == ' ') ch = "SPACE";
        else if (p.first == '\n') ch = "\\n";
        else ch = std::string(1, p.first);

        std::cout << "  " << std::setw(6) << std::left << ch
                  << " freq=" << std::setw(4) << p.second;

        auto it = codeTable_.find(p.first);
        if (it != codeTable_.end()) {
            std::cout << "  code=" << it->second
                      << " (" << it->second.length() << " bits)";
        }
        std::cout << std::endl;
    }

    std::cout << "\n--- Huffman Tree ---" << std::endl;
    printTree(root_, "", false);
}

void HuffmanTree::printTree(Node* node, std::string prefix, bool isLeft) const {
    if (!node) return;

    std::cout << prefix;
    std::cout << (isLeft ? "|-- " : "\\-- ");

    if (!node->left && !node->right) {
        std::string ch;
        if (node->ch == ' ') ch = "SPACE";
        else if (node->ch == '\n') ch = "\\n";
        else ch = std::string(1, node->ch);
        std::cout << "[" << ch << ":" << node->freq << "]" << std::endl;
    } else {
        std::cout << "(" << node->freq << ")" << std::endl;
    }

    printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
    printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
}
