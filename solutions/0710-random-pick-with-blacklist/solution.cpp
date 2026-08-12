/**
 * Problem: 710. Random Pick with Blacklist
 * Difficulty: Hard
 * Topics: Arrays & Hashing, Math & Geometry
 * LeetCode Link: https://leetcode.com/problems/random-pick-with-blacklist/
 *
 * Approach: Virtual Whitelist Remapping
 *   Let M = N - |blacklist| (number of valid integers).
 *   We generate a uniform random in [0, M) and need to map it to a valid number.
 *
 *   Partition [0, N) into two zones:
 *     - [0, M): the "virtual whitelist" zone. Any non-blacklisted index here
 *              maps to itself. Any blacklisted index here gets remapped.
 *     - [M, N): the "donor" zone. Valid numbers here are assigned as remap
 *              targets for blacklisted numbers in [0, M).
 *
 *   Construction:
 *     - Put blacklisted numbers >= M into a set (they're "consumed" by the split).
 *     - For each blacklisted number b < M, assign it a valid number from [M, N)
 *       not in the blacklist, stored in a hash map.
 *
 *   pick(): rand() % M → if in map, return map[x], else return x.
 *           Exactly ONE call to rand() per pick.
 *
 * Time Complexity:  O(B) constructor, O(1) pick
 * Space Complexity: O(B) for the remap table
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <cassert>

using namespace std;

class Solution {
    int m;  // number of valid integers = n - blacklist.size()
    unordered_map<int, int> remap;  // blacklisted index in [0,M) → valid index in [M,N)
    mt19937 rng;

public:
    Solution(int n, vector<int>& blacklist) {
        m = n - (int)blacklist.size();
        rng.seed(random_device{}());

        // Identify which blacklisted numbers are in the donor zone [M, N)
        unordered_set<int> blackInDonor;
        for (int b : blacklist) {
            if (b >= m) {
                blackInDonor.insert(b);
            }
        }

        // Assign donor targets: sweep through [M, N) for valid numbers
        int donor = m;
        for (int b : blacklist) {
            if (b < m) {
                // Find next valid number in [M, N)
                while (blackInDonor.count(donor)) {
                    donor++;
                }
                remap[b] = donor;
                donor++;
            }
        }
    }

    int pick() {
        int x = rng() % m;
        auto it = remap.find(x);
        return (it != remap.end()) ? it->second : x;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    // Test Case 1: n=7, blacklist=[2,3,5] → valid = {0,1,4,6}
    {
        vector<int> bl = {2, 3, 5};
        Solution sol(7, bl);
        unordered_set<int> valid = {0, 1, 4, 6};

        for (int i = 0; i < 100; i++) {
            int pick = sol.pick();
            assert(valid.count(pick) > 0);
        }
        cout << "Test 1 Passed! (all picks in valid set)" << endl;
    }

    // Test Case 2: n=1, blacklist=[] → valid = {0}
    {
        vector<int> bl = {};
        Solution sol(1, bl);
        for (int i = 0; i < 20; i++) {
            assert(sol.pick() == 0);
        }
        cout << "Test 2 Passed! (single valid element)" << endl;
    }

    // Test Case 3: n=3, blacklist=[0,1] → valid = {2}
    {
        vector<int> bl = {0, 1};
        Solution sol(3, bl);
        for (int i = 0; i < 20; i++) {
            assert(sol.pick() == 2);
        }
        cout << "Test 3 Passed! (only one valid element)" << endl;
    }

    // Test Case 4: n=5, blacklist=[] → valid = {0,1,2,3,4}
    {
        vector<int> bl = {};
        Solution sol(5, bl);
        unordered_set<int> valid = {0, 1, 2, 3, 4};
        for (int i = 0; i < 100; i++) {
            int pick = sol.pick();
            assert(valid.count(pick) > 0);
        }
        cout << "Test 4 Passed! (no blacklist)" << endl;
    }

    // Test Case 5: n=4, blacklist=[0,2] → valid = {1,3}
    {
        vector<int> bl = {0, 2};
        Solution sol(4, bl);
        unordered_set<int> valid = {1, 3};
        for (int i = 0; i < 100; i++) {
            int pick = sol.pick();
            assert(valid.count(pick) > 0);
        }
        cout << "Test 5 Passed! (alternating blacklist)" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
