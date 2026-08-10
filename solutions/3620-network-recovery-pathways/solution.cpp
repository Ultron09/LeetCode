/**
 * Problem: 3620. Network Recovery Pathways
 * Difficulty: Hard
 * Topics: Graph, Binary Search, Shortest Path, Dijkstra, Heap / Priority Queue
 * LeetCode Link: https://leetcode.com/problems/network-recovery-pathways/
 * 
 * Time Complexity:  O((N + M) log N * log M) where N = n, M = edges.size()
 * Space Complexity: O(N + M) for adjacency list and priority queue
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        // 1. Build Adjacency List
        vector<vector<pair<int, int>>> adj(n);
        vector<int> uniqueCosts;
        uniqueCosts.reserve(edges.size());

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];
            adj[u].push_back({v, cost});
            uniqueCosts.push_back(cost);
        }

        // 2. Sort and deduplicate edge costs to form the binary search domain
        sort(uniqueCosts.begin(), uniqueCosts.end());
        uniqueCosts.erase(unique(uniqueCosts.begin(), uniqueCosts.end()), uniqueCosts.end());

        if (uniqueCosts.empty()) {
            return -1;
        }

        // Helper function: Check if there exists a valid path with min_edge_cost >= threshold and total_cost <= k
        auto check = [&](int threshold) -> bool {
            vector<long long> dist(n, LLONG_MAX);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

            dist[0] = 0;
            pq.push({0, 0}); // {distance, node}

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();

                if (d > dist[u]) continue;
                if (u == n - 1) return true; // Reached destination within cost <= k

                for (const auto& [v, cost] : adj[u]) {
                    // Only traverse edges meeting the bottleneck threshold
                    if (cost < threshold) continue;

                    // Intermediate nodes must be online (destination n-1 is always valid)
                    if (v != n - 1 && !online[v]) continue;

                    long long nextDist = d + cost;
                    if (nextDist <= k && nextDist < dist[v]) {
                        dist[v] = nextDist;
                        pq.push({nextDist, v});
                    }
                }
            }

            return dist[n - 1] <= k;
        };

        // 3. Binary Search on the Answer Space (Bottleneck Edge Threshold)
        int low = 0;
        int high = static_cast<int>(uniqueCosts.size()) - 1;
        int bestScore = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int candidateThreshold = uniqueCosts[mid];

            if (check(candidateThreshold)) {
                bestScore = candidateThreshold; // Feasible, try to achieve a higher bottleneck score
                low = mid + 1;
            } else {
                high = mid - 1; // Infeasible, reduce threshold
            }
        }

        return bestScore;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1
    {
        vector<vector<int>> edges = {{0, 1, 5}, {1, 3, 10}, {0, 2, 3}, {2, 3, 4}};
        vector<bool> online = {true, true, true, true};
        long long k = 10;
        int expected = 3;
        assert(solver.findMaxPathScore(edges, online, k) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<vector<int>> edges = {{0, 1, 7}, {1, 4, 5}, {0, 2, 6}, {2, 3, 6}, {3, 4, 2}, {2, 4, 6}};
        vector<bool> online = {true, true, true, false, true};
        long long k = 12;
        int expected = 6;
        assert(solver.findMaxPathScore(edges, online, k) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
