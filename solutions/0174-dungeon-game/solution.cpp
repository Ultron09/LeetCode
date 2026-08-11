/**
 * Problem: 174. Dungeon Game
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming, Matrix
 * LeetCode Link: https://leetcode.com/problems/dungeon-game/
 * 
 * Time Complexity:  O(M * N)
 * Space Complexity: O(N) auxiliary space (using 1D rolling array)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = static_cast<int>(dungeon.size());
        int n = static_cast<int>(dungeon[0].size());

        // dp[j] represents the minimum HP required before entering cell (i, j)
        // Initialize with INT_MAX to safely handle boundary transitions
        vector<int> dp(n + 1, INT_MAX);

        // Base case: to survive after rescuing the princess at (m-1, n-1),
        // we need at least 1 HP upon exiting
        dp[n - 1] = 1;

        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i == m - 1 && j == n - 1) {
                    dp[j] = max(1, 1 - dungeon[i][j]);
                } else {
                    int minExitHP = min(dp[j], dp[j + 1]);
                    dp[j] = max(1, minExitHP - dungeon[i][j]);
                }
            }
        }

        return dp[0];
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: [[-2,-3,3],[-5,-10,1],[10,30,-5]] -> 7
    {
        vector<vector<int>> dungeon = {
            {-2, -3, 3},
            {-5, -10, 1},
            {10, 30, -5}
        };
        assert(solver.calculateMinimumHP(dungeon) == 7);
        cout << "Test 1 Passed: 3x3 Dungeon -> 7" << endl;
    }

    // Test Case 2: [[0]] -> 1
    {
        vector<vector<int>> dungeon = {{0}};
        assert(solver.calculateMinimumHP(dungeon) == 1);
        cout << "Test 2 Passed: Single neutral cell -> 1" << endl;
    }

    // Test Case 3: [[100]] -> 1
    {
        vector<vector<int>> dungeon = {{100}};
        assert(solver.calculateMinimumHP(dungeon) == 1);
        cout << "Test 3 Passed: Single positive cell -> 1" << endl;
    }

    // Test Case 4: [[-100]] -> 101
    {
        vector<vector<int>> dungeon = {{-100}};
        assert(solver.calculateMinimumHP(dungeon) == 101);
        cout << "Test 4 Passed: Single negative cell -> 101" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
