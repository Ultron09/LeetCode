/**
 * Problem: 887. Super Egg Drop
 * Difficulty: Hard
 * Topics: Math, Dynamic Programming, Binary Search
 * LeetCode Link: https://leetcode.com/problems/super-egg-drop/
 * 
 * Time Complexity:  O(K * M) where M is the answer (M <= N), worst case O(K * log N) average.
 * Space Complexity: O(K) - Using a 1D DP array for space optimization.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int superEggDrop(int k, int n) {
        // dp[i] represents the maximum number of floors we can check
        // with `i` eggs and the current number of moves `m`.
        vector<int> dp(k + 1, 0);
        int m = 0;
        
        while (dp[k] < n) {
            m++;
            // Update backwards to use the 1D space optimized array
            for (int i = k; i >= 1; --i) {
                // dp[i] for this move is 1 + (max floors if egg breaks) + (max floors if egg survives)
                // dp[i-1] is max floors if egg breaks (we used 1 egg, and have 1 less move)
                // dp[i] (before update) is max floors if egg survives (we still have i eggs, 1 less move)
                dp[i] = dp[i] + dp[i - 1] + 1;
            }
        }
        
        return m;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    assert(solver.superEggDrop(1, 2) == 2);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    assert(solver.superEggDrop(2, 6) == 3);
    cout << "Test 2 Passed!" << endl;

    // Test Case 3
    assert(solver.superEggDrop(3, 14) == 4);
    cout << "Test 3 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
