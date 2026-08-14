/**
 * Problem: 902. Numbers At Most N Given Digit Set
 * Difficulty: Hard
 * Topics: Math, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/numbers-at-most-n-given-digit-set/
 * 
 * Time Complexity:  O(log N) where log N is the number of digits in N.
 * Space Complexity: O(log N) to store the string representation of N.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string S = to_string(n);
        int K = S.length();
        int D = digits.size();
        
        int ans = 0;
        
        // Count numbers with length strictly less than K
        for (int i = 1; i < K; ++i) {
            ans += pow(D, i);
        }
        
        // Count numbers with length exactly K
        for (int i = 0; i < K; ++i) {
            bool hasSameNum = false;
            for (const string& d : digits) {
                if (d[0] < S[i]) {
                    ans += pow(D, K - 1 - i);
                } else if (d[0] == S[i]) {
                    hasSameNum = true;
                }
            }
            if (!hasSameNum) {
                // If there is no matching digit for S[i], 
                // we can't form a prefix that perfectly matches S up to here.
                return ans;
            }
        }
        
        // If we made it through the entire string perfectly matching every digit
        return ans + 1;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    vector<string> digits1 = {"1", "3", "5", "7"};
    assert(solver.atMostNGivenDigitSet(digits1, 100) == 20);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    vector<string> digits2 = {"1", "4", "9"};
    assert(solver.atMostNGivenDigitSet(digits2, 1000000000) == 29523);
    cout << "Test 2 Passed!" << endl;

    // Test Case 3
    vector<string> digits3 = {"7"};
    assert(solver.atMostNGivenDigitSet(digits3, 8) == 1);
    cout << "Test 3 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
