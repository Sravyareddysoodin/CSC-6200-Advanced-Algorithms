#include <vector>
#include <unordered_map>
#include <iostream>

// Function to find indices of two numbers in nums that add up to target.
// Assumes exactly one valid solution exists and the same element cannot be used twice.
// Returns indices in any order as a vector.
std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    // Hash map to store value-to-index mappings for quick lookup.
    std::unordered_map<long long, int> seen;
    // Reserve space to reduce rehashing for large inputs, improving performance.
    seen.reserve(nums.size() * 2);
    
    // Iterate through the array to find the pair.
    for (size_t i = 0; i < nums.size(); ++i) {
        // Calculate the complement needed to reach target.
        long long need = static_cast<long long>(target) - nums[i];
        // Check if complement exists in hash map.
        auto it = seen.find(need);
        if (it != seen.end()) {
            // Found a pair; return their indices.
            return {it->second, static_cast<int>(i)};
        }
        // Store current number and its index.
        seen[nums[i]] = i;
    }
    // Unreachable given problem constraints (one solution exists).
    return {};
}

// Main function for testing the twoSum function with example cases.
int main() {
    // Define test cases and their corresponding targets.
    std::vector<std::vector<int>> tests = {{2, 7, 11, 15}, {3, 2, 4}, {3, 3}};
    std::vector<int> targets = {9, 6, 6};
    
    // Run each test case and print results.
    for (size_t i = 0; i < tests.size(); ++i) {
        // Call twoSum and store result.
        auto ans = twoSum(tests[i], targets[i]);
        // Output indices in format [x,y].
        std::cout << "[" << ans[0] << "," << ans[1] << "]\n";
    }
    return 0;
}
