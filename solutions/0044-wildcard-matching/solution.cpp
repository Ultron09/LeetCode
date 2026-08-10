/**
 * Problem: 44. Wildcard Matching
 * Difficulty: Hard
 * Topics: String, Dynamic Programming, Greedy, Recursion
 * LeetCode Link: https://leetcode.com/problems/wildcard-matching/
 * 
 * Time Complexity:  O(M * N) worst case, O(M + N) average time
 * Space Complexity: O(1) auxiliary space (using greedy two-pointer backtracking)
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int sIdx = 0, pIdx = 0;
        int starIdx = -1;
        int sTmpIdx = -1;

        int m = static_cast<int>(s.length());
        int n = static_cast<int>(p.length());

        while (sIdx < m) {
            // Case 1: Direct match or '?' wildcard match
            if (pIdx < n && (p[pIdx] == '?' || p[pIdx] == s[sIdx])) {
                sIdx++;
                pIdx++;
            }
            // Case 2: '*' wildcard encountered -> record backtrack anchor
            else if (pIdx < n && p[pIdx] == '*') {
                starIdx = pIdx;
                sTmpIdx = sIdx;
                pIdx++;
            }
            // Case 3: Mismatch, but a previous '*' exists -> extend the '*' match in s
            else if (starIdx != -1) {
                pIdx = starIdx + 1;
                sTmpIdx++;
                sIdx = sTmpIdx;
            }
            // Case 4: Mismatch without any preceding '*'
            else {
                return false;
            }
        }

        // Consume any remaining '*' wildcards in pattern
        while (pIdx < n && p[pIdx] == '*') {
            pIdx++;
        }

        return pIdx == n;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: "aa", "a" -> false
    {
        assert(!solver.isMatch("aa", "a"));
        cout << "Test 1 Passed: \"aa\", \"a\" -> false" << endl;
    }

    // Test Case 2: "aa", "*" -> true
    {
        assert(solver.isMatch("aa", "*"));
        cout << "Test 2 Passed: \"aa\", \"*\" -> true" << endl;
    }

    // Test Case 3: "cb", "?a" -> false
    {
        assert(!solver.isMatch("cb", "?a"));
        cout << "Test 3 Passed: \"cb\", \"?a\" -> false" << endl;
    }

    // Test Case 4: "adceb", "*a*b" -> true
    {
        assert(solver.isMatch("adceb", "*a*b"));
        cout << "Test 4 Passed: \"adceb\", \"*a*b\" -> true" << endl;
    }

    // Test Case 5: "acdcb", "a*c?b" -> false
    {
        assert(!solver.isMatch("acdcb", "a*c?b"));
        cout << "Test 5 Passed: \"acdcb\", \"a*c?b\" -> false" << endl;
    }

    // Test Case 6: Empty strings
    {
        assert(solver.isMatch("", ""));
        assert(solver.isMatch("", "*"));
        assert(!solver.isMatch("", "?"));
        cout << "Test 6 Passed: Empty string edge cases" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
