/**
 * @file    main.cpp
 * @brief   Huffman compression tool demo: compress and decompress
 * @author  Cheolwon Park
 * @date    2025-06-16
 */

#include "HuffmanTree.h"
#include "BitStream.h"
#include <iostream>
#include <string>
#include <cassert>

/**
 * @brief Demonstrate basic Huffman encoding and decoding
 */
void demonstrateBasic() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Huffman Coding: Basic Demo" << std::endl;
    std::cout << "========================================" << std::endl;

    // Example from textbook: character frequencies
    std::unordered_map<char, int> freqMap = {
        {'a', 45}, {'b', 13}, {'c', 12}, {'d', 16}, {'e', 9}, {'f', 5}
    };

    HuffmanTree huffman;
    huffman.buildFromFrequencies(freqMap);
    huffman.display();

    std::cout << "\n--- Encode/Decode Test ---" << std::endl;
    std::string original = "abcdef";
    std::string encoded = huffman.encode(original);
    std::string decoded = huffman.decode(encoded);

    std::cout << "Original:  \"" << original << "\"" << std::endl;
    std::cout << "Encoded:   " << encoded << " (" << encoded.length() << " bits)" << std::endl;
    std::cout << "Decoded:   \"" << decoded << "\"" << std::endl;
    std::cout << "Match:     " << (original == decoded ? "YES" : "NO") << std::endl;
}

/**
 * @brief Demonstrate text compression with bit-level I/O
 */
void demonstrateTextCompression() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  Huffman Coding: Text Compression" << std::endl;
    std::cout << "========================================" << std::endl;

    std::string text = "huffman coding is a lossless data compression algorithm "
                       "that assigns variable length codes to characters based on "
                       "their frequency of occurrence";

    std::cout << "\nOriginal text (" << text.length() << " chars):" << std::endl;
    std::cout << "  \"" << text << "\"" << std::endl;

    // Build tree from text
    HuffmanTree huffman;
    huffman.buildFromText(text);
    huffman.display();

    // Encode
    std::string encodedBits = huffman.encode(text);
    size_t originalBits = text.length() * 8;
    size_t compressedBits = encodedBits.length();

    std::cout << "\n--- Compression Results ---" << std::endl;
    std::cout << "Original size:    " << originalBits << " bits ("
              << text.length() << " bytes)" << std::endl;
    std::cout << "Compressed size:  " << compressedBits << " bits ("
              << (compressedBits + 7) / 8 << " bytes)" << std::endl;
    std::cout << "Compression ratio: "
              << HuffmanTree::compressionRatio(originalBits, compressedBits)
              << "%" << std::endl;

    // Decode and verify
    std::string decoded = huffman.decode(encodedBits);
    std::cout << "Decode match:     " << (text == decoded ? "YES" : "NO") << std::endl;

    // Use BitWriter/BitReader for actual byte-level encoding
    std::cout << "\n--- Bit-Level I/O Demo ---" << std::endl;
    BitWriter writer;
    writer.writeBits(encodedBits);
    size_t totalBits = writer.totalBits();
    writer.flush();

    const auto& buffer = writer.getBuffer();
    std::cout << "Encoded to " << buffer.size() << " bytes"
              << " (" << totalBits << " significant bits)" << std::endl;

    // Read back
    BitReader reader(buffer, totalBits);
    std::string readBits;
    while (reader.hasNext()) {
        int bit = reader.readBit();
        readBits += (bit ? '1' : '0');
    }

    std::string decodedFromBytes = huffman.decode(readBits);
    std::cout << "Byte-level roundtrip match: "
              << (text == decodedFromBytes ? "YES" : "NO") << std::endl;
}

/**
 * @brief Demonstrate with a specific well-known example
 */
void demonstrateClassicExample() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  Huffman Coding: Classic Example" << std::endl;
    std::cout << "========================================" << std::endl;

    // Classic example: "ABRACADABRA"
    std::string text = "ABRACADABRA";
    std::cout << "\nText: \"" << text << "\"" << std::endl;

    HuffmanTree huffman;
    huffman.buildFromText(text);
    huffman.display();

    std::string encoded = huffman.encode(text);
    std::string decoded = huffman.decode(encoded);

    size_t originalBits = text.length() * 8;
    size_t compressedBits = encoded.length();

    std::cout << "\n--- Results ---" << std::endl;
    std::cout << "Original:     " << originalBits << " bits" << std::endl;
    std::cout << "Compressed:   " << compressedBits << " bits" << std::endl;
    std::cout << "Savings:      "
              << HuffmanTree::compressionRatio(originalBits, compressedBits)
              << "%" << std::endl;
    std::cout << "Decoded:      \"" << decoded << "\"" << std::endl;
    std::cout << "Correct:      " << (text == decoded ? "YES" : "NO") << std::endl;

    // Show individual character encoding
    std::cout << "\nPer-character encoding:" << std::endl;
    const auto& codeTable = huffman.getCodeTable();
    for (char c : text) {
        auto it = codeTable.find(c);
        if (it != codeTable.end()) {
            std::cout << "  '" << c << "' -> " << it->second << std::endl;
        }
    }
}

int main() {
    demonstrateBasic();
    demonstrateTextCompression();
    demonstrateClassicExample();

    std::cout << "\n========================================" << std::endl;
    std::cout << "   All Demos Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
