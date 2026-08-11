/**
 * Problem: 352. Data Stream as Disjoint Intervals
 * Difficulty: Hard
 * Topics: Binary Search, Design, Ordered Set, Intervals
 * LeetCode Link: https://leetcode.com/problems/data-stream-as-disjoint-intervals/
 * 
 * Time Complexity:  O(log K) for addNum, O(K) for getIntervals (where K is the number of disjoint intervals)
 * Space Complexity: O(K) - Storage for disjoint intervals in std::map
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

class SummaryRanges {
private:
    // intervals maps start -> end for each disjoint interval [start, end]
    map<int, int> intervals;

public:
    SummaryRanges() {
        intervals.clear();
    }
    
    void addNum(int value) {
        // Find the first interval with start > value
        auto it = intervals.upper_bound(value);
        auto prevIt = (it == intervals.begin()) ? intervals.end() : prev(it);

        // 1. Check if value is already contained in the previous interval
        if (prevIt != intervals.end() && prevIt->second >= value) {
            return;
        }

        bool mergeLeft = (prevIt != intervals.end() && prevIt->second + 1 == value);
        bool mergeRight = (it != intervals.end() && it->first == value + 1);

        if (mergeLeft && mergeRight) {
            // Case 1: Bridges the gap between left and right intervals
            prevIt->second = it->second;
            intervals.erase(it);
        } else if (mergeLeft) {
            // Case 2: Extends the left interval to the right by 1
            prevIt->second = value;
        } else if (mergeRight) {
            // Case 3: Extends the right interval to the left by 1
            int rightEnd = it->second;
            intervals.erase(it);
            intervals[value] = rightEnd;
        } else {
            // Case 4: Creates a new isolated interval [value, value]
            intervals[value] = value;
        }
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>> result;
        result.reserve(intervals.size());
        for (const auto& [start, end] : intervals) {
            result.push_back({start, end});
        }
        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    SummaryRanges summaryRanges;

    summaryRanges.addNum(1);
    assert(summaryRanges.getIntervals() == vector<vector<int>>({{1, 1}}));
    cout << "Test 1 Passed: [1, 1]" << endl;

    summaryRanges.addNum(3);
    assert(summaryRanges.getIntervals() == vector<vector<int>>({{1, 1}, {3, 3}}));
    cout << "Test 2 Passed: [1, 1], [3, 3]" << endl;

    summaryRanges.addNum(7);
    assert(summaryRanges.getIntervals() == vector<vector<int>>({{1, 1}, {3, 3}, {7, 7}}));
    cout << "Test 3 Passed: [1, 1], [3, 3], [7, 7]" << endl;

    summaryRanges.addNum(2);
    assert(summaryRanges.getIntervals() == vector<vector<int>>({{1, 3}, {7, 7}}));
    cout << "Test 4 Passed: [1, 3], [7, 7] (bridged left and right)" << endl;

    summaryRanges.addNum(6);
    assert(summaryRanges.getIntervals() == vector<vector<int>>({{1, 3}, {6, 7}}));
    cout << "Test 5 Passed: [1, 3], [6, 7] (extended left of right interval)" << endl;

    // Duplicate insertion
    summaryRanges.addNum(2);
    assert(summaryRanges.getIntervals() == vector<vector<int>>({{1, 3}, {6, 7}}));
    cout << "Test 6 Passed: Duplicate 2 ignored" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
