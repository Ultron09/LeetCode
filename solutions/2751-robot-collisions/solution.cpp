/**
 * Problem: 2751. Robot Collisions
 * Difficulty: Hard
 * Topics: Array, Stack, Sorting, Simulation
 * LeetCode Link: https://leetcode.com/problems/robot-collisions/
 * 
 * Time Complexity:  O(N log N) where N = positions.size() <= 10^5 (sorting indices)
 * Space Complexity: O(N) auxiliary space for sorted index list and collision stack
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = static_cast<int>(positions.size());

        // Create index array and sort by position
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return positions[a] < positions[b];
        });

        // Stack to store indices of surviving robots moving Right ('R')
        vector<int> st;

        for (int i : indices) {
            if (directions[i] == 'R') {
                // Moving Right: might collide with future Left-moving robots
                st.push_back(i);
            } else {
                // Moving Left: resolve collisions with previously encountered Right-moving robots
                while (!st.empty() && healths[i] > 0) {
                    int topIdx = st.back();

                    if (healths[topIdx] < healths[i]) {
                        // Current Left-moving robot survives, top Right-moving robot destroyed
                        healths[i] -= 1;
                        healths[topIdx] = 0;
                        st.pop_back();
                    } else if (healths[topIdx] > healths[i]) {
                        // Top Right-moving robot survives, current Left-moving robot destroyed
                        healths[topIdx] -= 1;
                        healths[i] = 0;
                        break;
                    } else {
                        // Both robots have equal health: both destroyed
                        healths[topIdx] = 0;
                        healths[i] = 0;
                        st.pop_back();
                        break;
                    }
                }
            }
        }

        // Collect healths of all survivors in their original input order
        vector<int> survivors;
        for (int i = 0; i < n; ++i) {
            if (healths[i] > 0) {
                survivors.push_back(healths[i]);
            }
        }

        return survivors;
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
        vector<int> positions = {5, 4, 3, 2, 1};
        vector<int> healths = {2, 17, 9, 15, 10};
        string directions = "RRRRR";
        vector<int> expected = {2, 17, 9, 15, 10};
        assert(solver.survivedRobotsHealths(positions, healths, directions) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<int> positions = {3, 5, 2, 6};
        vector<int> healths = {10, 10, 15, 12};
        string directions = "RLRL";
        vector<int> expected = {14};
        assert(solver.survivedRobotsHealths(positions, healths, directions) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        vector<int> positions = {1, 2, 5, 6};
        vector<int> healths = {10, 10, 11, 11};
        string directions = "RLRL";
        vector<int> expected = {};
        assert(solver.survivedRobotsHealths(positions, healths, directions) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
