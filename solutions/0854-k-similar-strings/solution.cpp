/**
 * Problem: 854. K-Similar Strings
 * Difficulty: Hard
 * Topics: Graphs, Breadth-First Search, String
 * LeetCode Link: https://leetcode.com/problems/k-similar-strings/
 * 
 * Time Complexity:  O(N * 3^N) - Bounded by the number of string states. In practice, pruning makes it run efficiently.
 * Space Complexity: O(3^N) - Queue and visited set size.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <cassert>

using namespace std;

class Solution {
public:
    int kSimilarity(string s1, string s2) {
        if (s1 == s2) return 0;
        
        queue<pair<string, int>> q;
        unordered_set<string> visited;
        
        q.push({s1, 0});
        visited.insert(s1);
        
        while (!q.empty()) {
            auto [curr, swaps] = q.front();
            q.pop();
            
            if (curr == s2) {
                return swaps;
            }
            
            int i = 0;
            // Find the first index where characters don't match
            while (i < curr.size() && curr[i] == s2[i]) {
                i++;
            }
            
            // Try swapping the mismatched character with a valid character down the line
            for (int j = i + 1; j < curr.size(); j++) {
                // We only swap if curr[j] is the character we need at index i, 
                // AND curr[j] is currently not in its correct place (to avoid breaking correctly placed characters)
                if (curr[j] == s2[i] && curr[j] != s2[j]) {
                    string next_str = curr;
                    swap(next_str[i], next_str[j]);
                    
                    if (visited.find(next_str) == visited.end()) {
                        visited.insert(next_str);
                        q.push({next_str, swaps + 1});
                    }
                }
            }
        }
        
        return -1;
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
        string s1 = "ab";
        string s2 = "ba";
        assert(solver.kSimilarity(s1, s2) == 1);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        string s1 = "abc";
        string s2 = "bca";
        assert(solver.kSimilarity(s1, s2) == 2);
        cout << "Test 2 Passed!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
