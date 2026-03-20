/**
 * @file    Lab_SkipList.cpp
 * @brief   Skip list implementation with search, insert, and delete
 * @author  Cheolwon Park
 * @date    2025-05-19
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <vector>

/**
 * @class SkipList
 * @brief Probabilistic data structure that allows O(log n) search, insert, delete
 *
 * Each node has a random level. Higher levels skip over more elements,
 * enabling fast traversal similar to binary search on a sorted linked list.
 */
class SkipList {
private:
    struct Node {
        int key;
        std::vector<Node*> forward; // forward[i] points to the next node at level i

        Node(int key, int level)
            : key(key), forward(level + 1, nullptr) {}
    };

    int maxLevel_;       // Maximum allowed level
    float probability_;  // Probability of promoting to next level
    int currentLevel_;   // Current highest level in the skip list
    Node* header_;       // Header node (sentinel)

    /**
     * @brief Generate a random level for a new node
     * @return Random level between 0 and maxLevel_
     */
    int randomLevel() {
        int level = 0;
        while (static_cast<float>(rand()) / RAND_MAX < probability_
               && level < maxLevel_) {
            level++;
        }
        return level;
    }

public:
    /**
     * @brief Construct a skip list
     * @param maxLevel Maximum level allowed
     * @param probability Probability of level promotion (default 0.5)
     */
    SkipList(int maxLevel = 16, float probability = 0.5f)
        : maxLevel_(maxLevel), probability_(probability), currentLevel_(0) {
        header_ = new Node(INT_MIN, maxLevel);
        srand(static_cast<unsigned>(time(nullptr)));
    }

    ~SkipList() {
        Node* current = header_->forward[0];
        while (current) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
        delete header_;
    }

    /**
     * @brief Search for a key in the skip list - O(log n) expected
     * @param key The key to search for
     * @return true if found, false otherwise
     */
    bool search(int key) const {
        Node* current = header_;

        // Start from the highest level and move down
        for (int i = currentLevel_; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }

        // Move to the candidate node at level 0
        current = current->forward[0];

        return (current != nullptr && current->key == key);
    }

    /**
     * @brief Insert a key into the skip list - O(log n) expected
     * @param key The key to insert
     */
    void insert(int key) {
        // Track the rightmost node at each level before the insertion point
        std::vector<Node*> update(maxLevel_ + 1, nullptr);
        Node* current = header_;

        for (int i = currentLevel_; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        // If key already exists, do not insert duplicate
        if (current != nullptr && current->key == key) {
            std::cout << "Key " << key << " already exists, skipping insert." << std::endl;
            return;
        }

        int newLevel = randomLevel();

        // If new level exceeds current level, update the header links
        if (newLevel > currentLevel_) {
            for (int i = currentLevel_ + 1; i <= newLevel; i++) {
                update[i] = header_;
            }
            currentLevel_ = newLevel;
        }

        Node* newNode = new Node(key, newLevel);

        // Splice the new node into the list at each level
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    /**
     * @brief Delete a key from the skip list - O(log n) expected
     * @param key The key to delete
     * @return true if key was found and deleted, false otherwise
     */
    bool remove(int key) {
        std::vector<Node*> update(maxLevel_ + 1, nullptr);
        Node* current = header_;

        for (int i = currentLevel_; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current == nullptr || current->key != key) {
            return false; // Key not found
        }

        // Remove the node from each level it appears in
        for (int i = 0; i <= currentLevel_; i++) {
            if (update[i]->forward[i] != current) break;
            update[i]->forward[i] = current->forward[i];
        }

        delete current;

        // Reduce the level if the highest levels are now empty
        while (currentLevel_ > 0 && header_->forward[currentLevel_] == nullptr) {
            currentLevel_--;
        }

        return true;
    }

    /**
     * @brief Display the skip list showing all levels
     */
    void display() const {
        std::cout << "\n--- Skip List ---" << std::endl;
        for (int i = currentLevel_; i >= 0; i--) {
            Node* node = header_->forward[i];
            std::cout << "Level " << i << ": ";
            while (node) {
                std::cout << node->key << " -> ";
                node = node->forward[i];
            }
            std::cout << "NULL" << std::endl;
        }
        std::cout << "-----------------" << std::endl;
    }
};

// ============================================================
// Main: Demonstrate skip list operations
// ============================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "     Skip List Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    SkipList sl(4, 0.5f);

    // Insert elements
    std::cout << "\n--- Inserting elements ---" << std::endl;
    int keys[] = {3, 6, 7, 9, 12, 17, 19, 21, 25, 26};
    for (int key : keys) {
        sl.insert(key);
        std::cout << "Inserted: " << key << std::endl;
    }

    sl.display();

    // Search operations
    std::cout << "\n--- Search Operations ---" << std::endl;
    int searchKeys[] = {7, 15, 21, 30};
    for (int key : searchKeys) {
        bool found = sl.search(key);
        std::cout << "Search " << key << ": " << (found ? "FOUND" : "NOT FOUND") << std::endl;
    }

    // Delete operations
    std::cout << "\n--- Delete Operations ---" << std::endl;
    int deleteKeys[] = {7, 19, 100};
    for (int key : deleteKeys) {
        bool removed = sl.remove(key);
        std::cout << "Delete " << key << ": " << (removed ? "SUCCESS" : "NOT FOUND") << std::endl;
    }

    sl.display();

    // Verify search after deletion
    std::cout << "\n--- Search After Deletion ---" << std::endl;
    std::cout << "Search 7: " << (sl.search(7) ? "FOUND" : "NOT FOUND") << std::endl;
    std::cout << "Search 9: " << (sl.search(9) ? "FOUND" : "NOT FOUND") << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
