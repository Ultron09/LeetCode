/**
 * Problem: 37. Sudoku Solver
 * Difficulty: Hard
 * Topics: Array, Hash Table, Backtracking, Matrix, Bit Manipulation
 * LeetCode Link: https://leetcode.com/problems/sudoku-solver/
 * 
 * Time Complexity:  O(9^M) worst-case bounded by MRV bitmask pruning (typically < 1 ms)
 * Space Complexity: O(1) auxiliary space (9x9 fixed grid recursion depth <= 81)
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    int rowMask[9] = {0};
    int colMask[9] = {0};
    int boxMask[9] = {0};

    int getBoxIndex(int r, int c) {
        return (r / 3) * 3 + (c / 3);
    }

    int getCandidates(int r, int c) {
        int used = rowMask[r] | colMask[c] | boxMask[getBoxIndex(r, c)];
        return (~used) & 0x1FF; // Only bits 0..8
    }

    bool backtrack(vector<vector<char>>& board) {
        int minChoices = 10;
        int bestR = -1, bestC = -1;
        int bestCand = 0;

        // Minimum Remaining Values (MRV) heuristic:
        // Pick the unassigned cell with the fewest available candidate digits
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] == '.') {
                    int cand = getCandidates(r, c);
                    int count = __builtin_popcount(cand);

                    if (count == 0) {
                        return false; // Dead end branch
                    }

                    if (count < minChoices) {
                        minChoices = count;
                        bestR = r;
                        bestC = c;
                        bestCand = cand;
                        if (count == 1) break; // Optimal constraint reached
                    }
                }
            }
            if (minChoices == 1) break;
        }

        // Base case: All cells filled successfully
        if (bestR == -1) return true;

        int r = bestR, c = bestC;
        int b = getBoxIndex(r, c);
        int cand = bestCand;

        while (cand > 0) {
            int lsb = cand & -cand;
            int digit = __builtin_ctz(lsb); // 0-indexed digit

            // Make choice
            board[r][c] = static_cast<char>('1' + digit);
            rowMask[r] |= lsb;
            colMask[c] |= lsb;
            boxMask[b] |= lsb;

            if (backtrack(board)) return true;

            // Undo choice (backtrack)
            board[r][c] = '.';
            rowMask[r] ^= lsb;
            colMask[c] ^= lsb;
            boxMask[b] ^= lsb;

            cand -= lsb;
        }

        return false;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        // Initialize bitmasks from given initial board
        for (int r = 0; r < 9; ++r) {
            rowMask[r] = 0;
            colMask[r] = 0;
            boxMask[r] = 0;
        }

        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] != '.') {
                    int d = board[r][c] - '1';
                    int mask = 1 << d;
                    rowMask[r] |= mask;
                    colMask[c] |= mask;
                    boxMask[getBoxIndex(r, c)] |= mask;
                }
            }
        }

        backtrack(board);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    solver.solveSudoku(board);

    vector<vector<char>> expected = {
        {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
        {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
        {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
        {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
        {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
        {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
        {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
        {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
        {'3', '4', '5', '2', '8', '6', '1', '7', '9'}
    };

    assert(board == expected);
    cout << "Test 1 Passed: Sudoku solved successfully!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
