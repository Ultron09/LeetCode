/**
 * Problem: 301. Remove Invalid Parentheses
 * Difficulty: Hard
 * Topics: String, Backtracking, Breadth-First Search
 * LeetCode Link: https://leetcode.com/problems/remove-invalid-parentheses/
 * 
 * Time Complexity:  O(2^N) - In the worst case, each parenthesis is either kept or removed
 * Space Complexity: O(N) - recursion call stack and current string buffer
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    unordered_set<string> resultSet;

    void dfs(const string& s, int index, int leftCount, int rightCount,
             int remL, int remR, string& current) {
        if (index == static_cast<int>(s.length())) {
            if (remL == 0 && remR == 0) {
                resultSet.insert(current);
            }
            return;
        }

        char c = s[index];

        // Option 1: Remove current parenthesis (if available removal budget)
        if (c == '(' && remL > 0) {
            dfs(s, index + 1, leftCount, rightCount, remL - 1, remR, current);
        } else if (c == ')' && remR > 0) {
            dfs(s, index + 1, leftCount, rightCount, remL, remR - 1, current);
        }

        // Option 2: Keep current character
        current.push_back(c);
        if (c != '(' && c != ')') {
            // Non-parenthesis letter: keep directly
            dfs(s, index + 1, leftCount, rightCount, remL, remR, current);
        } else if (c == '(') {
            dfs(s, index + 1, leftCount + 1, rightCount, remL, remR, current);
        } else if (rightCount < leftCount) {
            // Only keep ')' if it doesn't violate prefix balance
            dfs(s, index + 1, leftCount, rightCount + 1, remL, remR, current);
        }
        current.pop_back(); // Backtrack
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        resultSet.clear();

        // Step 1: Count minimum misplaced '(' and ')' to be removed
        int remL = 0, remR = 0;
        for (char c : s) {
            if (c == '(') {
                remL++;
            } else if (c == ')') {
                if (remL > 0) {
                    remL--;
                } else {
                    remR++;
                }
            }
        }

        // Step 2: Pruned Backtracking DFS
        string current = "";
        dfs(s, 0, 0, 0, remL, remR, current);

        return vector<string>(resultSet.begin(), resultSet.end());
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: "()())()" -> ["(())()","()()()"]
    {
        auto res = solver.removeInvalidParentheses("()())()");
        sort(res.begin(), res.end());
        vector<string> expected = {"(())()", "()()()"};
        sort(expected.begin(), expected.end());
        assert(res == expected);
        cout << "Test 1 Passed: \"()())()\"" << endl;
    }

    // Test Case 2: "(a)())()" -> ["(a())()","(a)()()"]
    {
        auto res = solver.removeInvalidParentheses("(a)())()");
        sort(res.begin(), res.end());
        vector<string> expected = {"(a())()", "(a)()()"};
        sort(expected.begin(), expected.end());
        assert(res == expected);
        cout << "Test 2 Passed: \"(a)())()\"" << endl;
    }

    // Test Case 3: ")(" -> [""]
    {
        auto res = solver.removeInvalidParentheses(")(");
        vector<string> expected = {""};
        assert(res == expected);
        cout << "Test 3 Passed: \")(\" -> [\"\"]" << endl;
    }

    // Test Case 4: Letters only: "abc"
    {
        auto res = solver.removeInvalidParentheses("abc");
        vector<string> expected = {"abc"};
        assert(res == expected);
        cout << "Test 4 Passed: \"abc\"" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
