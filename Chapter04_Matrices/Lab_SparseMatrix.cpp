/**
 * @file    Lab_SparseMatrix.cpp
 * @brief   Sparse matrix with array-of-triples and linked (orthogonal list) representations
 * @author  Cheolwon Park
 * @date    2025-03-31
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

// ============================================================
// Sparse Matrix using Array of Triples
// ============================================================

/**
 * @struct MatrixTerm
 * @brief Represents a non-zero element in a sparse matrix
 */
struct MatrixTerm {
    int row;
    int col;
    int value;
};

/**
 * @class SparseMatrix
 * @brief Sparse matrix stored as an array of (row, col, value) triples
 */
class SparseMatrix {
private:
    int rows_, cols_;
    std::vector<MatrixTerm> terms_;

public:
    SparseMatrix(int rows, int cols) : rows_(rows), cols_(cols) {}

    int numRows() const { return rows_; }
    int numCols() const { return cols_; }
    int numTerms() const { return static_cast<int>(terms_.size()); }

    /**
     * @brief Set a value at (row, col). If value is 0, removes the term.
     */
    void set(int row, int col, int value) {
        // Find existing term
        for (auto it = terms_.begin(); it != terms_.end(); ++it) {
            if (it->row == row && it->col == col) {
                if (value == 0) {
                    terms_.erase(it);
                } else {
                    it->value = value;
                }
                return;
            }
        }
        // Insert new term (if non-zero)
        if (value != 0) {
            terms_.push_back({row, col, value});
            // Keep sorted by row, then column
            std::sort(terms_.begin(), terms_.end(), [](const MatrixTerm& a, const MatrixTerm& b) {
                return (a.row < b.row) || (a.row == b.row && a.col < b.col);
            });
        }
    }

    /**
     * @brief Get the value at (row, col). Returns 0 if not stored.
     */
    int get(int row, int col) const {
        for (const auto& t : terms_) {
            if (t.row == row && t.col == col) return t.value;
        }
        return 0;
    }

    /**
     * @brief Fast transpose using O(terms + cols) algorithm
     * @return Transposed sparse matrix
     */
    SparseMatrix transpose() const {
        SparseMatrix result(cols_, rows_);
        if (terms_.empty()) return result;

        int t = static_cast<int>(terms_.size());

        // Step 1: Count elements in each column (becomes row in transpose)
        std::vector<int> colCount(cols_, 0);
        for (const auto& term : terms_) {
            colCount[term.col]++;
        }

        // Step 2: Compute starting positions
        std::vector<int> rowStart(cols_, 0);
        for (int i = 1; i < cols_; i++) {
            rowStart[i] = rowStart[i - 1] + colCount[i - 1];
        }

        // Step 3: Place elements
        result.terms_.resize(t);
        for (const auto& term : terms_) {
            int pos = rowStart[term.col]++;
            result.terms_[pos] = {term.col, term.row, term.value};
        }

        return result;
    }

    /**
     * @brief Add two sparse matrices
     */
    SparseMatrix add(const SparseMatrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::invalid_argument("Matrix dimensions must match");

        SparseMatrix result(rows_, cols_);
        int i = 0, j = 0;
        int t1 = static_cast<int>(terms_.size());
        int t2 = static_cast<int>(other.terms_.size());

        while (i < t1 && j < t2) {
            int idx1 = terms_[i].row * cols_ + terms_[i].col;
            int idx2 = other.terms_[j].row * cols_ + other.terms_[j].col;

            if (idx1 < idx2) {
                result.terms_.push_back(terms_[i++]);
            } else if (idx1 > idx2) {
                result.terms_.push_back(other.terms_[j++]);
            } else {
                int sum = terms_[i].value + other.terms_[j].value;
                if (sum != 0)
                    result.terms_.push_back({terms_[i].row, terms_[i].col, sum});
                i++; j++;
            }
        }
        while (i < t1) result.terms_.push_back(terms_[i++]);
        while (j < t2) result.terms_.push_back(other.terms_[j++]);

        return result;
    }

    /**
     * @brief Print as dense matrix (for debugging small matrices)
     */
    void printDense(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << ":" << std::endl;
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                std::cout << std::setw(4) << get(i, j);
            }
            std::cout << std::endl;
        }
    }

    /**
     * @brief Print the triple representation
     */
    void printTriples(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << ":" << std::endl;
        std::cout << "  Dimensions: " << rows_ << " x " << cols_
                  << ", Non-zeros: " << terms_.size() << std::endl;
        std::cout << "  Row  Col  Value" << std::endl;
        for (const auto& t : terms_) {
            std::cout << "  " << std::setw(3) << t.row
                      << "  " << std::setw(3) << t.col
                      << "  " << std::setw(5) << t.value << std::endl;
        }
    }
};

// ============================================================
// Sparse Matrix using Linked (Orthogonal List) Representation
// ============================================================

/**
 * @class LinkedSparseMatrix
 * @brief Sparse matrix using orthogonal linked lists
 */
class LinkedSparseMatrix {
private:
    struct Node {
        int row, col, value;
        Node* nextInRow;
        Node* nextInCol;
        Node(int r, int c, int v)
            : row(r), col(c), value(v), nextInRow(nullptr), nextInCol(nullptr) {}
    };

    int rows_, cols_;
    std::vector<Node*> rowHeads_;
    std::vector<Node*> colHeads_;

public:
    LinkedSparseMatrix(int rows, int cols)
        : rows_(rows), cols_(cols), rowHeads_(rows, nullptr), colHeads_(cols, nullptr) {}

    ~LinkedSparseMatrix() {
        for (int i = 0; i < rows_; i++) {
            Node* curr = rowHeads_[i];
            while (curr) {
                Node* temp = curr;
                curr = curr->nextInRow;
                delete temp;
            }
        }
    }

    /**
     * @brief Insert a non-zero element
     */
    void set(int row, int col, int value) {
        if (value == 0) return;

        Node* newNode = new Node(row, col, value);

        // Insert into row list (sorted by column)
        if (!rowHeads_[row] || rowHeads_[row]->col > col) {
            newNode->nextInRow = rowHeads_[row];
            rowHeads_[row] = newNode;
        } else {
            Node* curr = rowHeads_[row];
            while (curr->nextInRow && curr->nextInRow->col < col)
                curr = curr->nextInRow;
            newNode->nextInRow = curr->nextInRow;
            curr->nextInRow = newNode;
        }

        // Insert into column list (sorted by row)
        if (!colHeads_[col] || colHeads_[col]->row > row) {
            newNode->nextInCol = colHeads_[col];
            colHeads_[col] = newNode;
        } else {
            Node* curr = colHeads_[col];
            while (curr->nextInCol && curr->nextInCol->row < row)
                curr = curr->nextInCol;
            newNode->nextInCol = curr->nextInCol;
            curr->nextInCol = newNode;
        }
    }

    /**
     * @brief Get value at (row, col)
     */
    int get(int row, int col) const {
        Node* curr = rowHeads_[row];
        while (curr) {
            if (curr->col == col) return curr->value;
            if (curr->col > col) break;
            curr = curr->nextInRow;
        }
        return 0;
    }

    void printDense(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << ":" << std::endl;
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                std::cout << std::setw(4) << get(i, j);
            }
            std::cout << std::endl;
        }
    }
};

// ============================================================
// Main: Demonstration
// ============================================================

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Sparse Matrix Demonstration" << std::endl;
    std::cout << "========================================" << std::endl;

    // --- Array of Triples ---
    std::cout << "\n=== Array of Triples Representation ===" << std::endl;

    SparseMatrix A(4, 5);
    A.set(0, 0, 15); A.set(0, 3, 22); A.set(0, 4, -15);
    A.set(1, 1, 11); A.set(1, 2, 3);
    A.set(2, 3, -6);
    A.set(3, 0, 91); A.set(3, 2, 28);

    A.printDense("Matrix A");
    A.printTriples("\nTriples of A");

    // Transpose
    std::cout << "\n--- Fast Transpose ---" << std::endl;
    SparseMatrix AT = A.transpose();
    AT.printDense("A^T");
    AT.printTriples("\nTriples of A^T");

    // Addition
    std::cout << "\n--- Matrix Addition ---" << std::endl;
    SparseMatrix B(4, 5);
    B.set(0, 0, 5); B.set(0, 4, 10);
    B.set(1, 1, -11);
    B.set(2, 2, 7); B.set(2, 3, 6);
    B.set(3, 0, 9);

    B.printDense("Matrix B");

    SparseMatrix C = A.add(B);
    C.printDense("\nA + B");

    // --- Linked Representation ---
    std::cout << "\n=== Linked (Orthogonal) Representation ===" << std::endl;

    LinkedSparseMatrix L(4, 5);
    L.set(0, 0, 15); L.set(0, 3, 22); L.set(0, 4, -15);
    L.set(1, 1, 11); L.set(1, 2, 3);
    L.set(2, 3, -6);
    L.set(3, 0, 91); L.set(3, 2, 28);

    L.printDense("Linked Sparse Matrix");

    // Storage comparison
    std::cout << "\n--- Storage Comparison ---" << std::endl;
    int dense_storage = 4 * 5 * sizeof(int);
    int sparse_storage = A.numTerms() * 3 * sizeof(int) + 3 * sizeof(int); // terms + metadata
    std::cout << "Dense storage:  " << dense_storage << " bytes" << std::endl;
    std::cout << "Sparse storage: " << sparse_storage << " bytes (" << A.numTerms() << " non-zeros)" << std::endl;
    std::cout << "Savings: " << (1.0 - (double)sparse_storage / dense_storage) * 100 << "%" << std::endl;

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Demo Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
