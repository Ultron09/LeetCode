/**
 * Problem: 10. Regular Expression Matching
 * Difficulty: Hard
 * Topics: String, Dynamic Programming, Recursion
 * LeetCode Link: https://leetcode.com/problems/regular-expression-matching/
 * 
 * Time Complexity:  O(M * N) where M = s.length() <= 20, N = p.length() <= 20
 * Space Complexity: O(M * N) (or O(N) space-optimized)
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = static_cast<int>(s.length());
        int n = static_cast<int>(p.length());

        // dp[i][j] indicates whether s[0..i-1] matches p[0..j-1]
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;

        // Base cases: patterns like a*, a*b*, a*b*c* can match an empty string
        for (int j = 2; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                    // Direct single character match or wildcard dot
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    // Case 1: Match zero occurrences of preceding character p[j - 2]
                    dp[i][j] = dp[i][j - 2];

                    // Case 2: Match one or more occurrences of preceding character p[j - 2]
                    if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }

        return dp[m][n];
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    assert(solver.isMatch("aa", "a") == false);
    cout << "Test 1 Passed: ('aa', 'a') -> false" << endl;

    // Test Case 2
    assert(solver.isMatch("aa", "a*") == true);
    cout << "Test 2 Passed: ('aa', 'a*') -> true" << endl;

    // Test Case 3
    assert(solver.isMatch("ab", ".*") == true);
    cout << "Test 3 Passed: ('ab', '.*') -> true" << endl;

    // Test Case 4: Preceding multiplier with leading mismatch
    assert(solver.isMatch("aab", "c*a*b") == true);
    cout << "Test 4 Passed: ('aab', 'c*a*b') -> true" << endl;

    // Test Case 5: Complex non-match
    assert(solver.isMatch("mississippi", "mis*is*p*.") == false);
    cout << "Test 5 Passed: ('mississippi', 'mis*is*p*.') -> false" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
