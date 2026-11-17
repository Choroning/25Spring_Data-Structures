# Term Project — Huffman Coding Compression Tool

[Repository Guide](../../README.md) | [English](README.md) | [한국어](README.ko.md)

> **Last Updated:** 2026-11-18

---

## Overview

This term project implements a Huffman coding compression tool in C++. Huffman coding is a lossless data compression algorithm that assigns variable-length binary codes to characters based on their frequency of occurrence. More frequent characters receive shorter codes, minimizing the total number of bits.

## Features

- **Frequency analysis:** Automatically compute character frequencies from input text.
- **Huffman tree construction:** Build the optimal prefix-free code tree using a min-heap priority queue.
- **Encoding:** Compress text to a bit string using the generated code table.
- **Decoding:** Decompress a bit string back to the original text.
- **Bit-level I/O:** Pack encoded bits into bytes for realistic compression.
- **Compression statistics:** Report the original size, compressed size, and compression ratio.

## File Structure

| File | Description |
|:-----|:------------|
| `HuffmanTree.h` | Huffman tree class declaration |
| `HuffmanTree.cpp` | Tree construction, code generation, encode/decode |
| `PriorityQueue.h` | Min-heap priority queue (template) |
| `PriorityQueue.cpp` | Priority queue source (template instantiation) |
| `BitStream.h` | Bit-level writer and reader classes |
| `BitStream.cpp` | Bit-level I/O implementation |
| `main.cpp` | Demo: compress/decompress with multiple examples |

## Build and Run

```bash
g++ -std=c++17 -O2 -o huffman HuffmanTree.cpp BitStream.cpp PriorityQueue.cpp main.cpp
./huffman
```

## Algorithm

1. **Build a frequency table** from the input text.
2. **Create a leaf node** for each character with its frequency.
3. **Insert all nodes** into a min-priority queue.
4. **Repeat** until one node remains:
   - Extract the two nodes with the lowest frequencies.
   - Create a new internal node with these as children (its frequency is their sum).
   - Insert the new node back into the priority queue.
5. **Generate codes** by traversing the tree, with 0 for a left branch and 1 for a right branch.
6. **Encode** the text by replacing each character with its Huffman code.
7. **Decode** by traversing the tree following the bit string.

## Complexity

| Operation | Time |
|:----------|:-----|
| Build tree | $O(n \log n)$ where $n$ = unique characters |
| Encode text | $O(m)$ where $m$ = text length |
| Decode bits | $O(k)$ where $k$ = number of bits |

## Example

Input: `"ABRACADABRA"` (11 chars = 88 bits)

| Char | Freq | Code | Bits Used |
|:-----|:-----|:-----|:----------|
| A | 5 | 0 | 5 |
| R | 2 | 10 | 4 |
| B | 2 | 110 | 6 |
| D | 1 | 1110 | 4 |
| C | 1 | 1111 | 4 |

Compressed: 23 bits (73.9% smaller than the original)

## References

- "Assignment 7: Huffman Coding," *CS106B: Programming Abstractions*, Stanford University, Autumn 2026. https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1272/assignments/7-huffman/
- R. Sedgewick and K. Wayne, "5.5 Data Compression," lecture slides, *COS 226*, Princeton University, Spring 2023. https://www.cs.princeton.edu/courses/archive/spring23/cos226/lectures/55DataCompression.pdf
- S. Sahni, *Data Structures, Algorithms, and Applications in C++*. Boston, MA, USA: WCB/McGraw-Hill, 1998, Sec. 9.5.3.
