/**
 * Problem: 330. Patching Array
 * Difficulty: Hard
 * Topics: Array, Greedy
 * LeetCode Link: https://leetcode.com/problems/patching-array/
 * 
 * Time Complexity:  O(M + log N) - Where M is nums.size(), since miss at least doubles on each patch
 * Space Complexity: O(1) - Constant auxiliary space
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        long long miss = 1;
        int patches = 0;
        int i = 0;
        int m = static_cast<int>(nums.size());

        while (miss <= n) {
            if (i < m && nums[i] <= miss) {
                // If nums[i] <= miss, we can extend the coverage from [1, miss - 1] to [1, miss + nums[i] - 1]
                miss += nums[i];
                i++;
            } else {
                // Otherwise, greedily patch 'miss' itself, doubling the coverage to [1, 2 * miss - 1]
                miss += miss;
                patches++;
            }
        }

        return patches;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: nums = [1, 3], n = 6 -> 1 (patch 2)
    {
        vector<int> nums = {1, 3};
        int n = 6;
        int expected = 1;
        int result = solver.minPatches(nums, n);
        assert(result == expected);
        cout << "Test 1 Passed: [1, 3], n = 6 -> " << result << endl;
    }

    // Test Case 2: nums = [1, 5, 10], n = 20 -> 2 (patch 2, 4)
    {
        vector<int> nums = {1, 5, 10};
        int n = 20;
        int expected = 2;
        int result = solver.minPatches(nums, n);
        assert(result == expected);
        cout << "Test 2 Passed: [1, 5, 10], n = 20 -> " << result << endl;
    }

    // Test Case 3: nums = [1, 2, 2], n = 5 -> 0
    {
        vector<int> nums = {1, 2, 2};
        int n = 5;
        int expected = 0;
        int result = solver.minPatches(nums, n);
        assert(result == expected);
        cout << "Test 3 Passed: [1, 2, 2], n = 5 -> " << result << endl;
    }

    // Test Case 4: nums = [2], n = 5 -> 2 (patch 1, 4)
    {
        vector<int> nums = {2};
        int n = 5;
        int expected = 2;
        int result = solver.minPatches(nums, n);
        assert(result == expected);
        cout << "Test 4 Passed: [2], n = 5 -> " << result << endl;
    }

    // Test Case 5: Large n = 2147483647 with empty array
    {
        vector<int> nums = {};
        int n = 2147483647;
        int result = solver.minPatches(nums, n);
        assert(result == 31);
        cout << "Test 5 Passed: Empty array, n = INT_MAX -> " << result << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
