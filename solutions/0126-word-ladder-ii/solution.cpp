/**
 * Problem: 126. Word Ladder II
 * Difficulty: Hard
 * Topics: Hash Table, String, Backtracking, Breadth-First Search, Graphs
 * LeetCode Link: https://leetcode.com/problems/word-ladder-ii/
 * 
 * Time Complexity:  O(N * L * 26 + K * L) where N = wordList.length, L = word.length, K = number of paths
 * Space Complexity: O(N * L) for BFS queue, distance hash map, and parent DAG
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    void backtrack(const string& word, const string& beginWord,
                   unordered_map<string, vector<string>>& parents,
                   vector<string>& currentPath,
                   vector<vector<string>>& results) {
        if (word == beginWord) {
            vector<string> fullPath = currentPath;
            reverse(fullPath.begin(), fullPath.end());
            results.push_back(fullPath);
            return;
        }

        auto it = parents.find(word);
        if (it == parents.end()) {
            return;
        }

        for (const string& parent : it->second) {
            currentPath.push_back(parent);
            backtrack(parent, beginWord, parents, currentPath, results);
            currentPath.pop_back();
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end()) {
            return {};
        }

        // BFS: level-by-level to construct shortest-path DAG of parents
        unordered_map<string, int> dist;
        unordered_map<string, vector<string>> parents;
        queue<string> q;

        dist[beginWord] = 0;
        q.push(beginWord);

        bool reachedEnd = false;
        int wordLen = static_cast<int>(beginWord.length());

        while (!q.empty() && !reachedEnd) {
            int levelSize = static_cast<int>(q.size());
            for (int k = 0; k < levelSize; ++k) {
                string curr = q.front();
                q.pop();

                int currDist = dist[curr];
                string neighbor = curr;

                for (int i = 0; i < wordLen; ++i) {
                    char origChar = neighbor[i];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == origChar) continue;
                        neighbor[i] = c;

                        if (dict.find(neighbor) != dict.end()) {
                            auto distIt = dist.find(neighbor);
                            if (distIt == dist.end()) {
                                dist[neighbor] = currDist + 1;
                                parents[neighbor].push_back(curr);
                                q.push(neighbor);
                            } else if (distIt->second == currDist + 1) {
                                parents[neighbor].push_back(curr);
                            }

                            if (neighbor == endWord) {
                                reachedEnd = true;
                            }
                        }
                    }
                    neighbor[i] = origChar;
                }
            }
        }

        if (!reachedEnd) {
            return {};
        }

        // Backtrack along parents DAG from endWord to beginWord
        vector<vector<string>> results;
        vector<string> currentPath = {endWord};
        backtrack(endWord, beginWord, parents, currentPath, results);

        return results;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: "hit" -> "cog" with valid dictionary
    {
        string beginWord = "hit";
        string endWord = "cog";
        vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
        auto result = solver.findLadders(beginWord, endWord, wordList);
        assert(result.size() == 2);
        cout << "Test 1 Passed: 2 shortest paths found!" << endl;
    }

    // Test Case 2: "hit" -> "cog" without endWord
    {
        string beginWord = "hit";
        string endWord = "cog";
        vector<string> wordList = {"hot", "dot", "dog", "lot", "log"};
        auto result = solver.findLadders(beginWord, endWord, wordList);
        assert(result.empty());
        cout << "Test 2 Passed: empty list returned when endWord absent!" << endl;
    }

    // Test Case 3: "a" -> "c"
    {
        string beginWord = "a";
        string endWord = "c";
        vector<string> wordList = {"a", "b", "c"};
        auto result = solver.findLadders(beginWord, endWord, wordList);
        assert(result.size() == 1 && result[0].size() == 2);
        cout << "Test 3 Passed: single step transformation!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
