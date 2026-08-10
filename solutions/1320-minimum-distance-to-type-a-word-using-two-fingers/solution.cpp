/**
 * Problem: 1320. Minimum Distance to Type a Word Using Two Fingers
 * Difficulty: Hard
 * Topics: String, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/
 * 
 * Time Complexity:  O(N * Sigma) where N = word.length() <= 300, Sigma = 26
 * Space Complexity: O(Sigma) auxiliary space (27 states for the other finger)
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
public:
    int minimumDistance(string word) {
        int n = static_cast<int>(word.length());
        constexpr int INF = 1e9;
        constexpr int UNPLACED = 26;

        auto getDist = [](int a, int b) -> int {
            if (a == UNPLACED || b == UNPLACED) return 0;
            int r1 = a / 6, c1 = a % 6;
            int r2 = b / 6, c2 = b % 6;
            return abs(r1 - r2) + abs(c1 - c2);
        };

        // dp[other]: minimum distance to type prefix such that one finger is at
        // word[i - 1] and the other finger is at position 'other' (0..25 or 26 for unplaced)
        vector<int> dp(27, INF);
        dp[UNPLACED] = 0; // Initially, one finger is at word[0] with cost 0, other finger is unplaced

        for (int i = 1; i < n; ++i) {
            int curr = word[i] - 'A';
            int prev = word[i - 1] - 'A';

            vector<int> next_dp(27, INF);

            for (int other = 0; other <= UNPLACED; ++other) {
                if (dp[other] == INF) continue;

                // Option 1: Move the same finger from prev to curr
                next_dp[other] = min(next_dp[other], dp[other] + getDist(prev, curr));

                // Option 2: Move the other finger from 'other' to curr
                // The finger previously at 'prev' becomes the new "other" finger
                next_dp[prev] = min(next_dp[prev], dp[other] + getDist(other, curr));
            }

            dp = move(next_dp);
        }

        return *min_element(dp.begin(), dp.end());
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
        string word = "CAKE";
        int expected = 3;
        assert(solver.minimumDistance(word) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        string word = "HAPPY";
        int expected = 6;
        assert(solver.minimumDistance(word) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        string word = "YEAR";
        int expected = 7;
        assert(solver.minimumDistance(word) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
