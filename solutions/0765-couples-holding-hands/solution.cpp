/**
 * Problem: 765. Couples Holding Hands
 * Difficulty: Hard
 * Topics: Greedy, Union Find, Graph
 * LeetCode Link: https://leetcode.com/problems/couples-holding-hands/
 *
 * Approach: Union Find (Disjoint Set)
 *
 * Key Insight:
 *   We have N couches (where N = row.length / 2). Each couch has 2 seats.
 *   Ideally, each couch should hold exactly one couple.
 *   If we treat each couch as a node in a graph, and draw an edge between two couches 
 *   if they contain partners from the same couple, the graph will decompose into a 
 *   set of disjoint cycles.
 *   
 *   If a cycle has length L (meaning L couches are entangled), it takes exactly L - 1 
 *   swaps to put all couples in that cycle onto their own couches.
 *   Therefore, the total minimum swaps needed is the sum of (L_i - 1) over all cycles.
 *   Mathematically, this simplifies to: Total Swaps = N - (Number of Connected Components).
 *
 *   We can use a Union Find data structure where nodes are the N couples/couches.
 *   For each adjacent pair of seats (2*i, 2*i+1), we union the couple ID of the person 
 *   in seat 2*i with the couple ID of the person in seat 2*i+1.
 *   
 *   Couple ID of person `x` is simply `x / 2`.
 *
 * Time Complexity:  O(N) - We iterate through the array once. Union-Find operations take practically O(1) with path compression.
 * Space Complexity: O(N) - For the parent array in Union Find.
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    int count;

public:
    UnionFind(int n) : count(n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    
    void unite(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        if (rootI != rootJ) {
            parent[rootI] = rootJ;
            count--;
        }
    }
    
    int getCount() const {
        return count;
    }
};

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size() / 2;
        UnionFind uf(n);
        
        for (int i = 0; i < n; ++i) {
            int couple1 = row[2 * i] / 2;
            int couple2 = row[2 * i + 1] / 2;
            uf.unite(couple1, couple2);
        }
        
        // Swaps = Total Couples - Connected Components
        return n - uf.getCount();
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
        vector<int> row = {0, 2, 1, 3};
        int res = solver.minSwapsCouples(row);
        assert(res == 1);
        cout << "Test 1 Passed! Result: " << res << endl;
    }

    // Test Case 2
    {
        vector<int> row = {3, 2, 0, 1};
        int res = solver.minSwapsCouples(row);
        assert(res == 0);
        cout << "Test 2 Passed! Result: " << res << endl;
    }
    
    // Test Case 3: Larger cycle
    {
        vector<int> row = {5, 4, 2, 6, 3, 1, 0, 7}; // couples: (0,1), (2,3), (4,5), (6,7)
        // Seat pairs: (5,4)->couple(2,2) - same couple, no edges
        // (2,6)->couple(1,3)
        // (3,1)->couple(1,0)
        // (0,7)->couple(0,3)
        int res = solver.minSwapsCouples(row);
        assert(res == 2);
        cout << "Test 3 Passed! Result: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
