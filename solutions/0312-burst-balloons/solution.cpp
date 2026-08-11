/**
 * Problem: 312. Burst Balloons
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/burst-balloons/
 * 
 * Time Complexity:  O(N^3) where N <= 300 (Interval DP with (N^3)/6 operations)
 * Space Complexity: O(N^2) for the 2D DP memoization table
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        
        // Pad array with boundary sentinel values of 1
        vector<int> vals(n + 2, 1);
        for (int i = 0; i < n; ++i) {
            vals[i + 1] = nums[i];
        }

        int m = n + 2;
        // dp[i][j] = maximum coins collected by bursting all balloons strictly between i and j (exclusive)
        vector<vector<int>> dp(m, vector<int>(m, 0));

        // Iterate over interval length: len = j - i
        for (int len = 2; len < m; ++len) {
            for (int i = 0; i + len < m; ++i) {
                int j = i + len;
                // Try choosing balloon k as the LAST balloon to burst in interval (i, j)
                for (int k = i + 1; k < j; ++k) {
                    int coins = vals[i] * vals[k] * vals[j] + dp[i][k] + dp[k][j];
                    dp[i][j] = max(dp[i][j], coins);
                }
            }
        }

        return dp[0][m - 1];
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: [3, 1, 5, 8] -> 167
    {
        vector<int> nums = {3, 1, 5, 8};
        assert(solver.maxCoins(nums) == 167);
        cout << "Test 1 Passed: [3, 1, 5, 8] -> 167" << endl;
    }

    // Test Case 2: [1, 5] -> 10
    {
        vector<int> nums = {1, 5};
        assert(solver.maxCoins(nums) == 10);
        cout << "Test 2 Passed: [1, 5] -> 10" << endl;
    }

    // Test Case 3: Single element [7] -> 7
    {
        vector<int> nums = {7};
        assert(solver.maxCoins(nums) == 7);
        cout << "Test 3 Passed: [7] -> 7" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
