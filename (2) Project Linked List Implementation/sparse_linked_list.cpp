/*
 * Course: CSC 6200 - Advanced Algorithms
 * Assignment: Week 2 Project - Linked List Implementation for Sparse Matrices
 * Student: Sravya Reddy Soodini
 * University: Concordia University
 * Date: September 2025
 *
 * Description:
 * This program implements a sparse matrix using a linked list representation.
 * Each row of the matrix is stored as a linked list of nonzero elements,
 * supporting operations like insertion, deletion, addition, multiplication,
 * transpose, and printing.
 *
 * Notes:
 * - Nodes are kept in sorted order by column index.
 * - set(r,c,v) removes a node if v == 0, otherwise inserts or updates.
 * - Addition merges rows; multiplication uses transpose(B) for row access.
 * - Includes a demo() function that builds example matrices and demonstrates
 *   addition, multiplication, and transpose.
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int col;
    double val;
    Node* next;
    Node(int c, double v, Node* n=nullptr): col(c), val(v), next(n) {}
};


class SparseMatrixLL {
public:
    SparseMatrixLL(int rows, int cols)
        : R(rows), C(cols), heads(rows, nullptr), nnz_count(0) {}

    ~SparseMatrixLL() { clear(); }

    int rows() const { return R; }
    int cols() const { return C; }
    size_t nnz() const { return nnz_count; }

    double get(int r, int c) const {
        check_rc(r, c);
        Node* cur = heads[r];
        while (cur && cur->col < c) cur = cur->next;
        return (cur && cur->col == c) ? cur->val : 0.0;
    }

    void set(int r, int c, double v) {
        check_rc(r, c);
        Node*& head = heads[r];
        Node* prev = nullptr;
        Node* cur = head;

        while (cur && cur->col < c) {
            prev = cur; cur = cur->next;
        }
        if (cur && cur->col == c) {
            if (v == 0.0) {
                // remove node
                if (prev) prev->next = cur->next;
                else head = cur->next;
                delete cur;
                --nnz_count;
            } else {
                cur->val = v;
            }
            return;
        }
        if (v == 0.0) return; // nothing to store
        // insert new node before cur
        Node* node = new Node(c, v, cur);
        if (prev) prev->next = node;
        else head = node;
        ++nnz_count;
    }

    static SparseMatrixLL add(const SparseMatrixLL& A, const SparseMatrixLL& B) {
        require_same_shape(A, B);
        SparseMatrixLL C(A.R, A.C);
        for (int r = 0; r < A.R; ++r) {
            Node* a = A.heads[r];
            Node* b = B.heads[r];
            while (a || b) {
                if (b == nullptr || (a && a->col < b->col)) {
                    C.set(r, a->col, a->val);
                    a = a->next;
                } else if (a == nullptr || (b && b->col < a->col)) {
                    C.set(r, b->col, b->val);
                    b = b->next;
                } else {
                    double s = a->val + b->val;
                    if (s != 0.0) C.set(r, a->col, s);
                    a = a->next;
                    b = b->next;
                }
            }
        }
        return C;
    }

    static SparseMatrixLL multiply(const SparseMatrixLL& A, const SparseMatrixLL& B) {
        if (A.C != B.R) throw invalid_argument("shape mismatch in multiply");
        // For faster col access, compute BT = B^T to iterate rows
        SparseMatrixLL BT = B.transpose();
        SparseMatrixLL C(A.R, B.C);

        for (int i = 0; i < A.R; ++i) {
            for (Node* a = A.heads[i]; a; a = a->next) {
                int k = a->col;
                double aval = a->val;
                // Row k in B is column k in BT
                for (Node* b = BT.heads[k]; b; b = b->next) {
                    int j = b->col; // corresponds to B(k, j)
                    double add_val = aval * b->val;
                    if (add_val != 0.0) {
                        double cur = C.get(i, j);
                        double nxt = cur + add_val;
                        if (nxt != 0.0) C.set(i, j, nxt);
                        else if (cur != 0.0) C.set(i, j, 0.0); // remove
                    }
                }
            }
        }
        return C;
    }

    SparseMatrixLL transpose() const {
        SparseMatrixLL T(C, R);
        for (int i = 0; i < R; ++i) {
            for (Node* a = heads[i]; a; a = a->next) {
                T.set(a->col, i, a->val);
            }
        }
        return T;
    }

    void print_dense_like(ostream& os) const {
        for (int i = 0; i < R; ++i) {
            Node* cur = heads[i];
            int next_col = cur ? cur->col : C;
            for (int j = 0; j < C; ++j) {
                if (cur && j == cur->col) {
                    os << cur->val;
                    cur = cur->next;
                } else {
                    os << 0;
                }
                if (j + 1 < C) os << ' ';
            }
            os << '\n';
        }
    }

    void print_coo(ostream& os) const {
        // row, col, val triplets
        for (int i = 0; i < R; ++i) {
            for (Node* cur = heads[i]; cur; cur = cur->next) {
                os << i << ' ' << cur->col << ' ' << cur->val << '\n';
            }
        }
    }

private:
    int R, C;
    vector<Node*> heads;
    size_t nnz_count;

    void check_rc(int r, int c) const {
        if (r < 0 || r >= R || c < 0 || c >= C) throw out_of_range("index out of range");
    }

    static void require_same_shape(const SparseMatrixLL& A, const SparseMatrixLL& B) {
        if (A.R != B.R || A.C != B.C) throw invalid_argument("shape mismatch in add");
    }

    void clear() {
        for (Node*& head : heads) {
            while (head) {
                Node* nxt = head->next;
                delete head;
                head = nxt;
            }
        }
        nnz_count = 0;
    }
};

static void demo() {
    // Build A
    SparseMatrixLL A(3, 4);
    A.set(0, 1, 5);
    A.set(1, 0, 2);
    A.set(2, 3, -1);

    // Build B
    SparseMatrixLL B(3, 4);
    B.set(0, 1, 3);
    B.set(1, 2, 7);
    B.set(2, 3, 1);

    cout << "A (dense view):\n"; A.print_dense_like(cout);
    cout << "B (dense view):\n"; B.print_dense_like(cout);

    auto C = SparseMatrixLL::add(A, B);
    cout << "C = A + B (dense view):\n"; C.print_dense_like(cout);

    // Multiply A(3x4) by Bt(4x2) to show multiply
    SparseMatrixLL Bt(4, 2);
    Bt.set(1, 0, 2);
    Bt.set(3, 1, 4);
    cout << "Bt (dense view):\n"; Bt.print_dense_like(cout);

    auto P = SparseMatrixLL::multiply(A, Bt);
    cout << "P = A * Bt (dense view):\n"; P.print_dense_like(cout);

    // Transpose
    auto AT = A.transpose();
    cout << "A^T (dense view):\n"; AT.print_dense_like(cout);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Run demo. Replace with I/O as needed.
    demo();
    return 0;
}
