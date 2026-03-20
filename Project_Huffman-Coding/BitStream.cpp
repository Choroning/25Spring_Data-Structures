/**
 * @file    BitStream.cpp
 * @brief   Bit-level I/O implementation for Huffman coding
 * @author  Cheolwon Park
 * @date    2025-06-16
 */

#include "BitStream.h"

// ============================================================
// BitWriter
// ============================================================

BitWriter::BitWriter() : currentByte_(0), bitCount_(0) {}

void BitWriter::writeBit(int bit) {
    currentByte_ = (currentByte_ << 1) | (bit & 1);
    bitCount_++;

    if (bitCount_ == 8) {
        buffer_.push_back(currentByte_);
        currentByte_ = 0;
        bitCount_ = 0;
    }
}

void BitWriter::writeBits(const std::string& bits) {
    for (char c : bits) {
        writeBit(c == '1' ? 1 : 0);
    }
}

void BitWriter::writeByte(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        writeBit((byte >> i) & 1);
    }
}

void BitWriter::flush() {
    if (bitCount_ > 0) {
        currentByte_ <<= (8 - bitCount_); // Pad with zeros
        buffer_.push_back(currentByte_);
        currentByte_ = 0;
        bitCount_ = 0;
    }
}

const std::vector<uint8_t>& BitWriter::getBuffer() const {
    return buffer_;
}

size_t BitWriter::totalBits() const {
    return buffer_.size() * 8 + bitCount_;
}

// ============================================================
// BitReader
// ============================================================

BitReader::BitReader(const std::vector<uint8_t>& buffer, size_t totalBits)
    : buffer_(buffer), bytePos_(0), bitPos_(7), totalBits_(totalBits) {}

int BitReader::readBit() {
    if (!hasNext()) return -1;

    int bit = (buffer_[bytePos_] >> bitPos_) & 1;
    bitPos_--;

    if (bitPos_ < 0) {
        bitPos_ = 7;
        bytePos_++;
    }

    totalBits_--;
    return bit;
}

bool BitReader::hasNext() const {
    return totalBits_ > 0;
}
