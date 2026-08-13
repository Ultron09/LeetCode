/**
 * Problem: 782. Transform to Chessboard
 * Difficulty: Hard
 * Topics: Array, Math, Matrix
 * LeetCode Link: https://leetcode.com/problems/transform-to-chessboard/
 *
 * Approach: Math and Parity Analysis
 *
 * Key Insight:
 *   1. Swapping rows doesn't change the relative elements in a row, and swapping columns 
 *      doesn't change relative elements in a column. Thus, in a valid transformed chessboard, 
 *      there can only be TWO unique types of rows, and they must be bitwise inverses of each other. 
 *      The same applies to columns.
 *   2. The top-left element grid[0][0] dictates the relationship of all other elements:
 *      grid[r][c] ^ grid[0][0] ^ grid[r][0] ^ grid[0][c] MUST be 0 for all (r, c). 
 *      If not, it's impossible to form a chessboard.
 *   3. Since row swaps and column swaps are independent, we can calculate the minimum 
 *      number of row swaps and column swaps separately.
 *   4. For a line (row or column) to be valid, the count of 1s and 0s must be equal (N / 2) 
 *      or differ by 1 if N is odd.
 *   5. The number of swaps to reach an alternating sequence (e.g., 1010... or 0101...) is 
 *      half the number of misplaced elements compared to that sequence.
 *
 * Time Complexity:  O(N^2) to validate the board.
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
        int n = board.size();
        
        // 1. Check if the board is valid (all four corners of any rectangle must have an even number of 1s)
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if ((board[0][0] ^ board[r][0] ^ board[0][c] ^ board[r][c]) == 1) {
                    return -1;
                }
            }
        }
        
        // 2. Count 1s in the first row and first column
        int rowSum = 0, colSum = 0;
        int rowSwaps = 0, colSwaps = 0;
        
        for (int i = 0; i < n; ++i) {
            rowSum += board[0][i];
            colSum += board[i][0];
            
            // Check misplaced elements compared to the pattern starting with 1
            if (board[0][i] == i % 2) rowSwaps++;
            if (board[i][0] == i % 2) colSwaps++;
        }
        
        // 3. Check if counts of 1s and 0s are valid (N/2 or (N+1)/2)
        if (rowSum < n / 2 || rowSum > (n + 1) / 2) return -1;
        if (colSum < n / 2 || colSum > (n + 1) / 2) return -1;
        
        // 4. Calculate minimum swaps
        if (n % 2 == 1) {
            // For odd N, we can only have one valid pattern (the one that aligns with the majority element)
            // Misplaced elements must be an EVEN number, so if it's odd, we must use the other pattern.
            if (rowSwaps % 2 == 1) rowSwaps = n - rowSwaps;
            if (colSwaps % 2 == 1) colSwaps = n - colSwaps;
        } else {
            // For even N, both patterns are possible, so take the minimum
            rowSwaps = min(rowSwaps, n - rowSwaps);
            colSwaps = min(colSwaps, n - colSwaps);
        }
        
        // Return total swaps (each swap fixes 2 misplaced elements, hence divide by 2)
        return (rowSwaps / 2) + (colSwaps / 2);
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
        vector<vector<int>> board = {{0,1,1,0},{0,1,1,0},{1,0,0,1},{1,0,0,1}};
        int res = solver.movesToChessboard(board);
        assert(res == 2);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> board = {{0, 1}, {1, 0}};
        int res = solver.movesToChessboard(board);
        assert(res == 0);
        cout << "Test 2 Passed! Result: " << res << endl;
    }
    
    // Test Case 3
    {
        vector<vector<int>> board = {{1, 0}, {1, 0}};
        int res = solver.movesToChessboard(board);
        assert(res == -1);
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
