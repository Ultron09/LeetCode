/**
 * Problem: 982. Triples with Bitwise AND Equal To Zero
 * Difficulty: Hard
 * Topics: Array, Bit Manipulation, Hash Table
 * LeetCode Link: https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/
 * 
 * Time Complexity:  O(N^2 + N * 2^16) where N is the length of the array. The first step takes N^2, and the second takes N * 2^16 in the worst case.
 * Space Complexity: O(2^16) to store the frequencies of all possible bitwise AND results of two numbers.
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int countTriplets(vector<int>& nums) {
        // Since nums[i] < 2^16, the result of (nums[i] & nums[j]) will also be < 2^16.
        int count[65536] = {0};
        
        // Count frequencies of all pairs (nums[i] & nums[j])
        for (int a : nums) {
            for (int b : nums) {
                count[a & b]++;
            }
        }
        
        // Collect all non-zero counts to optimize the final iteration
        vector<pair<int, int>> non_zero_counts;
        for (int v = 0; v < 65536; ++v) {
            if (count[v] > 0) {
                non_zero_counts.push_back({v, count[v]});
            }
        }
        
        int triplets = 0;
        
        // For each k, find how many pairs (i, j) satisfy nums[k] & (nums[i] & nums[j]) == 0
        for (int c : nums) {
            for (const auto& p : non_zero_counts) {
                if ((c & p.first) == 0) {
                    triplets += p.second;
                }
            }
        }
        
        return triplets;
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
    assert(solver.countTriplets(nums1) == 12);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    vector<int> nums2 = {0, 0, 0};
    assert(solver.countTriplets(nums2) == 27);
    cout << "Test 2 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
