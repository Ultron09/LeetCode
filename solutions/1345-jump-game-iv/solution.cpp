/**
 * Problem: 1345. Jump Game IV
 * Difficulty: Hard
 * Topics: Array, Hash Table, Breadth-First Search (BFS), Graph
 * LeetCode Link: https://leetcode.com/problems/jump-game-iv/
 * 
 * Time Complexity:  O(N) where N = arr.size() <= 5 * 10^4
 * Space Complexity: O(N) for graph adjacency and BFS visited queue
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        if (n <= 1) {
            return 0;
        }

        // Map each distinct value to all its occurring indices
        unordered_map<int, vector<int>> valToIndices;
        for (int i = 0; i < n; ++i) {
            valToIndices[arr[i]].push_back(i);
        }

        // BFS to find shortest unweighted path
        queue<int> q;
        vector<bool> visited(n, false);

        q.push(0);
        visited[0] = true;
        int steps = 0;

        while (!q.empty()) {
            int levelSize = static_cast<int>(q.size());

            for (int k = 0; k < levelSize; ++k) {
                int curr = q.front();
                q.pop();

                // Target reached
                if (curr == n - 1) {
                    return steps;
                }

                // 1. Jump forward: i + 1
                if (curr + 1 < n && !visited[curr + 1]) {
                    visited[curr + 1] = true;
                    q.push(curr + 1);
                }

                // 2. Jump backward: i - 1
                if (curr - 1 >= 0 && !visited[curr - 1]) {
                    visited[curr - 1] = true;
                    q.push(curr - 1);
                }

                // 3. Jump to any index with the same value: arr[i] == arr[j]
                int val = arr[curr];
                auto it = valToIndices.find(val);
                if (it != valToIndices.end()) {
                    for (int nextIdx : it->second) {
                        if (!visited[nextIdx]) {
                            visited[nextIdx] = true;
                            q.push(nextIdx);
                        }
                    }
                    // CRITICAL OPTIMIZATION: Clear the list to prevent O(N^2) reprocessing
                    valToIndices.erase(it);
                }
            }

            steps++;
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

    // Test Case 1: Example 1
    {
        vector<int> arr = {100, -23, -23, 404, 100, 23, 23, 23, 3, 404};
        int expected = 3;
        assert(solver.minJumps(arr) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> arr = {7};
        int expected = 0;
        assert(solver.minJumps(arr) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        vector<int> arr = {7, 6, 9, 6, 9, 6, 9, 7};
        int expected = 1;
        assert(solver.minJumps(arr) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
