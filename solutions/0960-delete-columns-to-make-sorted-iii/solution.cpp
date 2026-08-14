/**
 * Problem: 960. Delete Columns to Make Sorted III
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/delete-columns-to-make-sorted-iii/
 * 
 * Time Complexity:  O(M^2 * N) where M is the length of each string and N is the number of strings.
 * Space Complexity: O(M) for the DP array.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public: 
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        if (n == 0) return 0;
        int m = strs[0].size();
        
        // dp[i] represents the length of the longest valid sequence of columns ending at index i
        vector<int> dp(m, 1);
        int max_kept = 1;
        
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < i; ++j) {
                bool valid = true;
                // Check if column j can precede column i for ALL strings
                for (int k = 0; k < n; ++k) {
                    if (strs[k][j] > strs[k][i]) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            max_kept = max(max_kept, dp[i]);
        }
        
        // Minimum deletions = total columns - max columns we can keep
        return m - max_kept;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    {
        vector<string> strs = {"babca", "bbazb"};
        assert(solver.minDeletionSize(strs) == 3);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<string> strs = {"edcba"};
        assert(solver.minDeletionSize(strs) == 4);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3
    {
        vector<string> strs = {"ghi", "def", "abc"};
        assert(solver.minDeletionSize(strs) == 0);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
