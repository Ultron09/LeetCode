/**
 * Problem: 466. Count The Repetitions
 * Difficulty: Hard
 * Topics: String, Dynamic Programming, Two Pointers
 * LeetCode Link: https://leetcode.com/problems/count-the-repetitions/
 * 
 * Time Complexity:  O(|s1| * |s2|) - Cycle is guaranteed within |s2| + 1 blocks of s1
 * Space Complexity: O(|s2|) - Storing index states for cycle detection
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int len1 = s1.length();
        int len2 = s2.length();

        // Maps s2_index -> {s1_count, s2_count} observed at the end of an s1 block
        unordered_map<int, pair<int, int>> seen;

        int s2Idx = 0;
        int s2Count = 0;
        int s1Count = 0;

        while (s1Count < n1) {
            s1Count++;

            // Match current s1 block against s2
            for (int i = 0; i < len1; ++i) {
                if (s1[i] == s2[s2Idx]) {
                    s2Idx++;
                    if (s2Idx == len2) {
                        s2Count++;
                        s2Idx = 0;
                    }
                }
            }

            // Check if we have encountered this s2Idx state previously
            if (seen.count(s2Idx)) {
                auto [prevS1, prevS2] = seen[s2Idx];
                int cycleS1 = s1Count - prevS1;
                int cycleS2 = s2Count - prevS2;

                // Calculate how many full cycles we can fast-forward
                int remainingS1 = n1 - s1Count;
                int numCycles = remainingS1 / cycleS1;

                s1Count += numCycles * cycleS1;
                s2Count += numCycles * cycleS2;

                // Clear history to complete the remaining tail iterations linearly
                seen.clear();
            } else {
                seen[s2Idx] = {s1Count, s2Count};
            }
        }

        return s2Count / n2;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1
    {
        string s1 = "acb";
        int n1 = 4;
        string s2 = "ab";
        int n2 = 2;
        int result = solver.getMaxRepetitions(s1, n1, s2, n2);
        cout << "Test 1 - s1=\"acb\", n1=4, s2=\"ab\", n2=2 -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 2: Exact matching strings
    {
        string s1 = "acb";
        int n1 = 1;
        string s2 = "acb";
        int n2 = 1;
        int result = solver.getMaxRepetitions(s1, n1, s2, n2);
        cout << "Test 2 - s1=\"acb\", n1=1, s2=\"acb\", n2=1 -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    // Test Case 3: Overlapping repeating pattern
    {
        string s1 = "aaa";
        int n1 = 3;
        string s2 = "aa";
        int n2 = 1;
        int result = solver.getMaxRepetitions(s1, n1, s2, n2);
        cout << "Test 3 - s1=\"aaa\", n1=3, s2=\"aa\", n2=1 -> Expected: 4, Got: " << result << endl;
        assert(result == 4);
    }

    // Test Case 4: Long repetition requiring cycle fast-forwarding
    {
        string s1 = "baba";
        int n1 = 11;
        string s2 = "ba";
        int n2 = 1;
        int result = solver.getMaxRepetitions(s1, n1, s2, n2);
        cout << "Test 4 - s1=\"baba\", n1=11, s2=\"ba\", n2=1 -> Expected: 22, Got: " << result << endl;
        assert(result == 22);
    }

    // Test Case 5: Large n1 and n2
    {
        string s1 = "bacaba";
        int n1 = 3;
        string s2 = "abacab";
        int n2 = 1;
        int result = solver.getMaxRepetitions(s1, n1, s2, n2);
        cout << "Test 5 - s1=\"bacaba\", n1=3, s2=\"abacab\", n2=1 -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
