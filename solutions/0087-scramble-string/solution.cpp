/**
 * Problem: 87. Scramble String
 * Difficulty: Hard
 * Topics: String, Dynamic Programming, Interval DP, Recursion with Memoization
 * LeetCode Link: https://leetcode.com/problems/scramble-string/
 * 
 * Time Complexity:  O(N^4) states & transitions
 * Space Complexity: O(N^3) memoization table
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

class Solution {
private:
    int memo[31][31][31];

    bool solve(int i1, int i2, int len, const string& s1, const string& s2) {
        if (memo[i1][i2][len] != -1) {
            return memo[i1][i2][len] == 1;
        }

        // Substrings match exactly
        if (s1.compare(i1, len, s2, i2, len) == 0) {
            memo[i1][i2][len] = 1;
            return true;
        }

        // Frequency histogram check for early pruning
        int count[26] = {0};
        for (int i = 0; i < len; ++i) {
            count[s1[i1 + i] - 'a']++;
            count[s2[i2 + i] - 'a']--;
        }
        for (int i = 0; i < 26; ++i) {
            if (count[i] != 0) {
                memo[i1][i2][len] = 0;
                return false;
            }
        }

        // Try all split points k in [1, len - 1]
        for (int k = 1; k < len; ++k) {
            // Case 1: Unswapped
            if (solve(i1, i2, k, s1, s2) && solve(i1 + k, i2 + k, len - k, s1, s2)) {
                memo[i1][i2][len] = 1;
                return true;
            }

            // Case 2: Swapped
            if (solve(i1, i2 + len - k, k, s1, s2) && solve(i1 + k, i2, len - k, s1, s2)) {
                memo[i1][i2][len] = 1;
                return true;
            }
        }

        memo[i1][i2][len] = 0;
        return false;
    }

public:
    bool isScramble(string s1, string s2) {
        if (s1.length() != s2.length()) {
            return false;
        }
        memset(memo, -1, sizeof(memo));
        return solve(0, 0, static_cast<int>(s1.length()), s1, s2);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: s1 = "great", s2 = "rgeat" -> true
    {
        assert(solver.isScramble("great", "rgeat") == true);
        cout << "Test 1 Passed: great -> rgeat (true)" << endl;
    }

    // Test Case 2: s1 = "abcde", s2 = "caebd" -> false
    {
        assert(solver.isScramble("abcde", "caebd") == false);
        cout << "Test 2 Passed: abcde -> caebd (false)" << endl;
    }

    // Test Case 3: s1 = "a", s2 = "a" -> true
    {
        assert(solver.isScramble("a", "a") == true);
        cout << "Test 3 Passed: a -> a (true)" << endl;
    }

    // Test Case 4: Long mismatch test case
    {
        string s1 = "eebaacbcbcadaaedceaaacadccd";
        string s2 = "eadcaacabaddaceacbceaabeccd";
        assert(solver.isScramble(s1, s2) == false);
        cout << "Test 4 Passed: complex 27-char mismatch (false)" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
