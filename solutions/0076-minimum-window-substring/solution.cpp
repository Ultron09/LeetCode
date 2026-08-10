/**
 * Problem: 76. Minimum Window Substring
 * Difficulty: Hard
 * Topics: Hash Table, String, Sliding Window
 * LeetCode Link: https://leetcode.com/problems/minimum-window-substring/
 * 
 * Time Complexity:  O(M + N) where M = s.length(), N = t.length()
 * Space Complexity: O(Sigma) = O(1) for fixed ASCII frequency tables
 */

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.length() < t.length()) {
            return "";
        }

        // ASCII frequency array for target characters
        int targetFreq[128] = {0};
        int windowFreq[128] = {0};
        int required = 0;

        for (char c : t) {
            if (targetFreq[static_cast<unsigned char>(c)] == 0) {
                required++;
            }
            targetFreq[static_cast<unsigned char>(c)]++;
        }

        int left = 0;
        int formed = 0;
        int minLen = INT_MAX;
        int minStart = 0;
        int n = static_cast<int>(s.length());

        // Dynamic sliding window
        for (int right = 0; right < n; ++right) {
            unsigned char rightChar = static_cast<unsigned char>(s[right]);
            windowFreq[rightChar]++;

            // If current char frequency matches target frequency, increment formed count
            if (targetFreq[rightChar] > 0 && windowFreq[rightChar] == targetFreq[rightChar]) {
                formed++;
            }

            // Shrink window from the left while all target characters are satisfied
            while (left <= right && formed == required) {
                int currentLen = right - left + 1;
                if (currentLen < minLen) {
                    minLen = currentLen;
                    minStart = left;
                }

                unsigned char leftChar = static_cast<unsigned char>(s[left]);
                windowFreq[leftChar]--;

                // If removing leftChar violates required frequency, decrement formed count
                if (targetFreq[leftChar] > 0 && windowFreq[leftChar] < targetFreq[leftChar]) {
                    formed--;
                }
                left++;
            }
        }

        return (minLen == INT_MAX) ? "" : s.substr(minStart, minLen);
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
        string s = "ADOBECODEBANC";
        string t = "ABC";
        assert(solver.minWindow(s, t) == "BANC");
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        string s = "a";
        string t = "a";
        assert(solver.minWindow(s, t) == "a");
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3
    {
        string s = "a";
        string t = "aa";
        assert(solver.minWindow(s, t) == "");
        cout << "Test 3 Passed!" << endl;
    }

    // Test Case 4
    {
        string s = "ab";
        string t = "b";
        assert(solver.minWindow(s, t) == "b");
        cout << "Test 4 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
