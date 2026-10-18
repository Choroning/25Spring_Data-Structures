/**
 * @file    BitStream.h
 * @brief   Bit-level I/O for Huffman encoding/decoding
 * @author  Cheolwon Park
 * @date    2025-06-16
 */

#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <vector>
#include <string>
#include <cstdint>

/**
 * @class BitWriter
 * @brief Writes individual bits to a byte buffer
 *
 * Accumulates bits into bytes. When 8 bits are collected,
 * the byte is flushed to the internal buffer. Final partial
 * byte is padded with zeros.
 */
class BitWriter {
private:
    std::vector<uint8_t> buffer_;
    uint8_t currentByte_;
    int bitCount_; // Number of bits written to currentByte_ (0-7)

public:
    BitWriter();

    /**
     * @brief Write a single bit (0 or 1)
     */
    void writeBit(int bit);

    /**
     * @brief Write a string of '0' and '1' characters
     */
    void writeBits(const std::string& bits);

    /**
     * @brief Write a byte (8 bits)
     */
    void writeByte(uint8_t byte);

    /**
     * @brief Flush remaining bits (pad with zeros)
     */
    void flush();

    /**
     * @brief Get the encoded byte buffer
     */
    const std::vector<uint8_t>& getBuffer() const;

    /**
     * @brief Get total number of bits written
     */
    size_t totalBits() const;
};

/**
 * @class BitReader
 * @brief Reads individual bits from a byte buffer
 */
class BitReader {
private:
    const std::vector<uint8_t>& buffer_;
    size_t bytePos_;
    int bitPos_; // 0-7, MSB first
    size_t totalBits_;

public:
    /**
     * @brief Construct from a byte buffer and total bit count
     */
    BitReader(const std::vector<uint8_t>& buffer, size_t totalBits);

    /**
     * @brief Read a single bit
     * @return 0 or 1, or -1 if end of stream
     */
    int readBit();

    /**
     * @brief Check if there are more bits to read
     */
    bool hasNext() const;
};

#endif // BITSTREAM_H
