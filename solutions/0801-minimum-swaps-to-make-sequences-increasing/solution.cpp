/**
 * Problem: 801. Minimum Swaps To Make Sequences Increasing
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/
 *
 * Approach: Dynamic Programming
 *
 * Key Insight:
 *   At any index `i`, we have two choices: we either swap `nums1[i]` and `nums2[i]`, 
 *   or we don't. The decision at index `i` only depends on the elements at `i-1` and 
 *   the decision we made at `i-1`.
 *
 *   Let's maintain two variables:
 *   - `keep`: The minimum swaps required to make the prefix up to `i` valid, given 
 *             that we DO NOT swap at index `i`.
 *   - `swap`: The minimum swaps required to make the prefix up to `i` valid, given 
 *             that we DO swap at index `i`.
 *
 *   For a transition from `i-1` to `i`, we evaluate two conditions:
 *   1. Normal order is strictly increasing: `nums1[i] > nums1[i-1]` and `nums2[i] > nums2[i-1]`
 *      If true, we can transition from non-swapped to non-swapped, or swapped to swapped.
 *   2. Cross order is strictly increasing: `nums1[i] > nums2[i-1]` and `nums2[i] > nums1[i-1]`
 *      If true, we can transition from swapped to non-swapped, or non-swapped to swapped.
 *
 *   Since we only need the DP states from the previous index, we can optimize the 
 *   space complexity from O(N) down to O(1).
 *
 * Time Complexity:  O(N) - One pass through the arrays.
 * Space Complexity: O(1) - Only two variables are maintained.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        
        int prev_keep = 0;
        int prev_swap = 1;
        
        for (int i = 1; i < n; ++i) {
            int curr_keep = 1e9;
            int curr_swap = 1e9;
            
            bool normal_increasing = nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1];
            bool cross_increasing = nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1];
            
            if (normal_increasing) {
                curr_keep = min(curr_keep, prev_keep);
                curr_swap = min(curr_swap, prev_swap + 1);
            }
            
            if (cross_increasing) {
                curr_keep = min(curr_keep, prev_swap);
                curr_swap = min(curr_swap, prev_keep + 1);
            }
            
            prev_keep = curr_keep;
            prev_swap = curr_swap;
        }
        
        return min(prev_keep, prev_swap);
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
        vector<int> nums1 = {1, 3, 5, 4};
        vector<int> nums2 = {1, 2, 3, 7};
        int res = solver.minSwap(nums1, nums2);
        assert(res == 1);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        vector<int> nums1 = {0, 3, 5, 8, 9};
        vector<int> nums2 = {2, 1, 4, 6, 9};
        int res = solver.minSwap(nums1, nums2);
        assert(res == 1);
        cout << "Test 2 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
