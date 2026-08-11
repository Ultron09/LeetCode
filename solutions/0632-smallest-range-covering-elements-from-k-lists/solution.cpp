/**
 * Problem: 632. Smallest Range Covering Elements from K Lists
 * Difficulty: Hard
 * Topics: Sliding Window, Heap (Priority Queue), Two Pointers, Greedy
 * LeetCode Link: https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/
 * 
 * Time Complexity:  O(N log K) where N is total elements across all K lists
 * Space Complexity: O(K) for the min-heap storing one element from each list
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

struct Element {
    int val;
    int row;
    int col;

    bool operator>(const Element& other) const {
        return val > other.val;
    }
};

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int k = nums.size();
        
        // Min-heap to maintain the smallest currently active element across all K lists
        priority_queue<Element, vector<Element>, greater<Element>> minHeap;
        int currentMax = INT_MIN;

        // Step 1: Initialize heap with the first element of each of the K sorted lists
        for (int i = 0; i < k; ++i) {
            minHeap.push({nums[i][0], i, 0});
            currentMax = max(currentMax, nums[i][0]);
        }

        int rangeStart = -1e9;
        int rangeEnd = 1e9;

        // Step 2: Continuously pop the minimum element and shrink/advance the range
        while (minHeap.size() == (size_t)k) {
            Element top = minHeap.top();
            minHeap.pop();

            int currentMin = top.val;

            // Check if the current window [currentMin, currentMax] is strictly tighter
            if ((long long)currentMax - currentMin < (long long)rangeEnd - rangeStart) {
                rangeStart = currentMin;
                rangeEnd = currentMax;
            }

            // Advance pointer in the list from which top originated
            if (top.col + 1 < (int)nums[top.row].size()) {
                int nextVal = nums[top.row][top.col + 1];
                minHeap.push({nextVal, top.row, top.col + 1});
                currentMax = max(currentMax, nextVal);
            } else {
                // One list is exhausted; we can no longer cover all K lists
                break;
            }
        }

        return {rangeStart, rangeEnd};
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1
    {
        vector<vector<int>> nums = {
            {4, 10, 15, 24, 26},
            {0, 9, 12, 20},
            {5, 18, 22, 30}
        };
        auto result = solver.smallestRange(nums);
        vector<int> expected = {20, 24};
        cout << "Test 1 -> Expected: [20, 24], Got: [" << result[0] << ", " << result[1] << "]" << endl;
        assert(result == expected);
    }

    // Test Case 2: Identical lists
    {
        vector<vector<int>> nums = {
            {1, 2, 3},
            {1, 2, 3},
            {1, 2, 3}
        };
        auto result = solver.smallestRange(nums);
        vector<int> expected = {1, 1};
        cout << "Test 2 -> Expected: [1, 1], Got: [" << result[0] << ", " << result[1] << "]" << endl;
        assert(result == expected);
    }

    // Test Case 3: Single element in each list
    {
        vector<vector<int>> nums = {
            {10},
            {12},
            {15}
        };
        auto result = solver.smallestRange(nums);
        vector<int> expected = {10, 15};
        cout << "Test 3 -> Expected: [10, 15], Got: [" << result[0] << ", " << result[1] << "]" << endl;
        assert(result == expected);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
