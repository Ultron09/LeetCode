/**
 * Problem: 3312. Sorted GCD Pair Queries
 * Difficulty: Hard
 * Topics: Array, Math, Binary Search, Number Theory, Combinatorics, Prefix Sum
 * LeetCode Link: https://leetcode.com/problems/sorted-gcd-pair-queries/
 * 
 * Time Complexity:  O(N + M log M + Q log M) where M = max(nums) <= 5 * 10^4
 * Space Complexity: O(M) for frequency, GCD counts, and prefix sum tables
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int maxVal = 0;
        for (int x : nums) {
            maxVal = max(maxVal, x);
        }

        // 1. Frequency count of each number in nums
        vector<long long> freq(maxVal + 1, 0);
        for (int x : nums) {
            freq[x]++;
        }

        // 2. Count pairs with exact GCD = g via Harmonic Sieve & Inclusion-Exclusion
        // gcdCounts[g] stores the number of pairs (nums[i], nums[j]) with gcd == g
        vector<long long> gcdCounts(maxVal + 1, 0);
        for (int g = maxVal; g >= 1; --g) {
            long long multiplesCount = 0;
            for (int multiple = g; multiple <= maxVal; multiple += g) {
                multiplesCount += freq[multiple];
            }

            // Total pairs where both elements are multiples of g (GCD is a multiple of g)
            long long totalPairs = multiplesCount * (multiplesCount - 1) / 2;

            // Subtract pairs where GCD is a strictly larger multiple of g (2g, 3g, ...)
            for (int multiple = 2 * g; multiple <= maxVal; multiple += g) {
                totalPairs -= gcdCounts[multiple];
            }

            gcdCounts[g] = totalPairs;
        }

        // 3. Compute Prefix Sum of GCD frequencies
        // prefixSum[g] stores the total number of pairs with GCD <= g
        vector<long long> prefixSum(maxVal + 1, 0);
        for (int i = 1; i <= maxVal; ++i) {
            prefixSum[i] = prefixSum[i - 1] + gcdCounts[i];
        }

        // 4. Answer each query using Binary Search
        vector<int> ans;
        ans.reserve(queries.size());

        for (long long q : queries) {
            // Find the first GCD value whose cumulative pair count exceeds q (0-indexed)
            auto it = upper_bound(prefixSum.begin(), prefixSum.end(), q);
            ans.push_back(static_cast<int>(distance(prefixSum.begin(), it)));
        }

        return ans;
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
        vector<int> nums = {2, 3, 4};
        vector<long long> queries = {0, 2, 2};
        vector<int> expected = {1, 2, 2};
        assert(solver.gcdValues(nums, queries) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> nums = {4, 4, 2, 1};
        vector<long long> queries = {5, 3, 1, 0};
        vector<int> expected = {4, 2, 1, 1};
        assert(solver.gcdValues(nums, queries) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        vector<int> nums = {2, 2};
        vector<long long> queries = {0, 0};
        vector<int> expected = {2, 2};
        assert(solver.gcdValues(nums, queries) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
