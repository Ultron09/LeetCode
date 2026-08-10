/**
 * Problem: 123. Best Time to Buy and Sell Stock III
 * Difficulty: Hard
 * Topics: Array, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
 * 
 * Time Complexity:  O(N) single linear pass
 * Space Complexity: O(1) state machine registers
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        // State variables representing the maximum balance at each phase:
        // buy1:  Maximum balance after buying 1st stock
        // sell1: Maximum profit after selling 1st stock
        // buy2:  Maximum balance after buying 2nd stock (reinvesting sell1)
        // sell2: Maximum profit after selling 2nd stock
        int buy1 = -prices[0];
        int sell1 = 0;
        int buy2 = -prices[0];
        int sell2 = 0;

        for (int price : prices) {
            buy1  = max(buy1, -price);
            sell1 = max(sell1, buy1 + price);
            buy2  = max(buy2, sell1 - price);
            sell2 = max(sell2, buy2 + price);
        }

        return sell2;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: prices = [3,3,5,0,0,3,1,4] -> 6
    {
        vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
        assert(solver.maxProfit(prices) == 6);
        cout << "Test 1 Passed: [3,3,5,0,0,3,1,4] -> 6" << endl;
    }

    // Test Case 2: prices = [1,2,3,4,5] -> 4
    {
        vector<int> prices = {1, 2, 3, 4, 5};
        assert(solver.maxProfit(prices) == 4);
        cout << "Test 2 Passed: [1,2,3,4,5] -> 4" << endl;
    }

    // Test Case 3: prices = [7,6,4,3,1] -> 0
    {
        vector<int> prices = {7, 6, 4, 3, 1};
        assert(solver.maxProfit(prices) == 0);
        cout << "Test 3 Passed: [7,6,4,3,1] -> 0" << endl;
    }

    // Test Case 4: Single day prices = [1] -> 0
    {
        vector<int> prices = {1};
        assert(solver.maxProfit(prices) == 0);
        cout << "Test 4 Passed: [1] -> 0" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
