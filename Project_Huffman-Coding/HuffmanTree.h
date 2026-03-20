/**
 * @file    HuffmanTree.h
 * @brief   Huffman tree construction and encoding/decoding
 * @author  Cheolwon Park
 * @date    2025-06-16
 */

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>

/**
 * @class HuffmanTree
 * @brief Huffman coding tree for data compression
 *
 * Huffman coding assigns variable-length binary codes to characters
 * based on their frequency. More frequent characters get shorter codes,
 * achieving optimal prefix-free encoding.
 *
 * Algorithm:
 * 1. Build a frequency table from input
 * 2. Create leaf nodes for each character
 * 3. Use a min-heap to repeatedly merge the two lowest-frequency nodes
 * 4. Generate codes by traversing the tree (left=0, right=1)
 *
 * Properties:
 * - Prefix-free: no code is a prefix of another
 * - Optimal: minimizes weighted path length (total encoded bits)
 * - Time: O(n log n) for construction, O(n) for encoding/decoding
 */
class HuffmanTree {
public:
    struct Node {
        char ch;
        int freq;
        Node* left;
        Node* right;

        Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
        Node(int f, Node* l, Node* r) : ch('\0'), freq(f), left(l), right(r) {}
    };

private:
    Node* root_;
    std::unordered_map<char, std::string> codeTable_;
    std::unordered_map<char, int> freqTable_;

    /**
     * @brief Recursively generate Huffman codes
     */
    void generateCodes(Node* node, const std::string& code);

    /**
     * @brief Destroy tree recursively
     */
    void destroy(Node* node);

    /**
     * @brief Print tree structure
     */
    void printTree(Node* node, std::string prefix, bool isLeft) const;

public:
    HuffmanTree();
    ~HuffmanTree();

    /**
     * @brief Build Huffman tree from a frequency table
     * @param freqMap Map of character -> frequency
     */
    void buildFromFrequencies(const std::unordered_map<char, int>& freqMap);

    /**
     * @brief Build Huffman tree from input text (auto-compute frequencies)
     * @param text The input text to analyze
     */
    void buildFromText(const std::string& text);

    /**
     * @brief Encode a string using the Huffman code table
     * @return Encoded bit string (as std::string of '0' and '1')
     */
    std::string encode(const std::string& text) const;

    /**
     * @brief Decode a bit string back to original text
     * @param bits Encoded bit string
     * @return Decoded text
     */
    std::string decode(const std::string& bits) const;

    /**
     * @brief Get the code table
     */
    const std::unordered_map<char, std::string>& getCodeTable() const;

    /**
     * @brief Get the frequency table
     */
    const std::unordered_map<char, int>& getFreqTable() const;

    /**
     * @brief Display tree structure and code table
     */
    void display() const;

    /**
     * @brief Calculate compression ratio
     * @param originalBits Original size in bits (8 * text length)
     * @param compressedBits Compressed size in bits
     * @return Compression ratio as percentage
     */
    static double compressionRatio(size_t originalBits, size_t compressedBits);
};

#endif // HUFFMANTREE_H
