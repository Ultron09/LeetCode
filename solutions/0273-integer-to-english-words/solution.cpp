/**
 * Problem: 273. Integer to English Words
 * Difficulty: Hard
 * Topics: Math, String, Recursion
 * LeetCode Link: https://leetcode.com/problems/integer-to-english-words/
 * 
 * Time Complexity:  O(1) - The number of digits is bounded by 10 (up to 2^31 - 1, at most 4 chunks of 3 digits)
 * Space Complexity: O(1) auxiliary space (fixed vocabulary lookup tables)
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
private:
    const vector<string> belowTwenty = {
        "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
        "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };

    const vector<string> tens = {
        "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
    };

    const vector<string> thousands = {
        "", "Thousand", "Million", "Billion"
    };

    string helper(int n) {
        if (n == 0) {
            return "";
        } else if (n < 20) {
            return belowTwenty[n];
        } else if (n < 100) {
            string rest = helper(n % 10);
            return tens[n / 10] + (rest.empty() ? "" : " " + rest);
        } else {
            string rest = helper(n % 100);
            return belowTwenty[n / 100] + " Hundred" + (rest.empty() ? "" : " " + rest);
        }
    }

public:
    string numberToWords(int num) {
        if (num == 0) {
            return "Zero";
        }

        string result = "";
        int thousandIdx = 0;

        while (num > 0) {
            int chunk = num % 1000;
            if (chunk != 0) {
                string chunkStr = helper(chunk);
                if (!thousands[thousandIdx].empty()) {
                    chunkStr += " " + thousands[thousandIdx];
                }
                if (result.empty()) {
                    result = chunkStr;
                } else {
                    result = chunkStr + " " + result;
                }
            }
            num /= 1000;
            thousandIdx++;
        }

        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: 123 -> "One Hundred Twenty Three"
    {
        assert(solver.numberToWords(123) == "One Hundred Twenty Three");
        cout << "Test 1 Passed: 123 -> \"One Hundred Twenty Three\"" << endl;
    }

    // Test Case 2: 12345 -> "Twelve Thousand Three Hundred Forty Five"
    {
        assert(solver.numberToWords(12345) == "Twelve Thousand Three Hundred Forty Five");
        cout << "Test 2 Passed: 12345 -> \"Twelve Thousand Three Hundred Forty Five\"" << endl;
    }

    // Test Case 3: 1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
    {
        assert(solver.numberToWords(1234567) == "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven");
        cout << "Test 3 Passed: 1234567 -> \"One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven\"" << endl;
    }

    // Test Case 4: 0 -> "Zero"
    {
        assert(solver.numberToWords(0) == "Zero");
        cout << "Test 4 Passed: 0 -> \"Zero\"" << endl;
    }

    // Test Case 5: 1000000 -> "One Million"
    {
        assert(solver.numberToWords(1000000) == "One Million");
        cout << "Test 5 Passed: 1000000 -> \"One Million\"" << endl;
    }

    // Test Case 6: 2147483647 (INT_MAX)
    {
        string expected = "Two Billion One Hundred Forty Seven Million Four Hundred Eighty Three Thousand Six Hundred Forty Seven";
        assert(solver.numberToWords(2147483647) == expected);
        cout << "Test 6 Passed: INT_MAX converted correctly!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
