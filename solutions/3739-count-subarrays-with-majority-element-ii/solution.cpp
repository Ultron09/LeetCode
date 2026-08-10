/**
 * Problem: 3739. Count Subarrays With Majority Element II
 * Difficulty: Hard
 * Topics: Array, Prefix Sum, Hash Table / Frequency Array
 * LeetCode Link: https://leetcode.com/problems/count-subarrays-with-majority-element-ii/
 * 
 * Time Complexity:  O(N) where N = nums.size()
 * Space Complexity: O(N) for the shifted prefix-sum frequency array
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        // Prefix sums can range from -n to +n.
        // Shift by n to store counts at non-negative indices in [0, 2*n].
        vector<int> pre(2 * n + 1, 0);

        int cnt = 0;              // Current prefix sum
        pre[cnt + n] = 1;         // Prefix sum 0 has appeared once at the beginning (empty prefix)

        long long presum = 0;     // Number of previous prefix sums strictly smaller than current prefix sum
        long long ans = 0;        // Total valid subarrays

        for (int x : nums) {
            if (x == target) {
                // Moving +1 expands the strictly-less-than range to include pre[cnt]
                presum += pre[cnt + n];
                cnt++;
            } else {
                // Moving -1 shrinks the strictly-less-than range by removing pre[cnt - 1]
                cnt--;
                presum -= pre[cnt + n];
            }

            ans += presum;
            pre[cnt + n]++;
        }

        return ans;
    }

    // Alias for backward compatibility
    long long countSubarrays(vector<int>& nums, int target) {
        return countMajoritySubarrays(nums, target);
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
        vector<int> nums = {1, 2, 2, 3};
        int target = 2;
        long long expected = 5;
        assert(solver.countMajoritySubarrays(nums, target) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> nums = {1, 1, 1, 1};
        int target = 1;
        long long expected = 10;
        assert(solver.countMajoritySubarrays(nums, target) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: No occurrences of target
    {
        vector<int> nums = {1, 2, 3};
        int target = 4;
        long long expected = 0;
        assert(solver.countMajoritySubarrays(nums, target) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
