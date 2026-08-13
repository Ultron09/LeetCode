/**
 * Problem: 745. Prefix and Suffix Search
 * Difficulty: Hard
 * Topics: Trie, Trees, String
 * LeetCode Link: https://leetcode.com/problems/prefix-and-suffix-search/
 *
 * Approach: Single Trie with Suffix Wrapping
 *
 * Key Insight:
 *   Instead of two separate Tries and doing intersection (which can be slow),
 *   we can wrap the suffix around the prefix using a delimiter (e.g., '{')
 *   and store them in a single Trie.
 *   For a word "apple", we insert the following into the Trie:
 *     "apple{apple"
 *     "pple{apple"
 *     "ple{apple"
 *     "le{apple"
 *     "e{apple"
 *     "{apple"
 *   Then, for a query with pref = "a" and suff = "e", we search for "e{a" in the Trie.
 *   Since we insert words in their original index order, each Trie node will store
 *   the maximum index of the word that shares that path.
 *
 * Time Complexity:
 *   Initialization: O(N * L^2), where N is the number of words, and L is the max length of a word (L <= 7).
 *   Query: O(L) - we simply follow the Trie path for length of `suff + '{' + pref`.
 * Space Complexity: O(N * L^2) for the Trie nodes.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class TrieNode {
public:
    TrieNode* children[27]; // 26 letters + '{'
    int weight;
    
    TrieNode() {
        weight = 0;
        for (int i = 0; i < 27; ++i) {
            children[i] = nullptr;
        }
    }
};

class WordFilter {
private:
    TrieNode* root;
    
public:
    WordFilter(vector<string>& words) {
        root = new TrieNode();
        
        for (int weight = 0; weight < words.size(); ++weight) {
            string word = words[weight];
            string suffix = "";
            
            // Generate all suffixes of the word + '{' + word
            for (int i = word.length(); i >= 0; --i) {
                suffix = word.substr(i);
                string insertStr = suffix + "{" + word;
                
                TrieNode* curr = root;
                curr->weight = weight;
                
                for (char c : insertStr) {
                    int idx = c - 'a'; // '{' - 'a' will be 26
                    if (curr->children[idx] == nullptr) {
                        curr->children[idx] = new TrieNode();
                    }
                    curr = curr->children[idx];
                    curr->weight = weight;
                }
            }
        }
    }
    
    int f(string pref, string suff) {
        TrieNode* curr = root;
        string searchStr = suff + "{" + pref;
        
        for (char c : searchStr) {
            int idx = c - 'a';
            if (curr->children[idx] == nullptr) {
                return -1;
            }
            curr = curr->children[idx];
        }
        
        return curr->weight;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    // Test Case 1
    {
        vector<string> words = {"apple"};
        WordFilter wordFilter(words);
        int result = wordFilter.f("a", "e");
        assert(result == 0);
        cout << "Test 1 Passed! f('a', 'e') -> " << result << endl;
    }
    
    // Test Case 2
    {
        vector<string> words = {"apple", "ape"};
        WordFilter wordFilter(words);
        int res1 = wordFilter.f("a", "e"); // Both match, but "ape" has larger index 1
        assert(res1 == 1);
        cout << "Test 2 Passed! f('a', 'e') -> " << res1 << endl;
    }
    
    // Test Case 3: No match
    {
        vector<string> words = {"apple"};
        WordFilter wordFilter(words);
        int res = wordFilter.f("b", "e");
        assert(res == -1);
        cout << "Test 3 Passed! f('b', 'e') -> " << res << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
