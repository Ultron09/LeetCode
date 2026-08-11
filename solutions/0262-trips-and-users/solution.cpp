/**
 * Problem: 262. Trips and Users
 * Difficulty: Hard
 * Topics: Database, SQL, Arrays & Hashing
 * LeetCode Link: https://leetcode.com/problems/trips-and-users/
 * 
 * Time Complexity:  O(T + U) where T is number of trips, U is number of users (single pass Hash Join)
 * Space Complexity: O(U + D) for user hash map and daily aggregations
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <iomanip>
#include <cmath>
#include <cassert>

using namespace std;

struct User {
    int usersId;
    string banned; // "Yes" or "No"
    string role;   // "client", "driver", "partner"
};

struct Trip {
    int id;
    int clientId;
    int driverId;
    int cityId;
    string status; // "completed", "cancelled_by_driver", "cancelled_by_client"
    string requestAt;
};

struct DailyCancellation {
    string day;
    double cancellationRate;
};

class Solution {
public:
    vector<DailyCancellation> findCancellationRate(const vector<Trip>& trips,
                                                  const vector<User>& users) {
        // Hash map for O(1) unbanned user lookup
        unordered_map<int, bool> isUnbanned;
        for (const auto& u : users) {
            isUnbanned[u.usersId] = (u.banned == "No");
        }

        // Ordered map to aggregate metrics by Day in sorted order
        map<string, pair<int, int>> dailyStats; // day -> {cancelledTrips, totalTrips}

        for (const auto& trip : trips) {
            // Filter dates: between "2013-10-01" and "2013-10-03"
            if (trip.requestAt < "2013-10-01" || trip.requestAt > "2013-10-03") {
                continue;
            }

            // Both client and driver must not be banned
            if (!isUnbanned[trip.clientId] || !isUnbanned[trip.driverId]) {
                continue;
            }

            dailyStats[trip.requestAt].second++;
            if (trip.status != "completed") {
                dailyStats[trip.requestAt].first++;
            }
        }

        vector<DailyCancellation> result;
        for (const auto& entry : dailyStats) {
            double rate = static_cast<double>(entry.second.first) / entry.second.second;
            // Round to 2 decimal places
            rate = round(rate * 100.0) / 100.0;
            result.push_back({entry.first, rate});
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

    vector<Trip> trips = {
        {1, 1, 10, 1, "completed", "2013-10-01"},
        {2, 2, 11, 1, "cancelled_by_driver", "2013-10-01"},
        {3, 3, 12, 6, "completed", "2013-10-01"},
        {4, 4, 13, 6, "cancelled_by_client", "2013-10-01"},
        {5, 1, 10, 1, "completed", "2013-10-02"},
        {6, 2, 11, 6, "completed", "2013-10-02"},
        {7, 3, 12, 6, "completed", "2013-10-02"},
        {8, 2, 12, 12, "completed", "2013-10-03"},
        {9, 3, 10, 12, "completed", "2013-10-03"},
        {10, 4, 13, 12, "cancelled_by_driver", "2013-10-03"}
    };

    vector<User> users = {
        {1, "No", "client"},
        {2, "Yes", "client"},
        {3, "No", "client"},
        {4, "No", "client"},
        {10, "No", "driver"},
        {11, "No", "driver"},
        {12, "No", "driver"},
        {13, "No", "driver"}
    };

    auto result = solver.findCancellationRate(trips, users);

    assert(result.size() == 3);
    assert(result[0].day == "2013-10-01" && fabs(result[0].cancellationRate - 0.33) < 1e-4);
    assert(result[1].day == "2013-10-02" && fabs(result[1].cancellationRate - 0.00) < 1e-4);
    assert(result[2].day == "2013-10-03" && fabs(result[2].cancellationRate - 0.50) < 1e-4);

    cout << "All 0262 test cases passed successfully!" << endl;
    return 0;
}
#endif
