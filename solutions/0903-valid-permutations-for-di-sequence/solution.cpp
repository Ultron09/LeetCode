/**
 * Problem: 903. Valid Permutations for DI Sequence
 * Difficulty: Hard
 * Topics: Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/valid-permutations-for-di-sequence/
 * 
 * Time Complexity:  O(N^2) using prefix sum optimization.
 * Space Complexity: O(N) by optimizing the 2D DP array into two 1D arrays.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    int numPermsDISequence(string s) {
        int n = s.length();
        int MOD = 1e9 + 7;
        
        // dp[j] represents the number of valid permutations of the currently processed length
        // ending with the j-th relative smallest available number.
        vector<int> dp(1, 1);
        
        for (int i = 0; i < n; ++i) {
            vector<int> next_dp(i + 2, 0);
            if (s[i] == 'I') {
                int current_sum = 0;
                for (int j = 1; j <= i + 1; ++j) {
                    current_sum = (current_sum + dp[j - 1]) % MOD;
                    next_dp[j] = current_sum;
                }
            } else {
                int current_sum = 0;
                for (int j = i; j >= 0; --j) {
                    current_sum = (current_sum + dp[j]) % MOD;
                    next_dp[j] = current_sum;
                }
            }
            dp = move(next_dp);
        }
        
        int result = 0;
        for (int x : dp) {
            result = (result + x) % MOD;
        }
        
        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    assert(solver.numPermsDISequence("DID") == 5);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    assert(solver.numPermsDISequence("D") == 1);
    cout << "Test 2 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
