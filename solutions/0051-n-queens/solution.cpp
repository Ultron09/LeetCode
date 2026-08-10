/**
 * Problem: 51. N-Queens
 * Difficulty: Hard
 * Topics: Array, Backtracking
 * LeetCode Link: https://leetcode.com/problems/n-queens/
 * 
 * Time Complexity:  O(N!) - at most N choices for row 0, N-1 for row 1, etc.
 * Space Complexity: O(N^2) for the board representation and recursion stack
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
private:
    vector<vector<string>> results;
    int cols = 0;   // Bitmask for columns
    int diag1 = 0;  // Bitmask for main diagonals (r - c + n - 1)
    int diag2 = 0;  // Bitmask for anti-diagonals (r + c)

    void backtrack(int r, int n, vector<string>& board) {
        if (r == n) {
            results.push_back(board);
            return;
        }

        for (int c = 0; c < n; ++c) {
            int d1 = r - c + n - 1;
            int d2 = r + c;

            // Check if column or either diagonal is attacked
            if (!(cols & (1 << c)) && !(diag1 & (1 << d1)) && !(diag2 & (1 << d2))) {
                // Place queen
                board[r][c] = 'Q';
                cols |= (1 << c);
                diag1 |= (1 << d1);
                diag2 |= (1 << d2);

                // Recurse to next row
                backtrack(r + 1, n, board);

                // Backtrack
                board[r][c] = '.';
                cols ^= (1 << c);
                diag1 ^= (1 << d1);
                diag2 ^= (1 << d2);
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        results.clear();
        cols = 0;
        diag1 = 0;
        diag2 = 0;

        vector<string> board(n, string(n, '.'));
        backtrack(0, n, board);
        return results;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: n = 4 -> 2 solutions
    {
        vector<vector<string>> res = solver.solveNQueens(4);
        assert(res.size() == 2);
        cout << "Test 1 Passed: n = 4 -> 2 distinct solutions" << endl;
    }

    // Test Case 2: n = 1 -> 1 solution [["Q"]]
    {
        vector<vector<string>> res = solver.solveNQueens(1);
        assert(res.size() == 1);
        assert(res[0][0] == "Q");
        cout << "Test 2 Passed: n = 1 -> [[\"Q\"]]" << endl;
    }

    // Test Case 3: n = 8 -> 92 solutions (standard 8-queens benchmark)
    {
        vector<vector<string>> res = solver.solveNQueens(8);
        assert(res.size() == 92);
        cout << "Test 3 Passed: n = 8 -> 92 solutions" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
