/**
 * Problem: 188. Best Time to Buy and Sell Stock IV
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
 * 
 * Time Complexity:  O(N * k) where N = prices.size(), k <= 100
 * Space Complexity: O(k) auxiliary space for DP state registers
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = static_cast<int>(prices.size());
        if (n <= 1 || k == 0) {
            return 0;
        }

        // Optimization: If k >= n / 2, we can perform unlimited transactions (Greedy)
        if (k >= n / 2) {
            int unlimitedProfit = 0;
            for (int i = 1; i < n; ++i) {
                if (prices[i] > prices[i - 1]) {
                    unlimitedProfit += prices[i] - prices[i - 1];
                }
            }
            return unlimitedProfit;
        }

        // buy[t]: max effective balance after buying the t-th stock
        // sell[t]: max profit after selling the t-th stock
        vector<int> buy(k + 1, -1e9);
        vector<int> sell(k + 1, 0);

        for (int p : prices) {
            for (int t = 1; t <= k; ++t) {
                buy[t] = max(buy[t], sell[t - 1] - p);
                sell[t] = max(sell[t], buy[t] + p);
            }
        }

        return sell[k];
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: k = 2, prices = [2, 4, 1] -> 2
    {
        vector<int> prices = {2, 4, 1};
        assert(solver.maxProfit(2, prices) == 2);
        cout << "Test 1 Passed: k = 2, [2, 4, 1] -> 2" << endl;
    }

    // Test Case 2: k = 2, prices = [3, 2, 6, 5, 0, 3] -> 7
    {
        vector<int> prices = {3, 2, 6, 5, 0, 3};
        assert(solver.maxProfit(2, prices) == 7);
        cout << "Test 2 Passed: k = 2, [3, 2, 6, 5, 0, 3] -> 7" << endl;
    }

    // Test Case 3: k = 1, prices = [1, 2] -> 1
    {
        vector<int> prices = {1, 2};
        assert(solver.maxProfit(1, prices) == 1);
        cout << "Test 3 Passed: k = 1, [1, 2] -> 1" << endl;
    }

    // Test Case 4: k = 100, prices with k >= n/2 optimization
    {
        vector<int> prices = {1, 2, 3, 4, 5};
        assert(solver.maxProfit(100, prices) == 4);
        cout << "Test 4 Passed: k >= n / 2 shortcut -> 4" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
