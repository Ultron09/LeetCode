/**
 * Problem: 2573. Find the String with LCP
 * Difficulty: Hard
 * Topics: Array, String, Dynamic Programming, Greedy, Matrix
 * LeetCode Link: https://leetcode.com/problems/find-the-string-with-lcp/
 * 
 * Time Complexity:  O(N^2) where N = lcp.size() <= 1000
 * Space Complexity: O(N^2) for 2D DP validation matrix (or O(N) rolling space)
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = static_cast<int>(lcp.size());
        string word(n, '\0');
        int charCode = 0;

        // 1. Greedy alphabetical character assignment
        for (int i = 0; i < n; ++i) {
            if (word[i] == '\0') {
                if (charCode >= 26) {
                    // Requires more than 26 distinct lowercase letters
                    return "";
                }
                word[i] = static_cast<char>('a' + charCode);
                charCode++;

                // Propagate character to all positions that share a non-zero LCP with i
                for (int j = i + 1; j < n; ++j) {
                    if (lcp[i][j] > 0) {
                        word[j] = word[i];
                    }
                }
            }
        }

        // 2. Suffix DP matrix reconstruction and validation
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (word[i] == word[j]) {
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                } else {
                    dp[i][j] = 0;
                }

                if (dp[i][j] != lcp[i][j]) {
                    // Constructed string violates the provided LCP matrix
                    return "";
                }
            }
        }

        return word;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1
    {
        vector<vector<int>> lcp = {
            {4, 0, 2, 0},
            {0, 3, 0, 1},
            {2, 0, 2, 0},
            {0, 1, 0, 1}
        };
        string expected = "abab";
        assert(solver.findTheString(lcp) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<vector<int>> lcp = {
            {4, 3, 2, 1},
            {3, 3, 2, 1},
            {2, 2, 2, 1},
            {1, 1, 1, 1}
        };
        string expected = "aaaa";
        assert(solver.findTheString(lcp) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3 (Impossible LCP matrix)
    {
        vector<vector<int>> lcp = {
            {4, 3, 2, 1},
            {3, 3, 2, 1},
            {2, 2, 2, 1},
            {1, 1, 1, 3}
        };
        string expected = "";
        assert(solver.findTheString(lcp) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
