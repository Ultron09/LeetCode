/**
 * Problem: 391. Perfect Rectangle
 * Difficulty: Hard
 * Topics: Array, Math, Geometry, Line Sweep
 * LeetCode Link: https://leetcode.com/problems/perfect-rectangle/
 * 
 * Time Complexity:  O(N) - Single pass through rectangles with O(1) set operations per corner
 * Space Complexity: O(N) - Corner point set stores at most 4N entries
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        // Track corners that appear an odd number of times
        set<pair<int,int>> corners;
        long long totalArea = 0;

        int X1 = INT_MAX, Y1 = INT_MAX, X2 = INT_MIN, Y2 = INT_MIN;

        for (const auto& r : rectangles) {
            int x1 = r[0], y1 = r[1], x2 = r[2], y2 = r[3];

            // Expand bounding rectangle
            X1 = min(X1, x1);
            Y1 = min(Y1, y1);
            X2 = max(X2, x2);
            Y2 = max(Y2, y2);

            totalArea += static_cast<long long>(x2 - x1) * (y2 - y1);

            // Toggle each of the 4 corners in the set
            pair<int,int> pts[4] = {{x1,y1}, {x1,y2}, {x2,y1}, {x2,y2}};
            for (const auto& p : pts) {
                if (corners.count(p)) {
                    corners.erase(p);
                } else {
                    corners.insert(p);
                }
            }
        }

        // Check 1: Total area must equal bounding rectangle area
        long long boundingArea = static_cast<long long>(X2 - X1) * (Y2 - Y1);
        if (totalArea != boundingArea) return false;

        // Check 2: Exactly 4 corners remain — the bounding rectangle's corners
        if (corners.size() != 4) return false;
        if (!corners.count({X1, Y1}) || !corners.count({X1, Y2}) ||
            !corners.count({X2, Y1}) || !corners.count({X2, Y2})) {
            return false;
        }

        return true;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Perfect cover
    {
        vector<vector<int>> rects = {{1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}};
        assert(solver.isRectangleCover(rects) == true);
        cout << "Test 1 Passed: Perfect cover -> true" << endl;
    }

    // Test Case 2: Gap between rectangles
    {
        vector<vector<int>> rects = {{1,1,2,3},{1,3,2,4},{3,1,4,2},{3,2,4,4}};
        assert(solver.isRectangleCover(rects) == false);
        cout << "Test 2 Passed: Gap -> false" << endl;
    }

    // Test Case 3: Overlapping rectangles
    {
        vector<vector<int>> rects = {{1,1,3,3},{3,1,4,2},{1,3,2,4},{2,2,4,4}};
        assert(solver.isRectangleCover(rects) == false);
        cout << "Test 3 Passed: Overlap -> false" << endl;
    }

    // Test Case 4: Single rectangle
    {
        vector<vector<int>> rects = {{0,0,1,1}};
        assert(solver.isRectangleCover(rects) == true);
        cout << "Test 4 Passed: Single rectangle -> true" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
