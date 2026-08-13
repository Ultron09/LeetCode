/**
 * Problem: 805. Split Array With Same Average
 * Difficulty: Hard
 * Topics: Array, Math, Meet in the Middle, Bit Manipulation
 * LeetCode Link: https://leetcode.com/problems/split-array-with-same-average/
 *
 * Approach: Math + Meet-in-the-Middle
 *
 * Key Insight:
 *   If we split the array into two subsets A and B such that average(A) == average(B),
 *   then their average must be equal to the average of the whole array.
 *   Average = S / N, where S is the sum of all elements and N is the total length.
 *   
 *   To avoid floating point issues, we can subtract the average from every element.
 *   Since the average might be fractional, we instead multiply every element by N and
 *   subtract S: 
 *       a[i] = nums[i] * N - S
 *
 *   Now, the problem is equivalent to finding a proper non-empty subset of `a` that 
 *   sums exactly to 0. 
 *
 *   Since N <= 30, a direct subset generation is 2^30 (too slow).
 *   We use Meet-in-the-Middle:
 *   1. Split the array into `left` (first N/2 elements) and `right` (remaining elements).
 *   2. Generate all subset sums of `left`. If any non-empty subset sums to 0, return true.
 *      Store all these sums in a sorted array `left_sums`.
 *   3. Generate all subset sums of `right`. We check all non-empty subsets EXCEPT the 
 *      full `right` subset. If any subset sums to 0, return true.
 *      If we find a sum where `-sum` exists in `left_sums`, return true.
 *
 *   Why can we skip the full `right` subset?
 *   If a valid proper subset consists of the full `right` subset and some subset L of `left`,
 *   then its complement must ALSO sum to 0. Its complement consists of an empty `right` 
 *   subset and the remaining elements of `left` (which is non-empty, since we are looking 
 *   for a proper subset). This complement would have been found entirely in the first step!
 *
 * Time Complexity:  O(2^(N/2) * log(2^(N/2))) due to sorting the left sums. 
 *                   For N=30, 2^15 = 32768, which is extremely fast.
 * Space Complexity: O(2^(N/2)) to store the left sums.
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return false;
        
        int total_sum = 0;
        for (int x : nums) {
            total_sum += x;
        }
        
        // Early Pruning: A valid subset of size k must exist such that (total_sum * k) % n == 0
        bool possible = false;
        for (int k = 1; k <= n / 2; ++k) {
            if ((total_sum * k) % n == 0) {
                possible = true;
                break;
            }
        }
        if (!possible) return false;
        
        // Shift values so that the target sum for any valid subset is 0
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = nums[i] * n - total_sum;
        }
        
        int left_n = n / 2;
        int right_n = n - left_n;
        
        vector<int> left_sums;
        left_sums.reserve(1 << left_n);
        
        // Generate all subset sums for the left half
        for (int mask = 1; mask < (1 << left_n); ++mask) {
            int sum = 0;
            for (int i = 0; i < left_n; ++i) {
                if ((mask >> i) & 1) {
                    sum += a[i];
                }
            }
            if (sum == 0) return true;
            left_sums.push_back(sum);
        }
        
        sort(left_sums.begin(), left_sums.end());
        left_sums.erase(unique(left_sums.begin(), left_sums.end()), left_sums.end());
        
        // Generate subset sums for the right half (excluding the full subset)
        for (int mask = 1; mask < (1 << right_n) - 1; ++mask) {
            int sum = 0;
            for (int i = 0; i < right_n; ++i) {
                if ((mask >> i) & 1) {
                    sum += a[left_n + i];
                }
            }
            if (sum == 0) return true;
            
            // Check if there is a matching sum in the left half
            auto it = lower_bound(left_sums.begin(), left_sums.end(), -sum);
            if (it != left_sums.end() && *it == -sum) {
                return true;
            }
        }
        
        return false;
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
        vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8};
        bool res = solver.splitArraySameAverage(nums);
        assert(res == true);
        cout << "Test 1 Passed! Result: true" << endl;
    }

    // Test Case 2
    {
        vector<int> nums = {3, 1};
        bool res = solver.splitArraySameAverage(nums);
        assert(res == false);
        cout << "Test 2 Passed! Result: false" << endl;
    }

    // Test Case 3 (All elements same)
    {
        vector<int> nums = {2, 2, 2, 2};
        bool res = solver.splitArraySameAverage(nums);
        assert(res == true);
        cout << "Test 3 Passed! Result: true" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
