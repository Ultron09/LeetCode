/**
 * Problem: 630. Course Schedule III
 * Difficulty: Hard
 * Topics: Greedy, Heap (Priority Queue), Sorting
 * LeetCode Link: https://leetcode.com/problems/course-schedule-iii/
 * 
 * Time Complexity:  O(N log N) where N is the number of courses
 * Space Complexity: O(N) for the max-heap priority queue
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // Step 1: Sort courses in ascending order of their deadlines (lastDay)
        sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        // Max-heap to track durations of all currently scheduled courses
        priority_queue<int> maxHeap;
        int currentTime = 0;

        for (const auto& course : courses) {
            int duration = course[0];
            int lastDay = course[1];

            // Case 1: Course fits within the deadline
            if (currentTime + duration <= lastDay) {
                currentTime += duration;
                maxHeap.push(duration);
            }
            // Case 2: Greedy Regret / Replacement
            // If the current course is shorter than the longest course taken so far,
            // replace the longest course to reduce currentTime and gain scheduling slack.
            else if (!maxHeap.empty() && maxHeap.top() > duration) {
                currentTime += duration - maxHeap.top();
                maxHeap.pop();
                maxHeap.push(duration);
            }
        }

        return maxHeap.size();
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
        vector<vector<int>> courses = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
        int result = solver.scheduleCourse(courses);
        cout << "Test 1 -> Expected: 3, Got: " << result << endl;
        assert(result == 3);
    }

    // Test Case 2: Single course
    {
        vector<vector<int>> courses = {{1, 2}};
        int result = solver.scheduleCourse(courses);
        cout << "Test 2 -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    // Test Case 3: Impossible courses
    {
        vector<vector<int>> courses = {{3, 2}, {4, 3}};
        int result = solver.scheduleCourse(courses);
        cout << "Test 3 -> Expected: 0, Got: " << result << endl;
        assert(result == 0);
    }

    // Test Case 4: Replacement opportunity
    {
        vector<vector<int>> courses = {{100, 100}, {30, 110}, {40, 120}};
        int result = solver.scheduleCourse(courses);
        cout << "Test 4 -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
