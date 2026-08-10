/**
 * Problem: 60. Permutation Sequence
 * Difficulty: Hard
 * Topics: Math, Recursion, Combinatorics
 * LeetCode Link: https://leetcode.com/problems/permutation-sequence/
 * 
 * Time Complexity:  O(N^2) where N <= 9
 * Space Complexity: O(N) auxiliary space
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> numbers;
        int fact = 1;

        // 1. Initialize candidate digits and (n - 1)!
        for (int i = 1; i <= n; ++i) {
            numbers.push_back(i);
            if (i < n) {
                fact *= i;
            }
        }

        // Convert k to 0-based index
        --k;

        string result = "";

        // 2. Factorial number system indexing
        for (int i = n - 1; i >= 1; --i) {
            int idx = k / fact;
            result += to_string(numbers[idx]);
            numbers.erase(numbers.begin() + idx);

            k %= fact;
            fact /= i;
        }

        // Append the last remaining number
        result += to_string(numbers[0]);

        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: n = 3, k = 3 -> "213"
    {
        assert(solver.getPermutation(3, 3) == "213");
        cout << "Test 1 Passed: n = 3, k = 3 -> \"213\"" << endl;
    }

    // Test Case 2: n = 4, k = 9 -> "2314"
    {
        assert(solver.getPermutation(4, 9) == "2314");
        cout << "Test 2 Passed: n = 4, k = 9 -> \"2314\"" << endl;
    }

    // Test Case 3: n = 3, k = 1 -> "123"
    {
        assert(solver.getPermutation(3, 1) == "123");
        cout << "Test 3 Passed: n = 3, k = 1 -> \"123\"" << endl;
    }

    // Test Case 4: n = 1, k = 1 -> "1"
    {
        assert(solver.getPermutation(1, 1) == "1");
        cout << "Test 4 Passed: n = 1, k = 1 -> \"1\"" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
