/*
 * Course: CSC 6200 - Advanced Algorithms
 * Assignment: Week 2 Project - Array Implementation for Sparse Matrices
 * Student: Sravya Reddy Soodini
 * University: Concordia University
 * Date: September 2025
 *
 * Description:
 * This program implements a sparse matrix using array-based storage.
 * It uses three arrays (rows, cols, vals) to represent nonzero entries.
 * Supports insertion, retrieval, addition, transpose, and multiplication.
 */

#include <bits/stdc++.h>
using namespace std;

struct Entry {
    int row, col;
    double val;
};

class SparseMatrixArr {
public:
    SparseMatrixArr(int rows, int cols)
        : R(rows), C(cols) {}

    void set(int r, int c, double v) {
        check_rc(r, c);
        for (auto &e : entries) {
            if (e.row == r && e.col == c) {
                if (v == 0.0) {
                    e = entries.back();
                    entries.pop_back();
                } else {
                    e.val = v;
                }
                return;
            }
        }
        if (v != 0.0) {
            entries.push_back({r, c, v});
        }
    }

    double get(int r, int c) const {
        check_rc(r, c);
        for (const auto &e : entries) {
            if (e.row == r && e.col == c) return e.val;
        }
        return 0.0;
    }

    SparseMatrixArr transpose() const {
        SparseMatrixArr T(C, R);
        for (auto &e : entries) {
            T.set(e.col, e.row, e.val);
        }
        return T;
    }

    static SparseMatrixArr add(const SparseMatrixArr& A, const SparseMatrixArr& B) {
        if (A.R != B.R || A.C != B.C) throw invalid_argument("shape mismatch in add");
        SparseMatrixArr C(A.R, A.C);
        for (auto &e : A.entries) C.set(e.row, e.col, e.val);
        for (auto &e : B.entries) {
            double sum = C.get(e.row, e.col) + e.val;
            C.set(e.row, e.col, sum);
        }
        return C;
    }

    static SparseMatrixArr multiply(const SparseMatrixArr& A, const SparseMatrixArr& B) {
        if (A.C != B.R) throw invalid_argument("shape mismatch in multiply");
        SparseMatrixArr C(A.R, B.C);
        for (auto &ea : A.entries) {
            for (auto &eb : B.entries) {
                if (ea.col == eb.row) {
                    double cur = C.get(ea.row, eb.col);
                    C.set(ea.row, eb.col, cur + ea.val * eb.val);
                }
            }
        }
        return C;
    }

    void print_dense_like() const {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cout << get(i, j) << " ";
            }
            cout << "\n";
        }
    }

    void print_coo() const {
        for (auto &e : entries) {
            cout << e.row << " " << e.col << " " << e.val << "\n";
        }
    }

private:
    int R, C;
    vector<Entry> entries;

    void check_rc(int r, int c) const {
        if (r < 0 || r >= R || c < 0 || c >= C) throw out_of_range("index out of range");
    }
};

// Demo
int main() {
    SparseMatrixArr A(3, 3);
    A.set(0, 1, 2);
    A.set(1, 2, 5);
    A.set(2, 0, -1);

    SparseMatrixArr B(3, 3);
    B.set(0, 1, 3);
    B.set(1, 2, 4);
    B.set(2, 0, 1);

    cout << "Matrix A (dense view):\n"; A.print_dense_like();
    cout << "Matrix B (dense view):\n"; B.print_dense_like();

    auto C = SparseMatrixArr::add(A, B);
    cout << "A + B (dense view):\n"; C.print_dense_like();

    auto AT = A.transpose();
    cout << "A^T (dense view):\n"; AT.print_dense_like();

    auto P = SparseMatrixArr::multiply(A, B);
    cout << "A * B (dense view):\n"; P.print_dense_like();

    return 0;
}
