/**
 * Problem: 899. Orderly Queue
 * Difficulty: Hard
 * Topics: Math, String, Sorting
 * LeetCode Link: https://leetcode.com/problems/orderly-queue/
 * 
 * Time Complexity:  O(N^2) for k == 1, O(N log N) for k > 1
 * Space Complexity: O(N) to store the rotated strings for k == 1, O(1) auxiliary space otherwise.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k > 1) {
            // If k > 1, we can swap any adjacent characters,
            // which means we can generate any permutation of the string.
            // The lexicographically smallest permutation is just the sorted string.
            sort(s.begin(), s.end());
            return s;
        } else {
            // If k == 1, we can only cyclically rotate the string.
            // We need to find the lexicographically smallest rotation.
            string ans = s;
            int n = s.length();
            for (int i = 1; i < n; ++i) {
                string rotated = s.substr(i) + s.substr(0, i);
                if (rotated < ans) {
                    ans = rotated;
                }
            }
            return ans;
        }
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    assert(solver.orderlyQueue("cba", 1) == "acb");
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    assert(solver.orderlyQueue("baaca", 3) == "aaabc");
    cout << "Test 2 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
