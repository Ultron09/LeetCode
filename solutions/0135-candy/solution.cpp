/**
 * Problem: 135. Candy
 * Difficulty: Hard
 * Topics: Array, Greedy
 * LeetCode Link: https://leetcode.com/problems/candy/
 * 
 * Time Complexity:  O(N) two linear passes
 * Space Complexity: O(N) auxiliary space (or O(1) with slope-counting)
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = static_cast<int>(ratings.size());
        if (n <= 1) {
            return n;
        }

        // Each child gets at least 1 candy initially
        vector<int> candies(n, 1);

        // Forward Pass: Satisfy left-neighbor condition
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // Backward Pass: Satisfy right-neighbor condition while preserving left-neighbor condition
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }

        // Aggregate total minimum candies
        return accumulate(candies.begin(), candies.end(), 0);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: ratings = [1, 0, 2] -> 5
    {
        vector<int> ratings = {1, 0, 2};
        assert(solver.candy(ratings) == 5);
        cout << "Test 1 Passed: [1, 0, 2] -> 5" << endl;
    }

    // Test Case 2: ratings = [1, 2, 2] -> 4
    {
        vector<int> ratings = {1, 2, 2};
        assert(solver.candy(ratings) == 4);
        cout << "Test 2 Passed: [1, 2, 2] -> 4" << endl;
    }

    // Test Case 3: ratings = [1, 3, 2, 2, 1] -> 7
    {
        vector<int> ratings = {1, 3, 2, 2, 1};
        assert(solver.candy(ratings) == 7);
        cout << "Test 3 Passed: [1, 3, 2, 2, 1] -> 7" << endl;
    }

    // Test Case 4: Single element ratings = [1] -> 1
    {
        vector<int> ratings = {1};
        assert(solver.candy(ratings) == 1);
        cout << "Test 4 Passed: [1] -> 1" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
