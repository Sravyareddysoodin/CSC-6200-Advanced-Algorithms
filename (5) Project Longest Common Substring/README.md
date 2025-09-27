# Week 5: Longest Common Substring Project

## Overview
This project implements the **Longest Common Substring (LCStr)** problem using **Dynamic Programming (DP)** in C++. The program takes two strings of equal length, builds a DP lookup table, and outputs the longest contiguous substring along with its length.

## Compilation
```bash
g++ -std=c++17 -O2 -Wall -Wextra -o lcsubstr lcsubstr.cpp
Usage
Terminal Input
bash

./lcsubstr
Enter first string: ABAB
Enter second string: BABA
File Input
input.txt example:

nginx

ABAB
BABA
Run:

bash

./lcsubstr < input.txt
Example Output
mathematica

Dynamic Programming Table:
0 0 0 0 0
0 0 1 0 1
0 1 0 2 0
0 0 2 0 3
0 1 0 3 0

Longest Common Substring: ABA
Length: 3
