/**
 * Problem: 329. Longest Increasing Path in a Matrix
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming, Depth-First Search, Breadth-First Search, Graph, Topological Sort, Memoization
 * LeetCode Link: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
 * 
 * Time Complexity:  O(M * N) - Each cell is visited and computed exactly once via memoized DFS on DAG
 * Space Complexity: O(M * N) - Memoization table and recursion call stack
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    int dfs(const vector<vector<int>>& matrix, int r, int c, vector<vector<int>>& memo, int m, int n) {
        if (memo[r][c] != 0) {
            return memo[r][c];
        }

        int maxLength = 1;
        static const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (const auto& dir : dirs) {
            int nr = r + dir[0];
            int nc = c + dir[1];

            // Only traverse to strictly increasing adjacent neighbors
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && matrix[nr][nc] > matrix[r][c]) {
                maxLength = max(maxLength, 1 + dfs(matrix, nr, nc, memo, m, n));
            }
        }

        return memo[r][c] = maxLength;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        int m = static_cast<int>(matrix.size());
        int n = static_cast<int>(matrix[0].size());

        vector<vector<int>> memo(m, vector<int>(n, 0));
        int longestPath = 0;

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                longestPath = max(longestPath, dfs(matrix, r, c, memo, m, n));
            }
        }

        return longestPath;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: matrix = [[9,9,4],[6,6,8],[2,1,1]] -> 4
    {
        vector<vector<int>> matrix = {
            {9, 9, 4},
            {6, 6, 8},
            {2, 1, 1}
        };
        int expected = 4;
        int result = solver.longestIncreasingPath(matrix);
        assert(result == expected);
        cout << "Test 1 Passed: [[9,9,4],[6,6,8],[2,1,1]] -> " << result << endl;
    }

    // Test Case 2: matrix = [[3,4,5],[3,2,6],[2,2,1]] -> 4
    {
        vector<vector<int>> matrix = {
            {3, 4, 5},
            {3, 2, 6},
            {2, 2, 1}
        };
        int expected = 4;
        int result = solver.longestIncreasingPath(matrix);
        assert(result == expected);
        cout << "Test 2 Passed: [[3,4,5],[3,2,6],[2,2,1]] -> " << result << endl;
    }

    // Test Case 3: Single element matrix = [[1]] -> 1
    {
        vector<vector<int>> matrix = {{1}};
        int expected = 1;
        int result = solver.longestIncreasingPath(matrix);
        assert(result == expected);
        cout << "Test 3 Passed: [[1]] -> " << result << endl;
    }

    // Test Case 4: All equal values matrix = [[7,7],[7,7]] -> 1
    {
        vector<vector<int>> matrix = {
            {7, 7},
            {7, 7}
        };
        int expected = 1;
        int result = solver.longestIncreasingPath(matrix);
        assert(result == expected);
        cout << "Test 4 Passed: All equal [[7,7],[7,7]] -> " << result << endl;
    }

    // Test Case 5: Spiral increasing matrix (3x3) -> 9
    {
        vector<vector<int>> matrix = {
            {1, 2, 3},
            {8, 9, 4},
            {7, 6, 5}
        };
        int expected = 9;
        int result = solver.longestIncreasingPath(matrix);
        assert(result == expected);
        cout << "Test 5 Passed: Spiral path 1->9 -> " << result << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
