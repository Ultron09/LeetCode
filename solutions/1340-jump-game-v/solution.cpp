/**
 * Problem: 1340. Jump Game V
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming, Memoization
 * LeetCode Link: https://leetcode.com/problems/jump-game-v/
 * 
 * Time Complexity:  O(N * D) where N = arr.size() <= 1000, D = d <= N
 * Space Complexity: O(N) for recursion stack and memoization table
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    int n;
    int maxDist;
    vector<int> memo;

    int dfs(int i, const vector<int>& arr) {
        if (memo[i] != -1) {
            return memo[i];
        }

        int maxVisits = 1;

        // Jump to the right within distance d
        for (int j = i + 1; j <= min(i + maxDist, n - 1); ++j) {
            // Cannot jump over or land on an element >= arr[i]
            if (arr[j] >= arr[i]) {
                break;
            }
            maxVisits = max(maxVisits, 1 + dfs(j, arr));
        }

        // Jump to the left within distance d
        for (int j = i - 1; j >= max(i - maxDist, 0); --j) {
            // Cannot jump over or land on an element >= arr[i]
            if (arr[j] >= arr[i]) {
                break;
            }
            maxVisits = max(maxVisits, 1 + dfs(j, arr));
        }

        return memo[i] = maxVisits;
    }

public:
    int maxJumps(vector<int>& arr, int d) {
        n = static_cast<int>(arr.size());
        maxDist = d;
        memo.assign(n, -1);

        int maxResult = 0;
        for (int i = 0; i < n; ++i) {
            maxResult = max(maxResult, dfs(i, arr));
        }

        return maxResult;
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
        vector<int> arr = {6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12};
        int d = 2;
        int expected = 4;
        assert(solver.maxJumps(arr, d) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> arr = {3, 3, 3, 3, 3};
        int d = 3;
        int expected = 1;
        assert(solver.maxJumps(arr, d) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        vector<int> arr = {7, 6, 5, 4, 3, 2, 1};
        int d = 1;
        int expected = 7;
        assert(solver.maxJumps(arr, d) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
