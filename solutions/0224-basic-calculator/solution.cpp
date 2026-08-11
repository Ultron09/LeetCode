/**
 * Problem: 224. Basic Calculator
 * Difficulty: Hard
 * Topics: Math, String, Stack, Recursion
 * LeetCode Link: https://leetcode.com/problems/basic-calculator/
 * 
 * Time Complexity:  O(N) where N = s.length() <= 3 * 10^5 (single pass)
 * Space Complexity: O(N) auxiliary space for evaluation stack
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        long long currentResult = 0;
        int sign = 1; // +1 for positive, -1 for negative
        int n = static_cast<int>(s.length());

        for (int i = 0; i < n; ++i) {
            char ch = s[i];

            if (isdigit(ch)) {
                long long num = 0;
                while (i < n && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    ++i;
                }
                --i; // Adjust index after multi-digit parse
                currentResult += sign * num;
            } else if (ch == '+') {
                sign = 1;
            } else if (ch == '-') {
                sign = -1;
            } else if (ch == '(') {
                // Save current accumulated result and current enclosing sign
                st.push(static_cast<int>(currentResult));
                st.push(sign);
                // Reset for the new parenthesized sub-expression
                currentResult = 0;
                sign = 1;
            } else if (ch == ')') {
                // Sub-expression complete: retrieve sign and parent result
                int prevSign = st.top();
                st.pop();
                int prevResult = st.top();
                st.pop();

                currentResult = prevResult + static_cast<long long>(prevSign) * currentResult;
            }
            // Ignore whitespaces ' '
        }

        return static_cast<int>(currentResult);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: "1 + 1" -> 2
    {
        string s = "1 + 1";
        assert(solver.calculate(s) == 2);
        cout << "Test 1 Passed: \"1 + 1\" = 2" << endl;
    }

    // Test Case 2: " 2-1 + 2 " -> 3
    {
        string s = " 2-1 + 2 ";
        assert(solver.calculate(s) == 3);
        cout << "Test 2 Passed: \" 2-1 + 2 \" = 3" << endl;
    }

    // Test Case 3: "(1+(4+5+2)-3)+(6+8)" -> 23
    {
        string s = "(1+(4+5+2)-3)+(6+8)";
        assert(solver.calculate(s) == 23);
        cout << "Test 3 Passed: \"(1+(4+5+2)-3)+(6+8)\" = 23" << endl;
    }

    // Test Case 4: Unary negations "- (3 - (- (4 + 5)))" -> -12
    {
        string s = "- (3 - (- (4 + 5)))";
        assert(solver.calculate(s) == -12);
        cout << "Test 4 Passed: nested unary negation = -12" << endl;
    }

    // Test Case 5: Direct unary minus "-(2 + 3)" -> -5
    {
        string s = "-(2 + 3)";
        assert(solver.calculate(s) == -5);
        cout << "Test 5 Passed: \"-(2 + 3)\" = -5" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
