/**
 * Problem: 233. Number of Digit One
 * Difficulty: Hard
 * Topics: Math, Dynamic Programming, Recursion, Digit DP
 * LeetCode Link: https://leetcode.com/problems/number-of-digit-one/
 * 
 * Time Complexity:  O(log10(N)) - iterate over the number of decimal digits (at most 10 iterations for N <= 10^9)
 * Space Complexity: O(1) auxiliary space
 */

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int countDigitOne(int n) {
        if (n <= 0) {
            return 0;
        }

        long long count = 0;
        // m represents the place value: 1, 10, 100, 1000, ...
        for (long long m = 1; m <= n; m *= 10) {
            long long higher = n / (m * 10);
            long long curr = (n / m) % 10;
            long long lower = n % m;

            if (curr == 0) {
                count += higher * m;
            } else if (curr == 1) {
                count += higher * m + (lower + 1);
            } else {
                count += (higher + 1) * m;
            }
        }

        return static_cast<int>(count);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: n = 13 -> 6 (1, 10, 11, 12, 13 contains 6 ones)
    {
        assert(solver.countDigitOne(13) == 6);
        cout << "Test 1 Passed: n = 13 -> 6" << endl;
    }

    // Test Case 2: n = 0 -> 0
    {
        assert(solver.countDigitOne(0) == 0);
        cout << "Test 2 Passed: n = 0 -> 0" << endl;
    }

    // Test Case 3: n = 100 -> 21
    {
        assert(solver.countDigitOne(100) == 21);
        cout << "Test 3 Passed: n = 100 -> 21" << endl;
    }

    // Test Case 4: Large n = 824883294 -> 767944060
    {
        assert(solver.countDigitOne(824883294) == 767944060);
        cout << "Test 4 Passed: n = 824883294 -> 767944060" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
