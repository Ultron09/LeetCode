/**
 * Problem: 483. Smallest Good Base
 * Difficulty: Hard
 * Topics: Math, Binary Search
 * LeetCode Link: https://leetcode.com/problems/smallest-good-base/
 * 
 * Time Complexity:  O((log2 N)^2) - Testing at most 60 polynomial degrees with logarithmic Horner evaluations
 * Space Complexity: O(1) - Constant auxiliary memory
 */

#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
#include <initializer_list>

using namespace std;

class Solution {
public:
    string smallestGoodBase(string n_str) {
        unsigned long long n = stoull(n_str);
        int maxM = log2(n) + 1;

        // Iterate m (number of 1s in base k representation) descending from maxM down to 3
        // Larger m corresponds to smaller base k
        for (int m = maxM; m >= 3; --m) {
            unsigned long long k = pow(n, 1.0 / (m - 1));

            for (unsigned long long candK : {k - 1, k, k + 1}) {
                if (candK < 2) continue;

                // Evaluate sum = 1 + candK + candK^2 + ... + candK^(m-1) via Horner's method
                unsigned long long sum = 0;
                bool overflow = false;

                for (int i = 0; i < m; ++i) {
                    if (sum > (n - 1) / candK) {
                        overflow = true;
                        break;
                    }
                    sum = sum * candK + 1;
                }

                if (!overflow && sum == n) {
                    return to_string(candK);
                }
            }
        }

        // Base case for m = 2: n = 1 + (n - 1) * 1 in base (n - 1) -> "11"
        return to_string(n - 1);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1
    {
        string n = "13";
        string expected = "3";
        string result = solver.smallestGoodBase(n);
        cout << "Test 1 - n=" << n << " -> Expected: " << expected << ", Got: " << result << endl;
        assert(result == expected);
    }

    // Test Case 2: Standard Example 2
    {
        string n = "4681";
        string expected = "8";
        string result = solver.smallestGoodBase(n);
        cout << "Test 2 - n=" << n << " -> Expected: " << expected << ", Got: " << result << endl;
        assert(result == expected);
    }

    // Test Case 3: Large 10^18 Example
    {
        string n = "1000000000000000000";
        string expected = "999999999999999999";
        string result = solver.smallestGoodBase(n);
        cout << "Test 3 - n=" << n << " -> Expected: " << expected << ", Got: " << result << endl;
        assert(result == expected);
    }

    // Test Case 4: Minimal input n = 3
    {
        string n = "3";
        string expected = "2";
        string result = solver.smallestGoodBase(n);
        cout << "Test 4 - n=" << n << " -> Expected: " << expected << ", Got: " << result << endl;
        assert(result == expected);
    }

    // Test Case 5: Mersenne number 2^51 - 1
    {
        string n = "2251799813685247";
        string expected = "2";
        string result = solver.smallestGoodBase(n);
        cout << "Test 5 - n=" << n << " -> Expected: " << expected << ", Got: " << result << endl;
        assert(result == expected);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
