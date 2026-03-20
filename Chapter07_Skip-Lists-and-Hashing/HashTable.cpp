/**
 * @file    HashTable.cpp
 * @brief   Hash table implementation with separate chaining and open addressing (linear probing)
 * @author  Cheolwon Park
 * @date    2025-05-19
 */

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>
#include <functional>

// ============================================================
// Part 1: Hash Table with Separate Chaining
// ============================================================

/**
 * @class ChainingHashTable
 * @brief Hash table using separate chaining for collision resolution
 *
 * Each bucket holds a linked list of key-value pairs that hash to the same index.
 */
template <typename K, typename V>
class ChainingHashTable {
private:
    struct Entry {
        K key;
        V value;
        Entry(const K& k, const V& v) : key(k), value(v) {}
    };

    std::vector<std::list<Entry>> table_;
    int size_;      // Number of elements
    int capacity_;  // Number of buckets

    int hash(const K& key) const {
        return std::hash<K>{}(key) % capacity_;
    }

public:
    explicit ChainingHashTable(int capacity = 11)
        : table_(capacity), size_(0), capacity_(capacity) {}

    /**
     * @brief Insert or update a key-value pair - O(1) average
     */
    void insert(const K& key, const V& value) {
        int idx = hash(key);
        for (auto& entry : table_[idx]) {
            if (entry.key == key) {
                entry.value = value; // Update existing
                return;
            }
        }
        table_[idx].emplace_back(key, value);
        size_++;
    }

    /**
     * @brief Search for a key - O(1) average, O(n) worst case
     * @return Pointer to the value if found, nullptr otherwise
     */
    V* search(const K& key) {
        int idx = hash(key);
        for (auto& entry : table_[idx]) {
            if (entry.key == key) return &entry.value;
        }
        return nullptr;
    }

    /**
     * @brief Remove a key-value pair - O(1) average
     * @return true if removed, false if key not found
     */
    bool remove(const K& key) {
        int idx = hash(key);
        auto& chain = table_[idx];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->key == key) {
                chain.erase(it);
                size_--;
                return true;
            }
        }
        return false;
    }

    int size() const { return size_; }
    bool empty() const { return size_ == 0; }
    double loadFactor() const { return static_cast<double>(size_) / capacity_; }

    void display() const {
        std::cout << "\n--- Chaining Hash Table ---" << std::endl;
        for (int i = 0; i < capacity_; i++) {
            std::cout << "Bucket " << i << ": ";
            if (table_[i].empty()) {
                std::cout << "(empty)";
            } else {
                for (const auto& entry : table_[i]) {
                    std::cout << "(" << entry.key << "," << entry.value << ") -> ";
                }
                std::cout << "NULL";
            }
            std::cout << std::endl;
        }
        std::cout << "Load factor: " << loadFactor() << std::endl;
    }
};

// ============================================================
// Part 2: Hash Table with Linear Probing (Open Addressing)
// ============================================================

/**
 * @class LinearProbingHashTable
 * @brief Hash table using linear probing for collision resolution
 *
 * All elements are stored within the table. Collisions are resolved
 * by probing the next slot: h_i(k) = (h(k) + i) mod m.
 */
template <typename K, typename V>
class LinearProbingHashTable {
private:
    enum SlotState { EMPTY, OCCUPIED, DELETED };

    struct Slot {
        K key;
        V value;
        SlotState state;
        Slot() : state(EMPTY) {}
    };

    std::vector<Slot> table_;
    int size_;
    int capacity_;

    int hash(const K& key) const {
        return std::hash<K>{}(key) % capacity_;
    }

public:
    explicit LinearProbingHashTable(int capacity = 11)
        : table_(capacity), size_(0), capacity_(capacity) {}

    /**
     * @brief Insert or update a key-value pair - O(1) average
     */
    void insert(const K& key, const V& value) {
        if (size_ >= capacity_ - 1) {
            std::cerr << "Hash table is full!" << std::endl;
            return;
        }

        int idx = hash(key);
        int firstDeleted = -1;

        for (int i = 0; i < capacity_; i++) {
            int probe = (idx + i) % capacity_;

            if (table_[probe].state == EMPTY) {
                int target = (firstDeleted != -1) ? firstDeleted : probe;
                table_[target].key = key;
                table_[target].value = value;
                table_[target].state = OCCUPIED;
                size_++;
                return;
            }

            if (table_[probe].state == DELETED && firstDeleted == -1) {
                firstDeleted = probe;
            }

            if (table_[probe].state == OCCUPIED && table_[probe].key == key) {
                table_[probe].value = value; // Update existing
                return;
            }
        }

        // If we reach here and had a deleted slot, use it
        if (firstDeleted != -1) {
            table_[firstDeleted].key = key;
            table_[firstDeleted].value = value;
            table_[firstDeleted].state = OCCUPIED;
            size_++;
        }
    }

    /**
     * @brief Search for a key - O(1) average
     * @return Pointer to the value if found, nullptr otherwise
     */
    V* search(const K& key) {
        int idx = hash(key);
        for (int i = 0; i < capacity_; i++) {
            int probe = (idx + i) % capacity_;
            if (table_[probe].state == EMPTY) return nullptr;
            if (table_[probe].state == OCCUPIED && table_[probe].key == key) {
                return &table_[probe].value;
            }
        }
        return nullptr;
    }

    /**
     * @brief Remove a key using lazy deletion - O(1) average
     * @return true if removed, false if key not found
     */
    bool remove(const K& key) {
        int idx = hash(key);
        for (int i = 0; i < capacity_; i++) {
            int probe = (idx + i) % capacity_;
            if (table_[probe].state == EMPTY) return false;
            if (table_[probe].state == OCCUPIED && table_[probe].key == key) {
                table_[probe].state = DELETED;
                size_--;
                return true;
            }
        }
        return false;
    }

    int size() const { return size_; }
    double loadFactor() const { return static_cast<double>(size_) / capacity_; }

    void display() const {
        std::cout << "\n--- Linear Probing Hash Table ---" << std::endl;
        for (int i = 0; i < capacity_; i++) {
            std::cout << "Slot " << i << ": ";
            if (table_[i].state == OCCUPIED)
                std::cout << "(" << table_[i].key << "," << table_[i].value << ")";
            else if (table_[i].state == DELETED)
                std::cout << "[DELETED]";
            else
                std::cout << "(empty)";
            std::cout << std::endl;
        }
        std::cout << "Load factor: " << loadFactor() << std::endl;
    }
};

// ============================================================
// Main: Demonstrate both hash table implementations
// ============================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "     Hash Table Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // --- Part 1: Chaining ---
    std::cout << "\n=== Separate Chaining ===" << std::endl;
    ChainingHashTable<int, std::string> chainHT(7);

    chainHT.insert(10, "Apple");
    chainHT.insert(22, "Banana");
    chainHT.insert(31, "Cherry");
    chainHT.insert(4,  "Date");
    chainHT.insert(15, "Elderberry");
    chainHT.insert(28, "Fig");   // 28 % 7 = 0 (collides with others)
    chainHT.insert(17, "Grape"); // 17 % 7 = 3 (collides with 10, 31)

    chainHT.display();

    std::cout << "\nSearch for key 22: ";
    auto* val = chainHT.search(22);
    std::cout << (val ? *val : "NOT FOUND") << std::endl;

    std::cout << "Search for key 99: ";
    val = chainHT.search(99);
    std::cout << (val ? *val : "NOT FOUND") << std::endl;

    chainHT.remove(31);
    std::cout << "After removing key 31:" << std::endl;
    chainHT.display();

    // --- Part 2: Linear Probing ---
    std::cout << "\n=== Linear Probing ===" << std::endl;
    LinearProbingHashTable<int, std::string> lpHT(11);

    // Insert keys from the quiz example: h(k) = k % 11
    lpHT.insert(20, "Twenty");
    lpHT.insert(31, "ThirtyOne");
    lpHT.insert(24, "TwentyFour");
    lpHT.insert(9,  "Nine");
    lpHT.insert(35, "ThirtyFive");
    lpHT.insert(42, "FortyTwo");

    lpHT.display();

    std::cout << "\nSearch for key 35: ";
    auto* val2 = lpHT.search(35);
    std::cout << (val2 ? *val2 : "NOT FOUND") << std::endl;

    std::cout << "Search for key 50: ";
    val2 = lpHT.search(50);
    std::cout << (val2 ? *val2 : "NOT FOUND") << std::endl;

    lpHT.remove(31);
    std::cout << "\nAfter removing key 31:" << std::endl;
    lpHT.display();

    // Verify search still works after deletion (lazy delete)
    std::cout << "Search for key 42 (after deleting 31): ";
    val2 = lpHT.search(42);
    std::cout << (val2 ? *val2 : "NOT FOUND") << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
