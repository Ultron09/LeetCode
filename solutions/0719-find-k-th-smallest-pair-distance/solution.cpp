/**
 * Problem: 719. Find K-th Smallest Pair Distance
 * Difficulty: Hard
 * Topics: Binary Search, Two Pointers, Sorting
 * LeetCode Link: https://leetcode.com/problems/find-k-th-smallest-pair-distance/
 *
 * Approach: Binary Search on Answer + Sliding Window Pair Counting
 *
 * Key Insight:
 *   After sorting, the minimum possible distance is 0 and the maximum is
 *   nums[n-1] - nums[0]. We binary search on the distance value `d` and
 *   ask: "How many pairs have distance ≤ d?" If count >= k, the answer
 *   is at most d (search left); otherwise search right.
 *
 *   Counting pairs with distance ≤ d on a sorted array is done in O(N)
 *   with a sliding window: for each right pointer j, advance left pointer
 *   until nums[j] - nums[left] <= d. All indices in [left, j) form valid
 *   pairs with j, contributing (j - left) pairs.
 *
 * Time Complexity:  O(N log N + N log W) — sorting + binary search × linear scan
 *                   where W = max(nums) - min(nums)
 * Space Complexity: O(log N) — for the sort (in-place); O(1) auxiliary
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = static_cast<int>(nums.size());

        // Binary search on the answer (distance value)
        int lo = 0;
        int hi = nums[n - 1] - nums[0]; // Maximum possible distance

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            // Count how many pairs have distance <= mid
            int count = 0;
            int left = 0;
            for (int right = 1; right < n; ++right) {
                // Shrink window: advance left until distance fits
                while (nums[right] - nums[left] > mid) {
                    ++left;
                }
                // All pairs (left, right), (left+1, right), ..., (right-1, right)
                count += right - left;
            }

            if (count >= k) {
                hi = mid; // Answer is at most mid; search for tighter bound
            } else {
                lo = mid + 1; // Need a larger distance
            }
        }

        return lo;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Basic mixed array
    {
        vector<int> nums = {1, 3, 1};
        int k = 1;
        int result = solver.smallestDistancePair(nums, k);
        assert(result == 0);
        cout << "Test 1 Passed! (k=1 → distance 0)" << endl;
    }

    // Test Case 2: All identical elements
    {
        vector<int> nums = {1, 1, 1};
        int k = 2;
        int result = solver.smallestDistancePair(nums, k);
        assert(result == 0);
        cout << "Test 2 Passed! (all same → distance 0)" << endl;
    }

    // Test Case 3: k = total pairs (largest distance)
    {
        vector<int> nums = {1, 6, 1};
        int k = 3;
        int result = solver.smallestDistancePair(nums, k);
        assert(result == 5);
        cout << "Test 3 Passed! (k=3 → distance 5)" << endl;
    }

    // Test Case 4: Two elements
    {
        vector<int> nums = {2, 7};
        int k = 1;
        int result = solver.smallestDistancePair(nums, k);
        assert(result == 5);
        cout << "Test 4 Passed! (two elements → distance 5)" << endl;
    }

    // Test Case 5: Larger sorted array with duplicates
    {
        vector<int> nums = {1, 1, 3, 5, 8};
        // Sorted: [1, 1, 3, 5, 8]
        // Distances: (1,1)=0, (1,3)=2, (1,3)=2, (1,5)=4, (1,5)=4,
        //            (1,8)=7, (1,8)=7, (3,5)=2, (3,8)=5, (5,8)=3
        // Sorted distances: 0, 2, 2, 2, 3, 4, 4, 5, 7, 7
        int k = 4;
        int result = solver.smallestDistancePair(nums, k);
        assert(result == 2);
        cout << "Test 5 Passed! (k=4 → distance 2)" << endl;
    }

    // Test Case 6: All zeros
    {
        vector<int> nums = {0, 0, 0, 0};
        int k = 6; // C(4,2) = 6, all distances = 0
        int result = solver.smallestDistancePair(nums, k);
        assert(result == 0);
        cout << "Test 6 Passed! (all zeros → distance 0)" << endl;
    }

    // Test Case 7: Large spread
    {
        vector<int> nums = {0, 1000000};
        int k = 1;
        int result = solver.smallestDistancePair(nums, k);
        assert(result == 1000000);
        cout << "Test 7 Passed! (max spread → distance 1000000)" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
