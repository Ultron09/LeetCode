    /**
    * Problem: 3559. Number of Ways to Assign Edge Weights II
    * Difficulty: Hard
    * Topics: Tree, Binary Lifting, Lowest Common Ancestor (LCA), Math, Combinatorics
    * LeetCode Link: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/
    * 
    * Time Complexity:  O((N + Q) log N) where N, Q <= 10^5
    * Space Complexity: O(N log N) for binary lifting jump table
    */

    #include <iostream>
    #include <vector>
    #include <queue>
    #include <algorithm>
    #include <cassert>

    using namespace std;

    class Solution {
    private:
        static constexpr int MOD = 1'000'000'007;
        static constexpr int MAX_LOG = 18; // 2^17 > 10^5

    public:
        vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
            int n = edges.size() + 1;
            vector<vector<int>> adj(n + 1);
            for (const auto& e : edges) {
                adj[e[0]].push_back(e[1]);
                adj[e[1]].push_back(e[0]);
            }

            // 1. Precompute depths and 2^0 ancestors using BFS
            vector<int> depth(n + 1, 0);
            vector<vector<int>> up(MAX_LOG, vector<int>(n + 1, 0));
            vector<bool> visited(n + 1, false);

            queue<int> q;
            q.push(1);
            visited[1] = true;
            depth[1] = 0;
            up[0][1] = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        depth[v] = depth[u] + 1;
                        up[0][v] = u;
                        q.push(v);
                    }
                }
            }

            // 2. Build Binary Lifting Table: up[k][u] = 2^k-th ancestor of u
            for (int k = 1; k < MAX_LOG; ++k) {
                for (int i = 1; i <= n; ++i) {
                    up[k][i] = up[k - 1][up[k - 1][i]];
                }
            }

            // 3. Precompute powers of 2 modulo MOD
            vector<int> pow2(n + 1, 1);
            for (int i = 1; i <= n; ++i) {
                pow2[i] = (1LL * pow2[i - 1] * 2) % MOD;
            }

            // 4. LCA Query Function
            auto getLCA = [&](int u, int v) -> int {
                if (depth[u] < depth[v]) swap(u, v);

                // Lift u to the same depth as v
                int diff = depth[u] - depth[v];
                for (int k = 0; k < MAX_LOG; ++k) {
                    if ((diff >> k) & 1) {
                        u = up[k][u];
                    }
                }

                if (u == v) return u;

                // Lift both nodes simultaneously
                for (int k = MAX_LOG - 1; k >= 0; --k) {
                    if (up[k][u] != up[k][v]) {
                        u = up[k][u];
                        v = up[k][v];
                    }
                }

                return up[0][u];
            };

            // 5. Answer each query
            vector<int> answer;
            answer.reserve(queries.size());

            for (const auto& query : queries) {
                int u = query[0], v = query[1];
                if (u == v) {
                    // Distance 0, sum of weights is 0 (even), 0 ways to be odd
                    answer.push_back(0);
                } else {
                    int lca = getLCA(u, v);
                    int dist = depth[u] + depth[v] - 2 * depth[lca];
                    // For d >= 1 edges with choices {1, 2}, exactly 2^(d - 1) assignments have odd sum
                    answer.push_back(pow2[dist - 1]);
                }
            }

            return answer;
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
            vector<vector<int>> edges = {{1, 2}};
            vector<vector<int>> queries = {{1, 1}, {1, 2}};
            vector<int> expected = {0, 1};
            assert(solver.assignEdgeWeights(edges, queries) == expected);
            cout << "Test 1 Passed!" << endl;
        }

        // Test Case 2: Example 2
        {
            vector<vector<int>> edges = {{1, 2}, {1, 3}, {3, 4}, {3, 5}};
            vector<vector<int>> queries = {{1, 4}, {3, 4}, {2, 5}};
            vector<int> expected = {2, 1, 4};
            assert(solver.assignEdgeWeights(edges, queries) == expected);
            cout << "Test 2 Passed!" << endl;
        }

        cout << "All test cases passed successfully!" << endl;
        return 0;
    }
    #endif
