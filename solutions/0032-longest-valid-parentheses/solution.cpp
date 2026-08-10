/**
 * Problem: 32. Longest Valid Parentheses
 * Difficulty: Hard
 * Topics: String, Dynamic Programming, Stack
 * LeetCode Link: https://leetcode.com/problems/longest-valid-parentheses/
 * 
 * Time Complexity:  O(N) where N = s.length() <= 3 * 10^4
 * Space Complexity: O(N) using stack (or O(1) using two-pass counters)
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        // Stack-based index tracking approach:
        // Maintains indices of unmatched characters, with the bottom of the stack
        // acting as the base boundary before the current valid substring.
        stack<int> st;
        st.push(-1); // Initial base boundary

        int maxLen = 0;
        int n = static_cast<int>(s.length());

        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    // New unmatched ')' becomes the new base boundary
                    st.push(i);
                } else {
                    maxLen = max(maxLen, i - st.top());
                }
            }
        }

        return maxLen;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: s = "(()" -> 2
    {
        assert(solver.longestValidParentheses("(()") == 2);
        cout << "Test 1 Passed: \"(()\" -> 2" << endl;
    }

    // Test Case 2: s = ")()())" -> 4
    {
        assert(solver.longestValidParentheses(")()())") == 4);
        cout << "Test 2 Passed: \")()())\" -> 4" << endl;
    }

    // Test Case 3: s = "" -> 0
    {
        assert(solver.longestValidParentheses("") == 0);
        cout << "Test 3 Passed: \"\" -> 0" << endl;
    }

    // Test Case 4: s = "()(())" -> 6
    {
        assert(solver.longestValidParentheses("()(())") == 6);
        cout << "Test 4 Passed: \"()(())\" -> 6" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
