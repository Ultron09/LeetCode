/**
 * Problem: 332. Reconstruct Itinerary
 * Difficulty: Hard
 * Topics: Depth-First Search, Graph, Eulerian Circuit
 * LeetCode Link: https://leetcode.com/problems/reconstruct-itinerary/
 * 
 * Time Complexity:  O(E log E) - Sorting outgoing edges per vertex + O(E) DFS traversal
 * Space Complexity: O(V + E) - Adjacency list and recursion call stack
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj;
    vector<string> itinerary;

    void dfs(const string& u) {
        auto& neighbors = adj[u];
        while (!neighbors.empty()) {
            string v = neighbors.top();
            neighbors.pop();
            dfs(v);
        }
        itinerary.push_back(u);
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        adj.clear();
        itinerary.clear();

        // Build min-heap adjacency list for lexicographically smallest order
        for (const auto& ticket : tickets) {
            adj[ticket[0]].push(ticket[1]);
        }

        // Start Hierholzer's algorithm from "JFK"
        dfs("JFK");

        // Post-order traversal yields the reversed Eulerian path
        reverse(itinerary.begin(), itinerary.end());
        return itinerary;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Simple linear itinerary
    {
        vector<vector<string>> tickets = {
            {"MUC", "LHR"},
            {"JFK", "MUC"},
            {"SFO", "SJC"},
            {"LHR", "SFO"}
        };
        vector<string> expected = {"JFK", "MUC", "LHR", "SFO", "SJC"};
        vector<string> result = solver.findItinerary(tickets);
        assert(result == expected);
        cout << "Test 1 Passed: Simple linear path" << endl;
    }

    // Test Case 2: Subcycles with multiple branches requiring lexicographical choice
    {
        vector<vector<string>> tickets = {
            {"JFK", "SFO"},
            {"JFK", "ATL"},
            {"SFO", "ATL"},
            {"ATL", "JFK"},
            {"ATL", "SFO"}
        };
        vector<string> expected = {"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"};
        vector<string> result = solver.findItinerary(tickets);
        assert(result == expected);
        cout << "Test 2 Passed: Lexicographical branch selection with subcycles" << endl;
    }

    // Test Case 3: Dead end prevention (JFK -> KUL, JFK -> NRT, NRT -> JFK)
    {
        vector<vector<string>> tickets = {
            {"JFK", "KUL"},
            {"JFK", "NRT"},
            {"NRT", "JFK"}
        };
        // Going JFK -> KUL directly would cause getting stuck at dead end KUL.
        // Valid Eulerian path: JFK -> NRT -> JFK -> KUL
        vector<string> expected = {"JFK", "NRT", "JFK", "KUL"};
        vector<string> result = solver.findItinerary(tickets);
        assert(result == expected);
        cout << "Test 3 Passed: Dead-end handling via Hierholzer's post-order" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
