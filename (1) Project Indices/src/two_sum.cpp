#include <bits/stdc++.h>
using namespace std;

// Return indices of two numbers that add up to target.
// Assumes exactly one valid answer and the same element cannot be used twice.
vector<int> twoSum(const vector<int>& nums, int target) {
    unordered_map<long long, int> seen;  // value -> index
    seen.reserve(nums.size() * 2);
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        long long need = static_cast<long long>(target) - nums[i];
        auto it = seen.find(need);
        if (it != seen.end()) {
            return {it->second, i};  // any order is fine
        }
        seen[nums[i]] = i;
    }
    return {};  // should never reach here under the problem guarantee
}

// Simple driver for quick manual tests.
//
int main() {
    // Example 1
    {
        vector<int> nums = {2, 7, 11, 15};
        int target = 9;
        auto ans = twoSum(nums, target);
        cout << "[" << ans[0] << "," << ans[1] << "]\n";  // expected [0,1]
    }
    // Example 2
    {
        vector<int> nums = {3, 2, 4};
        int target = 6;
        auto ans = twoSum(nums, target);
        cout << "[" << ans[0] << "," << ans[1] << "]\n";  // expected [1,2]
    }
    // Example 3
    {
        vector<int> nums = {3, 3};
        int target = 6;
        auto ans = twoSum(nums, target);
        cout << "[" << ans[0] << "," << ans[1] << "]\n";  // expected [0,1]
    }
    return 0;
}
