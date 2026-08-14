/**
 * Problem: 891. Sum of Subsequence Widths
 * Difficulty: Hard
 * Topics: Array, Math, Sorting
 * LeetCode Link: https://leetcode.com/problems/sum-of-subsequence-widths/
 * 
 * Time Complexity:  O(N log N) - due to sorting the array.
 * Space Complexity: O(1) - or O(N) depending on the sorting algorithm used internally.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int sumSubseqWidths(vector<int>& nums) {
        int n = nums.size();
        int mod = 1e9 + 7;
        
        sort(nums.begin(), nums.end());
        
        long long ans = 0;
        long long p = 1; // Power of 2: 2^i
        
        for (int i = 0; i < n; ++i) {
            // nums[i] is the maximum in 2^i subsequences
            // nums[i] is the minimum in 2^(n - 1 - i) subsequences
            // Therefore, its contribution to the total width is nums[i] * 2^i - nums[i] * 2^(n - 1 - i)
            // By grouping the calculation iteratively we can add nums[i] * 2^i and subtract nums[n - 1 - i] * 2^i
            ans = (ans + nums[i] * p - nums[n - 1 - i] * p) % mod;
            p = (p * 2) % mod;
        }
        
        return (ans + mod) % mod; // Ensure the answer is non-negative
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    vector<int> nums1 = {2, 1, 3};
    assert(solver.sumSubseqWidths(nums1) == 6);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    vector<int> nums2 = {2};
    assert(solver.sumSubseqWidths(nums2) == 0);
    cout << "Test 2 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
