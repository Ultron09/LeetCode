/**
 * Problem: 1665. Minimum Initial Energy to Finish Tasks
 * Difficulty: Hard
 * Topics: Array, Greedy, Sorting
 * LeetCode Link: https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/
 * 
 * Time Complexity:  O(N log N) where N = tasks.size() <= 10^5
 * Space Complexity: O(1) auxiliary space (or O(log N) for std::sort stack)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // Exchange argument: sort by (minimum - actual) descending
        // Tasks that preserve more leftover buffer should be performed first.
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });

        int totalEnergyNeeded = 0;
        int currentEnergy = 0;

        for (const auto& task : tasks) {
            int actual = task[0];
            int minimum = task[1];

            // If current energy is insufficient to start the task, increase initial energy
            if (currentEnergy < minimum) {
                totalEnergyNeeded += (minimum - currentEnergy);
                currentEnergy = minimum;
            }

            // Consume energy spent by completing the task
            currentEnergy -= actual;
        }

        return totalEnergyNeeded;
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
        vector<vector<int>> tasks = {{1, 2}, {2, 4}, {4, 8}};
        int expected = 8;
        assert(solver.minimumEffort(tasks) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<vector<int>> tasks = {{1, 3}, {2, 4}, {10, 11}, {10, 12}, {8, 9}};
        int expected = 32;
        assert(solver.minimumEffort(tasks) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        vector<vector<int>> tasks = {{1, 7}, {2, 8}, {3, 9}, {4, 10}, {5, 11}, {6, 12}};
        int expected = 27;
        assert(solver.minimumEffort(tasks) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
