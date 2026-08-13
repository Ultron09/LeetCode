/**
 * Problem: 741. Cherry Pickup
 * Difficulty: Hard
 * Topics: Dynamic Programming, Matrix
 * LeetCode Link: https://leetcode.com/problems/cherry-pickup/
 *
 * Approach: Two Simultaneous Forward Paths (3D DP)
 *
 * Key Insight:
 *   Going (0,0)→(n-1,n-1) then back is equivalent to sending TWO
 *   people simultaneously from (0,0) to (n-1,n-1), both moving only
 *   right or down. If they land on the same cell, the cherry is only
 *   counted once.
 *
 *   State: dp[t][r1][r2] = max cherries when both have taken t steps,
 *          person 1 is at row r1 (col = t - r1),
 *          person 2 is at row r2 (col = t - r2).
 *
 *   At each step, both persons independently move right or down,
 *   giving 4 transitions per state.
 *
 * Time Complexity:  O(N³) — t ranges [0, 2N-2], r1 and r2 each [0, N-1]
 * Space Complexity: O(N²) — rolling array optimization on t
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        const int NEG_INF = -1e9;

        // dp[r1][r2] = max cherries when both persons have taken t steps,
        // person 1 at (r1, t-r1), person 2 at (r2, t-r2)
        vector<vector<int>> dp(n, vector<int>(n, NEG_INF));
        dp[0][0] = grid[0][0];

        // Total steps to reach (n-1, n-1) = 2*(n-1)
        for (int t = 1; t <= 2 * (n - 1); ++t) {
            vector<vector<int>> ndp(n, vector<int>(n, NEG_INF));

            // r1 and r2 must satisfy: 0 <= r1 <= min(t, n-1)
            // and c1 = t - r1 must satisfy: 0 <= c1 <= n-1
            int rMin = max(0, t - (n - 1));
            int rMax = min(t, n - 1);

            for (int r1 = rMin; r1 <= rMax; ++r1) {
                int c1 = t - r1;
                if (c1 < 0 || c1 >= n) continue;
                if (grid[r1][c1] == -1) continue;

                for (int r2 = r1; r2 <= rMax; ++r2) { // r2 >= r1 by symmetry
                    int c2 = t - r2;
                    if (c2 < 0 || c2 >= n) continue;
                    if (grid[r2][c2] == -1) continue;

                    // Cherries collected at this step
                    int cherries = grid[r1][c1];
                    if (r1 != r2) { // Different cells
                        cherries += grid[r2][c2];
                    }

                    // Try all 4 previous states:
                    // Person 1 came from (r1, c1-1) or (r1-1, c1) → prev r1 is r1 or r1-1
                    // Person 2 came from (r2, c2-1) or (r2-1, c2) → prev r2 is r2 or r2-1
                    int best = NEG_INF;
                    for (int pr1 : {r1, r1 - 1}) {
                        for (int pr2 : {r2, r2 - 1}) {
                            if (pr1 >= 0 && pr2 >= 0 && pr1 < n && pr2 < n) {
                                // Maintain symmetry: ensure pr1 <= pr2
                                int a = min(pr1, pr2), b = max(pr1, pr2);
                                best = max(best, dp[a][b]);
                            }
                        }
                    }

                    if (best > NEG_INF) {
                        ndp[r1][r2] = max(ndp[r1][r2], best + cherries);
                    }
                }
            }

            dp = move(ndp);
        }

        return max(0, dp[n - 1][n - 1]);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard example
    {
        vector<vector<int>> grid = {{0,1,-1},{1,0,-1},{1,1,1}};
        int result = solver.cherryPickup(grid);
        assert(result == 5);
        cout << "Test 1 Passed! → " << result << endl;
    }

    // Test Case 2: No valid path
    {
        vector<vector<int>> grid = {{1,1,-1},{1,-1,1},{-1,1,1}};
        int result = solver.cherryPickup(grid);
        assert(result == 0);
        cout << "Test 2 Passed! → " << result << endl;
    }

    // Test Case 3: 1x1 grid
    {
        vector<vector<int>> grid = {{1}};
        int result = solver.cherryPickup(grid);
        assert(result == 1);
        cout << "Test 3 Passed! → " << result << endl;
    }

    // Test Case 4: All cherries, no thorns
    {
        vector<vector<int>> grid = {{1,1,1},{1,1,1},{1,1,1}};
        // Two paths can collect at most 2*(3-1)+2*(3-1)+1 = 9? Actually 2*5-1 = 9
        // Path 1: (0,0)→(0,1)→(0,2)→(1,2)→(2,2) picks 5
        // Path 2: (0,0)→(1,0)→(2,0)→(2,1)→(2,2) picks 4 new (shared start+end)
        // Total = 5 + 4 - 0(shared at start already picked) = hmm
        // Actually two paths both from (0,0) to (2,2):
        // Max is min(9, total cherries) if paths don't overlap much
        // Both go diagonal-ish: 5 cells each, 1 shared (start), so 9 cells total... but grid has 9 cells total all with cherries
        // Actually they share (0,0) and (2,2), so 5+5-2 = 8... but grid is 9.
        // Hmm, two paths of length 5 covering 8 unique cells = 8 cherries.
        int result = solver.cherryPickup(grid);
        assert(result == 8);
        cout << "Test 4 Passed! → " << result << endl;
    }

    // Test Case 5: All empty
    {
        vector<vector<int>> grid = {{0,0},{0,0}};
        int result = solver.cherryPickup(grid);
        assert(result == 0);
        cout << "Test 5 Passed! → " << result << endl;
    }

    // Test Case 6: 2x2 with cherries
    {
        vector<vector<int>> grid = {{1,1},{1,1}};
        // Path 1: right,down (picks 1+1+1=3) or down,right
        // Path 2: the other path, adds 1 more
        // Total = 4 (all cells picked)
        int result = solver.cherryPickup(grid);
        assert(result == 4);
        cout << "Test 6 Passed! → " << result << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
