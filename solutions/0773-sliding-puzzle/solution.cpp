/**
 * Problem: 773. Sliding Puzzle
 * Difficulty: Hard
 * Topics: Array, Breadth-First Search, Matrix
 * LeetCode Link: https://leetcode.com/problems/sliding-puzzle/
 *
 * Approach: Breadth-First Search (BFS)
 *
 * Key Insight:
 *   The puzzle board is 2x3, meaning there are 6 tiles in total (0-5). The total 
 *   number of possible states is 6! = 720, which is extremely small. 
 *   We can serialize the 2D board into a 1D string of length 6.
 *   The problem then reduces to finding the shortest path from the initial state 
 *   string to the target string "123450" on an unweighted graph, which is best 
 *   solved using Breadth-First Search (BFS).
 *
 *   For a 1D string of length 6 representing a 2x3 board, the valid adjacent 
 *   indices that the '0' tile can swap with are precomputed:
 *   Index 0 -> [1, 3]
 *   Index 1 -> [0, 2, 4]
 *   Index 2 -> [1, 5]
 *   Index 3 -> [0, 4]
 *   Index 4 -> [1, 3, 5]
 *   Index 5 -> [2, 4]
 *
 * Time Complexity:  O(6!) = O(720) ~ O(1) in the worst case.
 * Space Complexity: O(6!) = O(720) ~ O(1) to store the visited states and the BFS queue.
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <cassert>

using namespace std;

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string target = "123450";
        string start = "";
        
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                start += to_string(board[i][j]);
            }
        }
        
        if (start == target) return 0;
        
        vector<vector<int>> neighbors = {
            {1, 3},
            {0, 2, 4},
            {1, 5},
            {0, 4},
            {1, 3, 5},
            {2, 4}
        };
        
        queue<pair<string, int>> q; // {state, moves}
        unordered_set<string> visited;
        
        q.push({start, 0});
        visited.insert(start);
        
        while (!q.empty()) {
            auto [curr, moves] = q.front();
            q.pop();
            
            if (curr == target) return moves;
            
            int zero_idx = curr.find('0');
            
            for (int next_idx : neighbors[zero_idx]) {
                string next_state = curr;
                swap(next_state[zero_idx], next_state[next_idx]);
                
                if (visited.find(next_state) == visited.end()) {
                    visited.insert(next_state);
                    q.push({next_state, moves + 1});
                }
            }
        }
        
        return -1;
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
        vector<vector<int>> board = {{1, 2, 3}, {4, 0, 5}};
        int res = solver.slidingPuzzle(board);
        assert(res == 1);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> board = {{1, 2, 3}, {5, 4, 0}};
        int res = solver.slidingPuzzle(board);
        assert(res == -1);
        cout << "Test 2 Passed! Result: " << res << endl;
    }
    
    // Test Case 3
    {
        vector<vector<int>> board = {{4, 1, 2}, {5, 0, 3}};
        int res = solver.slidingPuzzle(board);
        assert(res == 5);
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
