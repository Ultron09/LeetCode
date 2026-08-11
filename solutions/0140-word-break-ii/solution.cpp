/**
 * Problem: 140. Word Break II
 * Difficulty: Hard
 * Topics: Array, Hash Table, String, Dynamic Programming, Backtracking, Trie, Memoization
 * LeetCode Link: https://leetcode.com/problems/word-break-ii/
 * 
 * Time Complexity:  O(2^N + N^2 + W) where N = s.length(), W = total length of words in wordDict
 * Space Complexity: O(2^N * N + W) for memoization cache and recursion stack
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    vector<string> dfs(int start, const string& s, const unordered_set<string>& dict,
                       unordered_map<int, vector<string>>& memo) {
        if (start == static_cast<int>(s.length())) {
            return {""};
        }

        auto it = memo.find(start);
        if (it != memo.end()) {
            return it->second;
        }

        vector<string> validSentences;
        int n = static_cast<int>(s.length());

        for (int end = start + 1; end <= n; ++end) {
            string word = s.substr(start, end - start);
            if (dict.find(word) != dict.end()) {
                vector<string> subSentences = dfs(end, s, dict, memo);
                for (const string& sub : subSentences) {
                    if (sub.empty()) {
                        validSentences.push_back(word);
                    } else {
                        validSentences.push_back(word + " " + sub);
                    }
                }
            }
        }

        memo[start] = validSentences;
        return validSentences;
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        unordered_map<int, vector<string>> memo;
        return dfs(0, s, dict, memo);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
    {
        string s = "catsanddog";
        vector<string> wordDict = {"cat", "cats", "and", "sand", "dog"};
        auto result = solver.wordBreak(s, wordDict);
        sort(result.begin(), result.end());
        vector<string> expected = {"cat sand dog", "cats and dog"};
        sort(expected.begin(), expected.end());
        assert(result == expected);
        cout << "Test 1 Passed: \"catsanddog\" -> [\"cat sand dog\", \"cats and dog\"]" << endl;
    }

    // Test Case 2: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
    {
        string s = "pineapplepenapple";
        vector<string> wordDict = {"apple", "pen", "applepen", "pine", "pineapple"};
        auto result = solver.wordBreak(s, wordDict);
        sort(result.begin(), result.end());
        vector<string> expected = {"pine apple pen apple", "pine applepen apple", "pineapple pen apple"};
        sort(expected.begin(), expected.end());
        assert(result == expected);
        cout << "Test 2 Passed: \"pineapplepenapple\" with multi-word segmentation" << endl;
    }

    // Test Case 3: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"] -> []
    {
        string s = "catsandog";
        vector<string> wordDict = {"cats", "dog", "sand", "and", "cat"};
        auto result = solver.wordBreak(s, wordDict);
        assert(result.empty());
        cout << "Test 3 Passed: \"catsandog\" -> []" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
