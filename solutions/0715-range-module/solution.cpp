/**
 * Problem: 715. Range Module
 * Difficulty: Hard
 * Topics: Intervals
 * LeetCode Link: https://leetcode.com/problems/range-module/
 *
 * Approach: Ordered Map (std::map<int,int>) maintaining disjoint half-open
 *           intervals [start, end). The map key is the interval start, value
 *           is the interval end. All intervals are non-overlapping and sorted.
 *
 *   addRange(l,r):   Merge [l,r) with all overlapping intervals.
 *   queryRange(l,r): Check if a single interval fully contains [l,r).
 *   removeRange(l,r): Trim/split all intervals overlapping with [l,r).
 *
 * Time Complexity:  O(N) worst case per operation (amortized O(log N) typical)
 *                   — each interval added is erased at most once
 * Space Complexity: O(N) — number of disjoint intervals stored
 */

#include <iostream>
#include <map>
#include <cassert>

using namespace std;

class RangeModule {
    map<int, int> intervals;  // start -> end, representing [start, end)

public:
    RangeModule() {}

    void addRange(int left, int right) {
        // Find the first interval that could overlap with [left, right)
        auto it = intervals.upper_bound(left);  // first start > left
        if (it != intervals.begin()) {
            --it;
            if (it->second < left) {
                ++it;  // prev interval ends before [left), no overlap
            }
        }

        // Merge all overlapping intervals into [left, right)
        while (it != intervals.end() && it->first <= right) {
            left = min(left, it->first);
            right = max(right, it->second);
            it = intervals.erase(it);
        }

        intervals[left] = right;
    }

    bool queryRange(int left, int right) {
        // Find the interval that could contain [left, right)
        auto it = intervals.upper_bound(left);  // first start > left
        if (it == intervals.begin()) return false;
        --it;
        // it->first <= left; check if it->second >= right
        return it->second >= right;
    }

    void removeRange(int left, int right) {
        // Find the first interval that could overlap with [left, right)
        auto it = intervals.upper_bound(left);  // first start > left
        if (it != intervals.begin()) {
            --it;
            if (it->second <= left) {
                ++it;  // prev interval ends at or before left, no overlap
            }
        }

        // Process all overlapping intervals
        while (it != intervals.end() && it->first < right) {
            int s = it->first, e = it->second;
            it = intervals.erase(it);

            // Keep the portion before [left, right)
            if (s < left) {
                intervals[s] = left;
            }
            // Keep the portion after [left, right)
            if (e > right) {
                intervals[right] = e;
            }
        }
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    // Test Case 1: Example from problem
    {
        RangeModule rm;
        rm.addRange(10, 20);
        rm.removeRange(14, 16);
        assert(rm.queryRange(10, 14) == true);
        assert(rm.queryRange(13, 15) == false);
        assert(rm.queryRange(16, 17) == true);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Overlapping adds merge correctly
    {
        RangeModule rm;
        rm.addRange(10, 20);
        rm.addRange(15, 25);
        assert(rm.queryRange(10, 25) == true);
        assert(rm.queryRange(24, 25) == true);
        assert(rm.queryRange(25, 26) == false);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Adjacent intervals merge
    {
        RangeModule rm;
        rm.addRange(10, 15);
        rm.addRange(15, 20);  // Touching at 15 → should merge to [10,20)
        assert(rm.queryRange(10, 20) == true);
        cout << "Test 3 Passed!" << endl;
    }

    // Test Case 4: Remove splits an interval
    {
        RangeModule rm;
        rm.addRange(1, 100);
        rm.removeRange(40, 60);
        assert(rm.queryRange(1, 40) == true);
        assert(rm.queryRange(39, 41) == false);
        assert(rm.queryRange(60, 100) == true);
        assert(rm.queryRange(59, 61) == false);
        cout << "Test 4 Passed!" << endl;
    }

    // Test Case 5: Query on empty module
    {
        RangeModule rm;
        assert(rm.queryRange(1, 10) == false);
        cout << "Test 5 Passed!" << endl;
    }

    // Test Case 6: Remove then re-add
    {
        RangeModule rm;
        rm.addRange(1, 10);
        rm.removeRange(1, 10);
        assert(rm.queryRange(1, 10) == false);
        rm.addRange(1, 10);
        assert(rm.queryRange(1, 10) == true);
        cout << "Test 6 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
