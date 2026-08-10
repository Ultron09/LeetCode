/**
 * Problem: 132. Palindrome Partitioning II
 * Difficulty: Hard
 * Topics: String, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/palindrome-partitioning-ii/
 * 
 * Time Complexity:  O(N^2) where N = s.length()
 * Space Complexity: O(N) auxiliary space for DP cuts array
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
public:
    int minCut(string s) {
        int n = static_cast<int>(s.length());
        if (n <= 1) {
            return 0;
        }

        // dp[i] stores the minimum cuts needed for substring prefix s[0..i]
        // Initially, worst-case cuts is i (each single character isolated)
        vector<int> dp(n);
        iota(dp.begin(), dp.end(), 0);

        for (int i = 0; i < n; ++i) {
            // Expand odd-length palindromes centered at i
            expandAroundCenter(s, i, i, n, dp);

            // Expand even-length palindromes centered at i and i + 1
            expandAroundCenter(s, i, i + 1, n, dp);
        }

        return dp[n - 1];
    }

private:
    void expandAroundCenter(const string& s, int l, int r, int n, vector<int>& dp) {
        while (l >= 0 && r < n && s[l] == s[r]) {
            if (l == 0) {
                dp[r] = 0; // Prefix s[0..r] is palindrome, no cuts needed
            } else {
                dp[r] = min(dp[r], dp[l - 1] + 1);
            }
            --l;
            ++r;
        }
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: s = "aab" -> 1 (["aa", "b"])
    {
        string s = "aab";
        assert(solver.minCut(s) == 1);
        cout << "Test 1 Passed: \"aab\" -> 1" << endl;
    }

    // Test Case 2: s = "a" -> 0
    {
        string s = "a";
        assert(solver.minCut(s) == 0);
        cout << "Test 2 Passed: \"a\" -> 0" << endl;
    }

    // Test Case 3: s = "ab" -> 1
    {
        string s = "ab";
        assert(solver.minCut(s) == 1);
        cout << "Test 3 Passed: \"ab\" -> 1" << endl;
    }

    // Test Case 4: s = "abacaba" -> 0 (already palindrome)
    {
        string s = "abacaba";
        assert(solver.minCut(s) == 0);
        cout << "Test 4 Passed: \"abacaba\" -> 0" << endl;
    }

    // Test Case 5: s = "coder" -> 4
    {
        string s = "coder";
        assert(solver.minCut(s) == 4);
        cout << "Test 5 Passed: \"coder\" -> 4" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
