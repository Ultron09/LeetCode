/**
 * Problem: 52. N-Queens II
 * Difficulty: Hard
 * Topics: Backtracking, Bit Manipulation
 * LeetCode Link: https://leetcode.com/problems/n-queens-ii/
 * 
 * Time Complexity:  O(N!)
 * Space Complexity: O(N) recursion stack space
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    int totalCount = 0;

    void backtrack(int row, int n, int cols, int diag1, int diag2) {
        if (row == n) {
            totalCount++;
            return;
        }

        // Available safe positions for current row
        int available = ((1 << n) - 1) & ~(cols | diag1 | diag2);

        while (available > 0) {
            int p = available & -available; // Isolate least significant bit
            available -= p;

            // In next row:
            // diag1 shifts left (<< 1) because row increases by 1
            // diag2 shifts right (>> 1) because row increases by 1
            backtrack(row + 1, n, cols | p, (diag1 | p) << 1, (diag2 | p) >> 1);
        }
    }

public:
    int totalNQueens(int n) {
        totalCount = 0;
        backtrack(0, n, 0, 0, 0);
        return totalCount;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: n = 4 -> 2
    {
        assert(solver.totalNQueens(4) == 2);
        cout << "Test 1 Passed: n = 4 -> 2" << endl;
    }

    // Test Case 2: n = 1 -> 1
    {
        assert(solver.totalNQueens(1) == 1);
        cout << "Test 2 Passed: n = 1 -> 1" << endl;
    }

    // Test Case 3: n = 8 -> 92
    {
        assert(solver.totalNQueens(8) == 92);
        cout << "Test 3 Passed: n = 8 -> 92" << endl;
    }

    // Test Case 4: n = 9 -> 352
    {
        assert(solver.totalNQueens(9) == 352);
        cout << "Test 4 Passed: n = 9 -> 352" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
