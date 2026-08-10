/**
 * Problem: 3614. Process String with Special Operations II
 * Difficulty: Hard
 * Topics: String, Stack / Simulation, Math, Recursion / Backward Tracing
 * LeetCode Link: https://leetcode.com/problems/process-string-with-special-operations-ii/
 * 
 * Time Complexity:  O(N) where N = s.length() <= 10^5
 * Space Complexity: O(N) for prefix length array
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    char processStr(string s, long long k) {
        int n = s.size();
        vector<long long> L(n, 0);
        long long curr = 0;

        // 1. Forward Pass: Track the exact virtual string length at each step
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (c == '*') {
                curr = max(0LL, curr - 1);
            } else if (c == '#') {
                curr *= 2;
            } else if (c == '%') {
                // Reversal does not change length
            } else {
                curr++;
            }
            L[i] = curr;
        }

        // 2. Out-of-bounds check
        if (k < 0 || k >= curr) {
            return '.';
        }

        // 3. Backward Pass: Backtrack index k to find the exact generating character
        long long curr_k = k;
        for (int i = n - 1; i >= 0; --i) {
            long long prev_len = (i > 0) ? L[i - 1] : 0;
            char c = s[i];

            if (c == '*') {
                // '*' removed the last character of previous state.
                // Any character currently surviving at index curr_k was untouched.
                continue;
            } else if (c == '#') {
                // '#' duplicated the string: [0 ... prev_len - 1] repeated twice.
                if (curr_k >= prev_len) {
                    curr_k -= prev_len;
                }
            } else if (c == '%') {
                // '%' reversed the string of length prev_len: index k maps to prev_len - 1 - k.
                curr_k = prev_len - 1 - curr_k;
            } else {
                // Lowercase letter appended to the end (at index prev_len).
                if (curr_k == prev_len) {
                    return c;
                }
            }
        }

        return '.';
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
        string s = "a#b%*";
        long long k = 1;
        char expected = 'a';
        assert(solver.processStr(s, k) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        string s = "cd%#*#";
        long long k = 3;
        char expected = 'd';
        assert(solver.processStr(s, k) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3 (Out of bounds)
    {
        string s = "z*#";
        long long k = 0;
        char expected = '.';
        assert(solver.processStr(s, k) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
