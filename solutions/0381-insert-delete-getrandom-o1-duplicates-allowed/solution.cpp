/**
 * Problem: 381. Insert Delete GetRandom O(1) - Duplicates allowed
 * Difficulty: Hard
 * Topics: Array, Hash Table, Math, Design, Randomized
 * LeetCode Link: https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/
 * 
 * Time Complexity:  O(1) average for insert, remove, getRandom
 * Space Complexity: O(N) - Storage for elements and index sets
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <cassert>

using namespace std;

class RandomizedCollection {
private:
    vector<int> nums;                                   // Dense array for O(1) random access
    unordered_map<int, unordered_set<int>> valToIdx;    // val -> set of indices in nums[]

public:
    RandomizedCollection() {}
    
    bool insert(int val) {
        bool notPresent = (valToIdx.find(val) == valToIdx.end() || valToIdx[val].empty());
        nums.push_back(val);
        valToIdx[val].insert(static_cast<int>(nums.size()) - 1);
        return notPresent;
    }
    
    bool remove(int val) {
        if (valToIdx.find(val) == valToIdx.end() || valToIdx[val].empty()) {
            return false;
        }

        // Pick any index of val to remove
        int removeIdx = *valToIdx[val].begin();
        int lastIdx = static_cast<int>(nums.size()) - 1;
        int lastVal = nums[lastIdx];

        // Swap the element to remove with the last element
        nums[removeIdx] = lastVal;

        // Update index sets
        valToIdx[val].erase(removeIdx);
        valToIdx[lastVal].erase(lastIdx);

        if (removeIdx != lastIdx) {
            valToIdx[lastVal].insert(removeIdx);
        }

        nums.pop_back();
        return true;
    }
    
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    RandomizedCollection rc;

    // Test Case 1: Basic insert/remove/getRandom
    {
        assert(rc.insert(1) == true);   // [1], returns true (new)
        assert(rc.insert(1) == false);  // [1,1], returns false (duplicate)
        assert(rc.insert(2) == true);   // [1,1,2], returns true (new)

        int r = rc.getRandom();
        assert(r == 1 || r == 2);
        cout << "Test 1a Passed: insert and getRandom work" << endl;

        assert(rc.remove(1) == true);   // removes one 1: [1,2] or [2,1]
        r = rc.getRandom();
        assert(r == 1 || r == 2);
        cout << "Test 1b Passed: remove and getRandom work" << endl;
    }

    // Test Case 2: Remove non-existent
    {
        RandomizedCollection rc2;
        rc2.insert(10);
        assert(rc2.remove(20) == false);
        cout << "Test 2 Passed: remove non-existent returns false" << endl;
    }

    // Test Case 3: Insert and remove all
    {
        RandomizedCollection rc3;
        rc3.insert(5);
        rc3.insert(5);
        rc3.insert(5);
        assert(rc3.remove(5) == true);
        assert(rc3.remove(5) == true);
        assert(rc3.remove(5) == true);
        assert(rc3.remove(5) == false);
        cout << "Test 3 Passed: insert/remove all duplicates" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
