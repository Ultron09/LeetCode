/**
 * Problem: 552. Student Attendance Record II
 * Difficulty: Hard
 * Topics: Dynamic Programming, Matrix Exponentiation
 * LeetCode Link: https://leetcode.com/problems/student-attendance-record-ii/
 * 
 * Time Complexity:  O(N) - Linear time scanning from length 1 to N
 * Space Complexity: O(1) - Fixed 2x3 state transition table
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int checkRecord(int n) {
        const int MOD = 1e9 + 7;

        // dp[a][l]: number of valid sequences of current length with:
        // a: total 'A' count (0 or 1)
        // l: trailing consecutive 'L' count (0, 1, or 2)
        int dp[2][3] = {0};
        dp[0][0] = 1;

        for (int i = 0; i < n; ++i) {
            int nextDp[2][3] = {0};

            for (int a = 0; a < 2; ++a) {
                for (int l = 0; l < 3; ++l) {
                    long long currentWays = dp[a][l];
                    if (currentWays == 0) continue;

                    // Choice 1: Append 'P' (Present)
                    // Leaves 'A' count unchanged, resets 'L' streak to 0
                    nextDp[a][0] = (nextDp[a][0] + currentWays) % MOD;

                    // Choice 2: Append 'A' (Absent)
                    // Only permissible if current 'A' count is 0, resets 'L' streak to 0
                    if (a == 0) {
                        nextDp[1][0] = (nextDp[1][0] + currentWays) % MOD;
                    }

                    // Choice 3: Append 'L' (Late)
                    // Permissible if trailing 'L' streak is strictly < 2
                    if (l < 2) {
                        nextDp[a][l + 1] = (nextDp[a][l + 1] + currentWays) % MOD;
                    }
                }
            }

            // Copy nextDp into dp
            for (int a = 0; a < 2; ++a) {
                for (int l = 0; l < 3; ++l) {
                    dp[a][l] = nextDp[a][l];
                }
            }
        }

        // Sum up all valid final states
        int totalValidRecords = 0;
        for (int a = 0; a < 2; ++a) {
            for (int l = 0; l < 3; ++l) {
                totalValidRecords = (totalValidRecords + dp[a][l]) % MOD;
            }
        }

        return totalValidRecords;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1
    {
        int n = 2;
        int result = solver.checkRecord(n);
        cout << "Test 1 - n=2 -> Expected: 8, Got: " << result << endl;
        assert(result == 8);
    }

    // Test Case 2: Standard Example 2
    {
        int n = 1;
        int result = solver.checkRecord(n);
        cout << "Test 2 - n=1 -> Expected: 3, Got: " << result << endl;
        assert(result == 3);
    }

    // Test Case 3: Standard Example 3
    {
        int n = 10101;
        int result = solver.checkRecord(n);
        cout << "Test 3 - n=10101 -> Expected: 183236316, Got: " << result << endl;
        assert(result == 183236316);
    }

    // Test Case 4: Minimal boundary
    {
        int n = 3;
        int result = solver.checkRecord(n);
        cout << "Test 4 - n=3 -> Expected: 19, Got: " << result << endl;
        assert(result == 19);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
