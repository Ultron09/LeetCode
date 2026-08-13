/**
 * Problem: 753. Cracking the Safe
 * Difficulty: Hard
 * Topics: Graphs, DFS, Eulerian Circuit, Math
 * LeetCode Link: https://leetcode.com/problems/cracking-the-safe/
 *
 * Approach: De Bruijn Sequence / Hierholzer's Algorithm
 *
 * Key Insight:
 *   The problem asks for the shortest string that contains all k^n possible n-length 
 *   strings formed by digits [0, k-1] as substrings. This is a classic De Bruijn sequence problem.
 *   We can model this as a directed graph where:
 *   - Nodes represent all possible strings of length n-1.
 *   - Edges represent transitions by appending a digit (0 to k-1). 
 *   - The edge itself represents the string of length n.
 *   Since every node has an in-degree of k and an out-degree of k, the graph is strongly 
 *   connected and balanced, meaning an Eulerian circuit is guaranteed to exist.
 *   We can find it using a post-order DFS (Hierholzer's Algorithm). To make it lexicographically 
 *   smallest (or just valid), we can visit edges in a consistent order (e.g., from k-1 down to 0).
 *
 * Time Complexity:  O(k^n) - We visit each of the k^n edges exactly once.
 * Space Complexity: O(k^n) - To store the visited edges and the call stack.
 */

#include <iostream>
#include <string>
#include <unordered_set>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
    unordered_set<string> visited;
    string ans;
    
    void dfs(string node, int k) {
        for (int i = 0; i < k; ++i) {
            string edge = node + to_string(i);
            if (visited.find(edge) == visited.end()) {
                visited.insert(edge);
                dfs(edge.substr(1), k);
                ans += to_string(i);
            }
        }
    }
    
public:
    string crackSafe(int n, int k) {
        if (n == 1 && k == 1) return "0";
        
        string startNode = string(n - 1, '0');
        dfs(startNode, k);
        ans += startNode;
        
        return ans;
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
        string res = solver.crackSafe(1, 2);
        // Valid answers could be "01" or "10". Length must be 2.
        assert(res.length() == 2);
        assert(res.find("0") != string::npos && res.find("1") != string::npos);
        cout << "Test 1 Passed! Output: " << res << endl;
    }

    // Test Case 2
    {
        string res = solver.crackSafe(2, 2);
        // Valid answer must contain "00", "01", "10", "11"
        assert(res.length() == 5); // k^n + (n-1) = 2^2 + 1 = 5
        assert(res.find("00") != string::npos);
        assert(res.find("01") != string::npos);
        assert(res.find("10") != string::npos);
        assert(res.find("11") != string::npos);
        cout << "Test 2 Passed! Output: " << res << endl;
    }
    
    // Test Case 3
    {
        string res = solver.crackSafe(3, 2);
        assert(res.length() == 10); // 2^3 + 2 = 10
        cout << "Test 3 Passed! Output: " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
