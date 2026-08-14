/**
 * Problem: 952. Largest Component Size by Common Factor
 * Difficulty: Hard
 * Topics: Array, Math, Union Find
 * LeetCode Link: https://leetcode.com/problems/largest-component-size-by-common-factor/
 * 
 * Time Complexity:  O(N * log(M) + M * log(log(M))) where N is nums.length and M is max(nums). 
 *                   Sieve takes O(M log log M). Factorization takes O(log M) per number.
 * Space Complexity: O(M) to store the DSU and SPF array.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    struct UnionFind {
        vector<int> parent;
        UnionFind(int n) {
            parent.resize(n);
            iota(parent.begin(), parent.end(), 0);
        }
        int find(int i) {
            if (parent[i] == i) return i;
            return parent[i] = find(parent[i]);
        }
        void unite(int i, int j) {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                parent[root_i] = root_j;
            }
        }
    };

public:
    int largestComponentSize(vector<int>& nums) {
        int max_val = *max_element(nums.begin(), nums.end());
        
        // Sieve of Eratosthenes to find Smallest Prime Factor (SPF)
        vector<int> spf(max_val + 1);
        iota(spf.begin(), spf.end(), 0);
        for (int i = 2; i * i <= max_val; ++i) {
            if (spf[i] == i) {
                for (int j = i * i; j <= max_val; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
        
        UnionFind uf(max_val + 1);
        
        // Union each number with its prime factors
        for (int x : nums) {
            int num = x;
            while (num > 1) {
                int p = spf[num];
                uf.unite(x, p);
                while (num % p == 0) {
                    num /= p;
                }
            }
        }
        
        // Count frequencies of the root for each number in nums
        unordered_map<int, int> root_counts;
        int max_size = 0;
        
        for (int x : nums) {
            int root = uf.find(x);
            root_counts[root]++;
            max_size = max(max_size, root_counts[root]);
        }
        
        return max_size;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    vector<int> nums1 = {4, 6, 15, 35};
    assert(solver.largestComponentSize(nums1) == 4);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    vector<int> nums2 = {20, 50, 9, 63};
    assert(solver.largestComponentSize(nums2) == 2);
    cout << "Test 2 Passed!" << endl;

    // Test Case 3
    vector<int> nums3 = {2, 3, 6, 7, 4, 12, 21, 39};
    assert(solver.largestComponentSize(nums3) == 8);
    cout << "Test 3 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
