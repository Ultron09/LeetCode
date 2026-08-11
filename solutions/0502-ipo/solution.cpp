/**
 * Problem: 502. IPO
 * Difficulty: Hard
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 * LeetCode Link: https://leetcode.com/problems/ipo/
 * 
 * Time Complexity:  O(N log N + k log N) - Sorting projects by required capital and priority queue operations
 * Space Complexity: O(N) - Storage for sorted project pairs and max-heap
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();

        // Pair up projects as (required_capital, profit)
        vector<pair<int, int>> projects(n);
        for (int i = 0; i < n; ++i) {
            projects[i] = {capital[i], profits[i]};
        }

        // Sort projects by capital requirement in ascending order
        sort(projects.begin(), projects.end());

        // Max-heap to dynamically store profits of all currently affordable projects
        priority_queue<int> maxProfitHeap;
        int projectIdx = 0;

        for (int step = 0; step < k; ++step) {
            // Unlock all projects whose capital requirement is <= current total capital w
            while (projectIdx < n && projects[projectIdx].first <= w) {
                maxProfitHeap.push(projects[projectIdx].second);
                projectIdx++;
            }

            // If no projects are affordable, cannot increase capital further
            if (maxProfitHeap.empty()) {
                break;
            }

            // Greedily choose the project yielding the highest profit
            w += maxProfitHeap.top();
            maxProfitHeap.pop();
        }

        return w;
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
        int k = 2, w = 0;
        vector<int> profits = {1, 2, 3};
        vector<int> capital = {0, 1, 1};
        int result = solver.findMaximizedCapital(k, w, profits, capital);
        cout << "Test 1 - k=2, w=0 -> Expected: 4, Got: " << result << endl;
        assert(result == 4);
    }

    // Test Case 2: Standard Example 2
    {
        int k = 3, w = 0;
        vector<int> profits = {1, 2, 3};
        vector<int> capital = {0, 1, 2};
        int result = solver.findMaximizedCapital(k, w, profits, capital);
        cout << "Test 2 - k=3, w=0 -> Expected: 6, Got: " << result << endl;
        assert(result == 6);
    }

    // Test Case 3: More k than available projects
    {
        int k = 10, w = 0;
        vector<int> profits = {1, 2, 3};
        vector<int> capital = {0, 1, 2};
        int result = solver.findMaximizedCapital(k, w, profits, capital);
        cout << "Test 3 - k=10, w=0 -> Expected: 6, Got: " << result << endl;
        assert(result == 6);
    }

    // Test Case 4: Initial capital enables immediate choice
    {
        int k = 1, w = 2;
        vector<int> profits = {1, 2, 3};
        vector<int> capital = {1, 1, 2};
        int result = solver.findMaximizedCapital(k, w, profits, capital);
        cout << "Test 4 - k=1, w=2 -> Expected: 5, Got: " << result << endl;
        assert(result == 5);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
