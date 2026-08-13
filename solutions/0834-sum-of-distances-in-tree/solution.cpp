/**
 * Problem: 834. Sum of Distances in Tree
 * Difficulty: Hard
 * Topics: Tree, Depth-First Search, Graph, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/sum-of-distances-in-tree/
 *
 * Approach: Re-rooting DP (Tree DP)
 * We can solve this in O(N) using two passes of DFS.
 * 
 * Pass 1 (Post-order):
 * Choose an arbitrary root (e.g., node 0). For each node `u`, compute:
 * - `count[u]`: Number of nodes in the subtree rooted at `u`.
 * - `ans[u]`: Sum of distances from all nodes in the subtree rooted at `u` to `u`.
 *   Transitions:
 *   count[u] = 1 + sum(count[v] for all children v)
 *   ans[u] = sum(ans[v] + count[v] for all children v)
 *
 * Pass 2 (Pre-order):
 * Re-root the tree. When we move the root from a parent `u` to a child `v`, the distance
 * for all nodes in the subtree of `v` decreases by 1, and the distance for all other nodes
 * (n - count[v]) increases by 1.
 *   Transition:
 *   ans[v] = ans[u] - count[v] + (n - count[v])
 * 
 * Time Complexity:  O(N) - Two passes over the tree.
 * Space Complexity: O(N) - Adjacency list and state arrays.
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
    vector<vector<int>> adj;
    vector<int> count;
    vector<int> ans;
    int n;

    void dfs1(int u, int p) {
        count[u] = 1;
        for (int v : adj[u]) {
            if (v != p) {
                dfs1(v, u);
                count[u] += count[v];
                ans[u] += ans[v] + count[v];
            }
        }
    }

    void dfs2(int u, int p) {
        for (int v : adj[u]) {
            if (v != p) {
                ans[v] = ans[u] - count[v] + (n - count[v]);
                dfs2(v, u);
            }
        }
    }

public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        this->n = n;
        adj.assign(n, vector<int>());
        count.assign(n, 0);
        ans.assign(n, 0);

        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Compute `count` and initial `ans` for root 0
        dfs1(0, -1);

        // Shift root to children and compute final answers
        dfs2(0, -1);

        return ans;
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
        int n = 6;
        vector<vector<int>> edges = {{0,1},{0,2},{2,3},{2,4},{2,5}};
        vector<int> expected = {8, 12, 6, 10, 10, 10};
        auto res = solver.sumOfDistancesInTree(n, edges);
        assert(res == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        int n = 1;
        vector<vector<int>> edges = {};
        vector<int> expected = {0};
        auto res = solver.sumOfDistancesInTree(n, edges);
        assert(res == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3
    {
        int n = 2;
        vector<vector<int>> edges = {{1,0}};
        vector<int> expected = {1, 1};
        auto res = solver.sumOfDistancesInTree(n, edges);
        assert(res == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
