/**
 * Problem: 218. The Skyline Problem
 * Difficulty: Hard
 * Topics: Array, Divide and Conquer, Tree, Binary Indexed Tree, Segment Tree, Line Sweep, Heap (Priority Queue), Ordered Set
 * LeetCode Link: https://leetcode.com/problems/the-skyline-problem/
 * 
 * Time Complexity:  O(N log N) where N = buildings.size() <= 10^4
 * Space Complexity: O(N) auxiliary space for events and active height multiset
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        // Event representation: pair<x-coordinate, height>
        // Start event: height is negative (-H)
        // End event: height is positive (+H)
        vector<pair<int, int>> events;
        for (const auto& b : buildings) {
            events.push_back({b[0], -b[2]}); // Left edge
            events.push_back({b[1], b[2]});  // Right edge
        }

        // Sort events:
        // 1. By x ascending
        // 2. If x equal:
        //    - Both start: higher building first (-H1 < -H2)
        //    - Both end: lower building first (+H1 < +H2)
        //    - One start, one end: start event first (-H < +H)
        sort(events.begin(), events.end());

        // Multiset to track active building heights in O(log N)
        multiset<int> activeHeights = {0};
        vector<vector<int>> result;
        int prevMaxHeight = 0;

        for (const auto& event : events) {
            int x = event.first;
            int h = event.second;

            if (h < 0) {
                // Building start: insert positive height
                activeHeights.insert(-h);
            } else {
                // Building end: erase one instance of height
                activeHeights.erase(activeHeights.find(h));
            }

            // Current maximum active height is at the end of the sorted multiset
            int currentMaxHeight = *activeHeights.rbegin();

            // If the maximum height changes, record a new key point
            if (currentMaxHeight != prevMaxHeight) {
                result.push_back({x, currentMaxHeight});
                prevMaxHeight = currentMaxHeight;
            }
        }

        return result;
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
        vector<vector<int>> buildings = {
            {2, 9, 10},
            {3, 7, 15},
            {5, 12, 12},
            {15, 20, 10},
            {19, 24, 8}
        };
        vector<vector<int>> expected = {
            {2, 10}, {3, 15}, {7, 12}, {12, 0}, {15, 10}, {20, 8}, {24, 0}
        };
        assert(solver.getSkyline(buildings) == expected);
        cout << "Test 1 Passed: Complex skyline contour correctly generated!" << endl;
    }

    // Test Case 2: Example 2 (Adjacent contiguous buildings of equal height)
    {
        vector<vector<int>> buildings = {
            {0, 2, 3},
            {2, 5, 3}
        };
        vector<vector<int>> expected = {
            {0, 3}, {5, 0}
        };
        assert(solver.getSkyline(buildings) == expected);
        cout << "Test 2 Passed: Contiguous equal height buildings merged properly!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
