/**
 * Problem: 315. Count of Smaller Numbers After Self
 * Difficulty: Hard
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set
 * LeetCode Link: https://leetcode.com/problems/count-of-smaller-numbers-after-self/
 * 
 * Time Complexity:  O(N log N) - Coordinate compression + Fenwick Tree (BIT) queries/updates
 * Space Complexity: O(N) - Storage for compressed ranks, BIT array, and output result
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class FenwickTree {
private:
    int size;
    vector<int> tree;

public:
    explicit FenwickTree(int n) : size(n), tree(n + 1, 0) {}

    void update(int idx, int delta) {
        for (; idx <= size; idx += idx & (-idx)) {
            tree[idx] += delta;
        }
    }

    int query(int idx) const {
        int sum = 0;
        for (; idx > 0; idx -= idx & (-idx)) {
            sum += tree[idx];
        }
        return sum;
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 0) return {};

        // Step 1: Coordinate Compression to map elements to [1, M]
        vector<int> sortedUnique = nums;
        sort(sortedUnique.begin(), sortedUnique.end());
        sortedUnique.erase(unique(sortedUnique.begin(), sortedUnique.end()), sortedUnique.end());
        int m = static_cast<int>(sortedUnique.size());

        auto getRank = [&](int val) -> int {
            return static_cast<int>(lower_bound(sortedUnique.begin(), sortedUnique.end(), val) - sortedUnique.begin()) + 1;
        };

        // Step 2: Traverse from right to left using Binary Indexed Tree (Fenwick Tree)
        FenwickTree bit(m);
        vector<int> result(n, 0);

        for (int i = n - 1; i >= 0; --i) {
            int rank = getRank(nums[i]);
            // Query prefix sum of all frequencies strictly smaller than current rank (i.e. rank - 1)
            result[i] = bit.query(rank - 1);
            // Insert current element's rank into the BIT
            bit.update(rank, 1);
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

    // Test Case 1: [5, 2, 6, 1] -> [2, 1, 1, 0]
    {
        vector<int> nums = {5, 2, 6, 1};
        vector<int> expected = {2, 1, 1, 0};
        assert(solver.countSmaller(nums) == expected);
        cout << "Test 1 Passed: [5, 2, 6, 1] -> [2, 1, 1, 0]" << endl;
    }

    // Test Case 2: [-1] -> [0]
    {
        vector<int> nums = {-1};
        vector<int> expected = {0};
        assert(solver.countSmaller(nums) == expected);
        cout << "Test 2 Passed: [-1] -> [0]" << endl;
    }

    // Test Case 3: [-1, -1] -> [0, 0]
    {
        vector<int> nums = {-1, -1};
        vector<int> expected = {0, 0};
        assert(solver.countSmaller(nums) == expected);
        cout << "Test 3 Passed: [-1, -1] -> [0, 0]" << endl;
    }

    // Test Case 4: [2, 0, 1] -> [2, 0, 0]
    {
        vector<int> nums = {2, 0, 1};
        vector<int> expected = {2, 0, 0};
        assert(solver.countSmaller(nums) == expected);
        cout << "Test 4 Passed: [2, 0, 1] -> [2, 0, 0]" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
