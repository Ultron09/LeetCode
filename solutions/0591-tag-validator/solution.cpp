/**
 * Problem: 591. Tag Validator
 * Difficulty: Hard
 * Topics: Stack, String
 * LeetCode Link: https://leetcode.com/problems/tag-validator/
 * 
 * Time Complexity:  O(N) where N is the length of code snippet
 * Space Complexity: O(N) for the parsing stack and tag strings
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isValid(string code) {
        int n = code.length();
        stack<string> tagStack;
        int i = 0;

        while (i < n) {
            // Rule 1 & Rule 4: Everything must be enclosed within a single closed root tag.
            // If stack becomes empty before consuming the entire string, it indicates
            // trailing content or multiple root tags.
            if (i > 0 && tagStack.empty()) {
                return false;
            }

            if (code[i] == '<') {
                // Case 1: CDATA Section <![CDATA[ ... ]]>
                if (code.compare(i, 9, "<![CDATA[") == 0) {
                    // CDATA must reside inside an open tag
                    if (tagStack.empty()) {
                        return false;
                    }
                    size_t cdataEnd = code.find("]]>", i + 9);
                    if (cdataEnd == string::npos) {
                        return false;
                    }
                    i = cdataEnd + 3;
                }
                // Case 2: End Tag </TAG_NAME>
                else if (i + 1 < n && code[i + 1] == '/') {
                    size_t closePos = code.find('>', i + 2);
                    if (closePos == string::npos) {
                        return false;
                    }
                    string tagName = code.substr(i + 2, closePos - (i + 2));
                    if (!isValidTagName(tagName)) {
                        return false;
                    }
                    if (tagStack.empty() || tagStack.top() != tagName) {
                        return false;
                    }
                    tagStack.pop();
                    i = closePos + 1;
                }
                // Case 3: Start Tag <TAG_NAME>
                else {
                    size_t closePos = code.find('>', i + 1);
                    if (closePos == string::npos) {
                        return false;
                    }
                    string tagName = code.substr(i + 1, closePos - (i + 1));
                    if (!isValidTagName(tagName)) {
                        return false;
                    }
                    tagStack.push(tagName);
                    i = closePos + 1;
                }
            } else {
                // Case 4: Plain Text Characters
                // Characters outside any enclosing tag are invalid
                if (tagStack.empty()) {
                    return false;
                }
                ++i;
            }
        }

        // All tags must be matched and closed
        return tagStack.empty();
    }

private:
    bool isValidTagName(const string& tag) {
        if (tag.empty() || tag.length() > 9) return false;
        for (char c : tag) {
            if (!isupper(c)) return false;
        }
        return true;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Valid CDATA and tags
    {
        string code = "<DIV>This is the first line <![CDATA[<div>]]></DIV>";
        assert(solver.isValid(code) == true);
        cout << "Test 1 Passed (Valid CDATA inside DIV)!" << endl;
    }

    // Test Case 2: Complex CDATA content with nested brackets
    {
        string code = "<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>";
        assert(solver.isValid(code) == true);
        cout << "Test 2 Passed (Complex CDATA with brackets)!" << endl;
    }

    // Test Case 3: Unbalanced tags
    {
        string code = "<A>  <B> </A>   </B>";
        assert(solver.isValid(code) == false);
        cout << "Test 3 Passed (Unbalanced tag nesting)!" << endl;
    }

    // Test Case 4: Standalone CDATA outside root tag
    {
        string code = "<![CDATA[abc]]>";
        assert(solver.isValid(code) == false);
        cout << "Test 4 Passed (Standalone CDATA outside root tag)!" << endl;
    }

    // Test Case 5: Multiple root tags
    {
        string code = "<A></A><B></B>";
        assert(solver.isValid(code) == false);
        cout << "Test 5 Passed (Multiple root tags rejected)!" << endl;
    }

    // Test Case 6: Tag name exceeding 9 characters
    {
        string code = "<AAAAAAAAAA>abc</AAAAAAAAAA>";
        assert(solver.isValid(code) == false);
        cout << "Test 6 Passed (Tag name length > 9 rejected)!" << endl;
    }

    // Test Case 7: CDATA containing closing tag syntax
    {
        string code = "<A><![CDATA[</A>]]>abc</A>";
        assert(solver.isValid(code) == true);
        cout << "Test 7 Passed (CDATA containing closing tag is literal)!" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
