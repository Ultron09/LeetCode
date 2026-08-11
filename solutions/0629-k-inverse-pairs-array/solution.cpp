/**
 * Problem: 629. K Inverse Pairs Array
 * Difficulty: Hard
 * Topics: Dynamic Programming, Prefix Sum
 * LeetCode Link: https://leetcode.com/problems/k-inverse-pairs-array/
 * 
 * Time Complexity:  O(N * K) via sliding window / prefix sum recurrence
 * Space Complexity: O(K) space-optimized with a 1D rolling DP array
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int kInversePairs(int n, int k) {
        if (k == 0) return 1;

        const int MOD = 1e9 + 7;

        // dp[j]: Number of permutations of current length having exactly j inverse pairs
        vector<int> dp(k + 1, 0);
        dp[0] = 1;

        for (int i = 2; i <= n; ++i) {
            vector<int> nextDp(k + 1, 0);
            nextDp[0] = 1;

            // Recurrence:
            // nextDp[j] = sum_{p=0}^{min(j, i-1)} dp[j - p]
            // With prefix optimization:
            // nextDp[j] = nextDp[j - 1] + dp[j] - (j >= i ? dp[j - i] : 0)
            for (int j = 1; j <= k; ++j) {
                long long val = (long long)nextDp[j - 1] + dp[j];
                if (j >= i) {
                    val -= dp[j - i];
                }
                nextDp[j] = (val % MOD + MOD) % MOD;
            }

            dp = move(nextDp);
        }

        return dp[k];
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
        int n = 3, k = 0;
        int result = solver.kInversePairs(n, k);
        cout << "Test 1 - n=3, k=0 -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    // Test Case 2: Example 2
    {
        int n = 3, k = 1;
        int result = solver.kInversePairs(n, k);
        cout << "Test 2 - n=3, k=1 -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 3: Symmetric inversion count
    {
        int n = 3, k = 2;
        int result = solver.kInversePairs(n, k);
        cout << "Test 3 - n=3, k=2 -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 4: Reverse permutation (maximum inversions for n=3 is n*(n-1)/2 = 3)
    {
        int n = 3, k = 3;
        int result = solver.kInversePairs(n, k);
        cout << "Test 4 - n=3, k=3 -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    // Test Case 5: Large boundary test
    {
        int n = 1000, k = 1000;
        int result = solver.kInversePairs(n, k);
        cout << "Test 5 - n=1000, k=1000 -> Expected: 663677020, Got: " << result << endl;
        assert(result == 663677020);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
