/**
 * Problem: 675. Cut Off Trees for Golf Event
 * Difficulty: Hard
 * Topics: Array, Breadth-First Search, Graph, Heap (Priority Queue), Matrix
 * LeetCode Link: https://leetcode.com/problems/cut-off-trees-for-golf-event/
 * 
 * Time Complexity:  O(T * M * N) = O(M^2 * N^2) where T <= M * N is the number of trees (M, N <= 50)
 * Space Complexity: O(M * N) for the BFS queue and visited matrix
 */

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    // Standard BFS to find shortest path from (sr, sc) to (tr, tc)
    int bfs(const vector<vector<int>>& forest, int sr, int sc, int tr, int tc, int m, int n) {
        if (sr == tr && sc == tc) return 0;

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;

        q.push({sr, sc});
        visited[sr][sc] = true;

        int steps = 0;
        const int dr[] = {-1, 1, 0, 0};
        const int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            int sz = q.size();
            ++steps;

            while (sz--) {
                auto [r, c] = q.front();
                q.pop();

                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc] && forest[nr][nc] != 0) {
                        if (nr == tr && nc == tc) {
                            return steps;
                        }
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
        }

        return -1; // Unreachable
    }

public:
    int cutOffTree(vector<vector<int>>& forest) {
        int m = forest.size();
        int n = forest[0].size();

        // Step 1: Collect all trees and sort them by height in ascending order
        vector<tuple<int, int, int>> trees; // {height, row, col}
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (forest[r][c] > 1) {
                    trees.emplace_back(forest[r][c], r, c);
                }
            }
        }

        sort(trees.begin(), trees.end());

        // Step 2: Traverse from current position to each tree in sorted order
        int sr = 0, sc = 0;
        int totalSteps = 0;

        for (const auto& [height, tr, tc] : trees) {
            int steps = bfs(forest, sr, sc, tr, tc, m, n);
            if (steps == -1) {
                return -1; // Forest is disconnected / unreachable
            }
            totalSteps += steps;
            sr = tr;
            sc = tc;
        }

        return totalSteps;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1
    {
        vector<vector<int>> forest = {
            {1, 2, 3},
            {0, 0, 4},
            {7, 6, 5}
        };
        int result = solver.cutOffTree(forest);
        cout << "Test 1 -> Expected: 6, Got: " << result << endl;
        assert(result == 6);
    }

    // Test Case 2: Blocked forest (Example 2)
    {
        vector<vector<int>> forest = {
            {1, 2, 3},
            {0, 0, 0},
            {7, 6, 5}
        };
        int result = solver.cutOffTree(forest);
        cout << "Test 2 -> Expected: -1, Got: " << result << endl;
        assert(result == -1);
    }

    // Test Case 3: Starting directly at the shortest tree (Example 3)
    {
        vector<vector<int>> forest = {
            {2, 3, 4},
            {0, 0, 5},
            {8, 7, 6}
        };
        int result = solver.cutOffTree(forest);
        cout << "Test 3 -> Expected: 6, Got: " << result << endl;
        assert(result == 6);
    }

    // Test Case 4: Single tree at (0, 0)
    {
        vector<vector<int>> forest = {
            {5}
        };
        int result = solver.cutOffTree(forest);
        cout << "Test 4 -> Expected: 0, Got: " << result << endl;
        assert(result == 0);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
