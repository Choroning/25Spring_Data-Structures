/**
 * @file    ArrayList.cpp
 * @brief   Template-based dynamic array list with iterator support
 * @author  Cheolwon Park
 * @date    2025-03-24
 */

#include <iostream>
#include <stdexcept>
#include <algorithm>

/**
 * @class ArrayList
 * @brief A dynamic array-based list that automatically resizes
 * @tparam T The type of elements stored in the list
 */
template <typename T>
class ArrayList {
private:
    T* data_;
    int size_;
    int capacity_;

    /**
     * @brief Doubles the capacity when the array is full
     */
    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size_; i++) {
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

public:
    // ---- Iterator ----
    class Iterator {
    private:
        T* ptr_;
    public:
        Iterator(T* p) : ptr_(p) {}
        T& operator*() { return *ptr_; }
        const T& operator*() const { return *ptr_; }
        T* operator->() { return ptr_; }
        Iterator& operator++() { ++ptr_; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++ptr_; return tmp; }
        Iterator& operator--() { --ptr_; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --ptr_; return tmp; }
        bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }
    };

    Iterator begin() { return Iterator(data_); }
    Iterator end() { return Iterator(data_ + size_); }

    // ---- Constructors and Destructor ----

    explicit ArrayList(int initialCapacity = 10)
        : size_(0), capacity_(initialCapacity) {
        if (initialCapacity < 1)
            throw std::invalid_argument("Capacity must be >= 1");
        data_ = new T[capacity_];
    }

    ArrayList(const ArrayList& other)
        : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (int i = 0; i < size_; i++)
            data_[i] = other.data_[i];
    }

    ArrayList& operator=(const ArrayList& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            for (int i = 0; i < size_; i++)
                data_[i] = other.data_[i];
        }
        return *this;
    }

    ~ArrayList() { delete[] data_; }

    // ---- Core Operations ----

    bool empty() const { return size_ == 0; }
    int size() const { return size_; }
    int capacity() const { return capacity_; }

    /**
     * @brief Access element at given index with bounds checking
     * @throws std::out_of_range if index is invalid
     */
    T& get(int index) {
        if (index < 0 || index >= size_)
            throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const T& get(int index) const {
        if (index < 0 || index >= size_)
            throw std::out_of_range("Index out of range");
        return data_[index];
    }

    T& operator[](int index) { return data_[index]; }
    const T& operator[](int index) const { return data_[index]; }

    /**
     * @brief Returns the index of the first occurrence, or -1 if not found
     */
    int indexOf(const T& element) const {
        for (int i = 0; i < size_; i++) {
            if (data_[i] == element) return i;
        }
        return -1;
    }

    /**
     * @brief Inserts an element at the given index
     * @param index Position to insert (0 <= index <= size)
     * @param element The element to insert
     */
    void insert(int index, const T& element) {
        if (index < 0 || index > size_)
            throw std::out_of_range("Insert index out of range");

        if (size_ == capacity_)
            resize(2 * capacity_);

        // Shift elements to the right
        for (int i = size_; i > index; i--)
            data_[i] = data_[i - 1];

        data_[index] = element;
        size_++;
    }

    /**
     * @brief Appends an element at the end of the list
     */
    void pushBack(const T& element) {
        insert(size_, element);
    }

    /**
     * @brief Removes the element at the given index
     * @param index Position to remove (0 <= index < size)
     */
    void erase(int index) {
        if (index < 0 || index >= size_)
            throw std::out_of_range("Erase index out of range");

        // Shift elements to the left
        for (int i = index; i < size_ - 1; i++)
            data_[i] = data_[i + 1];

        size_--;
    }

    /**
     * @brief Removes and returns the last element
     */
    T popBack() {
        if (empty())
            throw std::underflow_error("List is empty");
        return data_[--size_];
    }

    /**
     * @brief Clears all elements
     */
    void clear() { size_ = 0; }

    /**
     * @brief Prints the list contents
     */
    void print(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << ": ";
        std::cout << "[";
        for (int i = 0; i < size_; i++) {
            if (i > 0) std::cout << ", ";
            std::cout << data_[i];
        }
        std::cout << "]" << std::endl;
    }
};

// ============================================================
// Main: Demonstration
// ============================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   ArrayList Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // Basic operations
    ArrayList<int> list;
    std::cout << "\n--- Basic Operations ---" << std::endl;

    for (int i = 1; i <= 10; i++)
        list.pushBack(i * 10);

    list.print("After pushing 10-100");
    std::cout << "Size: " << list.size()
              << ", Capacity: " << list.capacity() << std::endl;

    // Insert and erase
    std::cout << "\n--- Insert and Erase ---" << std::endl;
    list.insert(0, 5);
    list.print("After insert(0, 5)");

    list.insert(5, 55);
    list.print("After insert(5, 55)");

    list.erase(0);
    list.print("After erase(0)");

    // Access
    std::cout << "\n--- Access ---" << std::endl;
    std::cout << "get(0) = " << list.get(0) << std::endl;
    std::cout << "get(4) = " << list.get(4) << std::endl;
    std::cout << "indexOf(55) = " << list.indexOf(55) << std::endl;
    std::cout << "indexOf(999) = " << list.indexOf(999) << std::endl;

    // Iterator usage
    std::cout << "\n--- Iterator ---" << std::endl;
    std::cout << "Elements via iterator: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Range-based for loop
    std::cout << "Range-based for: ";
    for (int x : list) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Copy constructor
    std::cout << "\n--- Copy ---" << std::endl;
    ArrayList<int> copy = list;
    copy.print("Copy of list");

    // String list
    std::cout << "\n--- String ArrayList ---" << std::endl;
    ArrayList<std::string> strList;
    strList.pushBack("Hello");
    strList.pushBack("World");
    strList.pushBack("Data");
    strList.pushBack("Structures");
    strList.print("String list");

    // Exception handling
    std::cout << "\n--- Exception Handling ---" << std::endl;
    try {
        list.get(100);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
