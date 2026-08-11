/**
 * Problem: 2996. Smallest Missing Integer Greater Than Sequential Prefix Sum
 * Difficulty: Easy
 * Topics: Array, Hash Table, Sorting
 * LeetCode Link: https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/
 * 
 * Time Complexity:  O(N) - Linear pass to calculate prefix sum and O(1) average hash set lookups
 * Space Complexity: O(N) - Hash set storing elements of nums
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>

using namespace std;

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        // Step 1: Compute sum of the longest sequential prefix
        long long prefixSum = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                prefixSum += nums[i];
            } else {
                break;
            }
        }

        // Step 2: Store elements in a hash set for O(1) existence queries
        unordered_set<int> numSet(nums.begin(), nums.end());

        // Step 3: Find the smallest missing integer >= prefixSum
        int candidate = prefixSum;
        while (numSet.count(candidate)) {
            candidate++;
        }

        return candidate;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1 (nums = [1,2,3,2,5] -> 6)
    {
        vector<int> nums = {1, 2, 3, 2, 5};
        int result = solver.missingInteger(nums);
        cout << "Test 1 - nums = [1,2,3,2,5] -> Expected: 6, Got: " << result << endl;
        assert(result == 6);
    }

    // Test Case 2: Standard Example 2 (nums = [3,4,5,1,12,14,13] -> 15)
    {
        vector<int> nums = {3, 4, 5, 1, 12, 14, 13};
        int result = solver.missingInteger(nums);
        cout << "Test 2 - nums = [3,4,5,1,12,14,13] -> Expected: 15, Got: " << result << endl;
        assert(result == 15);
    }

    // Test Case 3: Single element array (nums = [5] -> 6)
    {
        vector<int> nums = {5};
        int result = solver.missingInteger(nums);
        cout << "Test 3 - nums = [5] -> Expected: 6, Got: " << result << endl;
        assert(result == 6);
    }

    // Test Case 4: Non-consecutive from the start (nums = [5,1,2,3] -> 6)
    {
        vector<int> nums = {5, 1, 2, 3};
        int result = solver.missingInteger(nums);
        cout << "Test 4 - nums = [5,1,2,3] -> Expected: 6, Got: " << result << endl;
        assert(result == 6);
    }

    // Test Case 5: Sequential prefix sum matches elements in nums
    {
        vector<int> nums = {1, 2, 3, 4, 10, 11};
        int result = solver.missingInteger(nums);
        cout << "Test 5 - nums = [1,2,3,4,10,11] -> Expected: 12, Got: " << result << endl;
        assert(result == 12);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
