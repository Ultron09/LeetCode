/**
 * Problem: 458. Poor Pigs
 * Difficulty: Hard
 * Topics: Math, Dynamic Programming, Combinatorics, Information Theory
 * LeetCode Link: https://leetcode.com/problems/poor-pigs/
 * 
 * Time Complexity:  O(log_{states}(buckets)) - Simple loop or logarithm calculation
 * Space Complexity: O(1) - Constant auxiliary space
 */

#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        // Number of testing rounds available
        int rounds = minutesToTest / minutesToDie;
        // Each pig has (rounds + 1) possible distinct states:
        // Dies in round 1, 2, ..., rounds, or survives all rounds.
        int states = rounds + 1;

        int pigs = 0;
        long long maxBuckets = 1;

        // Find the minimum number of pigs such that states^pigs >= buckets
        while (maxBuckets < buckets) {
            maxBuckets *= states;
            pigs++;
        }

        return pigs;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: 4 buckets, 1 round (states = 2) -> 2 pigs
    {
        int buckets = 4, minutesToDie = 15, minutesToTest = 15;
        int result = solver.poorPigs(buckets, minutesToDie, minutesToTest);
        cout << "Test 1 - buckets=4, die=15, test=15 -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 2: 4 buckets, 2 rounds (states = 3) -> 2 pigs (3^2 = 9 >= 4)
    {
        int buckets = 4, minutesToDie = 15, minutesToTest = 30;
        int result = solver.poorPigs(buckets, minutesToDie, minutesToTest);
        cout << "Test 2 - buckets=4, die=15, test=30 -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 3: 1000 buckets, 4 rounds (states = 5) -> 5 pigs (5^5 = 3125 >= 1000)
    {
        int buckets = 1000, minutesToDie = 15, minutesToTest = 60;
        int result = solver.poorPigs(buckets, minutesToDie, minutesToTest);
        cout << "Test 3 - buckets=1000, die=15, test=60 -> Expected: 5, Got: " << result << endl;
        assert(result == 5);
    }

    // Test Case 4: 1 bucket (already known poisonous) -> 0 pigs
    {
        int buckets = 1, minutesToDie = 1, minutesToTest = 1;
        int result = solver.poorPigs(buckets, minutesToDie, minutesToTest);
        cout << "Test 4 - buckets=1, die=1, test=1 -> Expected: 0, Got: " << result << endl;
        assert(result == 0);
    }

    // Test Case 5: 125 buckets, 4 rounds (states = 5) -> 3 pigs (5^3 = 125)
    {
        int buckets = 125, minutesToDie = 1, minutesToTest = 4;
        int result = solver.poorPigs(buckets, minutesToDie, minutesToTest);
        cout << "Test 5 - buckets=125, die=1, test=4 -> Expected: 3, Got: " << result << endl;
        assert(result == 3);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
