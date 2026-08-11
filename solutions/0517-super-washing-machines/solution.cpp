/**
 * Problem: 517. Super Washing Machines
 * Difficulty: Hard
 * Topics: Array, Greedy, Math, Prefix Sum
 * LeetCode Link: https://leetcode.com/problems/super-washing-machines/
 * 
 * Time Complexity:  O(N) - Single pass through the array to compute sum and prefix flow bottlenecks
 * Space Complexity: O(1) - Constant auxiliary memory
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int n = machines.size();
        if (n == 0) return 0;

        int totalDresses = accumulate(machines.begin(), machines.end(), 0);
        if (totalDresses % n != 0) {
            return -1;
        }

        int target = totalDresses / n;
        int maxMoves = 0;
        int currBalance = 0;

        for (int count : machines) {
            int diff = count - target;
            currBalance += diff;

            // Two physical bottlenecks:
            // 1. Cut capacity: |currBalance| dresses must cross the boundary between machine i and i+1
            // 2. Machine output rate: a single machine with excess dresses can only emit 1 dress per turn
            maxMoves = max({maxMoves, abs(currBalance), diff});
        }

        return maxMoves;
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
        vector<int> machines = {1, 0, 5};
        int result = solver.findMinMoves(machines);
        cout << "Test 1 - {1, 0, 5} -> Expected: 3, Got: " << result << endl;
        assert(result == 3);
    }

    // Test Case 2: Standard Example 2
    {
        vector<int> machines = {0, 3, 0};
        int result = solver.findMinMoves(machines);
        cout << "Test 2 - {0, 3, 0} -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 3: Impossible distribution
    {
        vector<int> machines = {0, 2, 0};
        int result = solver.findMinMoves(machines);
        cout << "Test 3 - {0, 2, 0} -> Expected: -1, Got: " << result << endl;
        assert(result == -1);
    }

    // Test Case 4: Symmetric flow
    {
        vector<int> machines = {4, 0, 0, 4};
        int result = solver.findMinMoves(machines);
        cout << "Test 4 - {4, 0, 0, 4} -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
