/**
 * Problem: 850. Rectangle Area II
 * Difficulty: Hard
 * Topics: Array, Segment Tree, Line Sweep, Ordered Set
 * LeetCode Link: https://leetcode.com/problems/rectangle-area-ii/
 *
 * Approach: Line Sweep Algorithm
 * To compute the union of the area of multiple rectangles, we use a Line Sweep 
 * algorithm. We imagine a vertical line sweeping the plane from left to right.
 * 
 * Each rectangle generates two "events":
 * 1. An "enter" event at its left edge `x1`, which adds its y-interval `[y1, y2]` to our active set.
 * 2. A "leave" event at its right edge `x2`, which removes its y-interval from our active set.
 *
 * We sort all events by their x-coordinate. As we process each event, we first 
 * calculate the area covered between the previous event's x-coordinate and the 
 * current event's x-coordinate. This area is `(curr_x - prev_x) * active_y_length`.
 * 
 * To compute `active_y_length`, we take all currently active y-intervals, sort them, 
 * and merge overlapping intervals to find the true vertical coverage.
 * 
 * Time Complexity:  O(N^2 log N) - N is the number of rectangles (up to 200). 
 *                   There are 2N events. For each event, sorting the active intervals 
 *                   takes O(N log N). Overall O(N^2 log N). For N=200, this is extremely fast.
 * Space Complexity: O(N) to store events and active intervals.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
    const int MOD = 1e9 + 7;
    
    struct Event {
        int x;
        int type; // 1 for enter, -1 for leave
        int y1, y2;
        
        bool operator<(const Event& other) const {
            return x < other.x;
        }
    };

public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        vector<Event> events;
        for (const auto& rect : rectangles) {
            events.push_back({rect[0], 1, rect[1], rect[3]});
            events.push_back({rect[2], -1, rect[1], rect[3]});
        }
        
        sort(events.begin(), events.end());
        
        vector<pair<int, int>> active;
        long long total_area = 0;
        int prev_x = events[0].x;
        
        for (const auto& event : events) {
            int curr_x = event.x;
            long long width = curr_x - prev_x;
            
            // Calculate total active vertical length if we moved strictly forward in x
            long long active_y = 0;
            if (!active.empty() && width > 0) {
                // Sort active intervals by starting y to merge overlapping ones
                vector<pair<int, int>> sorted_active = active;
                sort(sorted_active.begin(), sorted_active.end());
                
                int curr_y1 = sorted_active[0].first;
                int curr_y2 = sorted_active[0].second;
                
                for (int i = 1; i < sorted_active.size(); ++i) {
                    if (sorted_active[i].first <= curr_y2) {
                        // Intervals overlap, extend the current interval
                        curr_y2 = max(curr_y2, sorted_active[i].second);
                    } else {
                        // No overlap, commit the previous interval and start a new one
                        active_y += (curr_y2 - curr_y1);
                        curr_y1 = sorted_active[i].first;
                        curr_y2 = sorted_active[i].second;
                    }
                }
                active_y += (curr_y2 - curr_y1);
            }
            
            // Accumulate the swept area
            total_area = (total_area + width * active_y) % MOD;
            
            // Update active intervals state
            if (event.type == 1) {
                active.push_back({event.y1, event.y2});
            } else {
                for (auto it = active.begin(); it != active.end(); ++it) {
                    if (it->first == event.y1 && it->second == event.y2) {
                        active.erase(it);
                        break;
                    }
                }
            }
            
            prev_x = curr_x;
        }
        
        return total_area;
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
        vector<vector<int>> rectangles = {{0,0,2,2},{1,0,2,3},{1,0,3,1}};
        int res = solver.rectangleArea(rectangles);
        assert(res == 6);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<vector<int>> rectangles = {{0,0,1000000000,1000000000}};
        int res = solver.rectangleArea(rectangles);
        assert(res == 49); // 10^18 % (10^9 + 7) = 49
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
