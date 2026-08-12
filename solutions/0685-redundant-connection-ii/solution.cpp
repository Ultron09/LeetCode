/**
 * Problem: 685. Redundant Connection II
 * Difficulty: Hard
 * Topics: Depth-First Search, Breadth-First Search, Union Find, Graph
 * LeetCode Link: https://leetcode.com/problems/redundant-connection-ii/
 * 
 * Time Complexity:  O(N * alpha(N)) where N is the number of vertices/edges
 * Space Complexity: O(N) for DSU structures and parent pointers
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

using namespace std;

class DSU {
private:
    vector<int> parent;

public:
    DSU(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        if (rootI == rootJ)
            return false; // Cycle detected
        parent[rootI] = rootJ;
        return true;
    }
};

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n + 1, 0);
        vector<int> cand1;
        vector<int> cand2;

        // Step 1: Detect if any node has two incoming edges (in-degree 2)
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            if (parent[v] != 0) {
                // v already has a parent: parent[v] was the first, u is the second
                cand1 = {parent[v], v};
                cand2 = {u, v};
                break;
            }
            parent[v] = u;
        }

        // Step 2: Simulate Union-Find graph construction
        DSU dsu(n);
        for (const auto& edge : edges) {
            // Skip cand2 to test if removing it resolves the tree invariant
            if (!cand2.empty() && edge[0] == cand2[0] && edge[1] == cand2[1]) {
                continue;
            }

            int u = edge[0];
            int v = edge[1];

            if (!dsu.unite(u, v)) {
                // A cycle is formed
                if (!cand1.empty()) {
                    // Two-parent case where the cycle exists without cand2;
                    // therefore cand1 is the culprit edge in the cycle.
                    return cand1;
                }
                // No two-parent node exists (pure cycle case)
                return edge;
            }
        }

        // Skipping cand2 yielded a cycle-free valid tree; cand2 is the redundant edge.
        return cand2;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1 (Two-parent node, no cycle created by first edge)
    {
        vector<vector<int>> edges = {{1, 2}, {1, 3}, {2, 3}};
        vector<int> result = solver.findRedundantDirectedConnection(edges);
        cout << "Test 1 -> Expected: [2, 3], Got: [" << result[0] << ", " << result[1] << "]" << endl;
        assert(result == (vector<int>{2, 3}));
    }

    // Test Case 2: Example 2 (Pure directed cycle, no node has in-degree 2)
    {
        vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 5}};
        vector<int> result = solver.findRedundantDirectedConnection(edges);
        cout << "Test 2 -> Expected: [4, 1], Got: [" << result[0] << ", " << result[1] << "]" << endl;
        assert(result == (vector<int>{4, 1}));
    }

    // Test Case 3: Two-parent node where cand1 forms a cycle
    {
        vector<vector<int>> edges = {{2, 1}, {3, 1}, {4, 2}, {1, 4}};
        vector<int> result = solver.findRedundantDirectedConnection(edges);
        cout << "Test 3 -> Expected: [2, 1], Got: [" << result[0] << ", " << result[1] << "]" << endl;
        assert(result == (vector<int>{2, 1}));
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
