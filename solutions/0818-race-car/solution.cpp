/**
 * Problem: 818. Race Car
 * Difficulty: Hard
 * Topics: Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/race-car/
 *
 * Approach: Dynamic Programming
 * 
 * Key Insight:
 *   Our speed increases exponentially as 1, 2, 4, 8, ...
 *   After `n` consecutive 'A' instructions, the distance traveled is `2^n - 1`.
 *   To reach a target `t`, we can either:
 *   
 *   1. Overshoot the target:
 *      Accelerate `n` times to reach `2^n - 1` (where `2^n - 1 >= t`). 
 *      Then we reverse ('R') and cover the remaining distance backward.
 *      The remaining distance is `(2^n - 1) - t`.
 *      Cost: n (forward) + 1 (reverse) + dp[(2^n - 1) - t].
 *
 *   2. Undershoot the target:
 *      Accelerate `k` times (where `k < n`) reaching `2^k - 1 < t`.
 *      Reverse ('R') and accelerate backward `j` times (where `j < k`), covering `2^j - 1`.
 *      Reverse again ('R') to face forward.
 *      Our net position is `(2^k - 1) - (2^j - 1)`. 
 *      The remaining distance to target is `t - ((2^k - 1) - (2^j - 1))`.
 *      Cost: k (forward) + 1 (reverse) + j (backward) + 1 (reverse) + dp[remaining].
 *
 *   Since both `(2^n - 1) - t` and the undershoot `remaining` distance are STRICTLY 
 *   less than `t`, we can build the answer iteratively using a DP array from 1 to `target`.
 *
 * Time Complexity:  O(T * log^2(T)) where T is the target.
 * Space Complexity: O(T) for the DP array.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int racecar(int target) {
        // dp[t] stores the minimum instructions to reach exactly distance t with speed +1
        vector<int> dp(target + 1, 1e9);
        dp[0] = 0;
        
        for (int t = 1; t <= target; ++t) {
            // Find the minimum n such that 2^n - 1 >= t
            int n = 1;
            while ((1 << n) - 1 < t) {
                n++;
            }
            
            // If we can reach it exactly
            if ((1 << n) - 1 == t) {
                dp[t] = n;
                continue;
            }
            
            // Option 1: Overshoot and go back
            // Go forward n steps, then Reverse
            dp[t] = min(dp[t], n + 1 + dp[(1 << n) - 1 - t]);
            
            // Option 2: Undershoot, reverse to burn speed/position, reverse again and continue
            // We can take k forward steps (k < n)
            for (int k = 1; k < n; ++k) {
                // Then reverse and take j backward steps (j < k)
                for (int j = 0; j < k; ++j) {
                    int remaining_dist = t - ((1 << k) - 1) + ((1 << j) - 1);
                    dp[t] = min(dp[t], k + 1 + j + 1 + dp[remaining_dist]);
                }
            }
        }
        
        return dp[target];
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
        int target = 3;
        int res = solver.racecar(target);
        assert(res == 2); // "AA"
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        int target = 6;
        int res = solver.racecar(target);
        assert(res == 5); // "AAARA"
        cout << "Test 2 Passed! Result: " << res << endl;
    }

    // Test Case 3
    {
        int target = 5;
        int res = solver.racecar(target);
        // Expected length is 7: AARARAA
        assert(res == 7);
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
