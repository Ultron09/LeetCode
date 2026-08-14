/**
 * Problem: 857. Minimum Cost to Hire K Workers
 * Difficulty: Hard
 * Topics: Greedy, Heaps & Priority Queues, Sorting
 * LeetCode Link: https://leetcode.com/problems/minimum-cost-to-hire-k-workers/
 * 
 * Time Complexity:  O(N log N) - Sorting the workers takes O(N log N). Pushing and popping from the heap takes O(N log K).
 * Space Complexity: O(N + K) - We store an array of workers of size N and a priority queue of size K.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<pair<double, int>> workers(n);
        
        for (int i = 0; i < n; ++i) {
            workers[i] = {(double)wage[i] / quality[i], quality[i]};
        }
        
        // Sort workers by their wage to quality ratio
        sort(workers.begin(), workers.end());
        
        priority_queue<int> max_heap;
        int sum_quality = 0;
        double min_cost = 1e18; // Initialize with a very large value
        
        for (int i = 0; i < n; ++i) {
            double ratio = workers[i].first;
            int q = workers[i].second;
            
            sum_quality += q;
            max_heap.push(q);
            
            // Keep only k workers with the smallest qualities
            if (max_heap.size() > k) {
                sum_quality -= max_heap.top();
                max_heap.pop();
            }
            
            if (max_heap.size() == k) {
                min_cost = min(min_cost, sum_quality * ratio);
            }
        }
        
        return min_cost;
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
        vector<int> quality = {10, 20, 5};
        vector<int> wage = {70, 50, 30};
        int k = 2;
        double expected = 105.00000;
        assert(abs(solver.mincostToHireWorkers(quality, wage, k) - expected) < 1e-5);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<int> quality = {3, 1, 10, 10, 1};
        vector<int> wage = {4, 8, 2, 2, 7};
        int k = 3;
        double expected = 30.66667;
        assert(abs(solver.mincostToHireWorkers(quality, wage, k) - expected) < 1e-5);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
