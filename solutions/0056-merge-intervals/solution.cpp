/**
 * Problem: 56. Merge Intervals
 * Difficulty: Medium
 * Topics: Intervals
 * LeetCode Link: https://leetcode.com/problems/merge-intervals/
 *
 * Approach: Sorting
 *
 * Key Insight:
 *   If we sort the intervals by their start time, we can greedily merge them.
 *   Two adjacent sorted intervals [s1, e1] and [s2, e2] overlap if and only if s2 <= e1.
 *   When they overlap, they can be merged into [s1, max(e1, e2)].
 *   Because they are sorted, if s2 > e1, then any subsequent interval will also have a start time > e1,
 *   so the current merged interval can be safely finalized.
 *
 * Time Complexity:  O(N log N) - Dominant operation is sorting the N intervals.
 * Space Complexity: O(log N) or O(N) depending on the sorting algorithm, plus space for the result array.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
        
        // Sort intervals based on the starting value
        sort(intervals.begin(), intervals.end());
        
        vector<vector<int>> merged;
        merged.push_back(intervals[0]);
        
        for (int i = 1; i < intervals.size(); ++i) {
            // If the current interval overlaps with the last merged interval, merge them
            if (intervals[i][0] <= merged.back()[1]) {
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                // Otherwise, add it as a new distinct interval
                merged.push_back(intervals[i]);
            }
        }
        
        return merged;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    {
        vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
        vector<vector<int>> expected = {{1,6},{8,10},{15,18}};
        auto result = solver.merge(intervals);
        assert(result == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> intervals = {{1,4},{4,5}};
        vector<vector<int>> expected = {{1,5}};
        auto result = solver.merge(intervals);
        assert(result == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Fully enclosed
    {
        vector<vector<int>> intervals = {{1,4},{2,3}};
        vector<vector<int>> expected = {{1,4}};
        auto result = solver.merge(intervals);
        assert(result == expected);
        cout << "Test 3 Passed! (Fully enclosed)" << endl;
    }
    
    // Test Case 4: Unsorted
    {
        vector<vector<int>> intervals = {{2,3},{1,4}};
        vector<vector<int>> expected = {{1,4}};
        auto result = solver.merge(intervals);
        assert(result == expected);
        cout << "Test 4 Passed! (Unsorted)" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
