/**
 * Problem: 956. Tallest Billboard
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/tallest-billboard/
 * 
 * Time Complexity:  O(N * S) where N is rods.length and S is sum(rods).
 * Space Complexity: O(S) for the DP array.
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int total_sum = accumulate(rods.begin(), rods.end(), 0);
        
        // dp[d] will store the maximum height of the taller support
        // when the height difference between the two supports is exactly d.
        vector<int> dp(total_sum + 1, -1);
        dp[0] = 0;
        
        for (int rod : rods) {
            // Create a copy of dp to update synchronously
            vector<int> next_dp = dp;
            
            for (int d = 0; d <= total_sum; ++d) {
                if (dp[d] < 0) continue;
                
                // Option 1: Put the rod on the taller support
                if (d + rod <= total_sum) {
                    next_dp[d + rod] = max(next_dp[d + rod], dp[d] + rod);
                }
                
                // Option 2: Put the rod on the shorter support
                int new_diff = abs(d - rod);
                // If d >= rod, we put it on shorter but shorter is still shorter (or equal).
                // The taller support's height doesn't change: it's still dp[d].
                // If d < rod, the shorter support becomes the taller one.
                // The new taller height is (dp[d] - d) + rod.
                // In both cases, the new height of the taller support is dp[d] + max(0, rod - d).
                next_dp[new_diff] = max(next_dp[new_diff], dp[d] + max(0, rod - d));
            }
            
            dp = move(next_dp);
        }
        
        return dp[0];
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    vector<int> rods1 = {1, 2, 3, 6};
    assert(solver.tallestBillboard(rods1) == 6);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    vector<int> rods2 = {1, 2, 3, 4, 5, 6};
    assert(solver.tallestBillboard(rods2) == 10);
    cout << "Test 2 Passed!" << endl;

    // Test Case 3
    vector<int> rods3 = {1, 2};
    assert(solver.tallestBillboard(rods3) == 0);
    cout << "Test 3 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
