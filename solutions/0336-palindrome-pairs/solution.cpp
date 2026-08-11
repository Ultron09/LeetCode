/**
 * Problem: 336. Palindrome Pairs
 * Difficulty: Hard
 * Topics: Array, Hash Table, String, Trie
 * LeetCode Link: https://leetcode.com/problems/palindrome-pairs/
 * 
 * Time Complexity:  O(sum of L_i^2) - Where L_i is the length of words[i]
 * Space Complexity: O(N * L) - Hash map storage for all unique words and reversed prefixes/suffixes
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }

public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string, int> wordMap;
        int n = static_cast<int>(words.size());
        wordMap.reserve(n);

        for (int i = 0; i < n; ++i) {
            wordMap[words[i]] = i;
        }

        vector<vector<int>> result;

        for (int i = 0; i < n; ++i) {
            const string& w = words[i];
            int len = static_cast<int>(w.length());

            for (int k = 0; k <= len; ++k) {
                // Case 1: suffix w[k..len-1] is a palindrome -> look for reversed(prefix) to append after w: (i, j)
                if (isPalindrome(w, k, len - 1)) {
                    string revPrefix = w.substr(0, k);
                    reverse(revPrefix.begin(), revPrefix.end());
                    auto it = wordMap.find(revPrefix);
                    if (it != wordMap.end() && it->second != i) {
                        result.push_back({i, it->second});
                    }
                }

                // Case 2: prefix w[0..k-1] is a palindrome (and non-empty k > 0) -> look for reversed(suffix) to prepend before w: (j, i)
                if (k > 0 && isPalindrome(w, 0, k - 1)) {
                    string revSuffix = w.substr(k, len - k);
                    reverse(revSuffix.begin(), revSuffix.end());
                    auto it = wordMap.find(revSuffix);
                    if (it != wordMap.end() && it->second != i) {
                        result.push_back({it->second, i});
                    }
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

    // Test Case 1: words = ["abcd","dcba","lls","s","sssll"]
    {
        vector<string> words = {"abcd", "dcba", "lls", "s", "sssll"};
        auto result = solver.palindromePairs(words);
        assert(result.size() == 4);
        cout << "Test 1 Passed: ["abcd","dcba","lls","s","sssll"] -> 4 pairs" << endl;
    }

    // Test Case 2: words = ["bat","tab","cat"]
    {
        vector<string> words = {"bat", "tab", "cat"};
        auto result = solver.palindromePairs(words);
        assert(result.size() == 2);
        cout << "Test 2 Passed: ["bat","tab","cat"] -> 2 pairs" << endl;
    }

    // Test Case 3: Empty string present words = ["a",""]
    {
        vector<string> words = {"a", ""};
        auto result = solver.palindromePairs(words);
        assert(result.size() == 2);
        cout << "Test 3 Passed: ["a",""] -> 2 pairs" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
