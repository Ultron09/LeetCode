# [940. Distinct Subsequences II](https://leetcode.com/problems/distinct-subsequences-ii/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), String

---

## 📌 Problem Statement

Given a string `s`, return the number of distinct non-empty subsequences of `s`. Since the answer may be very large, return it modulo `10^9 + 7`.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., `"ace"` is a subsequence of `"abcde"` while `"aec"` is not.)

### Example 1:
```
Input: s = "abc"
Output: 7
Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
```

### Example 2:
```
Input: s = "aba"
Output: 6
Explanation: The 6 distinct subsequences are "a", "b", "ab", "aa", "ba", and "aba".
```

### Example 3:
```
Input: s = "aaa"
Output: 3
Explanation: The 3 distinct subsequences are "a", "aa" and "aaa".
```

### Constraints:
- `1 <= s.length <= 2000`
- `s` consists of lowercase English letters.

---

## 💡 Intuition & Approach

This is a classic Dynamic Programming problem with a math optimization. Instead of keeping a 2D array, we can think about the subsequences *ending with* each specific character.

1. **State Definition**: Let `last[c]` be the number of distinct subsequences that end with the character `c`.
2. **Transition**:
   - When we process a new character `c` in the string, we can form new distinct subsequences by appending `c` to *all* previously formed distinct subsequences.
   - Also, the character `c` itself forms a new single-character subsequence.
   - Therefore, the new number of distinct subsequences ending in `c` is: `new_last[c] = (sum of all current distinct subsequences) + 1`.
3. **Optimization**:
   - Instead of summing up the `last` array every time (which takes $\mathcal{O}(26)$), we can maintain a running `total_sum`.
   - When updating `last[c]`, we adjust `total_sum` by adding the new contribution of `c` and subtracting its old contribution to avoid double counting.
   - `total_sum = (total_sum - old_last[c] + new_last[c]) % MOD`.
4. **Modulo Arithmetic**: We must be careful to handle negative numbers in modulo operations by doing `(total_sum + MOD) % MOD`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — We iterate through the string of length $N$ exactly once. Updating the states and rolling sums happens in $\mathcal{O}(1)$ time.
- **Space Complexity:** $\mathcal{O}(1)$ — Our state is represented by an array of size 26 (for each lowercase English letter), taking constant extra memory.

---

## 🔍 Edge Cases Considered

- String with all identical characters (e.g., `"aaa"`). Handled correctly as `old_val` perfectly offsets overlapping counts.
- String with all distinct characters. Handled correctly as `total_sum` precisely doubles (plus 1) at each step.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
