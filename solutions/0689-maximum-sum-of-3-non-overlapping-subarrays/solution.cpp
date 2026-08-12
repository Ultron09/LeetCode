/**
 * Problem: 689. Maximum Sum of 3 Non-Overlapping Subarrays
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/
 * 
 * Time Complexity:  O(N) single-pass precomputations and middle-anchor sweep
 * Space Complexity: O(N) for window sums and prefix/suffix optimal index arrays
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        // Step 1: Compute window sums of size k
        // windowSum[i] stores the sum of nums[i ... i + k - 1]
        int m = n - k + 1;
        vector<int> windowSum(m, 0);

        int currentSum = 0;
        for (int i = 0; i < k; ++i) {
            currentSum += nums[i];
        }
        windowSum[0] = currentSum;

        for (int i = k; i < n; ++i) {
            currentSum += nums[i] - nums[i - k];
            windowSum[i - k + 1] = currentSum;
        }

        // Step 2: Precompute leftMax[i]
        // leftMax[i] is the starting index in [0, i] that maximizes windowSum
        // Strict inequality (>) preserves the lexicographically smallest index on ties
        vector<int> leftMax(m, 0);
        int bestLeft = 0;
        for (int i = 0; i < m; ++i) {
            if (windowSum[i] > windowSum[bestLeft]) {
                bestLeft = i;
            }
            leftMax[i] = bestLeft;
        }

        // Step 3: Precompute rightMax[i]
        // rightMax[i] is the starting index in [i, m - 1] that maximizes windowSum
        // Non-strict inequality (>=) preserves the earlier (lexicographically smaller) index on ties
        vector<int> rightMax(m, 0);
        int bestRight = m - 1;
        for (int i = m - 1; i >= 0; --i) {
            if (windowSum[i] >= windowSum[bestRight]) {
                bestRight = i;
            }
            rightMax[i] = bestRight;
        }

        // Step 4: Sweep over all possible middle window positions j
        // Middle window index j ranges from k to m - 1 - k (leaving space for left & right windows)
        int maxSum = -1;
        vector<int> result(3, 0);

        for (int j = k; j <= m - 1 - k; ++j) {
            int l = leftMax[j - k];
            int r = rightMax[j + k];
            int total = windowSum[l] + windowSum[j] + windowSum[r];

            if (total > maxSum) {
                maxSum = total;
                result = {l, j, r};
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
        vector<int> nums = {1, 2, 1, 2, 6, 7, 5, 1};
        int k = 2;
        vector<int> result = solver.maxSumOfThreeSubarrays(nums, k);
        cout << "Test 1 -> Expected: [0, 3, 5], Got: [" 
             << result[0] << ", " << result[1] << ", " << result[2] << "]" << endl;
        assert(result == (vector<int>{0, 3, 5}));
    }

    // Test Case 2: Example 2 (Ties resolved lexicographically)
    {
        vector<int> nums = {1, 2, 1, 2, 1, 2, 1, 2, 1};
        int k = 2;
        vector<int> result = solver.maxSumOfThreeSubarrays(nums, k);
        cout << "Test 2 -> Expected: [0, 2, 4], Got: [" 
             << result[0] << ", " << result[1] << ", " << result[2] << "]" << endl;
        assert(result == (vector<int>{0, 2, 4}));
    }

    // Test Case 3: k = 1
    {
        vector<int> nums = {4, 5, 10, 6, 11, 17, 4, 11, 1, 3};
        int k = 1;
        vector<int> result = solver.maxSumOfThreeSubarrays(nums, k);
        cout << "Test 3 -> Expected: [4, 5, 7], Got: [" 
             << result[0] << ", " << result[1] << ", " << result[2] << "]" << endl;
        assert(result == (vector<int>{4, 5, 7}));
    }

    // Test Case 4: Minimal valid array size (3 * k elements)
    {
        vector<int> nums = {7, 7, 7};
        int k = 1;
        vector<int> result = solver.maxSumOfThreeSubarrays(nums, k);
        cout << "Test 4 -> Expected: [0, 1, 2], Got: [" 
             << result[0] << ", " << result[1] << ", " << result[2] << "]" << endl;
        assert(result == (vector<int>{0, 1, 2}));
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
