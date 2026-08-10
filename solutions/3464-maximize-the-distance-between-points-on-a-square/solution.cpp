/**
 * Problem: 3464. Maximize the Distance Between Points on a Square
 * Difficulty: Hard
 * Topics: Array, Binary Search, Greedy, Geometry
 * LeetCode Link: https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/
 * 
 * Time Complexity:  O(N log N + log(side) * (N / k) * k log N) = O(N log N * log(side))
 * Space Complexity: O(N) for perimeter coordinates and extended positions array
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        // Linearize 2D points on the square perimeter to 1D positions in [0, 4 * side)
        auto getPos = [&](long long x, long long y) -> long long {
            if (y == 0) {
                return x;
            } else if (x == side) {
                return side + y;
            } else if (y == side) {
                return 3LL * side - x;
            } else {
                return 4LL * side - y;
            }
        };

        int n = static_cast<int>(points.size());
        vector<long long> positions(n);
        for (int i = 0; i < n; ++i) {
            positions[i] = getPos(points[i][0], points[i][1]);
        }
        sort(positions.begin(), positions.end());

        long long P = 4LL * side;
        // Extend array to handle circular boundary seamlessly
        vector<long long> extPositions(2 * n);
        for (int i = 0; i < n; ++i) {
            extPositions[i] = positions[i];
            extPositions[i + n] = positions[i] + P;
        }

        // Feasibility check: can we select k points with circular perimeter gap >= d?
        auto canPlace = [&](long long d) -> bool {
            long long maxFirstOffset = P / k;
            for (int i = 0; i < n; ++i) {
                if (positions[i] - positions[0] > maxFirstOffset) {
                    break;
                }

                int currIdx = i;
                bool possible = true;

                for (int step = 1; step < k; ++step) {
                    long long target = extPositions[currIdx] + d;
                    auto it = lower_bound(extPositions.begin() + currIdx, extPositions.begin() + i + n, target);
                    if (it == extPositions.begin() + i + n) {
                        possible = false;
                        break;
                    }
                    currIdx = static_cast<int>(distance(extPositions.begin(), it));
                }

                // Check wrap-around distance between the last selected point and the first point
                if (possible && (extPositions[i] + P - extPositions[currIdx] >= d)) {
                    return true;
                }
            }
            return false;
        };

        // Binary search on the answer in [1, side]
        // Since k >= 4, the answer can never exceed side
        long long low = 1, high = side;
        long long ans = 1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (canPlace(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return static_cast<int>(ans);
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
        int side = 2;
        vector<vector<int>> points = {{0, 2}, {2, 0}, {2, 2}, {0, 0}};
        int k = 4;
        int expected = 2;
        assert(solver.maxDistance(side, points, k) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        int side = 2;
        vector<vector<int>> points = {{0, 0}, {1, 2}, {2, 0}, {2, 2}, {2, 1}};
        int k = 4;
        int expected = 1;
        assert(solver.maxDistance(side, points, k) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        int side = 2;
        vector<vector<int>> points = {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 2}, {2, 1}};
        int k = 5;
        int expected = 1;
        assert(solver.maxDistance(side, points, k) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
