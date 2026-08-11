/**
 * Problem: 587. Erect the Fence
 * Difficulty: Hard
 * Topics: Geometry, Math, Array
 * LeetCode Link: https://leetcode.com/problems/erect-the-fence/
 * 
 * Time Complexity:  O(N log N) where N is the number of trees (dominated by sorting)
 * Space Complexity: O(N) to store lower and upper hull vertices
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    // 2D Cross Product of vectors OA and OB
    // cross > 0: Counter-clockwise (left turn)
    // cross < 0: Clockwise (right turn)
    // cross = 0: Collinear
    int crossProduct(const vector<int>& O, const vector<int>& A, const vector<int>& B) {
        return (A[0] - O[0]) * (B[1] - O[1]) - (A[1] - O[1]) * (B[0] - O[0]);
    }

public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        int n = trees.size();
        if (n <= 3) return trees;

        // Sort points lexicographically by x-coordinate, then by y-coordinate
        sort(trees.begin(), trees.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] < b[0];
            return a[1] < b[1];
        });

        vector<vector<int>> lower;
        // Build lower hull: pop strictly on clockwise turn (crossProduct < 0)
        // to retain all collinear boundary points (crossProduct == 0)
        for (int i = 0; i < n; ++i) {
            while (lower.size() >= 2 && crossProduct(lower[lower.size() - 2], lower.back(), trees[i]) < 0) {
                lower.pop_back();
            }
            lower.push_back(trees[i]);
        }

        vector<vector<int>> upper;
        // Build upper hull: scan right to left, pop strictly on clockwise turn (crossProduct < 0)
        for (int i = n - 1; i >= 0; --i) {
            while (upper.size() >= 2 && crossProduct(upper[upper.size() - 2], upper.back(), trees[i]) < 0) {
                upper.pop_back();
            }
            upper.push_back(trees[i]);
        }

        // Concatenate lower and upper hulls
        vector<vector<int>> result = lower;
        result.insert(result.end(), upper.begin(), upper.end());

        // Deduplicate points (endpoints of lower and upper hull overlap)
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());

        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard convex polygon with interior point
    {
        vector<vector<int>> trees = {{1, 1}, {2, 2}, {2, 0}, {2, 4}, {3, 3}, {4, 2}};
        auto result = solver.outerTrees(trees);
        sort(result.begin(), result.end());
        vector<vector<int>> expected = {{1, 1}, {2, 0}, {2, 4}, {3, 3}, {4, 2}};
        sort(expected.begin(), expected.end());
        assert(result == expected);
        cout << "Test 1 Passed (Interior point excluded, boundary included)!" << endl;
    }

    // Test Case 2: All points collinear
    {
        vector<vector<int>> trees = {{1, 2}, {2, 2}, {4, 2}};
        auto result = solver.outerTrees(trees);
        sort(result.begin(), result.end());
        vector<vector<int>> expected = {{1, 2}, {2, 2}, {4, 2}};
        sort(expected.begin(), expected.end());
        assert(result == expected);
        cout << "Test 2 Passed (Collinear line test)!" << endl;
    }

    // Test Case 3: Minimal size (<= 3 points)
    {
        vector<vector<int>> trees = {{0, 0}, {0, 10}, {10, 0}};
        auto result = solver.outerTrees(trees);
        sort(result.begin(), result.end());
        vector<vector<int>> expected = {{0, 0}, {0, 10}, {10, 0}};
        sort(expected.begin(), expected.end());
        assert(result == expected);
        cout << "Test 3 Passed (Triangle boundary)!" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
