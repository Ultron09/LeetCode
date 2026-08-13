/**
 * Problem: 815. Bus Routes
 * Difficulty: Hard
 * Topics: Array, Hash Table, Breadth-First Search
 * LeetCode Link: https://leetcode.com/problems/bus-routes/
 *
 * Approach: Breadth-First Search (BFS) on Buses
 *
 * Key Insight:
 *   Instead of running BFS on the individual bus stops (which could be up to 10^6 and highly connected),
 *   we should run BFS on the BUSES themselves.
 *   
 *   1. We first build a mapping from each `stop` to a list of `bus_id`s that visit it.
 *   2. We initialize our BFS queue with all `bus_id`s that visit the `source` stop.
 *   3. At each step, we pop a `bus_id`, iterate through all stops it visits, and if we hit the `target`,
 *      we return the current distance (number of buses taken).
 *   4. If a stop isn't the target, we look at all `next_bus`es available from that stop. If they 
 *      haven't been boarded yet, we mark them visited and push them to the queue.
 *   5. Optimization: Once we evaluate all buses departing from a specific stop, we can clear 
 *      that stop's entry in our mapping. This prevents redundant iterations if another bus visits 
 *      the same stop later, ensuring O(N) traversal time where N is the total number of stops 
 *      across all routes.
 *
 * Time Complexity:  O(Sum of lengths of all routes) - Each stop in each route is processed at most once.
 * Space Complexity: O(Sum of lengths of all routes) - For the stop_to_buses hash map.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

using namespace std;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        
        // Map from stop to list of bus routes (bus_id) that visit this stop
        unordered_map<int, vector<int>> stop_to_buses;
        for (int i = 0; i < routes.size(); ++i) {
            for (int stop : routes[i]) {
                stop_to_buses[stop].push_back(i);
            }
        }
        
        // BFS queue stores the bus IDs, not the stops
        queue<int> q;
        vector<bool> visited_buses(routes.size(), false);
        
        // Start by boarding all buses that stop at the source
        if (stop_to_buses.find(source) != stop_to_buses.end()) {
            for (int bus : stop_to_buses[source]) {
                q.push(bus);
                visited_buses[bus] = true;
            }
        }
        
        int num_buses = 1;
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; ++i) {
                int bus = q.front();
                q.pop();
                
                // For the current bus, visit all its stops
                for (int stop : routes[bus]) {
                    if (stop == target) {
                        return num_buses;
                    }
                    
                    // Board all available unvisited buses from this stop
                    for (int next_bus : stop_to_buses[stop]) {
                        if (!visited_buses[next_bus]) {
                            visited_buses[next_bus] = true;
                            q.push(next_bus);
                        }
                    }
                    // Clear the buses for this stop so we don't process it again (pruning)
                    stop_to_buses[stop].clear();
                }
            }
            num_buses++;
        }
        
        return -1;
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
        vector<vector<int>> routes = {{1, 2, 7}, {3, 6, 7}};
        int source = 1, target = 6;
        int res = solver.numBusesToDestination(routes, source, target);
        assert(res == 2);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> routes = {{7, 12}, {4, 5, 15}, {6}, {15, 19}, {9, 12, 13}};
        int source = 15, target = 12;
        int res = solver.numBusesToDestination(routes, source, target);
        assert(res == -1);
        cout << "Test 2 Passed! Result: " << res << endl;
    }

    // Test Case 3: Source is target
    {
        vector<vector<int>> routes = {{1, 2, 7}, {3, 6, 7}};
        int source = 7, target = 7;
        int res = solver.numBusesToDestination(routes, source, target);
        assert(res == 0);
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
