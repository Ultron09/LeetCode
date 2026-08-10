/**
 * Problem: 3225. Maximum Score From Grid Operations
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming, Matrix, Prefix Sum
 * LeetCode Link: https://leetcode.com/problems/maximum-score-from-grid-operations/
 * 
 * Time Complexity:  O(N^3) where N = grid.size() <= 100
 * Space Complexity: O(N^2) using rolling arrays and 2D prefix sums
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = static_cast<int>(grid.size());

        // 1-indexed prefix sums for each column
        // S[i][j] = sum of first j elements in column i (1 <= i <= n, 0 <= j <= n)
        vector<vector<long long>> S(n + 2, vector<long long>(n + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                S[i][j] = S[i][j - 1] + grid[j - 1][i - 1];
            }
        }

        // dp[h_curr][h_prev]: max score after processing up to column i
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));

        // Process columns 2 to n + 1 (column n + 1 is a virtual dummy column)
        for (int i = 2; i <= n + 1; ++i) {
            vector<vector<long long>> next_dp(n + 1, vector<long long>(n + 1, 0));

            // Precompute prefix and suffix maximums from dp
            vector<vector<long long>> prevMax(n + 1, vector<long long>(n + 1, 0));
            vector<vector<long long>> prevSuffixMax(n + 1, vector<long long>(n + 1, 0));

            for (int h_prev = 0; h_prev <= n; ++h_prev) {
                // Compute prevMax[h_prev][j]
                long long currMax = -1e18;
                for (int k = 0; k <= n; ++k) {
                    long long diff = max(0LL, S[i - 1][k] - S[i - 1][h_prev]);
                    currMax = max(currMax, dp[h_prev][k] - diff);
                    prevMax[h_prev][k] = currMax;
                }

                // Compute prevSuffixMax[h_prev][j]
                long long currSuff = -1e18;
                for (int k = n; k >= 0; --k) {
                    currSuff = max(currSuff, dp[h_prev][k]);
                    prevSuffixMax[h_prev][k] = currSuff;
                }
            }

            // Perform O(1) state transitions per (h_curr, h_prev) pair
            for (int h_curr = 0; h_curr <= n; ++h_curr) {
                for (int h_prev = 0; h_prev <= n; ++h_prev) {
                    if (h_curr <= h_prev) {
                        next_dp[h_curr][h_prev] = prevSuffixMax[h_prev][0] + S[i][h_prev] - S[i][h_curr];
                    } else {
                        long long opt1 = prevSuffixMax[h_prev][h_curr];
                        long long opt2 = prevMax[h_prev][h_curr] + S[i - 1][h_curr] - S[i - 1][h_prev];
                        next_dp[h_curr][h_prev] = max(opt1, opt2);
                    }
                }
            }

            dp = move(next_dp);
        }

        // The answer is the max score at the dummy column with height 0
        long long ans = 0;
        for (int h_prev = 0; h_prev <= n; ++h_prev) {
            ans = max(ans, dp[0][h_prev]);
        }

        return ans;
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
        vector<vector<int>> grid = {
            {0, 0, 0, 0, 0},
            {0, 0, 3, 0, 0},
            {0, 1, 0, 0, 0},
            {5, 0, 0, 3, 0},
            {0, 0, 0, 0, 2}
        };
        long long expected = 11;
        assert(solver.maximumScore(grid) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<vector<int>> grid = {
            {10, 9, 0, 0, 15},
            {7, 1, 0, 8, 0},
            {5, 20, 0, 11, 0},
            {0, 0, 0, 1, 2},
            {8, 12, 1, 10, 3}
        };
        long long expected = 94;
        assert(solver.maximumScore(grid) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
