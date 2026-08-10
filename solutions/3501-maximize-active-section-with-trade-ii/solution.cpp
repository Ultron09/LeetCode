/**
 * Problem: 3501. Maximize Active Section with Trade II
 * Difficulty: Hard
 * Topics: Binary Search, Data Structures, Sparse Table, String
 * LeetCode Link: https://leetcode.com/problems/maximize-active-section-with-trade-ii/
 * 
 * Time Complexity:  O(N log N + Q log N) where N = s.length() and Q = queries.size()
 * Space Complexity: O(N log N) for Sparse Table table and zero-group metadata
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class SparseTable {
private:
    int n;
    int k;
    vector<vector<int>> st;
    vector<int> logTable;

public:
    SparseTable(const vector<int>& nums) {
        n = nums.size();
        if (n == 0) return;

        logTable.resize(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            logTable[i] = logTable[i / 2] + 1;
        }

        k = logTable[n] + 1;
        st.assign(k, vector<int>(n, 0));
        st[0] = nums;

        for (int i = 1; i < k; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r || n == 0) return 0;
        int len = r - l + 1;
        int i = logTable[len];
        return max(st[i][l], st[i][r - (1 << i) + 1]);
    }
};

struct ZeroGroup {
    int start;
    int end;
    int length;
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int totalOnes = 0;
        for (char c : s) {
            if (c == '1') totalOnes++;
        }

        // 1. Group contiguous blocks of '0's
        vector<ZeroGroup> zeroGroups;
        int i = 0;
        while (i < n) {
            if (s[i] == '0') {
                int start = i;
                while (i < n && s[i] == '0') {
                    i++;
                }
                zeroGroups.push_back({start, i - 1, i - start});
            } else {
                i++;
            }
        }

        int m = zeroGroups.size();
        if (m <= 1) {
            // No trade possible if there is <= 1 zero block
            return vector<int>(queries.size(), totalOnes);
        }

        // 2. Precompute merge lengths between adjacent zero groups
        vector<int> mergeLengths(m - 1);
        for (int j = 0; j < m - 1; ++j) {
            mergeLengths[j] = zeroGroups[j].length + zeroGroups[j + 1].length;
        }

        SparseTable st(mergeLengths);

        // 3. Extract start and end boundaries for binary searching
        vector<int> groupStarts(m), groupEnds(m);
        for (int j = 0; j < m; ++j) {
            groupStarts[j] = zeroGroups[j].start;
            groupEnds[j] = zeroGroups[j].end;
        }

        // 4. Process each query [l, r]
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];

            // First zero group with end >= l
            int first = lower_bound(groupEnds.begin(), groupEnds.end(), l) - groupEnds.begin();
            // Last zero group with start <= r
            int last = upper_bound(groupStarts.begin(), groupStarts.end(), r) - groupStarts.begin() - 1;

            if (first >= last || first >= m || last < 0) {
                ans.push_back(totalOnes);
                continue;
            }

            int effFirst = zeroGroups[first].end - max(zeroGroups[first].start, l) + 1;
            int effLast = min(zeroGroups[last].end, r) - zeroGroups[last].start + 1;

            int maxGain = 0;
            if (last == first + 1) {
                maxGain = effFirst + effLast;
            } else {
                maxGain = max(
                    effFirst + zeroGroups[first + 1].length,
                    zeroGroups[last - 1].length + effLast
                );
                if (first + 1 <= last - 2) {
                    maxGain = max(maxGain, st.query(first + 1, last - 2));
                }
            }

            ans.push_back(totalOnes + maxGain);
        }

        return ans;
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
        string s = "01";
        vector<vector<int>> queries = {{0, 1}};
        vector<int> expected = {1};
        assert(solver.maxActiveSectionsAfterTrade(s, queries) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        string s = "0100";
        vector<vector<int>> queries = {{0, 3}, {0, 2}, {1, 3}, {2, 3}};
        vector<int> expected = {4, 3, 1, 1};
        assert(solver.maxActiveSectionsAfterTrade(s, queries) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Example 3
    {
        string s = "1000100";
        vector<vector<int>> queries = {{1, 5}, {0, 6}, {0, 4}};
        vector<int> expected = {6, 7, 2};
        assert(solver.maxActiveSectionsAfterTrade(s, queries) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    // Test Case 4: Example 4
    {
        string s = "01010";
        vector<vector<int>> queries = {{0, 3}, {1, 4}, {1, 3}};
        vector<int> expected = {4, 4, 2};
        assert(solver.maxActiveSectionsAfterTrade(s, queries) == expected);
        cout << "Test 4 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
