/**
 * Problem: 913. Cat and Mouse
 * Difficulty: Hard
 * Topics: Graph, Math, Dynamic Programming, Topological Sort, Game Theory
 * LeetCode Link: https://leetcode.com/problems/cat-and-mouse/
 * 
 * Time Complexity:  O(V + E) where V = N^2, E = N^3 (at most) -> O(N^3)
 * Space Complexity: O(N^2) for the state matrix and queue.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cassert>

using namespace std;

class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        // color[m][c][t]: 0=Draw, 1=Mouse, 2=Cat
        vector<vector<vector<int>>> color(n, vector<vector<int>>(n, vector<int>(2, 0)));
        // out_degree[m][c][t]
        vector<vector<vector<int>>> out_degree(n, vector<vector<int>>(n, vector<int>(2, 0)));
        
        queue<tuple<int, int, int>> q;
        
        for (int m = 0; m < n; ++m) {
            for (int c = 0; c < n; ++c) {
                out_degree[m][c][0] = graph[m].size();
                out_degree[m][c][1] = graph[c].size();
                for (int next_node : graph[c]) {
                    if (next_node == 0) {
                        out_degree[m][c][1]--; // Cat cannot go to 0
                    }
                }
            }
        }
        
        // Terminal states
        for (int i = 1; i < n; ++i) {
            // Mouse reaches hole (Mouse wins)
            color[0][i][0] = 1;
            color[0][i][1] = 1;
            q.push({0, i, 0});
            q.push({0, i, 1});
            
            // Cat catches Mouse (Cat wins)
            color[i][i][0] = 2;
            color[i][i][1] = 2;
            q.push({i, i, 0});
            q.push({i, i, 1});
        }
        
        while (!q.empty()) {
            auto [m, c, t] = q.front();
            q.pop();
            
            int winner = color[m][c][t];
            
            // Look at predecessor states
            if (t == 1) { // Predecessor was Mouse's turn
                for (int pm : graph[m]) {
                    if (color[pm][c][0] == 0) {
                        if (winner == 1) {
                            color[pm][c][0] = 1;
                            q.push({pm, c, 0});
                        } else {
                            out_degree[pm][c][0]--;
                            if (out_degree[pm][c][0] == 0) {
                                color[pm][c][0] = 2;
                                q.push({pm, c, 0});
                            }
                        }
                    }
                }
            } else { // Predecessor was Cat's turn
                for (int pc : graph[c]) {
                    if (pc == 0) continue; // Cat cannot have been at 0
                    if (color[m][pc][1] == 0) {
                        if (winner == 2) {
                            color[m][pc][1] = 2;
                            q.push({m, pc, 1});
                        } else {
                            out_degree[m][pc][1]--;
                            if (out_degree[m][pc][1] == 0) {
                                color[m][pc][1] = 1;
                                q.push({m, pc, 1});
                            }
                        }
                    }
                }
            }
        }
        
        return color[1][2][0];
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    vector<vector<int>> graph1 = {{2,5},{3},{0,4,5},{1,4,5},{2,3},{0,2,3}};
    assert(solver.catMouseGame(graph1) == 0);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    vector<vector<int>> graph2 = {{1,3},{0},{3},{0,2}};
    assert(solver.catMouseGame(graph2) == 1);
    cout << "Test 2 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
