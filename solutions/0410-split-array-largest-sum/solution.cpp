/**
 * Problem: 410. Split Array Largest Sum
 * Difficulty: Hard
 * Topics: Array, Binary Search, Dynamic Programming, Greedy
 * LeetCode Link: https://leetcode.com/problems/split-array-largest-sum/
 * 
 * Time Complexity:  O(N * log(Sum - Max)) - Binary search over answer space with O(N) feasibility check
 * Space Complexity: O(1) - Constant auxiliary space
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    /**
     * Checks if it is possible to split nums into at most k contiguous
     * subarrays such that no subarray sum exceeds targetMaxSum.
     */
    bool canSplit(const vector<int>& nums, int k, long long targetMaxSum) {
        int subarraysCount = 1;
        long long currentSum = 0;

        for (int num : nums) {
            if (currentSum + num > targetMaxSum) {
                // Start a new subarray
                subarraysCount++;
                currentSum = num;
                if (subarraysCount > k) {
                    return false;
                }
            } else {
                currentSum += num;
            }
        }

        return true;
    }

public:
    int splitArray(vector<int>& nums, int k) {
        // Lower bound: maximum individual element (no subarray can be smaller than this)
        long long low = *max_element(nums.begin(), nums.end());
        
        // Upper bound: sum of all elements (entire array in a single partition)
        long long high = accumulate(nums.begin(), nums.end(), 0LL);
        long long result = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (canSplit(nums, k, mid)) {
                result = mid;     // Target is feasible; try finding a smaller maximum sum
                high = mid - 1;
            } else {
                low = mid + 1;    // Infeasible; must increase the allowed subarray capacity
            }
        }

        return static_cast<int>(result);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1 (nums = [7,2,5,10,8], k = 2 -> 18)
    {
        vector<int> nums = {7, 2, 5, 10, 8};
        int k = 2;
        int result = solver.splitArray(nums, k);
        cout << "Test 1 - [7,2,5,10,8], k=2 -> Expected: 18, Got: " << result << endl;
        assert(result == 18);
    }

    // Test Case 2: Standard Example 2 (nums = [1,2,3,4,5], k = 2 -> 9)
    {
        vector<int> nums = {1, 2, 3, 4, 5};
        int k = 2;
        int result = solver.splitArray(nums, k);
        cout << "Test 2 - [1,2,3,4,5], k=2 -> Expected: 9, Got: " << result << endl;
        assert(result == 9);
    }

    // Test Case 3: k == nums.length (each element forms its own subarray)
    {
        vector<int> nums = {1, 4, 4};
        int k = 3;
        int result = solver.splitArray(nums, k);
        cout << "Test 3 - [1,4,4], k=3 -> Expected: 4, Got: " << result << endl;
        assert(result == 4);
    }

    // Test Case 4: k == 1 (single partition containing all elements)
    {
        vector<int> nums = {10, 20, 30};
        int k = 1;
        int result = solver.splitArray(nums, k);
        cout << "Test 4 - [10,20,30], k=1 -> Expected: 60, Got: " << result << endl;
        assert(result == 60);
    }

    // Test Case 5: Single element array
    {
        vector<int> nums = {42};
        int k = 1;
        int result = solver.splitArray(nums, k);
        cout << "Test 5 - [42], k=1 -> Expected: 42, Got: " << result << endl;
        assert(result == 42);
    }

    // Test Case 6: All zeros
    {
        vector<int> nums = {0, 0, 0, 0};
        int k = 2;
        int result = solver.splitArray(nums, k);
        cout << "Test 6 - [0,0,0,0], k=2 -> Expected: 0, Got: " << result << endl;
        assert(result == 0);
    }

    // Test Case 7: Large numbers
    {
        vector<int> nums = {1, 1000000};
        int k = 2;
        int result = solver.splitArray(nums, k);
        cout << "Test 7 - [1, 1000000], k=2 -> Expected: 1000000, Got: " << result << endl;
        assert(result == 1000000);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
