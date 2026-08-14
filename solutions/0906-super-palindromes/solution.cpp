/**
 * Problem: 906. Super Palindromes
 * Difficulty: Hard
 * Topics: Math, String
 * LeetCode Link: https://leetcode.com/problems/super-palindromes/
 * 
 * Time Complexity:  O(W^0.25 * log W) where W is the maximum value of `right` (10^18). We generate W^0.25 (10^5) prefixes.
 * Space Complexity: O(log W) to convert numbers to string for palindrome check.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
private:
    bool isPalindrome(long long x) {
        string s = to_string(x);
        int l = 0, r = s.length() - 1;
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++;
            r--;
        }
        return true;
    }

public:
    int superpalindromesInRange(string left, string right) {
        long long L = stoll(left);
        long long R = stoll(right);
        int magic = 100000;
        int ans = 0;

        // Generate odd length palindromes: e.g. 123 -> 12321
        for (int k = 1; k < magic; ++k) {
            string s = to_string(k);
            string rev = s;
            reverse(rev.begin(), rev.end());
            string p_str = s + rev.substr(1);
            long long v = stoll(p_str);
            if (v > 1e9) continue; // v^2 would exceed 10^18
            long long v2 = v * v;
            if (v2 > R) continue;
            if (v2 >= L && isPalindrome(v2)) {
                ans++;
            }
        }

        // Generate even length palindromes: e.g. 123 -> 123321
        for (int k = 1; k < magic; ++k) {
            string s = to_string(k);
            string rev = s;
            reverse(rev.begin(), rev.end());
            string p_str = s + rev;
            long long v = stoll(p_str);
            if (v > 1e9) continue; // v^2 would exceed 10^18
            long long v2 = v * v;
            if (v2 > R) continue;
            if (v2 >= L && isPalindrome(v2)) {
                ans++;
            }
        }

        return ans;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    assert(solver.superpalindromesInRange("4", "1000") == 4);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    assert(solver.superpalindromesInRange("1", "2") == 1);
    cout << "Test 2 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
