/**
 * Problem: 601. Human Traffic of Stadium
 * Difficulty: Hard
 * Topics: Database, SQL, Arrays & Hashing
 * LeetCode Link: https://leetcode.com/problems/human-traffic-of-stadium/
 * 
 * Time Complexity:  O(N) where N is the number of rows in the Stadium table
 * Space Complexity: O(N) to store filtered result rows
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

struct Stadium {
    int id;
    string visitDate;
    int people;

    bool operator==(const Stadium& other) const {
        return id == other.id && visitDate == other.visitDate && people == other.people;
    }
};

class Solution {
public:
    vector<Stadium> humanTraffic(const vector<Stadium>& stadium) {
        int n = stadium.size();
        if (n < 3) return {};

        // Step 1: Extract all qualifying records (people >= 100)
        vector<Stadium> qualifying;
        for (const auto& row : stadium) {
            if (row.people >= 100) {
                qualifying.push_back(row);
            }
        }

        int m = qualifying.size();
        if (m < 3) return {};

        // Step 2: Two-pointer Island detection (consecutive IDs)
        vector<Stadium> result;
        int i = 0;

        while (i < m) {
            int j = i;
            // Extend the contiguous streak of consecutive IDs
            while (j + 1 < m && qualifying[j + 1].id == qualifying[j].id + 1) {
                ++j;
            }

            int streakLength = j - i + 1;
            // If the streak has 3 or more consecutive IDs, include all rows in this island
            if (streakLength >= 3) {
                for (int k = i; k <= j; ++k) {
                    result.push_back(qualifying[k]);
                }
            }

            i = j + 1;
        }

        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example
    {
        vector<Stadium> stadium = {
            {1, "2017-01-01", 10},
            {2, "2017-01-02", 109},
            {3, "2017-01-03", 150},
            {4, "2017-01-04", 99},
            {5, "2017-01-05", 145},
            {6, "2017-01-06", 1455},
            {7, "2017-01-07", 199},
            {8, "2017-01-09", 188}
        };

        auto result = solver.humanTraffic(stadium);
        vector<Stadium> expected = {
            {5, "2017-01-05", 145},
            {6, "2017-01-06", 1455},
            {7, "2017-01-07", 199},
            {8, "2017-01-09", 188}
        };

        assert(result == expected);
        cout << "Test 1 Passed (Consecutive high-traffic island 5,6,7,8 extracted)!" << endl;
    }

    // Test Case 2: No valid streak of length >= 3
    {
        vector<Stadium> stadium = {
            {1, "2017-01-01", 120},
            {2, "2017-01-02", 130},
            {4, "2017-01-04", 150},
            {5, "2017-01-05", 160}
        };

        auto result = solver.humanTraffic(stadium);
        assert(result.empty());
        cout << "Test 2 Passed (No streak >= 3 returns empty)!" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
