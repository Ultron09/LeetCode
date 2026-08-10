/**
 * Problem: 65. Valid Number
 * Difficulty: Hard
 * Topics: String, Deterministic Finite Automaton (DFA)
 * LeetCode Link: https://leetcode.com/problems/valid-number/
 * 
 * Time Complexity:  O(N) where N = s.length() <= 20
 * Space Complexity: O(1) auxiliary space
 */

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        bool seenDigit = false;
        bool seenDot = false;
        bool seenExponent = false;

        int n = static_cast<int>(s.length());

        for (int i = 0; i < n; ++i) {
            char c = s[i];

            if (isdigit(c)) {
                seenDigit = true;
            } else if (c == '+' || c == '-') {
                // Sign can only appear at index 0 or immediately after an exponent 'e'/'E'
                if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E') {
                    return false;
                }
            } else if (c == '.') {
                // Dot cannot appear more than once, nor after an exponent
                if (seenDot || seenExponent) {
                    return false;
                }
                seenDot = true;
            } else if (c == 'e' || c == 'E') {
                // Exponent can only appear once and must be preceded by at least one digit
                if (seenExponent || !seenDigit) {
                    return false;
                }
                seenExponent = true;
                seenDigit = false; // Must be followed by at least one integer digit
            } else {
                // Any other character is invalid
                return false;
            }
        }

        // String is valid if it terminated with at least one valid digit in the active section
        return seenDigit;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Valid number test suite
    vector<string> validCases = {
        "2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", 
        "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789", "0"
    };
    for (const string& s : validCases) {
        assert(solver.isNumber(s) == true);
    }
    cout << "All valid test cases passed!" << endl;

    // Invalid number test suite
    vector<string> invalidCases = {
        "abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53", 
        "e", ".", "+", "-.", ".-4"
    };
    for (const string& s : invalidCases) {
        assert(solver.isNumber(s) == false);
    }
    cout << "All invalid test cases passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
