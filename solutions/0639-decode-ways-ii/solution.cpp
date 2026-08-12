/**
 * Problem: 639. Decode Ways II
 * Difficulty: Hard
 * Topics: Dynamic Programming, String
 * LeetCode Link: https://leetcode.com/problems/decode-ways-ii/
 * 
 * Time Complexity:  O(N) where N is the length of string s
 * Space Complexity: O(1) using constant rolling DP state variables
 */

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    int numDecodings(const string& s) {
        int n = s.length();
        if (n == 0) return 0;

        const int MOD = 1e9 + 7;

        // dp0 represents ways to decode prefix up to index i - 2
        // dp1 represents ways to decode prefix up to index i - 1
        long long dp0 = 1;
        long long dp1 = 0;

        // Base case for s[0]
        if (s[0] == '*') {
            dp1 = 9;
        } else if (s[0] >= '1' && s[0] <= '9') {
            dp1 = 1;
        } else {
            return 0; // Leading '0' is un-decodable
        }

        for (int i = 1; i < n; ++i) {
            char c1 = s[i - 1];
            char c2 = s[i];
            long long current = 0;

            // 1-digit decoding for s[i]
            if (c2 == '*') {
                current = (current + 9 * dp1) % MOD;
            } else if (c2 != '0') {
                current = (current + dp1) % MOD;
            }

            // 2-digit decoding for s[i-1..i]
            long long twoDigitWays = 0;
            if (c1 == '*' && c2 == '*') {
                // "11"-"19" (9) + "21"-"26" (6) = 15
                twoDigitWays = 15;
            } else if (c1 == '*') {
                // If c2 in ['0'..'6'], c1 can be '1' or '2' -> 2 ways
                // If c2 in ['7'..'9'], c1 can only be '1' -> 1 way
                if (c2 >= '0' && c2 <= '6') {
                    twoDigitWays = 2;
                } else {
                    twoDigitWays = 1;
                }
            } else if (c2 == '*') {
                if (c1 == '1') {
                    // "11"-"19" -> 9 ways
                    twoDigitWays = 9;
                } else if (c1 == '2') {
                    // "21"-"26" -> 6 ways
                    twoDigitWays = 6;
                }
            } else {
                int val = (c1 - '0') * 10 + (c2 - '0');
                if (val >= 10 && val <= 26) {
                    twoDigitWays = 1;
                }
            }

            current = (current + twoDigitWays * dp0) % MOD;

            dp0 = dp1;
            dp1 = current;
        }

        return dp1;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1 ("*")
    {
        string s = "*";
        int result = solver.numDecodings(s);
        cout << "Test 1 - s=\"*\" -> Expected: 9, Got: " << result << endl;
        assert(result == 9);
    }

    // Test Case 2: Example 2 ("1*")
    {
        string s = "1*";
        int result = solver.numDecodings(s);
        cout << "Test 2 - s=\"1*\" -> Expected: 18, Got: " << result << endl;
        assert(result == 18);
    }

    // Test Case 3: Example 3 ("2*")
    {
        string s = "2*";
        int result = solver.numDecodings(s);
        cout << "Test 3 - s=\"2*\" -> Expected: 15, Got: " << result << endl;
        assert(result == 15);
    }

    // Test Case 4: Double Wildcards ("**")
    {
        string s = "**";
        int result = solver.numDecodings(s);
        // 1-digit: 9 * 9 = 81; 2-digit: 15; total = 96
        cout << "Test 4 - s=\"**\" -> Expected: 96, Got: " << result << endl;
        assert(result == 96);
    }

    // Test Case 5: Embedded zero and wildcard ("*10")
    {
        string s = "*10";
        int result = solver.numDecodings(s);
        // s="*1" has 11 ways. '0' can only form "10" with previous '1'.
        // Hence result = dp["*"] * 1 = 9 * 1 = 9
        cout << "Test 5 - s=\"*10\" -> Expected: 9, Got: " << result << endl;
        assert(result == 9);
    }

    // Test Case 6: Invalid leading zero
    {
        string s = "0";
        int result = solver.numDecodings(s);
        cout << "Test 6 - s=\"0\" -> Expected: 0, Got: " << result << endl;
        assert(result == 0);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
