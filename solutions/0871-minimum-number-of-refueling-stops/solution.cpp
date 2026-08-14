/**
 * Problem: 871. Minimum Number of Refueling Stops
 * Difficulty: Hard
 * Topics: Greedy, Heaps & Priority Queues
 * LeetCode Link: https://leetcode.com/problems/minimum-number-of-refueling-stops/
 * 
 * Time Complexity:  O(N log N) - Where N is the number of stations. Each station is pushed and popped from the max-heap at most once.
 * Space Complexity: O(N) - To store the fuel amounts in the max-heap.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int> max_heap;
        int n = stations.size();
        int stops = 0;
        int current_pos = 0;
        int current_fuel = startFuel;
        int idx = 0;
        
        while (current_pos + current_fuel < target) {
            // While there are stations within our current reach, add their fuel to the max-heap
            while (idx < n && stations[idx][0] <= current_pos + current_fuel) {
                max_heap.push(stations[idx][1]);
                idx++;
            }
            
            // If we have no reachable stations with fuel left to take, we can't reach the target
            if (max_heap.empty()) {
                return -1;
            }
            
            // Greedily refuel from the station with the maximum fuel available
            current_fuel += max_heap.top();
            max_heap.pop();
            stops++;
        }
        
        return stops;
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
        vector<vector<int>> stations;
        assert(solver.minRefuelStops(1, 1, stations) == 0);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> stations = {{10, 100}};
        assert(solver.minRefuelStops(100, 1, stations) == -1);
        cout << "Test 2 Passed!" << endl;
    }
    
    // Test Case 3
    {
        vector<vector<int>> stations = {{10, 60}, {20, 30}, {30, 30}, {60, 40}};
        assert(solver.minRefuelStops(100, 10, stations) == 2);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
