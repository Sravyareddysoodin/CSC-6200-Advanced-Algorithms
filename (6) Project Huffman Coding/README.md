# Week 6: Huffman Coding Project

## Overview
This project implements **Huffman Coding**, a greedy algorithm used for data compression. 
The program constructs a Huffman Tree from a set of characters and their frequencies, 
then prints out the Huffman codes in **preorder traversal** along with the character-to-code mapping.

### Example
**Input:**
```
abcdef
5 9 12 13 16 45
```

**Output:**
```
0 100 101 1100 1101 111
f : 0
c : 100
d : 101
a : 1100
b : 1101
e : 111
```

## How to Compile
From the `(6) Project Huffman Coding` directory, run:
```bash
g++ -std=c++17 -O2 -Wall -Wextra -o huffman huffman.cpp
```

## How to Run
You can run the program in two ways:

1. **Direct execution with built-in sample data:**
```bash
./huffman
```

2. **Using an input file (e.g., input.txt):**
```bash
./huffman < input.txt
```

Where `input.txt` contains:
```
abcdef
5 9 12 13 16 45
```

## Files
- `huffman.cpp` – Source code for Huffman coding implementation
- `README.md` – Documentation file (this file)

## Notes
- The program assumes that the input string consists of **distinct characters**.
- Frequencies must be positive integers provided in the same order as the characters.
