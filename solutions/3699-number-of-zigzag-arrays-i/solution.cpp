/**
 * Problem: 3699. Number of ZigZag Arrays I
 * Difficulty: Hard
 * Topics: Dynamic Programming, Prefix Sum
 * LeetCode Link: https://leetcode.com/problems/number-of-zigzag-arrays-i/
 * 
 * Time Complexity:  O(N * M) where N = n, M = r - l + 1 <= 2000
 * Space Complexity: O(M) using rolling prefix-sum arrays
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        constexpr int MOD = 1'000'000'007;
        int m = r - l + 1;
        if (m <= 1) return 0;

        // Base states at length 2:
        // dp0[j]: number of valid sequences ending with value j where last transition was decreasing
        // dp1[j]: number of valid sequences ending with value j where last transition was increasing
        vector<int> dp0(m);
        vector<int> dp1(m);

        for (int j = 0; j < m; ++j) {
            dp0[j] = m - 1 - j; // Previous element was any value k in [j + 1, m - 1]
            dp1[j] = j;         // Previous element was any value k in [0, j - 1]
        }

        // Rolling transition for length 3 to n
        vector<int> sum0(m + 1, 0);
        vector<int> sum1(m + 1, 0);
        vector<int> next_dp0(m, 0);
        vector<int> next_dp1(m, 0);

        for (int len = 3; len <= n; ++len) {
            // Build prefix sums: sum[j] = sum of dp[0 ... j-1]
            for (int j = 0; j < m; ++j) {
                sum0[j + 1] = (sum0[j] + dp0[j]) % MOD;
                sum1[j + 1] = (sum1[j] + dp1[j]) % MOD;
            }

            for (int j = 0; j < m; ++j) {
                // Decreasing step to j: previous state was increasing (1) with value k in [j + 1, m - 1]
                next_dp0[j] = (sum1[m] - sum1[j + 1] + MOD) % MOD;
                // Increasing step to j: previous state was decreasing (0) with value k in [0, j - 1]
                next_dp1[j] = sum0[j] % MOD;
            }

            dp0 = next_dp0;
            dp1 = next_dp1;
        }

        long long total = 0;
        for (int j = 0; j < m; ++j) {
            total = (total + dp0[j] + dp1[j]) % MOD;
        }

        return static_cast<int>(total);
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
        int n = 3, l = 4, r = 5;
        int expected = 2;
        assert(solver.zigZagArrays(n, l, r) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        int n = 3, l = 1, r = 3;
        int expected = 10;
        assert(solver.zigZagArrays(n, l, r) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
