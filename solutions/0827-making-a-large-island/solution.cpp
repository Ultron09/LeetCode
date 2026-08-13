/**
 * Problem: 827. Making A Large Island
 * Difficulty: Hard
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 * LeetCode Link: https://leetcode.com/problems/making-a-large-island/
 *
 * Approach:
 * Two-pass Component Labeling (similar to Union-Find / Connected Components)
 * 1. First Pass: Traverse the grid to find all islands (connected groups of 1s).
 *    - Use BFS (or DFS) to traverse each island.
 *    - Assign a unique ID (starting from 2 to avoid collision with 0 and 1) to each island.
 *    - Compute the area of each island and store it in an array mapped by the ID.
 *    - Also keep track of the maximum island size found so far.
 * 2. Second Pass: Iterate through every 0 in the grid.
 *    - For each 0, check its 4 neighbors to see if they belong to any islands.
 *    - Sum the areas of the UNIQUE neighboring islands and add 1 (for the 0 flipped to 1).
 *    - Keep track of the maximum possible island size.
 *
 * Time Complexity:  O(N^2) where N x N is the grid size. We visit each cell a constant number of times.
 * Space Complexity: O(N^2) for the BFS queue and the area storage vector in the worst case (e.g. grid full of 1s).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Maximum possible number of components is (N*N)/2.
        // We start IDs from 2, so N*N + 2 is perfectly safe.
        vector<int> area(n * n + 2, 0);
        int comp_id = 2;
        int max_area = 0;
        
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        // Pass 1: Label all existing islands
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    int current_area = 0;
                    
                    // BFS Queue
                    vector<pair<int, int>> q;
                    q.push_back({i, j});
                    grid[i][j] = comp_id;
                    
                    int head = 0;
                    while (head < q.size()) {
                        auto [r, c] = q[head++];
                        current_area++;
                        
                        for (auto& d : dirs) {
                            int nr = r + d[0];
                            int nc = c + d[1];
                            if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                                grid[nr][nc] = comp_id;
                                q.push_back({nr, nc});
                            }
                        }
                    }
                    area[comp_id] = current_area;
                    max_area = max(max_area, current_area);
                    comp_id++;
                }
            }
        }
        
        // Pass 2: Try flipping each 0 to a 1
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    int possible_area = 1;
                    int seen[4] = {0, 0, 0, 0};
                    int seen_count = 0;
                    
                    for (auto& d : dirs) {
                        int nr = i + d[0];
                        int nc = j + d[1];
                        if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] > 1) {
                            int id = grid[nr][nc];
                            
                            // Check if this island ID has already been included
                            bool duplicate = false;
                            for (int k = 0; k < seen_count; ++k) {
                                if (seen[k] == id) {
                                    duplicate = true;
                                    break;
                                }
                            }
                            
                            if (!duplicate) {
                                seen[seen_count++] = id;
                                possible_area += area[id];
                            }
                        }
                    }
                    
                    max_area = max(max_area, possible_area);
                }
            }
        }
        
        return max_area;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    {
        vector<vector<int>> grid = {{1,0},{0,1}};
        int res = solver.largestIsland(grid);
        assert(res == 3);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> grid = {{1,1},{1,0}};
        int res = solver.largestIsland(grid);
        assert(res == 4);
        cout << "Test 2 Passed! Result: " << res << endl;
    }

    // Test Case 3
    {
        vector<vector<int>> grid = {{1,1},{1,1}};
        int res = solver.largestIsland(grid);
        assert(res == 4);
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    // Test Case 4 (No 1s)
    {
        vector<vector<int>> grid = {{0,0},{0,0}};
        int res = solver.largestIsland(grid);
        assert(res == 1);
        cout << "Test 4 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
