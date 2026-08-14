/**
 * Problem: 882. Reachable Nodes In Subdivided Graph
 * Difficulty: Hard
 * Topics: Graphs, Dijkstra's Algorithm
 * LeetCode Link: https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/
 * 
 * Time Complexity:  O(E log V) - Where E is the number of edges and V is the number of vertices.
 * Space Complexity: O(E + V) - For adjacency list and distance array.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cnt = edge[2];
            adj[u].emplace_back(v, cnt + 1);
            adj[v].emplace_back(u, cnt + 1);
        }
        
        vector<int> dist(n, 2e9); // 2e9 is safely larger than max possible distance within maxMoves
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[0] = 0;
        pq.emplace(0, 0);
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }
        
        int reachable_nodes = 0;
        
        // Count reachable original nodes
        for (int i = 0; i < n; ++i) {
            if (dist[i] <= maxMoves) {
                reachable_nodes++;
            }
        }
        
        // Count reachable subdivided nodes on each edge
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cnt = edge[2];
            
            int reachable_from_u = max(0, maxMoves - dist[u]);
            int reachable_from_v = max(0, maxMoves - dist[v]);
            
            reachable_nodes += min(cnt, reachable_from_u + reachable_from_v);
        }
        
        return reachable_nodes;
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
        vector<vector<int>> edges = {{0,1,10},{0,2,1},{1,2,2}};
        assert(solver.reachableNodes(edges, 6, 3) == 13);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> edges = {{0,1,4},{1,2,6},{0,2,8},{1,3,1}};
        assert(solver.reachableNodes(edges, 10, 4) == 23);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3
    {
        vector<vector<int>> edges = {{1,2,4},{1,4,5},{1,3,1},{2,3,4},{3,4,5}};
        assert(solver.reachableNodes(edges, 17, 5) == 1);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
