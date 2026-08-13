/**
 * Problem: 829. Consecutive Numbers Sum
 * Difficulty: Hard
 * Topics: Math
 * LeetCode Link: https://leetcode.com/problems/consecutive-numbers-sum/
 *
 * Approach:
 * We want to write `n` as a sum of `k` consecutive integers starting from `x` (x >= 1).
 * The sum of `k` consecutive integers starting from `x` is:
 * x + (x + 1) + (x + 2) + ... + (x + k - 1) = k * x + k * (k - 1) / 2
 *
 * Therefore, we must have:
 * k * x + k * (k - 1) / 2 = n
 * k * x = n - k * (k - 1) / 2
 *
 * For `x` to be a valid positive integer (x >= 1), two conditions must be met:
 * 1. n - k * (k - 1) / 2 > 0  (which means the numerator must be positive)
 * 2. (n - k * (k - 1) / 2) % k == 0 (which means x must be an integer)
 *
 * We can simply iterate over all possible values of `k` starting from 1.
 * The loop terminates when `k * (k - 1) / 2 >= n`, which happens around k = sqrt(2n).
 * 
 * Time Complexity: O(sqrt(n)), as the loop runs approximately sqrt(2n) times.
 * Space Complexity: O(1)
 */

#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int count = 0;
        // Using long long for k to prevent overflow when calculating k * (k - 1)
        for (long long k = 1; k * (k - 1) / 2 < n; ++k) {
            long long remainder = n - k * (k - 1) / 2;
            if (remainder % k == 0) {
                count++;
            }
        }
        return count;
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
        int n = 5;
        int res = solver.consecutiveNumbersSum(n);
        assert(res == 2); // 5 = 2 + 3
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        int n = 9;
        int res = solver.consecutiveNumbersSum(n);
        assert(res == 3); // 9 = 4 + 5 = 2 + 3 + 4
        cout << "Test 2 Passed! Result: " << res << endl;
    }

    // Test Case 3
    {
        int n = 15;
        int res = solver.consecutiveNumbersSum(n);
        assert(res == 4); // 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
