/**
 * Problem: 936. Stamping The Sequence
 * Difficulty: Hard
 * Topics: String, Greedy
 * LeetCode Link: https://leetcode.com/problems/stamping-the-sequence/
 * 
 * Time Complexity:  O(N * (N - M)) in the worst case, but heavily optimized by early exits.
 * Space Complexity: O(N) for the result array and visited tracking.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int m = stamp.length();
        int n = target.length();
        vector<int> res;
        bool changed = true;
        int total_stars = 0;
        vector<bool> visited(n - m + 1, false);

        while (changed) {
            changed = false;
            for (int i = 0; i <= n - m; i++) {
                if (!visited[i] && canReplace(target, stamp, i)) {
                    total_stars += doReplace(target, i, m);
                    changed = true;
                    visited[i] = true;
                    res.push_back(i);
                    if (total_stars == n) {
                        break;
                    }
                }
            }
        }
        
        if (total_stars != n) {
            return {};
        }
        
        reverse(res.begin(), res.end());
        return res;
    }

private:
    bool canReplace(const string& target, const string& stamp, int pos) {
        bool hasChar = false;
        for (int i = 0; i < stamp.length(); i++) {
            if (target[pos + i] == '?') continue;
            if (target[pos + i] != stamp[i]) return false;
            hasChar = true;
        }
        return hasChar;
    }

    int doReplace(string& target, int pos, int m) {
        int count = 0;
        for (int i = 0; i < m; i++) {
            if (target[pos + i] != '?') {
                target[pos + i] = '?';
                count++;
            }
        }
        return count;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    string stamp1 = "abc", target1 = "ababc";
    vector<int> exp1 = {0, 2}; // Note: other valid sequences like [1,0,2] are possible. Our greedy logic outputs [0, 2].
    assert(solver.movesToStamp(stamp1, target1) == exp1 || !solver.movesToStamp(stamp1, target1).empty());
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    string stamp2 = "abca", target2 = "aabcaca";
    vector<int> exp2 = {3, 0, 1}; // Note: could be different, just check it's not empty
    assert(!solver.movesToStamp(stamp2, target2).empty());
    cout << "Test 2 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
