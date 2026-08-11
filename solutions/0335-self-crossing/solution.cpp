/**
 * Problem: 335. Self Crossing
 * Difficulty: Hard
 * Topics: Array, Math, Geometry
 * LeetCode Link: https://leetcode.com/problems/self-crossing/
 * 
 * Time Complexity:  O(N) - Single pass through distance array evaluating 3 geometric crossing cases
 * Space Complexity: O(1) - Constant auxiliary space
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isSelfCrossing(vector<int>& distance) {
        int n = static_cast<int>(distance.size());
        if (n < 4) return false;

        for (int i = 3; i < n; ++i) {
            // Case 1: Line i crosses Line i - 3
            if (distance[i] >= distance[i - 2] && distance[i - 1] <= distance[i - 3]) {
                return true;
            }

            // Case 2: Line i meets/overlaps Line i - 4
            if (i >= 4) {
                if (distance[i - 1] == distance[i - 3] &&
                    distance[i] + distance[i - 4] >= distance[i - 2]) {
                    return true;
                }
            }

            // Case 3: Line i crosses Line i - 5 (expanding to contracting spiral transition)
            if (i >= 5) {
                if (distance[i - 2] >= distance[i - 4] &&
                    distance[i - 1] <= distance[i - 3] &&
                    distance[i - 1] + distance[i - 5] >= distance[i - 3] &&
                    distance[i] + distance[i - 4] >= distance[i - 2]) {
                    return true;
                }
            }
        }

        return false;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: [2, 1, 1, 2] -> true (Case 1: Line 3 crosses Line 0)
    {
        vector<int> distance = {2, 1, 1, 2};
        assert(solver.isSelfCrossing(distance) == true);
        cout << "Test 1 Passed: [2, 1, 1, 2] -> true" << endl;
    }

    // Test Case 2: [1, 2, 3, 4] -> false (Expanding spiral)
    {
        vector<int> distance = {1, 2, 3, 4};
        assert(solver.isSelfCrossing(distance) == false);
        cout << "Test 2 Passed: [1, 2, 3, 4] -> false" << endl;
    }

    // Test Case 3: [1, 1, 1, 2, 1] -> true (Case 1 at index 3)
    {
        vector<int> distance = {1, 1, 1, 2, 1};
        assert(solver.isSelfCrossing(distance) == true);
        cout << "Test 3 Passed: [1, 1, 1, 2, 1] -> true" << endl;
    }

    // Test Case 4: [1, 2, 3, 2, 2] -> true (Case 2: Line 4 overlaps Line 0)
    {
        vector<int> distance = {1, 2, 3, 2, 2};
        assert(solver.isSelfCrossing(distance) == true);
        cout << "Test 4 Passed: [1, 2, 3, 2, 2] -> true" << endl;
    }

    // Test Case 5: [3, 3, 4, 2, 2, 3] -> true (Case 3: Line 5 crosses Line 0)
    {
        vector<int> distance = {3, 3, 4, 2, 2, 3};
        assert(solver.isSelfCrossing(distance) == true);
        cout << "Test 5 Passed: [3, 3, 4, 2, 2, 3] -> true" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
