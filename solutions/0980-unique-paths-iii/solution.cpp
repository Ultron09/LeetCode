/**
 * Problem: 980. Unique Paths III
 * Difficulty: Hard
 * Topics: Array, Backtracking, Bit Manipulation, Matrix
 * LeetCode Link: https://leetcode.com/problems/unique-paths-iii/
 * 
 * Time Complexity:  O(3^(M*N)) where M and N are the dimensions of the grid. At each step, we have at most 3 directions to explore.
 * Space Complexity: O(M*N) for the recursion stack depth during DFS.
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    int paths = 0;
    int m, n;
    
    void dfs(vector<vector<int>>& grid, int x, int y, int current_zeros) {
        if (x < 0 || y < 0 || x >= m || y >= n || grid[x][y] == -1) {
            return;
        }
        
        if (grid[x][y] == 2) {
            if (current_zeros == 0) {
                paths++;
            }
            return;
        }
        
        // Mark as visited by temporarily converting it into an obstacle
        int temp = grid[x][y];
        grid[x][y] = -1;
        
        // Explore all 4 possible directions
        dfs(grid, x + 1, y, current_zeros - 1);
        dfs(grid, x - 1, y, current_zeros - 1);
        dfs(grid, x, y + 1, current_zeros - 1);
        dfs(grid, x, y - 1, current_zeros - 1);
        
        // Backtrack
        grid[x][y] = temp;
    }
    
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        int start_x = 0, start_y = 0;
        int zeros = 0;
        paths = 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    zeros++;
                } else if (grid[i][j] == 1) {
                    start_x = i;
                    start_y = j;
                }
            }
        }
        
        // We pass zeros + 1 to account for the starting square itself
        dfs(grid, start_x, start_y, zeros + 1);
        
        return paths;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    vector<vector<int>> grid1 = {
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 2, -1}
    };
    assert(solver.uniquePathsIII(grid1) == 2);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    vector<vector<int>> grid2 = {
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 2}
    };
    assert(solver.uniquePathsIII(grid2) == 4);
    cout << "Test 2 Passed!" << endl;

    // Test Case 3
    vector<vector<int>> grid3 = {
        {0, 1},
        {2, 0}
    };
    assert(solver.uniquePathsIII(grid3) == 0);
    cout << "Test 3 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
