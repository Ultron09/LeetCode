/**
 * Problem: 839. Similar String Groups
 * Difficulty: Hard
 * Topics: Array, Hash Table, String, Depth-First Search, Breadth-First Search, Union Find
 * LeetCode Link: https://leetcode.com/problems/similar-string-groups/
 *
 * Approach: Union-Find (Disjoint Set)
 * We can model the strings as nodes in a graph. An edge exists between two nodes if 
 * the corresponding strings are "similar" (identical or differ in exactly 2 positions).
 * Because all strings in the input are guaranteed to be anagrams of each other, they 
 * can never differ in exactly 1 position. Thus, any pair differing by 0 or 2 positions 
 * is considered similar.
 * 
 * We check all pairs of strings (O(N^2) checks). For each similar pair, we union their
 * sets in a Disjoint Set Union (DSU) data structure. The number of connected components
 * remaining at the end is our answer.
 * 
 * Time Complexity:  O(N^2 * L) where N is the number of strings and L is the length of each string.
 *                   Given N, L <= 300, N^2 * L = 300^2 * 300 = 2.7 * 10^7 operations, which is well within 1 sec.
 * Space Complexity: O(N) for the DSU parent array.
 */

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cassert>

using namespace std;

class DSU {
private:
    vector<int> parent;
    int components;
public:
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        components = n;
    }
    
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // Path compression
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
            components--;
        }
    }
    
    int getComponents() {
        return components;
    }
};

class Solution {
    bool isSimilar(const string& a, const string& b) {
        int diff = 0;
        for (int i = 0; i < a.length(); ++i) {
            if (a[i] != b[i]) {
                diff++;
                if (diff > 2) return false;
            }
        }
        return true; // diff will be 0 or 2 because they are anagrams
    }
    
public:
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        DSU dsu(n);
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // If they are not already in the same component, check similarity
                if (dsu.find(i) != dsu.find(j) && isSimilar(strs[i], strs[j])) {
                    dsu.unite(i, j);
                }
            }
        }
        
        return dsu.getComponents();
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    {
        vector<string> strs = {"tars","rats","arts","star"};
        int res = solver.numSimilarGroups(strs);
        assert(res == 2);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        vector<string> strs = {"omv","ovm"};
        int res = solver.numSimilarGroups(strs);
        assert(res == 1);
        cout << "Test 2 Passed!" << endl;
    }
    
    // Test Case 3: Identical strings
    {
        vector<string> strs = {"abc", "abc"};
        int res = solver.numSimilarGroups(strs);
        assert(res == 1);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
