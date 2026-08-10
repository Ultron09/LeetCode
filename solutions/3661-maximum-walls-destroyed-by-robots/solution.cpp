/**
 * Problem: 3661. Maximum Walls Destroyed by Robots
 * Difficulty: Hard
 * Topics: Array, Binary Search, Dynamic Programming, Sorting
 * LeetCode Link: https://leetcode.com/problems/maximum-walls-destroyed-by-robots/
 * 
 * Time Complexity:  O(N log N + M log M + N log M) where N = robots.size() <= 10^5, M = walls.size() <= 10^5
 * Space Complexity: O(N) for robot coordinate pairing and O(1) DP auxiliary space
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = static_cast<int>(robots.size());

        // Pair robots with their shooting distances and sort by position
        vector<pair<int, int>> robotPairs(n);
        for (int i = 0; i < n; ++i) {
            robotPairs[i] = {robots[i], distance[i]};
        }
        sort(robotPairs.begin(), robotPairs.end());

        // Sort walls for binary search range queries
        sort(walls.begin(), walls.end());

        // Helper lambda to count walls in [leftBound, rightBound]
        auto countWalls = [&](int leftBound, int rightBound) -> int {
            if (leftBound > rightBound) return 0;
            auto lIt = lower_bound(walls.begin(), walls.end(), leftBound);
            auto rIt = upper_bound(walls.begin(), walls.end(), rightBound);
            return static_cast<int>(rIt - lIt);
        };

        // Base case: i = 0
        int r0 = robotPairs[0].first;
        int d0 = robotPairs[0].second;

        int left0 = countWalls(r0 - d0, r0);
        int right0 = countWalls(r0, (n == 1) ? (r0 + d0) : min(r0 + d0, robotPairs[1].first - 1));

        int dp0 = left0;   // i-th robot shoots LEFT
        int dp1 = right0;  // i-th robot shoots RIGHT
        int prevRight = right0;

        for (int i = 1; i < n; ++i) {
            int rCurr = robotPairs[i].first;
            int dCurr = robotPairs[i].second;
            int rPrev = robotPairs[i - 1].first;

            // Attack range to the left: bounded by previous robot position + 1
            int leftBound = max(rCurr - dCurr, rPrev + 1);
            int leftCurr = countWalls(leftBound, rCurr);

            // Attack range to the right: bounded by next robot position - 1
            int rightCurr = 0;
            if (i == n - 1) {
                rightCurr = countWalls(rCurr, rCurr + dCurr);
            } else {
                rightCurr = countWalls(rCurr, min(rCurr + dCurr, robotPairs[i + 1].first - 1));
            }

            // Total walls between robot i-1 and robot i
            int numBetween = countWalls(rPrev, rCurr);

            // Transitions:
            // 1. Current robot shoots LEFT:
            //    - If previous robot shot LEFT: simply add leftCurr
            //    - If previous robot shot RIGHT: union of ranges cannot exceed numBetween
            int nextDp0 = max(dp0 + leftCurr, dp1 - prevRight + min(prevRight + leftCurr, numBetween));

            // 2. Current robot shoots RIGHT:
            int nextDp1 = max(dp0, dp1) + rightCurr;

            dp0 = nextDp0;
            dp1 = nextDp1;
            prevRight = rightCurr;
        }

        return max(dp0, dp1);
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
        vector<int> robots = {4};
        vector<int> distance = {3};
        vector<int> walls = {1, 10};
        int expected = 1;
        assert(solver.maxWalls(robots, distance, walls) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> robots = {10, 2};
        vector<int> distance = {5, 1};
        vector<int> walls = {5, 2, 7};
        int expected = 3;
        assert(solver.maxWalls(robots, distance, walls) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        vector<int> robots = {1, 2};
        vector<int> distance = {100, 1};
        vector<int> walls = {10};
        int expected = 0;
        assert(solver.maxWalls(robots, distance, walls) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
