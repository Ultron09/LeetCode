/**
 * Problem: 3548. Equal Sum Grid Partition II
 * Difficulty: Hard
 * Topics: Array, Hash Table, Matrix, Prefix Sum
 * LeetCode Link: https://leetcode.com/problems/equal-sum-grid-partition-ii/
 * 
 * Time Complexity:  O(M * N) where M = grid.length, N = grid[0].length (M * N <= 10^5)
 * Space Complexity: O(M * N) for frequency tracking and matrix transposition
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
private:
    bool checkHorizontal(const vector<vector<int>>& g) {
        int R = static_cast<int>(g.size());
        int C = static_cast<int>(g[0].size());

        long long totalSum = 0;
        vector<long long> rowSums(R, 0);
        unordered_map<long long, int> bottomCount;
        unordered_map<long long, int> topCount;

        bottomCount.reserve(R * C);
        topCount.reserve(R * C);

        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                totalSum += g[r][c];
                rowSums[r] += g[r][c];
                bottomCount[g[r][c]]++;
            }
        }

        long long topSum = 0;
        for (int r = 0; r < R - 1; ++r) {
            int topRows = r + 1;
            int botRows = R - topRows;

            topSum += rowSums[r];
            long long botSum = totalSum - topSum;

            // Move current row elements from bottom partition to top partition
            for (int c = 0; c < C; ++c) {
                int val = g[r][c];
                topCount[val]++;
                if (--bottomCount[val] == 0) {
                    bottomCount.erase(val);
                }
            }

            // Case 1: Exact equal partition with zero discounting
            if (topSum == botSum) {
                return true;
            }

            // Case 2: Discount one cell from the TOP section
            if (topSum > botSum) {
                long long diff = topSum - botSum;
                if (topRows == 1 && C > 1) {
                    // 1 x C row: only endpoints keep the segment connected
                    if (g[0][0] == diff || g[0][C - 1] == diff) return true;
                } else if (C == 1 && topRows > 1) {
                    // R x 1 column: only top/bottom endpoints keep it connected
                    if (g[0][0] == diff || g[topRows - 1][0] == diff) return true;
                } else if (topRows > 1 && C > 1) {
                    // 2D rectangle (>= 2x2): any cell removal preserves connectivity
                    if (topCount.find(diff) != topCount.end()) return true;
                }
            }

            // Case 3: Discount one cell from the BOTTOM section
            if (botSum > topSum) {
                long long diff = botSum - topSum;
                if (botRows == 1 && C > 1) {
                    // 1 x C row: only endpoints keep the segment connected
                    if (g[r + 1][0] == diff || g[r + 1][C - 1] == diff) return true;
                } else if (C == 1 && botRows > 1) {
                    // R x 1 column: only top/bottom endpoints keep it connected
                    if (g[r + 1][0] == diff || g[R - 1][0] == diff) return true;
                } else if (botRows > 1 && C > 1) {
                    // 2D rectangle (>= 2x2): any cell removal preserves connectivity
                    if (bottomCount.find(diff) != bottomCount.end()) return true;
                }
            }
        }

        return false;
    }

    vector<vector<int>> transpose(const vector<vector<int>>& g) {
        int R = static_cast<int>(g.size());
        int C = static_cast<int>(g[0].size());
        vector<vector<int>> t(C, vector<int>(R));
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                t[c][r] = g[r][c];
            }
        }
        return t;
    }

public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        // Check horizontal cuts on original grid or vertical cuts on transposed grid
        return checkHorizontal(grid) || checkHorizontal(transpose(grid));
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
        vector<vector<int>> grid = {{1, 4}, {2, 3}};
        assert(solver.canPartitionGrid(grid) == true);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<vector<int>> grid = {{1, 2}, {3, 4}};
        assert(solver.canPartitionGrid(grid) == true);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3 (Disconnecting removal)
    {
        vector<vector<int>> grid = {{1, 2, 4}, {2, 3, 5}};
        assert(solver.canPartitionGrid(grid) == false);
        cout << "Test 3 Passed!" << endl;
    }

    // Test Case 4: Example 4
    {
        vector<vector<int>> grid = {{4, 1, 8}, {3, 2, 6}};
        assert(solver.canPartitionGrid(grid) == false);
        cout << "Test 4 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
