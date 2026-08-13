/**
 * Problem: 778. Swim in Rising Water
 * Difficulty: Hard
 * Topics: Array, Binary Search, Depth-First Search, Breadth-First Search, Union Find, Heap (Priority Queue), Matrix
 * LeetCode Link: https://leetcode.com/problems/swim-in-rising-water/
 *
 * Approach: Dijkstra's Algorithm (Priority Queue)
 *
 * Key Insight:
 *   We want to find a path from the top-left to the bottom-right such that the 
 *   MAXIMUM elevation along the path is minimized. This is a classic "Bottleneck 
 *   Shortest Path" problem.
 *   
 *   We can use Dijkstra's algorithm. Instead of accumulating distances, our path cost 
 *   is defined as the maximum elevation encountered so far. We use a min-heap to 
 *   always expand the node with the lowest path cost.
 *
 *   Algorithm:
 *   1. Push the starting node (0, 0) into a min-heap with cost `grid[0][0]`.
 *   2. Maintain a `visited` set to avoid cycles.
 *   3. Pop the node with the minimum cost. If it's the destination, return the cost.
 *   4. Otherwise, for each unvisited neighbor, push it into the heap with cost 
 *      `max(current_cost, grid[next_x][next_y])`.
 *
 * Time Complexity:  O(N^2 * log N) - where N is the grid dimension. Each of the N^2 cells is pushed to the heap once.
 * Space Complexity: O(N^2) - For the visited array and the priority queue.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Min-heap storing {max_elevation_so_far, r, c}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        pq.push({grid[0][0], 0, 0});
        visited[0][0] = true;
        
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!pq.empty()) {
            auto curr = pq.top();
            pq.pop();
            
            int max_elev = curr[0];
            int r = curr[1];
            int c = curr[2];
            
            if (r == n - 1 && c == n - 1) {
                return max_elev;
            }
            
            for (auto& dir : dirs) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    pq.push({max(max_elev, grid[nr][nc]), nr, nc});
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
        vector<vector<int>> grid = {{0, 2}, {1, 3}};
        int res = solver.swimInWater(grid);
        assert(res == 3);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> grid = {
            {0, 1, 2, 3, 4},
            {24, 23, 22, 21, 5},
            {12, 13, 14, 15, 16},
            {11, 17, 18, 19, 20},
            {10, 9, 8, 7, 6}
        };
        int res = solver.swimInWater(grid);
        assert(res == 16);
        cout << "Test 2 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
