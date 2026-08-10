/**
 * Problem: 154. Find Minimum in Rotated Sorted Array II
 * Difficulty: Hard
 * Topics: Array, Binary Search
 * LeetCode Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
 * 
 * Time Complexity:  O(log N) average, O(N) worst-case (when all elements are identical)
 * Space Complexity: O(1) auxiliary space
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right]) {
                // Minimum must lie strictly in the right half (mid + 1 .. right)
                left = mid + 1;
            } else if (nums[mid] < nums[right]) {
                // Minimum lies in the left half including mid (left .. mid)
                right = mid;
            } else {
                // nums[mid] == nums[right]
                // Ambiguity due to duplicates; safely reduce the upper bound
                right--;
            }
        }

        return nums[left];
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
        vector<int> nums = {1, 3, 5};
        assert(solver.findMin(nums) == 1);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> nums = {2, 2, 2, 0, 1};
        assert(solver.findMin(nums) == 0);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Tricky duplicates on boundaries
    {
        vector<int> nums = {1, 0, 1, 1, 1};
        assert(solver.findMin(nums) == 0);
        cout << "Test 3 Passed!" << endl;
    }

    // Test Case 4: Duplicates on both sides
    {
        vector<int> nums = {1, 1, 1, 0, 1};
        assert(solver.findMin(nums) == 0);
        cout << "Test 4 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
