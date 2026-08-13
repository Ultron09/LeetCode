/**
 * Problem: 757. Set Intersection Size At Least Two
 * Difficulty: Hard
 * Topics: Greedy, Intervals, Sorting
 * LeetCode Link: https://leetcode.com/problems/set-intersection-size-at-least-two/
 *
 * Approach: Greedy with Sorting
 *
 * Key Insight:
 *   We want to pick the minimum number of points such that every interval contains 
 *   at least two points. To minimize the total points, we should always pick points 
 *   as far right (as large) as possible in the current interval, so they have the 
 *   highest chance of falling into subsequent intervals.
 *   
 *   1. Sort intervals primarily by their end points in ascending order.
 *      If end points are equal, sort by start points in descending order.
 *      This ensures that for intervals ending at the same point, the shortest one
 *      is processed first, establishing the tightest constraints early.
 *   2. Keep track of the two largest points added to our set: `largest` and `second_largest`.
 *   3. Iterate through the intervals:
 *      - If the current interval's start > `largest`: 
 *        It means neither of our tracked points are in this interval. We must add two 
 *        new points. The optimal points are `end - 1` and `end`.
 *      - If the current interval's start > `second_largest` (but <= `largest`):
 *        It means exactly one point (`largest`) is in this interval. We must add one 
 *        more point. The optimal point is `end`.
 *      - If the current interval's start <= `second_largest`:
 *        It means both tracked points are inside the interval. We don't need to add any points.
 *
 * Time Complexity:  O(N log N) - for sorting the intervals.
 * Space Complexity: O(log N) / O(1) - depending on the sorting algorithm overhead.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        // Sort intervals by end ascending, then start descending
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[1] != b[1]) {
                return a[1] < b[1];
            }
            return a[0] > b[0];
        });
        
        int size = 0;
        int largest = -1;
        int second_largest = -1;
        
        for (const auto& interval : intervals) {
            int start = interval[0];
            int end = interval[1];
            
            if (start > largest) {
                // We need 2 new points
                size += 2;
                second_largest = end - 1;
                largest = end;
            } else if (start > second_largest) {
                // We need 1 new point
                size += 1;
                second_largest = largest;
                largest = end;
            }
        }
        
        return size;
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
        vector<vector<int>> intervals = {{1,3},{3,7},{8,9}};
        int res = solver.intersectionSizeTwo(intervals);
        assert(res == 5);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> intervals = {{1,3},{1,4},{2,5},{3,5}};
        int res = solver.intersectionSizeTwo(intervals);
        assert(res == 3);
        cout << "Test 2 Passed! Result: " << res << endl;
    }
    
    // Test Case 3
    {
        vector<vector<int>> intervals = {{1,2},{2,3},{2,4},{4,5}};
        int res = solver.intersectionSizeTwo(intervals);
        assert(res == 5);
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
