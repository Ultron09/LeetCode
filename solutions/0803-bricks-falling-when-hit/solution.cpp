/**
 * Problem: 803. Bricks Falling When Hit
 * Difficulty: Hard
 * Topics: Array, Matrix, Union Find (Disjoint Set Union)
 * LeetCode Link: https://leetcode.com/problems/bricks-falling-when-hit/
 *
 * Approach: Reverse Time + Disjoint Set Union (DSU)
 *
 * Key Insight:
 *   Simulating the removal of bricks and detecting disconnected components is 
 *   computationally expensive because splitting a connected component is hard.
 *   However, adding edges and merging components is easy and fast using DSU.
 *
 *   Therefore, we can process time in reverse:
 *   1. Erase all the bricks mentioned in `hits` from the grid.
 *   2. Build a DSU for the remaining bricks. We use a special "roof" node to 
 *      represent the top of the grid. Any brick in row 0 is connected to the roof.
 *      The DSU maintains the size of each component.
 *   3. Traverse the `hits` in reverse order (from last to first):
 *      - If the original grid didn't have a brick at the hit location, ignore it (0 dropped).
 *      - Otherwise, add the brick back to the grid.
 *      - Connect it to adjacent bricks (up, down, left, right) and to the roof if it's 
 *        in row 0.
 *      - Count how many *new* bricks became connected to the roof as a result of this 
 *        operation. If the new brick connects to the roof, the number of fallen bricks 
 *        for this hit is `(new_roof_size - old_roof_size - 1)`. We subtract 1 because 
 *        the brick we just added doesn't count as a "falling" brick.
 *
 * Time Complexity:  O(M * N + H * alpha(M * N)), where M, N are grid dimensions and H is number of hits.
 * Space Complexity: O(M * N) for the DSU parent and size arrays.
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class DSU {
    vector<int> parent;
    vector<int> size;
public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            // Merge smaller into larger
            if (size[root_i] < size[root_j]) {
                swap(root_i, root_j);
            }
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
        }
    }

    int get_size(int i) {
        return size[find(i)];
    }
};

class Solution {
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int m = grid.size();
        int n = grid[0].size();
        int h = hits.size();
        
        // Mark hits in grid
        vector<vector<int>> current_grid = grid;
        for (int i = 0; i < h; ++i) {
            current_grid[hits[i][0]][hits[i][1]] = 0;
        }
        
        // Initialize DSU. Node m*n is the "roof".
        int roof = m * n;
        DSU dsu(roof + 1);
        
        auto get_id = [&](int r, int c) {
            return r * n + c;
        };
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Connect initial remaining bricks
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (current_grid[i][j] == 1) {
                    if (i == 0) {
                        dsu.unite(get_id(i, j), roof);
                    }
                    if (i > 0 && current_grid[i - 1][j] == 1) {
                        dsu.unite(get_id(i, j), get_id(i - 1, j));
                    }
                    if (j > 0 && current_grid[i][j - 1] == 1) {
                        dsu.unite(get_id(i, j), get_id(i, j - 1));
                    }
                }
            }
        }
        
        vector<int> result(h, 0);
        
        // Reverse time
        for (int i = h - 1; i >= 0; --i) {
            int r = hits[i][0];
            int c = hits[i][1];
            
            if (grid[r][c] == 0) continue; // Was originally empty
            
            int pre_roof_size = dsu.get_size(roof);
            
            // Add brick back
            current_grid[r][c] = 1;
            int current_id = get_id(r, c);
            
            // Connect to adjacent
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && current_grid[nr][nc] == 1) {
                    dsu.unite(current_id, get_id(nr, nc));
                }
            }
            
            // Connect to roof
            if (r == 0) {
                dsu.unite(current_id, roof);
            }
            
            int post_roof_size = dsu.get_size(roof);
            
            // If the size of the roof component increased, it means some bricks became stable
            if (dsu.find(roof) == dsu.find(current_id)) { // check if connected to roof
                result[i] = max(0, post_roof_size - pre_roof_size - 1);
            }
        }
        
        return result;
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
        vector<vector<int>> grid = {{1,0,0,0},{1,1,1,0}};
        vector<vector<int>> hits = {{1,0}};
        vector<int> res = solver.hitBricks(grid, hits);
        vector<int> expected = {2};
        assert(res == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> grid = {{1,0,0,0},{1,1,0,0}};
        vector<vector<int>> hits = {{1,1},{1,0}};
        vector<int> res = solver.hitBricks(grid, hits);
        vector<int> expected = {0, 0};
        assert(res == expected);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
