/**
 * Problem: 3336. Find the Number of Subsequences With Equal GCD
 * Difficulty: Hard
 * Topics: Array, Math, Dynamic Programming, Number Theory
 * LeetCode Link: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/
 * 
 * Time Complexity:  O(N * M^2) where N = nums.size() <= 200, M = max(nums) <= 200
 * Space Complexity: O(M^2) for 2D DP rolling table
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        constexpr int MOD = 1'000'000'007;

        int maxVal = 0;
        for (int x : nums) {
            maxVal = max(maxVal, x);
        }

        // Precompute GCD table for O(1) transitions
        vector<vector<int>> gcdTable(maxVal + 1, vector<int>(maxVal + 1, 0));
        for (int i = 0; i <= maxVal; ++i) {
            for (int j = 0; j <= maxVal; ++j) {
                if (i == 0) gcdTable[i][j] = j;
                else if (j == 0) gcdTable[i][j] = i;
                else gcdTable[i][j] = std::gcd(i, j);
            }
        }

        // dp[g1][g2]: number of disjoint subsequence pairs with GCD(seq1) = g1 and GCD(seq2) = g2
        // g1 = 0 represents seq1 is empty, g2 = 0 represents seq2 is empty
        vector<vector<int>> dp(maxVal + 1, vector<int>(maxVal + 1, 0));
        dp[0][0] = 1;

        for (int num : nums) {
            vector<vector<int>> nextDp = dp; // Option 1: Skip num (leaves g1, g2 unchanged)

            for (int g1 = 0; g1 <= maxVal; ++g1) {
                for (int g2 = 0; g2 <= maxVal; ++g2) {
                    int ways = dp[g1][g2];
                    if (ways == 0) continue;

                    // Option 2: Add num to seq1
                    int ng1 = gcdTable[g1][num];
                    nextDp[ng1][g2] = (nextDp[ng1][g2] + ways) % MOD;

                    // Option 3: Add num to seq2
                    int ng2 = gcdTable[g2][num];
                    nextDp[g1][ng2] = (nextDp[g1][ng2] + ways) % MOD;
                }
            }

            dp = std::move(nextDp);
        }

        // Sum counts for non-empty subsequences where GCD(seq1) == GCD(seq2)
        int totalPairs = 0;
        for (int g = 1; g <= maxVal; ++g) {
            totalPairs = (totalPairs + dp[g][g]) % MOD;
        }

        return totalPairs;
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
        vector<int> nums = {1, 2, 3, 4};
        int expected = 10;
        assert(solver.subsequencePairCount(nums) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> nums = {10, 20, 30};
        int expected = 2;
        assert(solver.subsequencePairCount(nums) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        vector<int> nums = {1, 1, 1, 1};
        int expected = 50;
        assert(solver.subsequencePairCount(nums) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
