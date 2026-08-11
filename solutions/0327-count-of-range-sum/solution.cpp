/**
 * Problem: 327. Count of Range Sum
 * Difficulty: Hard
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set
 * LeetCode Link: https://leetcode.com/problems/count-of-range-sum/
 * 
 * Time Complexity:  O(N log N) - Divide and conquer via merge sort on prefix sums with two-pointer range queries
 * Space Complexity: O(N) - Temporary buffer for merge sort and prefix sum array
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    int countWhileMergeSort(vector<long long>& sums, int left, int right, int lower, int upper, vector<long long>& temp) {
        if (left >= right) return 0;

        int mid = left + (right - left) / 2;
        int count = countWhileMergeSort(sums, left, mid, lower, upper, temp) +
                    countWhileMergeSort(sums, mid + 1, right, lower, upper, temp);

        // Two-pointer range counting across split [left..mid] and [mid+1..right]
        // For each j in [mid + 1, right], find i in [left, mid] such that:
        // sums[j] - upper <= sums[i] <= sums[j] - lower
        int low_ptr = left;
        int high_ptr = left;

        for (int j = mid + 1; j <= right; ++j) {
            long long min_val = sums[j] - upper;
            long long max_val = sums[j] - lower;

            while (low_ptr <= mid && sums[low_ptr] < min_val) {
                low_ptr++;
            }
            while (high_ptr <= mid && sums[high_ptr] <= max_val) {
                high_ptr++;
            }
            count += (high_ptr - low_ptr);
        }

        // Standard merge of two sorted halves [left..mid] and [mid+1..right]
        int p1 = left, p2 = mid + 1, p = left;
        while (p1 <= mid && p2 <= right) {
            if (sums[p1] <= sums[p2]) {
                temp[p++] = sums[p1++];
            } else {
                temp[p++] = sums[p2++];
            }
        }
        while (p1 <= mid) temp[p++] = sums[p1++];
        while (p2 <= right) temp[p++] = sums[p2++];

        for (int i = left; i <= right; ++i) {
            sums[i] = temp[i];
        }

        return count;
    }

public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = static_cast<int>(nums.size());
        if (n == 0) return 0;

        // Compute prefix sums: prefix[0] = 0, prefix[k] = sum(nums[0..k-1])
        // Use long long to avoid 32-bit signed integer overflow
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        vector<long long> temp(n + 1, 0);
        return countWhileMergeSort(prefix, 0, n, lower, upper, temp);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: nums = [-2, 5, -1], lower = -2, upper = 2 -> 3
    {
        vector<int> nums = {-2, 5, -1};
        int lower = -2, upper = 2;
        int expected = 3;
        int result = solver.countRangeSum(nums, lower, upper);
        assert(result == expected);
        cout << "Test 1 Passed: [-2, 5, -1], [-2, 2] -> " << result << endl;
    }

    // Test Case 2: nums = [0], lower = 0, upper = 0 -> 1
    {
        vector<int> nums = {0};
        int lower = 0, upper = 0;
        int expected = 1;
        int result = solver.countRangeSum(nums, lower, upper);
        assert(result == expected);
        cout << "Test 2 Passed: [0], [0, 0] -> " << result << endl;
    }

    // Test Case 3: All zeroes nums = [0, 0], lower = 0, upper = 0 -> 3
    {
        vector<int> nums = {0, 0};
        int lower = 0, upper = 0;
        int expected = 3;
        int result = solver.countRangeSum(nums, lower, upper);
        assert(result == expected);
        cout << "Test 3 Passed: [0, 0], [0, 0] -> " << result << endl;
    }

    // Test Case 4: Single element outside range nums = [5], lower = 6, upper = 10 -> 0
    {
        vector<int> nums = {5};
        int lower = 6, upper = 10;
        int expected = 0;
        int result = solver.countRangeSum(nums, lower, upper);
        assert(result == expected);
        cout << "Test 4 Passed: [5], [6, 10] -> " << result << endl;
    }

    // Test Case 5: Large values and negative numbers (overflow check)
    {
        vector<int> nums = {-2147483647, 0, -2147483647, 2147483647};
        int lower = -564, upper = 3864;
        int result = solver.countRangeSum(nums, lower, upper);
        // Subarrays:
        // [1, 1] = 0 (valid)
        // [2, 3] = -2147483647 + 2147483647 = 0 (valid)
        // [1, 3] = 0 + (-2147483647) + 2147483647 = 0 (valid)
        int expected = 3;
        assert(result == expected);
        cout << "Test 5 Passed: Large 64-bit sum values -> " << result << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
