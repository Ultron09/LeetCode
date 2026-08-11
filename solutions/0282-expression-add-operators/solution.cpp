/**
 * Problem: 282. Expression Add Operators
 * Difficulty: Hard
 * Topics: Math, String, Backtracking
 * LeetCode Link: https://leetcode.com/problems/expression-add-operators/
 * 
 * Time Complexity:  O(4^N) where N is length of num (up to 10)
 * Space Complexity: O(N) recursion stack and expression buffer
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    vector<string> result;
    string numStr;
    long long targetVal;
    int n;

    void dfs(int index, long long currentVal, long long prevOperand, string currentExpr) {
        if (index == n) {
            if (currentVal == targetVal) {
                result.push_back(currentExpr);
            }
            return;
        }

        long long currentNum = 0;
        string part = "";

        for (int len = 1; index + len <= n; ++len) {
            // Numbers with length > 1 cannot start with '0'
            if (len > 1 && numStr[index] == '0') {
                break;
            }

            char c = numStr[index + len - 1];
            currentNum = currentNum * 10 + (c - '0');
            part += c;

            if (index == 0) {
                // First operand has no preceding operator
                dfs(len, currentNum, currentNum, part);
            } else {
                // Addition: '+'
                dfs(index + len, currentVal + currentNum, currentNum, currentExpr + "+" + part);

                // Subtraction: '-'
                dfs(index + len, currentVal - currentNum, -currentNum, currentExpr + "-" + part);

                // Multiplication: '*'
                // Precedence rule: undo previous operand contribution, multiply, and re-add
                long long multipliedVal = (currentVal - prevOperand) + (prevOperand * currentNum);
                dfs(index + len, multipliedVal, prevOperand * currentNum, currentExpr + "*" + part);
            }
        }
    }

public:
    vector<string> addOperators(string num, int target) {
        result.clear();
        numStr = num;
        targetVal = target;
        n = static_cast<int>(num.length());

        if (n == 0) {
            return result;
        }

        dfs(0, 0, 0, "");
        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: "123", target = 6 -> ["1+2+3", "1*2*3"]
    {
        auto res = solver.addOperators("123", 6);
        sort(res.begin(), res.end());
        vector<string> expected = {"1*2*3", "1+2+3"};
        sort(expected.begin(), expected.end());
        assert(res == expected);
        cout << "Test 1 Passed: num = \"123\", target = 6" << endl;
    }

    // Test Case 2: "232", target = 8 -> ["2*3+2", "2+3*2"]
    {
        auto res = solver.addOperators("232", 8);
        sort(res.begin(), res.end());
        vector<string> expected = {"2*3+2", "2+3*2"};
        sort(expected.begin(), expected.end());
        assert(res == expected);
        cout << "Test 2 Passed: num = \"232\", target = 8" << endl;
    }

    // Test Case 3: "3456237490", target = 9191 -> []
    {
        auto res = solver.addOperators("3456237490", 9191);
        assert(res.empty());
        cout << "Test 3 Passed: num = \"3456237490\", target = 9191 -> []" << endl;
    }

    // Test Case 4: "105", target = 5 -> ["1*0+5", "10-5"]
    {
        auto res = solver.addOperators("105", 5);
        sort(res.begin(), res.end());
        vector<string> expected = {"1*0+5", "10-5"};
        sort(expected.begin(), expected.end());
        assert(res == expected);
        cout << "Test 4 Passed: num = \"105\", target = 5" << endl;
    }

    // Test Case 5: "00", target = 0 -> ["0*0", "0+0", "0-0"]
    {
        auto res = solver.addOperators("00", 0);
        sort(res.begin(), res.end());
        vector<string> expected = {"0*0", "0+0", "0-0"};
        sort(expected.begin(), expected.end());
        assert(res == expected);
        cout << "Test 5 Passed: num = \"00\", target = 0" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
