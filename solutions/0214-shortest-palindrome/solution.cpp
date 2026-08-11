/**
 * Problem: 214. Shortest Palindrome
 * Difficulty: Hard
 * Topics: String, String Matching, Hash Function, Rolling Hash
 * LeetCode Link: https://leetcode.com/problems/shortest-palindrome/
 * 
 * Time Complexity:  O(N) where N = s.length() <= 5 * 10^4
 * Space Complexity: O(N) auxiliary space for KMP prefix table / combined string
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        if (s.empty()) {
            return "";
        }

        string revS = s;
        reverse(revS.begin(), revS.end());

        // Create combined string: s + '#' + rev(s)
        string combined = s + '#' + revS;
        int n = static_cast<int>(combined.length());

        // Compute KMP Longest Proper Prefix which is also Suffix (LPS / pi array)
        vector<int> pi(n, 0);
        for (int i = 1; i < n; ++i) {
            int j = pi[i - 1];
            while (j > 0 && combined[i] != combined[j]) {
                j = pi[j - 1];
            }
            if (combined[i] == combined[j]) {
                ++j;
            }
            pi[i] = j;
        }

        // The length of the longest palindromic prefix of s
        int longestPalindromicPrefixLen = pi[n - 1];

        // The suffix that must be reversed and prepended
        string toPrepend = revS.substr(0, s.length() - longestPalindromicPrefixLen);

        return toPrepend + s;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: "aacecaaa" -> "aaacecaaa"
    {
        string s = "aacecaaa";
        assert(solver.shortestPalindrome(s) == "aaacecaaa");
        cout << "Test 1 Passed: \"aacecaaa\" -> \"aaacecaaa\"" << endl;
    }

    // Test Case 2: "abcd" -> "dcbabcd"
    {
        string s = "abcd";
        assert(solver.shortestPalindrome(s) == "dcbabcd");
        cout << "Test 2 Passed: \"abcd\" -> \"dcbabcd\"" << endl;
    }

    // Test Case 3: Empty string -> ""
    {
        string s = "";
        assert(solver.shortestPalindrome(s) == "");
        cout << "Test 3 Passed: empty string -> \"\"" << endl;
    }

    // Test Case 4: Already palindrome "abacaba" -> "abacaba"
    {
        string s = "abacaba";
        assert(solver.shortestPalindrome(s) == "abacaba");
        cout << "Test 4 Passed: already palindrome -> \"abacaba\"" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
