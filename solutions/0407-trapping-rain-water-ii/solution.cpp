/**
 * Problem: 407. Trapping Rain Water II
 * Difficulty: Hard
 * Topics: Array, Breadth-First Search, Heap (Priority Queue), Matrix
 * LeetCode Link: https://leetcode.com/problems/trapping-rain-water-ii/
 * 
 * Time Complexity:  O(M * N * log(M * N)) - Each cell is pushed/popped from the min-heap at most once
 * Space Complexity: O(M * N) - Visited matrix and priority queue storing at most M * N cells
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    struct Cell {
        int height;
        int r, c;

        // Min-heap comparator: smallest height has highest priority
        bool operator>(const Cell& other) const {
            return height > other.height;
        }
    };

public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if (heightMap.empty() || heightMap[0].empty()) return 0;

        int m = heightMap.size();
        int n = heightMap[0].size();
        if (m < 3 || n < 3) return 0; // Boundary only; cannot trap water

        priority_queue<Cell, vector<Cell>, greater<Cell>> minHeap;
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Step 1: Push all outer boundary cells into the min-heap
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r == 0 || r == m - 1 || c == 0 || c == n - 1) {
                    minHeap.push({heightMap[r][c], r, c});
                    visited[r][c] = true;
                }
            }
        }

        int trappedWater = 0;
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        // Step 2: Inward boundary propagation via Dijkstra-like BFS
        while (!minHeap.empty()) {
            Cell curr = minHeap.top();
            minHeap.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = curr.r + dr[i];
                int nc = curr.c + dc[i];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = true;

                    // If neighbor is lower than current spillway height, water is trapped
                    if (heightMap[nr][nc] < curr.height) {
                        trappedWater += curr.height - heightMap[nr][nc];
                    }

                    // Effective boundary height becomes max(curr.height, neighbor's ground height)
                    minHeap.push({max(curr.height, heightMap[nr][nc]), nr, nc});
                }
            }
        }

        return trappedWater;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1 (Multiple small ponds)
    {
        vector<vector<int>> heightMap = {
            {1, 4, 3, 1, 3, 2},
            {3, 2, 1, 3, 2, 4},
            {2, 3, 3, 2, 3, 1}
        };
        int result = solver.trapRainWater(heightMap);
        cout << "Test 1 - Standard 3x6 map -> Expected: 4, Got: " << result << endl;
        assert(result == 4);
    }

    // Test Case 2: Standard Example 2 (Concentric bowl)
    {
        vector<vector<int>> heightMap = {
            {3, 3, 3, 3, 3},
            {3, 2, 2, 2, 3},
            {3, 2, 1, 2, 3},
            {3, 2, 2, 2, 3},
            {3, 3, 3, 3, 3}
        };
        int result = solver.trapRainWater(heightMap);
        cout << "Test 2 - Concentric 5x5 bowl -> Expected: 10, Got: " << result << endl;
        assert(result == 10);
    }

    // Test Case 3: Flat elevation (No water trapped)
    {
        vector<vector<int>> heightMap = {
            {2, 2, 2},
            {2, 2, 2},
            {2, 2, 2}
        };
        int result = solver.trapRainWater(heightMap);
        cout << "Test 3 - Flat 3x3 map -> Expected: 0, Got: " << result << endl;
        assert(result == 0);
    }

    // Test Case 4: Narrow boundary (m < 3 or n < 3)
    {
        vector<vector<int>> heightMap = {
            {1, 2},
            {3, 4}
        };
        int result = solver.trapRainWater(heightMap);
        cout << "Test 4 - 2x2 map -> Expected: 0, Got: " << result << endl;
        assert(result == 0);
    }

    // Test Case 5: 3x3 Single Basin
    {
        vector<vector<int>> heightMap = {
            {5, 5, 5},
            {5, 1, 5},
            {5, 5, 5}
        };
        int result = solver.trapRainWater(heightMap);
        cout << "Test 5 - 3x3 Single basin -> Expected: 4, Got: " << result << endl;
        assert(result == 4);
    }

    // Test Case 6: Unequal boundary spillway (Lowest wall determines water level)
    {
        vector<vector<int>> heightMap = {
            {10, 10, 10},
            {10,  2,  3}, // Spillway at height 3 on the right
            {10, 10, 10}
        };
        int result = solver.trapRainWater(heightMap);
        cout << "Test 6 - Spillway at boundary -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
