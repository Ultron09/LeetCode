/**
 * Problem: 20. Valid Parentheses
 * Difficulty: Easy
 * Topics: Stack & Queue
 * LeetCode Link: https://leetcode.com/problems/valid-parentheses/
 *
 * Approach: Stack
 *
 * Key Insight:
 *   An opening bracket must be closed by the same type of bracket.
 *   Open brackets must be closed in the correct order.
 *   This LIFO (Last-In-First-Out) matching property makes a Stack the perfect data structure.
 *   Iterate through the string: push opening brackets to the stack, 
 *   and for closing brackets, check if they match the top of the stack.
 *
 * Time Complexity:  O(N) - We iterate through the string of length n exactly once.
 * Space Complexity: O(N) - In the worst case (all opening brackets), the stack will hold n characters.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            } else {
                if (st.empty()) return false;
                
                char top = st.top();
                if ((c == ')' && top == '(') ||
                    (c == '}' && top == '{') ||
                    (c == ']' && top == '[')) {
                    st.pop();
                } else {
                    return false;
                }
            }
        }
        
        return st.empty();
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
        string s = "()";
        assert(solver.isValid(s) == true);
        cout << "Test 1 Passed! '()' -> true" << endl;
    }

    // Test Case 2
    {
        string s = "()[]{}";
        assert(solver.isValid(s) == true);
        cout << "Test 2 Passed! '()[]{}' -> true" << endl;
    }

    // Test Case 3
    {
        string s = "(]";
        assert(solver.isValid(s) == false);
        cout << "Test 3 Passed! '(]' -> false" << endl;
    }
    
    // Test Case 4
    {
        string s = "([)]";
        assert(solver.isValid(s) == false);
        cout << "Test 4 Passed! '([)]' -> false" << endl;
    }
    
    // Test Case 5
    {
        string s = "{[]}";
        assert(solver.isValid(s) == true);
        cout << "Test 5 Passed! '{[]}' -> true" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
