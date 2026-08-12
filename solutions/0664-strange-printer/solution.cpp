/**
 * Problem: 664. Strange Printer
 * Difficulty: Hard
 * Topics: Dynamic Programming, String
 * LeetCode Link: https://leetcode.com/problems/strange-printer/
 * 
 * Time Complexity:  O(N^3) where N <= 100 is the length of the compressed string
 * Space Complexity: O(N^2) for the 2D interval DP memoization table
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int strangePrinter(string s) {
        if (s.empty()) return 0;

        // Step 1: Compress consecutive duplicate characters
        string compact = "";
        for (char c : s) {
            if (compact.empty() || compact.back() != c) {
                compact.push_back(c);
            }
        }

        int n = compact.length();
        // dp[i][j]: Minimum turns needed to print substring compact[i...j]
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: Substrings of length 1 require 1 turn
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }

        // Step 2: Interval DP by increasing substring length
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;

                // Baseline: Print compact[j] in a new separate turn
                dp[i][j] = dp[i][j - 1] + 1;

                // Optimization: If compact[k] == compact[j], compact[j] can be covered
                // in the same turn that originally printed compact[k].
                for (int k = i; k < j; ++k) {
                    if (compact[k] == compact[j]) {
                        int cost = dp[i][k] + (k + 1 <= j - 1 ? dp[k + 1][j - 1] : 0);
                        dp[i][j] = min(dp[i][j], cost);
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1 ("aaabbb")
    {
        string s = "aaabbb";
        int result = solver.strangePrinter(s);
        cout << "Test 1 - s=\"aaabbb\" -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 2: Example 2 ("aba")
    {
        string s = "aba";
        int result = solver.strangePrinter(s);
        cout << "Test 2 - s=\"aba\" -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 3: Palindromic nesting ("abacaba")
    {
        string s = "abacaba";
        int result = solver.strangePrinter(s);
        cout << "Test 3 - s=\"abacaba\" -> Expected: 4, Got: " << result << endl;
        assert(result == 4);
    }

    // Test Case 4: Single character
    {
        string s = "a";
        int result = solver.strangePrinter(s);
        cout << "Test 4 - s=\"a\" -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    // Test Case 5: All distinct characters ("abcde")
    {
        string s = "abcde";
        int result = solver.strangePrinter(s);
        cout << "Test 5 - s=\"abcde\" -> Expected: 5, Got: " << result << endl;
        assert(result == 5);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
