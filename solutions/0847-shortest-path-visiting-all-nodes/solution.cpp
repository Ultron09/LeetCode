/**
 * Problem: 847. Shortest Path Visiting All Nodes
 * Difficulty: Hard
 * Topics: Dynamic Programming, Bit Manipulation, Breadth-First Search, Graph
 * LeetCode Link: https://leetcode.com/problems/shortest-path-visiting-all-nodes/
 *
 * Approach: BFS with Bitmask State
 * We need to find the shortest path that visits all nodes. Since we can start at any 
 * node and re-visit nodes, this boils down to finding the shortest path in a state-space 
 * graph. Because N is very small (N <= 12), we can represent the set of visited nodes 
 * using a bitmask.
 *
 * A state is defined by `(current_node, visited_mask)`. 
 * - `current_node` (0 to N-1)
 * - `visited_mask` (0 to 2^N - 1)
 * 
 * We initialize our BFS queue with all possible starting nodes: `(i, 1 << i)` with 
 * distance 0. Then we explore neighbor nodes, updating the visited mask via bitwise OR.
 * A `visited` boolean matrix prevents revisiting the exact same state and infinite loops.
 * The BFS guarantees that the first time we reach the target mask `(1 << N) - 1`, it is 
 * via the shortest possible path.
 * 
 * Time Complexity:  O(N * 2^N) - In the worst case, we visit every node in every possible mask state.
 * Space Complexity: O(N * 2^N) - For the queue and the visited tracking matrix.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cassert>

using namespace std;

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        if (n == 1) return 0; // Trivial case for a 1-node graph
        
        int finalMask = (1 << n) - 1;
        
        // queue stores: {current_node, visited_mask, distance}
        queue<tuple<int, int, int>> q;
        
        // visited[node][mask]
        vector<vector<bool>> visited(n, vector<bool>(1 << n, false));
        
        // We can start at any node, so push all initial states
        for (int i = 0; i < n; ++i) {
            q.push({i, 1 << i, 0});
            visited[i][1 << i] = true;
        }
        
        while (!q.empty()) {
            auto [u, mask, dist] = q.front();
            q.pop();
            
            for (int v : graph[u]) {
                int nextMask = mask | (1 << v);
                
                // If this step visits the last unvisited node, return the distance
                if (nextMask == finalMask) {
                    return dist + 1;
                }
                
                // If this exact state hasn't been seen before, explore it
                if (!visited[v][nextMask]) {
                    visited[v][nextMask] = true;
                    q.push({v, nextMask, dist + 1});
                }
            }
        }
        
        return 0; // Should not reach here for valid connected graphs
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
        vector<vector<int>> graph = {{1,2,3},{0},{0},{0}};
        int res = solver.shortestPathLength(graph);
        assert(res == 4);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> graph = {{1},{0,2,4},{1,3,4},{2},{1,2}};
        int res = solver.shortestPathLength(graph);
        assert(res == 4);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
