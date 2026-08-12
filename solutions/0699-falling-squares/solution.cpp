/**
 * Problem: 699. Falling Squares
 * Difficulty: Hard
 * Topics: Intervals, Coordinate Compression
 * LeetCode Link: https://leetcode.com/problems/falling-squares/
 *
 * Approach: For each new square [left, left+side), scan all previously
 *           placed squares to find the maximum height among overlapping
 *           intervals. The new square lands at that height + its side length.
 *           Track the running global maximum after each drop.
 *
 * Two intervals [l1, r1) and [l2, r2) overlap iff l1 < r2 && l2 < r1.
 * Note: "brushing" (sharing only an endpoint) does NOT count as overlap.
 *
 * Time Complexity:  O(N^2) — for each of N squares, scan all previous ones
 * Space Complexity: O(N)   — store intervals and heights
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> ans(n);

        // For each placed square, store its interval [left, right) and its top height
        vector<int> lefts, rights, heights;

        int globalMax = 0;

        for (int i = 0; i < n; i++) {
            int left = positions[i][0];
            int side = positions[i][1];
            int right = left + side;

            // Find the max height among all previously placed squares
            // whose x-interval overlaps with [left, right)
            int baseHeight = 0;
            for (int j = 0; j < (int)lefts.size(); j++) {
                // Check overlap: [left, right) ∩ [lefts[j], rights[j]) ≠ ∅
                if (left < rights[j] && lefts[j] < right) {
                    baseHeight = max(baseHeight, heights[j]);
                }
            }

            int topHeight = baseHeight + side;

            lefts.push_back(left);
            rights.push_back(right);
            heights.push_back(topHeight);

            globalMax = max(globalMax, topHeight);
            ans[i] = globalMax;
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

    // Test Case 1: positions = [[1,2],[2,3],[6,1]]
    {
        vector<vector<int>> positions = {{1, 2}, {2, 3}, {6, 1}};
        vector<int> result = solver.fallingSquares(positions);
        vector<int> expected = {2, 5, 5};
        assert(result == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: positions = [[100,100],[200,100]]
    {
        vector<vector<int>> positions = {{100, 100}, {200, 100}};
        vector<int> result = solver.fallingSquares(positions);
        vector<int> expected = {100, 100};
        assert(result == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Stacking directly on top
    {
        vector<vector<int>> positions = {{1, 2}, {1, 2}};
        vector<int> result = solver.fallingSquares(positions);
        vector<int> expected = {2, 4};
        assert(result == expected);
        cout << "Test 3 Passed!" << endl;
    }

    // Test Case 4: No overlaps at all
    {
        vector<vector<int>> positions = {{1, 1}, {3, 1}, {5, 1}};
        vector<int> result = solver.fallingSquares(positions);
        vector<int> expected = {1, 1, 1};
        assert(result == expected);
        cout << "Test 4 Passed!" << endl;
    }

    // Test Case 5: Single square
    {
        vector<vector<int>> positions = {{5, 3}};
        vector<int> result = solver.fallingSquares(positions);
        vector<int> expected = {3};
        assert(result == expected);
        cout << "Test 5 Passed!" << endl;
    }

    // Test Case 6: Partial overlap cascade
    {
        vector<vector<int>> positions = {{1, 5}, {2, 2}, {7, 5}};
        vector<int> result = solver.fallingSquares(positions);
        vector<int> expected = {5, 7, 7};
        assert(result == expected);
        cout << "Test 6 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
