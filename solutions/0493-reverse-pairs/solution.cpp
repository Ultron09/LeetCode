/**
 * Problem: 493. Reverse Pairs
 * Difficulty: Hard
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort
 * LeetCode Link: https://leetcode.com/problems/reverse-pairs/
 * 
 * Time Complexity:  O(N log N) - Standard divide and conquer merge sort with two-pointer counting
 * Space Complexity: O(N) - Temporary buffer for merging sorted subarrays
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    int mergeSort(vector<int>& nums, int left, int right, vector<int>& temp) {
        if (left >= right) {
            return 0;
        }

        int mid = left + (right - left) / 2;
        int count = mergeSort(nums, left, mid, temp) + mergeSort(nums, mid + 1, right, temp);

        // Count cross-partition reverse pairs (nums[i] > 2 * nums[j])
        int j = mid + 1;
        for (int i = left; i <= mid; ++i) {
            while (j <= right && (long long)nums[i] > 2LL * nums[j]) {
                j++;
            }
            count += (j - (mid + 1));
        }

        // Standard merge of two sorted halves [left..mid] and [mid+1..right]
        int p1 = left;
        int p2 = mid + 1;
        int pTemp = left;

        while (p1 <= mid && p2 <= right) {
            if (nums[p1] <= nums[p2]) {
                temp[pTemp++] = nums[p1++];
            } else {
                temp[pTemp++] = nums[p2++];
            }
        }

        while (p1 <= mid) {
            temp[pTemp++] = nums[p1++];
        }
        while (p2 <= right) {
            temp[pTemp++] = nums[p2++];
        }

        // Copy merged elements back to original array
        for (int k = left; k <= right; ++k) {
            nums[k] = temp[k];
        }

        return count;
    }

public:
    int reversePairs(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int> temp(nums.size());
        return mergeSort(nums, 0, nums.size() - 1, temp);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1
    {
        vector<int> nums = {1, 3, 2, 3, 1};
        int result = solver.reversePairs(nums);
        cout << "Test 1 - {1, 3, 2, 3, 1} -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 2: Standard Example 2
    {
        vector<int> nums = {2, 4, 3, 5, 1};
        int result = solver.reversePairs(nums);
        cout << "Test 2 - {2, 4, 3, 5, 1} -> Expected: 3, Got: " << result << endl;
        assert(result == 3);
    }

    // Test Case 3: Extreme 32-bit Integer Boundary Values
    {
        vector<int> nums = {2147483647, 2147483647, -2147483647, -2147483647, -2147483648, 2147483647};
        int result = solver.reversePairs(nums);
        cout << "Test 3 - Extreme boundaries -> Expected: 9, Got: " << result << endl;
        assert(result == 9);
    }

    // Test Case 4: Single element array
    {
        vector<int> nums = {5};
        int result = solver.reversePairs(nums);
        cout << "Test 4 - Single element -> Expected: 0, Got: " << result << endl;
        assert(result == 0);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
