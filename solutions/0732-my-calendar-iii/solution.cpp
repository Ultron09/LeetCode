/**
 * Problem: 732. My Calendar III
 * Difficulty: Hard
 * Topics: Intervals, Ordered Map (Sweep Line / Difference Array)
 * LeetCode Link: https://leetcode.com/problems/my-calendar-iii/
 *
 * Approach: Sweep Line with Ordered Difference Map
 *
 * Key Insight:
 *   For each booking [start, end), treat it as two "events":
 *     +1 at start  (an interval opens)
 *     -1 at end    (an interval closes)
 *
 *   Store these deltas in an ordered map (std::map<int, int>).
 *   After each book(), sweep through the map in sorted key order,
 *   accumulating a running prefix sum. The maximum prefix sum at
 *   any point is the maximum k-booking.
 *
 *   This is the classic "sweep line" / "line sweep" technique for
 *   computing maximum overlap among intervals.
 *
 * Time Complexity:  O(N) per book() call — sweep through all endpoints
 *                   O(N²) total for N calls
 * Space Complexity: O(N) — map of event endpoints
 */

#include <iostream>
#include <map>
#include <cassert>

using namespace std;

class MyCalendarThree {
private:
    map<int, int> diff; // difference map: point → delta

public:
    MyCalendarThree() {}

    int book(int startTime, int endTime) {
        // Record the sweep line events
        diff[startTime]++;
        diff[endTime]--;

        // Sweep through all events to find the maximum overlap
        int maxBooking = 0;
        int active = 0;
        for (auto& [time, delta] : diff) {
            active += delta;
            maxBooking = max(maxBooking, active);
        }

        return maxBooking;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    // Test Case 1: Example from problem statement
    {
        MyCalendarThree cal;
        assert(cal.book(10, 20) == 1);
        cout << "book(10, 20) → 1 ✓" << endl;

        assert(cal.book(50, 60) == 1);
        cout << "book(50, 60) → 1 ✓" << endl;

        assert(cal.book(10, 40) == 2);
        cout << "book(10, 40) → 2 ✓" << endl;

        assert(cal.book(5, 15) == 3);
        cout << "book(5, 15) → 3 ✓" << endl;

        assert(cal.book(5, 10) == 3);
        cout << "book(5, 10) → 3 ✓" << endl;

        assert(cal.book(25, 55) == 3);
        cout << "book(25, 55) → 3 ✓" << endl;

        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Single booking
    {
        MyCalendarThree cal;
        assert(cal.book(0, 1000000000) == 1);
        cout << "\nTest 2 Passed! Single max-range booking → 1" << endl;
    }

    // Test Case 3: Fully overlapping bookings
    {
        MyCalendarThree cal;
        assert(cal.book(0, 10) == 1);
        assert(cal.book(0, 10) == 2);
        assert(cal.book(0, 10) == 3);
        assert(cal.book(0, 10) == 4);
        cout << "Test 3 Passed! 4 identical intervals → 4" << endl;
    }

    // Test Case 4: Non-overlapping bookings
    {
        MyCalendarThree cal;
        assert(cal.book(0, 5) == 1);
        assert(cal.book(5, 10) == 1);
        assert(cal.book(10, 15) == 1);
        cout << "Test 4 Passed! Non-overlapping → always 1" << endl;
    }

    // Test Case 5: Gradual stacking
    {
        MyCalendarThree cal;
        assert(cal.book(0, 100) == 1);
        assert(cal.book(10, 90) == 2);
        assert(cal.book(20, 80) == 3);
        assert(cal.book(30, 70) == 4);
        cout << "Test 5 Passed! Nested intervals → 4" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
