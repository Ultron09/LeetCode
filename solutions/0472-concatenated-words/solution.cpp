/**
 * Problem: 472. Concatenated Words
 * Difficulty: Hard
 * Topics: Array, String, Dynamic Programming, Depth-First Search, Trie
 * LeetCode Link: https://leetcode.com/problems/concatenated-words/
 * 
 * Time Complexity:  O(N * log N + N * L^3) where N is the number of words and L is the max word length (L <= 30)
 * Space Complexity: O(sum(|W_i|)) - Storing dictionary words in an unordered hash set
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        // Sort words by length in ascending order so shorter words are processed first
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.length() < b.length();
        });

        unordered_set<string> wordSet;
        vector<string> result;

        for (const string& word : words) {
            if (word.empty()) continue;

            int len = word.length();
            // dp[i] indicates whether word[0..i-1] can be segmented into words in wordSet
            vector<bool> dp(len + 1, false);
            dp[0] = true;

            for (int i = 1; i <= len; ++i) {
                for (int j = 0; j < i; ++j) {
                    if (dp[j] && wordSet.count(word.substr(j, i - j))) {
                        dp[i] = true;
                        break;
                    }
                }
            }

            // If the whole word can be formed by strictly shorter words in wordSet
            if (dp[len]) {
                result.push_back(word);
            }

            // Add the current word into the set of available vocabulary for longer words
            wordSet.insert(word);
        }

        return result;
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
        vector<string> words = {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};
        vector<string> result = solver.findAllConcatenatedWordsInADict(words);
        sort(result.begin(), result.end());
        vector<string> expected = {"catsdogcats","dogcatsdog","ratcatdogcat"};
        sort(expected.begin(), expected.end());
        cout << "Test 1 - Words list -> Passed: " << (result == expected) << endl;
        assert(result == expected);
    }

    // Test Case 2: Simple 2-word composition
    {
        vector<string> words = {"cat","dog","catdog"};
        vector<string> result = solver.findAllConcatenatedWordsInADict(words);
        vector<string> expected = {"catdog"};
        cout << "Test 2 - Words list -> Passed: " << (result == expected) << endl;
        assert(result == expected);
    }

    // Test Case 3: Chain with non-decomposable longer words
    {
        vector<string> words = {"a", "b", "ab", "abc"};
        vector<string> result = solver.findAllConcatenatedWordsInADict(words);
        vector<string> expected = {"ab"};
        cout << "Test 3 - Words list -> Passed: " << (result == expected) << endl;
        assert(result == expected);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
