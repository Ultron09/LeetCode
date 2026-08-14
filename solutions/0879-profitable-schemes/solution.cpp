/**
 * Problem: 879. Profitable Schemes
 * Difficulty: Hard
 * Topics: Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/profitable-schemes/
 * 
 * Time Complexity:  O(N * M * P) - Where N is number of crimes, M is number of members, P is minProfit. Max 100 * 100 * 100 = 1,000,000 operations.
 * Space Complexity: O(M * P) - Using a 2D DP array.
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int MOD = 1e9 + 7;
        
        // dp[j][k] is the number of schemes using exactly j members and producing at least k profit
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));
        
        // Base case: 0 members, 0 profit -> 1 scheme (empty set)
        dp[0][0] = 1;
        
        for (int i = 0; i < group.size(); ++i) {
            int g = group[i];
            int p = profit[i];
            
            // Traverse backwards to use 1D/2D space optimization without overriding current step values
            for (int j = n; j >= g; --j) {
                for (int k = minProfit; k >= 0; --k) {
                    int next_profit = max(0, k - p);
                    dp[j][k] = (dp[j][k] + dp[j - g][next_profit]) % MOD;
                }
            }
        }
        
        int total_schemes = 0;
        for (int j = 0; j <= n; ++j) {
            total_schemes = (total_schemes + dp[j][minProfit]) % MOD;
        }
        
        return total_schemes;
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
        vector<int> group = {2, 2};
        vector<int> profit = {2, 3};
        assert(solver.profitableSchemes(5, 3, group, profit) == 2);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<int> group = {2, 3, 5};
        vector<int> profit = {6, 7, 8};
        assert(solver.profitableSchemes(10, 5, group, profit) == 7);
        cout << "Test 2 Passed!" << endl;
    }
    
    // Test Case 3 (Zero minProfit edge case)
    {
        vector<int> group = {1, 1};
        vector<int> profit = {1, 1};
        assert(solver.profitableSchemes(1, 0, group, profit) == 3); // {}, {1}, {1} (first or second)
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
