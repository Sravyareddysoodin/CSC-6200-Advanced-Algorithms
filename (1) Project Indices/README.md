   # Two Sum in C++

This repository contains an O(n) hash map solution to the Two Sum problem.

## Build
```bash
g++ -std=c++17 -O2 -Wall -Wextra -o two_sum src/two_sum.cpp
```

## Run
```bash
./two_sum
```

## Approach
Use an unordered_map from value to index. For each nums[i], compute `need = target - nums[i]`. If `need` exists in the map, return `{map[need], i}`. Otherwise insert `nums[i] -> i` and continue.

## Complexity
- **Time:** O(n)
- **Space:** O(n)

## AI usage disclosure
I used ChatGPT to draft the initial implementation notes and README text, then reviewed, compiled, and tested locally. All code and comments were verified and edited by me.
