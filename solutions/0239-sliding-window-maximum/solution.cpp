/**
 * Problem: 239. Sliding Window Maximum
 * Difficulty: Hard
 * Topics: Array, Queue, Sliding Window, Heap (Priority Queue), Monotonic Queue
 * LeetCode Link: https://leetcode.com/problems/sliding-window-maximum/
 * 
 * Time Complexity:  O(N) - each element index is pushed and popped at most once
 * Space Complexity: O(K) auxiliary space for the monotonic deque
 */

#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq; // Stores indices of elements in decreasing order of value
        vector<int> result;
        int n = static_cast<int>(nums.size());
        result.reserve(n - k + 1);

        for (int i = 0; i < n; ++i) {
            // 1. Remove indices that are outside the current sliding window
            if (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }

            // 2. Maintain monotonic decreasing order:
            // Remove smaller elements from the back as they are dominated by nums[i]
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            // 3. Add current element index
            dq.push_back(i);

            // 4. Record the maximum (at the front of deque) once window size reaches k
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
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
        vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
        vector<int> expected = {3, 3, 5, 5, 6, 7};
        assert(solver.maxSlidingWindow(nums, 3) == expected);
        cout << "Test 1 Passed: [1,3,-1,-3,5,3,6,7] with k=3 -> [3,3,5,5,6,7]" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> nums = {1};
        vector<int> expected = {1};
        assert(solver.maxSlidingWindow(nums, 1) == expected);
        cout << "Test 2 Passed: Single element with k=1" << endl;
    }

    // Test Case 3: Decreasing Array
    {
        vector<int> nums = {9, 8, 7, 6};
        vector<int> expected = {9, 8, 7};
        assert(solver.maxSlidingWindow(nums, 2) == expected);
        cout << "Test 3 Passed: Decreasing array window max" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
