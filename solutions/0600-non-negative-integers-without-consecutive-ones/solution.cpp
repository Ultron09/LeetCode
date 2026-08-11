/**
 * Problem: 600. Non-negative Integers without Consecutive Ones
 * Difficulty: Hard
 * Topics: Dynamic Programming, Bit Manipulation, Digit DP
 * LeetCode Link: https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/
 * 
 * Time Complexity:  O(log N) - Iterates through 31 bit positions
 * Space Complexity: O(1) - Fixed 32-element precomputed Fibonacci array
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int findIntegers(int n) {
        // f[k]: Number of valid binary strings of length k without consecutive ones
        // f[0] = 1 (""), f[1] = 2 ("0", "1")
        // Recurrence: f[k] = f[k - 1] (starts with 0) + f[k - 2] (starts with 10)
        int f[32];
        f[0] = 1;
        f[1] = 2;
        for (int i = 2; i < 32; ++i) {
            f[i] = f[i - 1] + f[i - 2];
        }

        int ans = 0;
        int prevBit = 0;

        // Scan bits from most significant (bit 30 since 10^9 < 2^30) down to 0
        for (int k = 30; k >= 0; --k) {
            if ((n & (1 << k)) != 0) {
                // If the k-th bit of n is 1:
                // Branch 1: Set the k-th bit to 0. Any valid k-bit suffix is strictly < n.
                ans += f[k];

                // Branch 2: Set the k-th bit to 1 (to continue prefix match with n).
                // If the previous bit was also 1, this creates consecutive ones ("11").
                // All strictly smaller valid values have been counted, and no matching
                // prefix extension is valid. Break immediately.
                if (prevBit == 1) {
                    return ans;
                }
                prevBit = 1;
            } else {
                prevBit = 0;
            }
        }

        // If loop completes without breaking on "11", n itself contains no consecutive ones
        return ans + 1;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1
    {
        int n = 5;
        int result = solver.findIntegers(n);
        cout << "Test 1 - n=5 -> Expected: 5, Got: " << result << endl;
        assert(result == 5);
    }

    // Test Case 2: Example 2
    {
        int n = 1;
        int result = solver.findIntegers(n);
        cout << "Test 2 - n=1 -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 3: Example 3
    {
        int n = 2;
        int result = solver.findIntegers(n);
        cout << "Test 3 - n=2 -> Expected: 3, Got: " << result << endl;
        assert(result == 3);
    }

    // Test Case 4: Power of 2
    {
        int n = 4; // 0, 1, 2, 4 (3 has consecutive 1s)
        int result = solver.findIntegers(n);
        cout << "Test 4 - n=4 -> Expected: 4, Got: " << result << endl;
        assert(result == 4);
    }

    // Test Case 5: Large boundary
    {
        int n = 1000000000;
        int result = solver.findIntegers(n);
        cout << "Test 5 - n=10^9 -> Got: " << result << endl;
        assert(result == 2178309);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
