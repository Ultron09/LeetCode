/**
 * Problem: 30. Substring with Concatenation of All Words
 * Difficulty: Hard
 * Topics: Hash Table, String, Sliding Window
 * LeetCode Link: https://leetcode.com/problems/substring-with-concatenation-of-all-words/
 * 
 * Time Complexity:  O(N * L) where N = s.length(), L = word length (<= 30)
 * Space Complexity: O(K * L) for storing frequency maps of words
 */

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (s.empty() || words.empty()) return result;

        int wordLen = static_cast<int>(words[0].length());
        int numWords = static_cast<int>(words.size());
        int totalLen = wordLen * numWords;
        int sLen = static_cast<int>(s.length());

        if (sLen < totalLen) return result;

        // 1. Build frequency map of target words
        unordered_map<string_view, int> wordCount;
        for (const string& w : words) {
            wordCount[w]++;
        }

        string_view sv(s);

        // 2. Run sliding window with wordLen different phase offsets [0, wordLen - 1]
        for (int i = 0; i < wordLen; ++i) {
            int left = i;
            unordered_map<string_view, int> windowCount;
            int count = 0; // Number of valid words in the current window

            for (int right = i; right <= sLen - wordLen; right += wordLen) {
                string_view sub = sv.substr(right, wordLen);

                auto it = wordCount.find(sub);
                if (it != wordCount.end()) {
                    windowCount[sub]++;
                    count++;

                    // If frequency exceeds target, shrink window from the left
                    while (windowCount[sub] > it->second) {
                        string_view leftSub = sv.substr(left, wordLen);
                        windowCount[leftSub]--;
                        count--;
                        left += wordLen;
                    }

                    // If exact full permutation is matched
                    if (count == numWords) {
                        result.push_back(left);
                    }
                } else {
                    // Invalid chunk encountered; reset the entire window
                    windowCount.clear();
                    count = 0;
                    left = right + wordLen;
                }
            }
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

    // Test Case 1: s = "barfoothefoobarman", words = ["foo","bar"]
    {
        string s = "barfoothefoobarman";
        vector<string> words = {"foo", "bar"};
        vector<int> res = solver.findSubstring(s, words);
        sort(res.begin(), res.end());
        vector<int> expected = {0, 9};
        assert(res == expected);
        cout << "Test 1 Passed: [0, 9]" << endl;
    }

    // Test Case 2: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
    {
        string s = "wordgoodgoodgoodbestword";
        vector<string> words = {"word", "good", "best", "word"};
        vector<int> res = solver.findSubstring(s, words);
        vector<int> expected = {};
        assert(res == expected);
        cout << "Test 2 Passed: []" << endl;
    }

    // Test Case 3: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
    {
        string s = "barfoofoobarthefoobarman";
        vector<string> words = {"bar", "foo", "the"};
        vector<int> res = solver.findSubstring(s, words);
        sort(res.begin(), res.end());
        vector<int> expected = {6, 9, 12};
        assert(res == expected);
        cout << "Test 3 Passed: [6, 9, 12]" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
