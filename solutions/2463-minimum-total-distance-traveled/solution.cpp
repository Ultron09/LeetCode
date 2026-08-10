/**
 * Problem: 2463. Minimum Total Distance Traveled
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming, Greedy, Sorting
 * LeetCode Link: https://leetcode.com/problems/minimum-total-distance-traveled/
 * 
 * Time Complexity:  O(M * N * min(N, limit)) where N = robot.size() <= 100, M = factory.size() <= 100
 * Space Complexity: O(N) using space-optimized 1D rolling DP table
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        // Sort robots and factories by their 1D positions
        // Optimal assignment preserves relative spatial order (no path crossing)
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        int n = static_cast<int>(robot.size());
        constexpr long long INF = 1e18;

        // dp[i]: minimum total distance to repair the first i robots
        vector<long long> dp(n + 1, INF);
        dp[0] = 0;

        for (const auto& f : factory) {
            long long pos = f[0];
            int limit = f[1];

            vector<long long> next_dp = dp;

            for (int i = 0; i <= n; ++i) {
                if (dp[i] == INF) continue;

                long long cost = 0;
                // Assign k robots (1 <= k <= limit) to the current factory
                for (int k = 1; k <= limit && i + k <= n; ++k) {
                    cost += std::abs(static_cast<long long>(robot[i + k - 1]) - pos);
                    if (dp[i] + cost < next_dp[i + k]) {
                        next_dp[i + k] = dp[i] + cost;
                    }
                }
            }

            dp = move(next_dp);
        }

        return dp[n];
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
        vector<int> robot = {0, 4, 6};
        vector<vector<int>> factory = {{2, 2}, {6, 2}};
        long long expected = 4;
        assert(solver.minimumTotalDistance(robot, factory) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> robot = {1, -1};
        vector<vector<int>> factory = {{-2, 1}, {2, 1}};
        long long expected = 2;
        assert(solver.minimumTotalDistance(robot, factory) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
