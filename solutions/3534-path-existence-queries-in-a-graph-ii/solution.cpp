/**
 * Problem: 3534. Path Existence Queries in a Graph II
 * Difficulty: Hard
 * Topics: Array, Two Pointers, Binary Lifting, Sorting, Graph Theory
 * LeetCode Link: https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/
 * 
 * Time Complexity:  O(N log N + Q log N) where N = nums.size(), Q = queries.size()
 * Space Complexity: O(N log N) for binary lifting jump table
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // 1. Pair each number with its original index and sort by value
        vector<pair<int, int>> sortedPairs(n);
        for (int i = 0; i < n; ++i) {
            sortedPairs[i] = {nums[i], i};
        }
        sort(sortedPairs.begin(), sortedPairs.end());

        vector<int> sortedNums(n);
        vector<int> indexMap(n); // original index -> sorted index
        for (int i = 0; i < n; ++i) {
            sortedNums[i] = sortedPairs[i].first;
            indexMap[sortedPairs[i].second] = i;
        }

        // 2. Compute max jump levels: log2(n) + 1
        int maxLevel = 0;
        while ((1 << maxLevel) <= n) {
            maxLevel++;
        }
        maxLevel++;

        // jump[i][k]: the furthest reachable index from sorted position i in 2^k jumps
        vector<vector<int>> jump(n, vector<int>(maxLevel, 0));

        // 3. Two Pointers / Sliding Window to find jump[i][0] (1 step reach)
        int right = 0;
        for (int i = 0; i < n; ++i) {
            while (right + 1 < n && sortedNums[right + 1] - sortedNums[i] <= maxDiff) {
                right++;
            }
            jump[i][0] = right;
        }

        // 4. Binary Lifting DP table: jump[i][k] = jump[jump[i][k - 1]][k - 1]
        for (int k = 1; k < maxLevel; ++k) {
            for (int i = 0; i < n; ++i) {
                jump[i][k] = jump[jump[i][k - 1]][k - 1];
            }
        }

        // 5. Answer each query [u, v] in O(log N)
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int u = q[0];
            int v = q[1];

            int start = min(indexMap[u], indexMap[v]);
            int target = max(indexMap[u], indexMap[v]);

            if (start == target) {
                ans.push_back(0);
                continue;
            }

            // Direct 1-hop reach
            if (jump[start][0] >= target) {
                ans.push_back(1);
                continue;
            }

            // If even max possible jumps cannot reach target, disconnected
            if (jump[start][maxLevel - 1] < target) {
                ans.push_back(-1);
                continue;
            }

            // Greedily make binary lifting jumps from largest power of 2
            int jumps = 0;
            int curr = start;
            for (int k = maxLevel - 1; k >= 0; --k) {
                if (jump[curr][k] < target) {
                    curr = jump[curr][k];
                    jumps += (1 << k);
                }
            }

            // Final 1 jump to reach or exceed target
            if (jump[curr][0] >= target) {
                ans.push_back(jumps + 1);
            } else {
                ans.push_back(-1);
            }
        }

        return ans;
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
        int n = 5;
        vector<int> nums = {1, 8, 3, 4, 2};
        int maxDiff = 3;
        vector<vector<int>> queries = {{0, 3}, {2, 4}};
        vector<int> expected = {1, 1};
        assert(solver.pathExistenceQueries(n, nums, maxDiff, queries) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        int n = 5;
        vector<int> nums = {5, 3, 1, 9, 10};
        int maxDiff = 2;
        vector<vector<int>> queries = {{0, 1}, {0, 2}, {2, 3}, {4, 3}};
        vector<int> expected = {1, 2, -1, 1};
        assert(solver.pathExistenceQueries(n, nums, maxDiff, queries) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        int n = 3;
        vector<int> nums = {3, 6, 1};
        int maxDiff = 1;
        vector<vector<int>> queries = {{0, 0}, {0, 1}, {1, 2}};
        vector<int> expected = {0, -1, -1};
        assert(solver.pathExistenceQueries(n, nums, maxDiff, queries) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
