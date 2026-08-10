/**
 * Problem: 3753. Total Waviness of Numbers in Range II
 * Difficulty: Hard
 * Topics: Dynamic Programming, Digit DP, Math
 * LeetCode Link: https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/
 * 
 * Time Complexity:  O(D^3 * log10(num2)) where D = 10
 * Space Complexity: O(D^2 * log10(num2)) for memoization tables
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    struct DPResult {
        long long count;
        long long sum;
    };

    long long memo_cnt[20][11][11];
    long long memo_sum[20][11][11];

    DPResult dfs(int pos, int prev, int curr, bool isLimit, bool isLeading, const string& s) {
        if (pos == static_cast<int>(s.size())) {
            return {1, 0}; // 1 valid number formed, 0 suffix waviness
        }

        int prevIdx = prev + 1; // Map -1..9 to 0..10
        int currIdx = curr + 1;

        if (!isLimit && !isLeading && memo_cnt[pos][prevIdx][currIdx] != -1) {
            return {memo_cnt[pos][prevIdx][currIdx], memo_sum[pos][prevIdx][currIdx]};
        }

        int up = isLimit ? (s[pos] - '0') : 9;
        long long totalCount = 0;
        long long totalSum = 0;

        for (int digit = 0; digit <= up; ++digit) {
            bool nextLimit = isLimit && (digit == up);
            bool nextLeading = isLeading && (digit == 0);

            int nextPrev = -1;
            int nextCurr = -1;

            if (nextLeading) {
                nextPrev = -1;
                nextCurr = -1;
            } else if (isLeading) { // First non-zero digit
                nextPrev = -1;
                nextCurr = digit;
            } else { // Already placed at least one non-zero digit
                nextPrev = curr;
                nextCurr = digit;
            }

            DPResult sub = dfs(pos + 1, nextPrev, nextCurr, nextLimit, nextLeading, s);

            totalCount += sub.count;
            totalSum += sub.sum;

            // Check if curr forms a peak or valley:
            // prev, curr, and digit must be valid non-leading digits
            if (prev >= 0 && curr >= 0 && !isLeading) {
                if ((prev < curr && curr > digit) || (prev > curr && curr < digit)) {
                    // When curr is a peak or valley, every number in this subtree gains +1 waviness
                    totalSum += sub.count;
                }
            }
        }

        if (!isLimit && !isLeading) {
            memo_cnt[pos][prevIdx][currIdx] = totalCount;
            memo_sum[pos][prevIdx][currIdx] = totalSum;
        }

        return {totalCount, totalSum};
    }

    long long solve(long long num) {
        if (num < 100) return 0;
        string s = to_string(num);
        memset(memo_cnt, -1, sizeof(memo_cnt));
        memset(memo_sum, -1, sizeof(memo_sum));
        return dfs(0, -1, -1, true, true, s).sum;
    }

public:
    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: [1, 100] -> 0
    {
        long long num1 = 1, num2 = 100;
        long long expected = 0;
        assert(solver.totalWaviness(num1, num2) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: [120, 122] -> 2 (120: 1<2>0 peak, 121: 1<2>1 peak, 122: no peak/valley)
    {
        long long num1 = 120, num2 = 122;
        long long expected = 2;
        assert(solver.totalWaviness(num1, num2) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: [100, 200] -> 53
    {
        long long num1 = 100, num2 = 200;
        long long expected = 53;
        assert(solver.totalWaviness(num1, num2) == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
