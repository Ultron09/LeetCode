/**
 * Problem: 149. Max Points on a Line
 * Difficulty: Hard
 * Topics: Array, Hash Table, Math & Geometry
 * LeetCode Link: https://leetcode.com/problems/max-points-on-a-line/
 * 
 * Time Complexity:  O(N^2 * log(max_coord)) where N = points.size() <= 300
 * Space Complexity: O(N) auxiliary space for slope hash map
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <cstdint>
#include <cassert>

using namespace std;

class Solution {
private:
    int gcd(int a, int b) {
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

public:
    int maxPoints(vector<vector<int>>& points) {
        int n = static_cast<int>(points.size());
        if (n <= 2) {
            return n;
        }

        int maxCollinear = 1;

        for (int i = 0; i < n; ++i) {
            // Hash map keyed by canonical coprime slope representation (encoded 64-bit int)
            unordered_map<int64_t, int> slopeCount;
            int currentMax = 0;

            for (int j = i + 1; j < n; ++j) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                int g = gcd(abs(dx), abs(dy));
                dx /= g;
                dy /= g;

                // Canonical orientation
                if (dx < 0) {
                    dx = -dx;
                    dy = -dy;
                } else if (dx == 0) {
                    dy = 1; // Vertical line
                } else if (dy == 0) {
                    dx = 1; // Horizontal line
                }

                // Pack coprime (dx, dy) into a 64-bit integer
                int64_t key = (static_cast<int64_t>(dx) << 32) | static_cast<uint32_t>(dy);
                slopeCount[key]++;
                currentMax = max(currentMax, slopeCount[key]);
            }

            // Add 1 for the anchor point itself
            maxCollinear = max(maxCollinear, currentMax + 1);
        }

        return maxCollinear;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: [[1,1],[2,2],[3,3]] -> 3
    {
        vector<vector<int>> points = {{1, 1}, {2, 2}, {3, 3}};
        assert(solver.maxPoints(points) == 3);
        cout << "Test 1 Passed: [[1,1],[2,2],[3,3]] -> 3" << endl;
    }

    // Test Case 2: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]] -> 4
    {
        vector<vector<int>> points = {{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}};
        assert(solver.maxPoints(points) == 4);
        cout << "Test 2 Passed: 6 points with 4 collinear -> 4" << endl;
    }

    // Test Case 3: Single point -> 1
    {
        vector<vector<int>> points = {{0, 0}};
        assert(solver.maxPoints(points) == 1);
        cout << "Test 3 Passed: single point -> 1" << endl;
    }

    // Test Case 4: Two points -> 2
    {
        vector<vector<int>> points = {{0, 0}, {1, 1}};
        assert(solver.maxPoints(points) == 2);
        cout << "Test 4 Passed: two points -> 2" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
