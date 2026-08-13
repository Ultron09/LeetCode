/**
 * Problem: 843. Guess the Word
 * Difficulty: Hard
 * Topics: Array, String, Game Theory, Interactive
 * LeetCode Link: https://leetcode.com/problems/guess-the-word/
 *
 * Approach: Minimax Strategy
 * We have up to 10 guesses to find a secret word from a list of up to 100 6-letter words.
 * Each time we guess a word, we receive the number of exact character matches.
 * 
 * To minimize the number of remaining possible words in the worst-case scenario, 
 * we use a Minimax approach:
 * 1. Maintain a list of `candidates` (initially all words).
 * 2. For each word in `candidates`, simulate guessing it. We group the other 
 *    candidates into buckets (0 to 6) based on how many matches they share with the guess.
 * 3. The worst-case for a guess is the size of its largest bucket.
 * 4. We pick the word that has the MINIMUM worst-case bucket size (Minimax).
 * 5. We call `master.guess(best_word)`. Let the result be `matches`.
 * 6. Filter `candidates`: keep only those that have exactly `matches` matches with `best_word`.
 * 7. Repeat until we get 6 matches.
 *
 * Time Complexity:  O(N^2) per guess step, where N is the number of remaining candidates.
 *                   Initially N = 100. 100^2 = 10000 operations per step. Very fast.
 * Space Complexity: O(N) to store candidates and buckets.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

#ifdef LOCAL_TEST
class Master {
    string secret;
    int guesses;
public:
    Master(string s) : secret(s), guesses(0) {}
    int guess(string word) {
        guesses++;
        int matches = 0;
        for (int i = 0; i < 6; ++i) {
            if (word[i] == secret[i]) matches++;
        }
        return matches;
    }
    int getGuesses() const { return guesses; }
};
#else
// This is the Master's API interface for LeetCode submission.
// class Master {
//   public:
//     int guess(string word);
// };
#endif

class Solution {
    int match(const string& a, const string& b) {
        int matches = 0;
        for (int i = 0; i < 6; ++i) {
            if (a[i] == b[i]) matches++;
        }
        return matches;
    }
    
public:
    void findSecretWord(vector<string>& words, Master& master) {
        vector<string> candidates = words;
        
        for (int i = 0; i < 30; ++i) { // At most 30 guesses allowed, typically solves in < 10
            if (candidates.empty()) break;
            
            // Find the best word to guess using Minimax
            string best_guess = candidates[0];
            int min_max_group = candidates.size() + 1;
            
            for (const string& w : candidates) {
                vector<int> group_counts(7, 0);
                for (const string& c : candidates) {
                    if (w == c) continue;
                    group_counts[match(w, c)]++;
                }
                
                int max_group = 0;
                for (int count : group_counts) {
                    max_group = max(max_group, count);
                }
                
                if (max_group < min_max_group) {
                    min_max_group = max_group;
                    best_guess = w;
                }
            }
            
            // Make the guess
            int matches = master.guess(best_guess);
            if (matches == 6) return;
            
            // Filter candidates
            vector<string> next_candidates;
            for (const string& c : candidates) {
                if (match(best_guess, c) == matches) {
                    next_candidates.push_back(c);
                }
            }
            candidates = next_candidates;
        }
    }
};

// ==========================================
// Local Test Runner
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    {
        string secret = "acckzz";
        vector<string> words = {"acckzz","ccbazz","eiowzz","abcczz"};
        Master master(secret);
        solver.findSecretWord(words, master);
        assert(master.getGuesses() <= 10);
        cout << "Test 1 Passed! Guesses used: " << master.getGuesses() << endl;
    }

    // Test Case 2
    {
        string secret = "hamada";
        vector<string> words = {"hamada","khaled"};
        Master master(secret);
        solver.findSecretWord(words, master);
        assert(master.getGuesses() <= 10);
        cout << "Test 2 Passed! Guesses used: " << master.getGuesses() << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
