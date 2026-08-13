# [843. Guess the Word](https://leetcode.com/problems/guess-the-word/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), Game Theory, Interactive

---

## 📌 Problem Statement

You are given an array of unique strings `words` where `words[i]` is six letters long. One word of `words` was chosen as a secret word.

You are also given the helper object `Master`. You may call `Master.guess(word)` where `word` is a six-letter-long string, and it must be from `words`. `Master.guess(word)` returns:
- `-1` if `word` is not from `words`, or
- an integer representing the number of exact matches (value and position) of your guess to the secret word.

There is a parameter `allowedGuesses` for each test case where `allowedGuesses` is the maximum number of times you can call `Master.guess(word)`.

For each test case, you should call `Master.guess` with the secret word without exceeding the maximum number of allowed guesses.

### Example 1:
```
Input: secret = "acckzz", words = ["acckzz","ccbazz","eiowzz","abcczz"], allowedGuesses = 10
Output: You guessed the secret word correctly.
Explanation:
master.guess("aaaaaa") returns -1, because "aaaaaa" is not in words.
master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
master.guess("abcczz") returns 4, because "abcczz" has 4 matches.
We made 5 calls to master.guess, and one of them was the secret, so we pass the test case.
```

### Constraints:
- `1 <= words.length <= 100`
- `words[i].length == 6`
- `words[i]` consist of lowercase English letters.
- All the strings of `words` are unique.
- `secret` exists in `words`.
- `10 <= allowedGuesses <= 30`

---

## 💡 Intuition & Approach

This is an interactive problem where every API call gives us information to filter down our candidate pool. With up to 100 words and $10$ allowed guesses, making random guesses could technically result in a failure if we hit a streak of zero-match words that don't effectively reduce our search space.

To guarantee solving it within the guess limit, we can employ a **Minimax Algorithm**:
1. We maintain a `candidates` list of words that are still potentially the secret word.
2. If we guess a word $W$, the Master will return a match count from $0$ to $6$. Depending on this return value, our candidates list shrinks to only contain words that share exactly that many matches with $W$.
3. To eliminate as many words as possible in the **worst-case scenario**, we simulate guessing every word $W$ in our candidate list. We group the other candidates into buckets (from $0$ to $6$ matches). The largest bucket represents the *worst-case* number of remaining candidates if we guess $W$.
4. We choose the word $W$ that minimizes this maximum bucket size (hence, **Minimax**).
5. We call the Master API with this optimal $W$, use the result to filter our `candidates`, and repeat.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$ per step. Finding the best word involves comparing every candidate with every other candidate. Since there are at most $N = 100$ words, $N^2 = 10,000$ operations. It takes at most $\approx 6-7$ steps to converge, so the total time complexity is comfortably tiny ($\ll 1 \text{ms}$).
- **Space Complexity:** $\mathcal{O}(N)$ — We need to store the list of remaining candidates (up to $100$ strings) and the match frequency buckets.

---

## 🔍 Edge Cases Considered

- **Randomness:** Minimax is strictly deterministic and optimized for the worst-case, meaning it avoids the variance of random guess strategies and guarantees convergence well within the 10-guess limit.
- **Match calculations:** Character matching is strictly positional ($a[i] == b[i]$), which maps directly to the API's behavior.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
