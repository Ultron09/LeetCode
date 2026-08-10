/**
 * Problem: 4. Median of Two Sorted Arrays
 * Difficulty: Hard
 * Topics: Array, Binary Search, Divide and Conquer
 * LeetCode Link: https://leetcode.com/problems/median-of-two-sorted-arrays/
 * 
 * Time Complexity:  O(log(min(M, N))) where M = nums1.size(), N = nums2.size()
 * Space Complexity: O(1) auxiliary space
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
#include <cmath>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Ensure binary search is performed on the smaller array for O(log(min(M, N)))
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = static_cast<int>(nums1.size());
        int n = static_cast<int>(nums2.size());
        int low = 0, high = m;

        while (low <= high) {
            int i = low + (high - low) / 2;
            int j = (m + n + 1) / 2 - i;

            int maxLeft1 = (i == 0) ? INT_MIN : nums1[i - 1];
            int minRight1 = (i == m) ? INT_MAX : nums1[i];

            int maxLeft2 = (j == 0) ? INT_MIN : nums2[j - 1];
            int minRight2 = (j == n) ? INT_MAX : nums2[j];

            if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
                // Correct partition achieved
                if ((m + n) % 2 == 1) {
                    return static_cast<double>(max(maxLeft1, maxLeft2));
                } else {
                    return (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0;
                }
            } else if (maxLeft1 > minRight2) {
                // nums1 partition is too far right; move left
                high = i - 1;
            } else {
                // nums1 partition is too far left; move right
                low = i + 1;
            }
        }

        return 0.0;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Odd total length
    {
        vector<int> nums1 = {1, 3};
        vector<int> nums2 = {2};
        double result = solver.findMedianSortedArrays(nums1, nums2);
        assert(fabs(result - 2.0) < 1e-5);
        cout << "Test 1 Passed: Median = " << result << endl;
    }

    // Test Case 2: Even total length
    {
        vector<int> nums1 = {1, 2};
        vector<int> nums2 = {3, 4};
        double result = solver.findMedianSortedArrays(nums1, nums2);
        assert(fabs(result - 2.5) < 1e-5);
        cout << "Test 2 Passed: Median = " << result << endl;
    }

    // Test Case 3: One array is empty
    {
        vector<int> nums1 = {};
        vector<int> nums2 = {1};
        double result = solver.findMedianSortedArrays(nums1, nums2);
        assert(fabs(result - 1.0) < 1e-5);
        cout << "Test 3 Passed: Median = " << result << endl;
    }

    // Test Case 4: Negative values
    {
        vector<int> nums1 = {-5, 3, 6};
        vector<int> nums2 = {-2, 4};
        // Merged: [-5, -2, 3, 4, 6] -> Median = 3
        double result = solver.findMedianSortedArrays(nums1, nums2);
        assert(fabs(result - 3.0) < 1e-5);
        cout << "Test 4 Passed: Median = " << result << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
