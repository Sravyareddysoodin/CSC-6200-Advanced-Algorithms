// Course: CSC 6200 Advanced Algorithms
// Project: (5) Longest Common Substring
// Student: Sravya Reddy Soodini
// File: lcsubstr.cpp

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;

    int m = s1.size();
    int n = s2.size();

    // DP table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    int maxLen = 0;
    int endPos = 0;

    // Fill DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    endPos = i; // record end index in s1
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // Print DP table
    cout << "\nDP Table:\n";
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }

    // Extract substring
    string lcs = s1.substr(endPos - maxLen, maxLen);

    cout << "\nLongest Common Substring: " << lcs << "\n";
    cout << "Length: " << maxLen << "\n";

    return 0;
}
