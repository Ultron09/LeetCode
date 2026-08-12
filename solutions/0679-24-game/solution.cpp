/**
 * Problem: 679. 24 Game
 * Difficulty: Hard
 * Topics: Array, Math, Backtracking
 * LeetCode Link: https://leetcode.com/problems/24-game/
 * 
 * Time Complexity:  O(1) bounded (at most ~3888 operator/operand permutation states evaluated)
 * Space Complexity: O(1) bounded recursion depth of 4
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
private:
    static constexpr double EPS = 1e-6;
    static constexpr double TARGET = 24.0;

    bool solve(vector<double>& nums) {
        if (nums.size() == 1) {
            return fabs(nums[0] - TARGET) < EPS;
        }

        int n = nums.size();
        // Pick any two distinct operands nums[i] and nums[j]
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;

                double a = nums[i];
                double b = nums[j];

                // Form remaining list of numbers excluding i and j
                vector<double> nextNums;
                nextNums.reserve(n - 1);
                for (int k = 0; k < n; ++k) {
                    if (k != i && k != j) {
                        nextNums.push_back(nums[k]);
                    }
                }

                // Generate all valid arithmetic results between a and b
                // Note: a + b and a * b are commutative (handled implicitly by ordered pairs (i, j))
                vector<double> candidates = {a + b, a - b, a * b};
                if (fabs(b) > EPS) {
                    candidates.push_back(a / b);
                }

                for (double cand : candidates) {
                    nextNums.push_back(cand);
                    if (solve(nextNums)) {
                        return true;
                    }
                    nextNums.pop_back(); // Backtrack
                }
            }
        }

        return false;
    }

public:
    bool judgePoint24(vector<int>& cards) {
        vector<double> nums;
        nums.reserve(cards.size());
        for (int card : cards) {
            nums.push_back(static_cast<double>(card));
        }
        return solve(nums);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1 ([4, 1, 8, 7] -> (8-4)*(7-1) = 24)
    {
        vector<int> cards = {4, 1, 8, 7};
        bool result = solver.judgePoint24(cards);
        cout << "Test 1 - cards=[4, 1, 8, 7] -> Expected: true, Got: " << boolalpha << result << endl;
        assert(result == true);
    }

    // Test Case 2: Example 2 ([1, 2, 1, 2] -> false)
    {
        vector<int> cards = {1, 2, 1, 2};
        bool result = solver.judgePoint24(cards);
        cout << "Test 2 - cards=[1, 2, 1, 2] -> Expected: false, Got: " << boolalpha << result << endl;
        assert(result == false);
    }

    // Test Case 3: Division with real fraction ([3, 3, 8, 8] -> 8 / (3 - 8/3) = 24)
    {
        vector<int> cards = {3, 3, 8, 8};
        bool result = solver.judgePoint24(cards);
        cout << "Test 3 - cards=[3, 3, 8, 8] -> Expected: true, Got: " << boolalpha << result << endl;
        assert(result == true);
    }

    // Test Case 4: Fractional division ([1, 3, 4, 6] -> 6 / (1 - 3/4) = 24)
    {
        vector<int> cards = {1, 3, 4, 6};
        bool result = solver.judgePoint24(cards);
        cout << "Test 4 - cards=[1, 3, 4, 6] -> Expected: true, Got: " << boolalpha << result << endl;
        assert(result == true);
    }

    // Test Case 5: Impossible identical cards ([1, 1, 1, 1] -> false)
    {
        vector<int> cards = {1, 1, 1, 1};
        bool result = solver.judgePoint24(cards);
        cout << "Test 5 - cards=[1, 1, 1, 1] -> Expected: false, Got: " << boolalpha << result << endl;
        assert(result == false);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
