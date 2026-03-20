# Project: Huffman Coding Compression Tool

> **Course:** Data Structures (DCCS201) — Korea University Sejong
> **Author:** Cheolwon Park
> **Date:** 2025-06-16

---

## Overview

A Huffman coding compression tool implemented in C++. Huffman coding is a lossless data compression algorithm that assigns variable-length binary codes to characters based on their frequency of occurrence. More frequent characters receive shorter codes, minimizing the total number of bits.

## Features

- **Frequency analysis** — Automatically compute character frequencies from input text
- **Huffman tree construction** — Build optimal prefix-free code tree using a min-heap priority queue
- **Encoding** — Compress text to a bit string using the generated code table
- **Decoding** — Decompress a bit string back to the original text
- **Bit-level I/O** — Pack encoded bits into bytes for realistic compression
- **Compression statistics** — Report original size, compressed size, and compression ratio

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

1. **Build frequency table** from input text
2. **Create leaf nodes** for each character with its frequency
3. **Insert all nodes** into a min-priority queue
4. **Repeat** until one node remains:
   - Extract the two nodes with lowest frequency
   - Create a new internal node with these as children (freq = sum)
   - Insert the new node back into the priority queue
5. **Generate codes** by traversing the tree: left = 0, right = 1
6. **Encode** text by replacing each character with its Huffman code
7. **Decode** by traversing the tree following the bit string

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
| B | 2 | 10 | 4 |
| R | 2 | 110 | 6 |
| C | 1 | 1110 | 4 |
| D | 1 | 1111 | 4 |

Compressed: 23 bits (73.9% compression ratio)

## References

- **Stanford CS106B: Programming Abstractions** — Huffman encoding assignment and greedy algorithm analysis (https://cs106b.stanford.edu/)
- **Princeton COS226: Algorithms and Data Structures** — Data compression lecture covering Huffman, LZW, and entropy (https://www.cs.princeton.edu/courses/archive/spring24/cos226/)
- Sahni, S. *Data Structures, Algorithms, and Applications in C++*, Chapter 13 (Greedy Method)
