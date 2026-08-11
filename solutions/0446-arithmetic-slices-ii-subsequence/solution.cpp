/**
 * Problem: 446. Arithmetic Slices II - Subsequence
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/
 * 
 * Time Complexity:  O(N^2) - Iterating over all pairs (j, i) with O(1) hash map operations
 * Space Complexity: O(N^2) - Storing transition counts in hash maps across all indices
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;

        int totalCount = 0;
        // dp[i][d] stores the number of arithmetic subsequences of length >= 2 ending at index i with common difference d
        vector<unordered_map<long long, int>> dp(n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                // Prevent 32-bit signed integer overflow when computing difference
                long long diff = static_cast<long long>(nums[i]) - static_cast<long long>(nums[j]);

                auto it = dp[j].find(diff);
                int countAtJ = (it != dp[j].end()) ? it->second : 0;

                // Any arithmetic subsequence of length >= 2 ending at j extended by nums[i]
                // forms a valid arithmetic subsequence of length >= 3 ending at i.
                totalCount += countAtJ;

                // dp[i][diff] gains all existing subsequences extended from j (countAtJ)
                // plus the 2-element pair (nums[j], nums[i]) (+1).
                dp[i][diff] += countAtJ + 1;
            }
        }

        return totalCount;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard consecutive even numbers
    {
        vector<int> nums = {2, 4, 6, 8, 10};
        int result = solver.numberOfArithmeticSlices(nums);
        cout << "Test 1 - {2, 4, 6, 8, 10} -> Expected: 7, Got: " << result << endl;
        assert(result == 7);
    }

    // Test Case 2: Identical elements (difference 0)
    {
        vector<int> nums = {7, 7, 7, 7, 7};
        int result = solver.numberOfArithmeticSlices(nums);
        cout << "Test 2 - {7, 7, 7, 7, 7} -> Expected: 16, Got: " << result << endl;
        assert(result == 16);
    }

    // Test Case 3: Four identical elements
    {
        vector<int> nums = {1, 1, 1, 1};
        int result = solver.numberOfArithmeticSlices(nums);
        cout << "Test 3 - {1, 1, 1, 1} -> Expected: 5, Got: " << result << endl;
        assert(result == 5);
    }

    // Test Case 4: Long sequence
    {
        vector<int> nums = {1, 2, 3, 4, 5, 6};
        int result = solver.numberOfArithmeticSlices(nums);
        cout << "Test 4 - {1, 2, 3, 4, 5, 6} -> Expected: 12, Got: " << result << endl;
        assert(result == 12);
    }

    // Test Case 5: Large potential overflow differences
    {
        vector<int> nums = {0, 2000000000, -294967296};
        int result = solver.numberOfArithmeticSlices(nums);
        cout << "Test 5 - Large numbers -> Expected: 0, Got: " << result << endl;
        assert(result == 0);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
