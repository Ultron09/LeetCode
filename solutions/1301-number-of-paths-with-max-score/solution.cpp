/**
 * Problem: 1301. Number of Paths with Max Score
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming, Matrix
 * LeetCode Link: https://leetcode.com/problems/number-of-paths-with-max-score/
 * 
 * Time Complexity:  O(N^2) where N = board.size() <= 100
 * Space Complexity: O(N^2) for 2D DP table (can be optimized to O(N))
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        constexpr int MOD = 1'000'000'007;
        int n = board.size();

        // dp[r][c] stores {maxScore, pathCount} to reach (r, c) from (n-1, n-1)
        // Initialize with maxScore = -1 (unreachable) and pathCount = 0
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {-1, 0}));
        dp[n - 1][n - 1] = {0, 1}; // Starting point 'S'

        // 3 valid directions to arrive at (r, c) from bottom-right
        const vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {1, 1}};

        for (int r = n - 1; r >= 0; --r) {
            for (int c = n - 1; c >= 0; --c) {
                if (r == n - 1 && c == n - 1) continue;
                if (board[r][c] == 'X') continue;

                int bestScore = -1;
                int ways = 0;

                for (const auto& [dr, dc] : directions) {
                    int nr = r + dr;
                    int nc = c + dc;

                    if (nr < n && nc < n && dp[nr][nc].first != -1) {
                        int score = dp[nr][nc].first;
                        int count = dp[nr][nc].second;

                        if (score > bestScore) {
                            bestScore = score;
                            ways = count;
                        } else if (score == bestScore) {
                            ways = (ways + count) % MOD;
                        }
                    }
                }

                if (bestScore != -1) {
                    int val = (board[r][c] == 'E') ? 0 : (board[r][c] - '0');
                    dp[r][c] = {bestScore + val, ways};
                }
            }
        }

        if (dp[0][0].first == -1) {
            return {0, 0};
        }
        return {dp[0][0].first, dp[0][0].second};
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
        vector<string> board = {"E23", "2X2", "12S"};
        vector<int> expected = {7, 1};
        assert(solver.pathsWithMaxScore(board) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<string> board = {"E12", "1X1", "21S"};
        vector<int> expected = {4, 2};
        assert(solver.pathsWithMaxScore(board) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        vector<string> board = {"E11", "XXX", "11S"};
        vector<int> expected = {0, 0};
        assert(solver.pathsWithMaxScore(board) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
