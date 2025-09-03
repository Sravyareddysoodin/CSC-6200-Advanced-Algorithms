# Sparse Matrix using Linked Lists (C++)

This project stores only nonzero entries of a matrix using row-wise singly linked lists. Each row keeps nodes sorted by column.

## Features
- get(r, c), set(r, c, v) with automatic deletion on v == 0
- Addition: C = A + B
- Multiplication: C = A * B
- Transpose: A^T
- Print as dense or COO triplets

## Build
g++ -std=c++17 -O2 -Wall -Wextra -o sparse src/sparse_linked_list.cpp

## Run
./sparse

## Complexity
Let nnz be the number of stored nonzeros. Row operations traverse only the nodes in that row. Addition merges rows in O(nnzA + nnzB). Multiplication iterates over nonzeros of A and, for each, over the target row in B^T.

## AI usage disclosure
I used ChatGPT to draft the initial implementation and README. I verified, compiled, and adjusted the code locally.
