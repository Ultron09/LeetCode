/**
 * Problem: 321. Create Maximum Number
 * Difficulty: Hard
 * Topics: Stack, Greedy, Monotonic Stack, Two Pointers
 * LeetCode Link: https://leetcode.com/problems/create-maximum-number/
 * 
 * Time Complexity:  O(k * (m + n + k^2)) where m, n <= 500, k <= m + n
 * Space Complexity: O(k) for monotonic stack and merged candidates
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    // Subproblem 1: Extract the largest subsequence of length `len` from `nums` using a monotonic stack
    vector<int> maxSubsequence(const vector<int>& nums, int len) {
        int drop = static_cast<int>(nums.size()) - len;
        vector<int> stack;
        stack.reserve(nums.size());

        for (int num : nums) {
            while (drop > 0 && !stack.empty() && stack.back() < num) {
                stack.pop_back();
                --drop;
            }
            stack.push_back(num);
        }
        stack.resize(len);
        return stack;
    }

    // Helper: Compare suffix of seq1 starting at i with suffix of seq2 starting at j
    bool isGreater(const vector<int>& seq1, int i, const vector<int>& seq2, int j) {
        int n1 = static_cast<int>(seq1.size());
        int n2 = static_cast<int>(seq2.size());
        while (i < n1 && j < n2 && seq1[i] == seq2[j]) {
            ++i;
            ++j;
        }
        return (j == n2) || (i < n1 && seq1[i] > seq2[j]);
    }

    // Subproblem 2: Merge two sequences into the lexicographically largest sequence
    vector<int> merge(const vector<int>& seq1, const vector<int>& seq2, int k) {
        vector<int> merged;
        merged.reserve(k);
        int i = 0, j = 0;
        int n1 = static_cast<int>(seq1.size());
        int n2 = static_cast<int>(seq2.size());

        while (i < n1 || j < n2) {
            if (isGreater(seq1, i, seq2, j)) {
                merged.push_back(seq1[i++]);
            } else {
                merged.push_back(seq2[j++]);
            }
        }
        return merged;
    }

public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = static_cast<int>(nums1.size());
        int n = static_cast<int>(nums2.size());
        vector<int> best;

        // Subproblem 3: Try all valid distributions of length (i from nums1, k - i from nums2)
        int minI = max(0, k - n);
        int maxI = min(k, m);

        for (int i = minI; i <= maxI; ++i) {
            vector<int> s1 = maxSubsequence(nums1, i);
            vector<int> s2 = maxSubsequence(nums2, k - i);
            vector<int> candidate = merge(s1, s2, k);
            if (candidate > best) {
                best = move(candidate);
            }
        }

        return best;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5 -> [9,8,6,5,3]
    {
        vector<int> nums1 = {3, 4, 6, 5};
        vector<int> nums2 = {9, 1, 2, 5, 8, 3};
        int k = 5;
        vector<int> expected = {9, 8, 6, 5, 3};
        assert(solver.maxNumber(nums1, nums2, k) == expected);
        cout << "Test 1 Passed: [3,4,6,5] & [9,1,2,5,8,3], k = 5 -> [9,8,6,5,3]" << endl;
    }

    // Test Case 2: nums1 = [6,7], nums2 = [6,0,4], k = 5 -> [6,7,6,0,4]
    {
        vector<int> nums1 = {6, 7};
        vector<int> nums2 = {6, 0, 4};
        int k = 5;
        vector<int> expected = {6, 7, 6, 0, 4};
        assert(solver.maxNumber(nums1, nums2, k) == expected);
        cout << "Test 2 Passed: [6,7] & [6,0,4], k = 5 -> [6,7,6,0,4]" << endl;
    }

    // Test Case 3: nums1 = [3,9], nums2 = [8,9], k = 3 -> [9,8,9]
    {
        vector<int> nums1 = {3, 9};
        vector<int> nums2 = {8, 9};
        int k = 3;
        vector<int> expected = {9, 8, 9};
        assert(solver.maxNumber(nums1, nums2, k) == expected);
        cout << "Test 3 Passed: [3,9] & [8,9], k = 3 -> [9,8,9]" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
