/**
 * Problem: 3161. Block Placement Queries
 * Difficulty: Hard
 * Topics: Array, Segment Tree, Binary Search, Ordered Set / BST
 * LeetCode Link: https://leetcode.com/problems/block-placement-queries/
 * 
 * Time Complexity:  O(Q log M) where Q = queries.size() <= 1.5 * 10^5, M = max(x) <= 5 * 10^4
 * Space Complexity: O(M) for Segment Tree and std::set
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

class SegmentTree {
private:
    int n;
    vector<int> tree;

public:
    SegmentTree(int size) : n(size), tree(4 * size, 0) {}

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l || l > r) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        return max(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }

    void update(int idx, int val) {
        update(1, 0, n, idx, val);
    }

    int query(int l, int r) {
        return query(1, 0, n, l, r);
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int max_x = 0;
        for (const auto& q : queries) {
            max_x = max(max_x, q[1]);
        }

        int M = max(max_x + 1, 50005);
        SegmentTree st(M);

        set<int> obstacles;
        obstacles.insert(0); // Virtual base obstacle at the origin

        vector<bool> results;

        for (const auto& q : queries) {
            int type = q[0];
            int x = q[1];

            if (type == 1) {
                // Place an obstacle at x
                auto it = obstacles.upper_bound(x);
                int next_obs = (it != obstacles.end()) ? *it : -1;
                int prev_obs = *prev(it);

                // Insert obstacle x
                obstacles.insert(x);

                // Update gap ending at x
                st.update(x, x - prev_obs);

                // If a next obstacle exists, its preceding gap shrinks
                if (next_obs != -1) {
                    st.update(next_obs, next_obs - x);
                }
            } else {
                // Check if a block of size sz can fit in [0, x]
                int sz = q[2];

                // Find largest obstacle <= x
                auto it = obstacles.upper_bound(x);
                int prev_obs = *prev(it);

                // Maximum gap in [0, x] is max of:
                // 1. Any full gap between obstacles in [0, prev_obs]
                // 2. The partial gap between prev_obs and x
                int max_gap = max(st.query(0, prev_obs), x - prev_obs);

                results.push_back(max_gap >= sz);
            }
        }

        return results;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1
    {
        vector<vector<int>> queries = {{1, 2}, {2, 3, 3}, {2, 3, 1}, {2, 2, 2}};
        vector<bool> expected = {false, true, true};
        assert(solver.getResults(queries) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        vector<vector<int>> queries = {{1, 7}, {2, 7, 6}, {1, 2}, {2, 7, 5}, {2, 7, 6}};
        vector<bool> expected = {true, true, false};
        assert(solver.getResults(queries) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
