/**
 * Problem: 115. Distinct Subsequences
 * Difficulty: Hard
 * Topics: String, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/distinct-subsequences/
 * 
 * Time Complexity:  O(M * N) where M = s.length(), N = t.length()
 * Space Complexity: O(N) space-optimized rolling DP table
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cassert>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = static_cast<int>(s.length());
        int n = static_cast<int>(t.length());

        if (m < n) {
            return 0;
        }

        // dp[j] stores the number of subsequences of current s-prefix matching t[0..j-1]
        // Use unsigned long long to prevent intermediate overflow during accumulation
        vector<unsigned long long> dp(n + 1, 0ULL);
        dp[0] = 1ULL; // Empty string match base case

        for (int i = 1; i <= m; ++i) {
            char charS = s[i - 1];
            // Iterate backwards to use previous row values in-place
            for (int j = n; j >= 1; --j) {
                if (charS == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return static_cast<int>(dp[n]);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: s = "rabbbit", t = "rabbit" -> 3
    {
        string s = "rabbbit";
        string t = "rabbit";
        assert(solver.numDistinct(s, t) == 3);
        cout << "Test 1 Passed: rabbbit -> rabbit (3)" << endl;
    }

    // Test Case 2: s = "babgbag", t = "bag" -> 5
    {
        string s = "babgbag";
        string t = "bag";
        assert(solver.numDistinct(s, t) == 5);
        cout << "Test 2 Passed: babgbag -> bag (5)" << endl;
    }

    // Test Case 3: s = "a", t = "b" -> 0
    {
        string s = "a";
        string t = "b";
        assert(solver.numDistinct(s, t) == 0);
        cout << "Test 3 Passed: a -> b (0)" << endl;
    }

    // Test Case 4: s = "a", t = "a" -> 1
    {
        string s = "a";
        string t = "a";
        assert(solver.numDistinct(s, t) == 1);
        cout << "Test 4 Passed: a -> a (1)" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
