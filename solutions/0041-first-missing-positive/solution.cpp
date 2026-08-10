/**
 * Problem: 41. First Missing Positive
 * Difficulty: Hard
 * Topics: Array, Hash Table
 * LeetCode Link: https://leetcode.com/problems/first-missing-positive/
 * 
 * Time Complexity:  O(N) where N = nums.size() <= 10^5
 * Space Complexity: O(1) auxiliary space (in-place cycle sort)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        // 1. In-place cycle sort: place each positive integer x in [1, n] at index x - 1
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        // 2. Scan for the first index where nums[i] != i + 1
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }

        // If all 1..n are present in correct positions, the answer is n + 1
        return n + 1;
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
        vector<int> nums = {1, 2, 0};
        assert(solver.firstMissingPositive(nums) == 3);
        cout << "Test 1 Passed: {1, 2, 0} -> 3" << endl;
    }

    // Test Case 2
    {
        vector<int> nums = {3, 4, -1, 1};
        assert(solver.firstMissingPositive(nums) == 2);
        cout << "Test 2 Passed: {3, 4, -1, 1} -> 2" << endl;
    }

    // Test Case 3
    {
        vector<int> nums = {7, 8, 9, 11, 12};
        assert(solver.firstMissingPositive(nums) == 1);
        cout << "Test 3 Passed: {7, 8, 9, 11, 12} -> 1" << endl;
    }

    // Test Case 4: No missing in 1..9
    {
        vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        assert(solver.firstMissingPositive(nums) == 10);
        cout << "Test 4 Passed: 1..9 -> 10" << endl;
    }

    // Test Case 5: Negatives and duplicates
    {
        vector<int> nums = {-10, 1, 2, 2, 3, 4, 6, 6, 8};
        assert(solver.firstMissingPositive(nums) == 5);
        cout << "Test 5 Passed: duplicates and negatives -> 5" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
