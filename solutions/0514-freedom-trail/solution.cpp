/**
 * Problem: 514. Freedom Trail
 * Difficulty: Hard
 * Topics: String, Dynamic Programming, Depth-First Search, Breadth-First Search
 * LeetCode Link: https://leetcode.com/problems/freedom-trail/
 * 
 * Time Complexity:  O(K * R^2) - Dynamic programming over key characters and ring positions
 * Space Complexity: O(R) - 1D DP state storage between consecutive key stages
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
private:
    inline int getCircularDistance(int i, int j, int r) {
        int diff = abs(i - j);
        return min(diff, r - diff);
    }

public:
    int findRotateSteps(string ring, string key) {
        int rLen = ring.length();
        int kLen = key.length();

        // Map each character to all its 0-indexed occurrence positions in ring
        vector<vector<int>> charPositions(26);
        for (int i = 0; i < rLen; ++i) {
            charPositions[ring[i] - 'a'].push_back(i);
        }

        // dp[pos]: minimum steps (rotations + button presses) to spell key[0..step-1]
        // ending with the 12:00 pointer at ring position `pos`
        const int INF = 1e9;
        vector<int> dp(rLen, INF);
        dp[0] = 0; // Initially pointer starts at index 0

        for (char targetChar : key) {
            vector<int> nextDp(rLen, INF);
            const vector<int>& targetPositions = charPositions[targetChar - 'a'];

            for (int nxt : targetPositions) {
                for (int prev = 0; prev < rLen; ++prev) {
                    if (dp[prev] == INF) continue;
                    int stepCost = dp[prev] + getCircularDistance(prev, nxt, rLen) + 1;
                    nextDp[nxt] = min(nextDp[nxt], stepCost);
                }
            }

            dp = move(nextDp);
        }

        int minTotalSteps = INF;
        for (int steps : dp) {
            minTotalSteps = min(minTotalSteps, steps);
        }

        return minTotalSteps;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1
    {
        string ring = "godding", key = "gd";
        int result = solver.findRotateSteps(ring, key);
        cout << "Test 1 - ring=\"godding\", key=\"gd\" -> Expected: 4, Got: " << result << endl;
        assert(result == 4);
    }

    // Test Case 2: Standard Example 2
    {
        string ring = "godding", key = "godding";
        int result = solver.findRotateSteps(ring, key);
        cout << "Test 2 - ring=\"godding\", key=\"godding\" -> Expected: 13, Got: " << result << endl;
        assert(result == 13);
    }

    // Test Case 3: Duplicate characters with optimal branching
    {
        string ring = "ababcab", key = "acba";
        int result = solver.findRotateSteps(ring, key);
        cout << "Test 3 - ring=\"ababcab\", key=\"acba\" -> Expected: 9, Got: " << result << endl;
        assert(result == 9);
    }

    // Test Case 4: Single character string
    {
        string ring = "a", key = "a";
        int result = solver.findRotateSteps(ring, key);
        cout << "Test 4 - ring=\"a\", key=\"a\" -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
