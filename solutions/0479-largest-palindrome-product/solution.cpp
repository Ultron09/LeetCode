/**
 * Problem: 479. Largest Palindrome Product
 * Difficulty: Hard
 * Topics: Math, Number Theory
 * LeetCode Link: https://leetcode.com/problems/largest-palindrome-product/
 * 
 * Time Complexity:  O(10^n) worst case, but practically near O(1) as the largest palindromic product lies very close to (10^n - 1)^2
 * Space Complexity: O(1) - Constant auxiliary memory
 */

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int largestPalindrome(int n) {
        // Base case: for n = 1, largest product is 9 = 9 * 1 or 3 * 3
        if (n == 1) return 9;

        long long upper = pow(10, n) - 1;
        long long lower = pow(10, n - 1);

        // Search candidate palindromes by decreasing n-digit upper halves
        for (long long h = upper; h >= lower; --h) {
            // Construct the 2n-digit palindrome P by mirroring h
            long long p = h;
            long long temp = h;
            while (temp > 0) {
                p = p * 10 + (temp % 10);
                temp /= 10;
            }

            // Check if P can be factored into two n-digit numbers x and y (x >= y)
            for (long long x = upper; x * x >= p; --x) {
                if (p % x == 0) {
                    long long y = p / x;
                    if (y >= lower && y <= upper) {
                        return p % 1337;
                    }
                }
            }
        }

        return 0;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test all constraint values n in [1, 8]
    assert(solver.largestPalindrome(1) == 9);
    cout << "n = 1 -> Expected: 9, Got: " << solver.largestPalindrome(1) << endl;

    assert(solver.largestPalindrome(2) == 987);
    cout << "n = 2 -> Expected: 987, Got: " << solver.largestPalindrome(2) << endl;

    assert(solver.largestPalindrome(3) == 123);
    cout << "n = 3 -> Expected: 123, Got: " << solver.largestPalindrome(3) << endl;

    assert(solver.largestPalindrome(4) == 597);
    cout << "n = 4 -> Expected: 597, Got: " << solver.largestPalindrome(4) << endl;

    assert(solver.largestPalindrome(5) == 677);
    cout << "n = 5 -> Expected: 677, Got: " << solver.largestPalindrome(5) << endl;

    assert(solver.largestPalindrome(6) == 1218);
    cout << "n = 6 -> Expected: 1218, Got: " << solver.largestPalindrome(6) << endl;

    assert(solver.largestPalindrome(7) == 877);
    cout << "n = 7 -> Expected: 877, Got: " << solver.largestPalindrome(7) << endl;

    assert(solver.largestPalindrome(8) == 475);
    cout << "n = 8 -> Expected: 475, Got: " << solver.largestPalindrome(8) << endl;

    cout << "\nAll test cases from n = 1 to n = 8 passed successfully!" << endl;
    return 0;
}
#endif
