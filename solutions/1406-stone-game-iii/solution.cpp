/**
 * Problem: 1406. Stone Game III
 * Difficulty: Hard
 * Topics: Dynamic Programming, Math, Game Theory
 * LeetCode Link: https://leetcode.com/problems/stone-game-iii/
 * 
 * Time Complexity:  O(N) - Single pass backwards through array of size N
 * Space Complexity: O(1) - Using 3 variables to store previous DP states
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        // dp[i] represents the maximum score difference (current_player - opponent) starting from index i
        // Space-optimized to 3 variables for dp[i+1], dp[i+2], dp[i+3]
        int dp1 = 0; // dp[i+1]
        int dp2 = 0; // dp[i+2]
        int dp3 = 0; // dp[i+3]

        for (int i = n - 1; i >= 0; --i) {
            int currentStoneSum = 0;
            int maxScoreDiff = INT_MIN;

            // Choice 1: Take 1 stone
            currentStoneSum += stoneValue[i];
            maxScoreDiff = max(maxScoreDiff, currentStoneSum - dp1);

            // Choice 2: Take 2 stones
            if (i + 1 < n) {
                currentStoneSum += stoneValue[i + 1];
                maxScoreDiff = max(maxScoreDiff, currentStoneSum - dp2);
            }

            // Choice 3: Take 3 stones
            if (i + 2 < n) {
                currentStoneSum += stoneValue[i + 2];
                maxScoreDiff = max(maxScoreDiff, currentStoneSum - dp3);
            }

            // Shift DP state for previous indices
            dp3 = dp2;
            dp2 = dp1;
            dp1 = maxScoreDiff;
        }

        if (dp1 > 0) return "Alice";
        if (dp1 < 0) return "Bob";
        return "Tie";
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
        vector<int> stoneValue = {1, 2, 3, 7};
        string result = solver.stoneGameIII(stoneValue);
        assert(result == "Bob");
        cout << "Test 1 Passed! Result: " << result << endl;
    }

    // Test Case 2
    {
        vector<int> stoneValue = {1, 2, 3, -9};
        string result = solver.stoneGameIII(stoneValue);
        assert(result == "Alice");
        cout << "Test 2 Passed! Result: " << result << endl;
    }

    // Test Case 3
    {
        vector<int> stoneValue = {1, 2, 3, 6};
        string result = solver.stoneGameIII(stoneValue);
        assert(result == "Tie");
        cout << "Test 3 Passed! Result: " << result << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
