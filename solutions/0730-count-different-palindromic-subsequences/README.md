# [730. Count Different Palindromic Subsequences](https://leetcode.com/problems/count-different-palindromic-subsequences/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

Given a string `s`, return the number of **different non-empty palindromic subsequences** in `s`. Since the answer may be very large, return it modulo $10^9 + 7$.

A **subsequence** is obtained by deleting zero or more characters from the string. Two subsequences are different if there is some index `i` for which they differ.

### Example 1:
```
Input: s = "bccb"
Output: 6
Explanation: The 6 palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
```

### Example 2:
```
Input: s = "abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba"
Output: 104860361
Explanation: 3104860382 palindromic subsequences mod 10⁹+7 = 104860361.
```

### Constraints:
- $1 \le s.\text{length} \le 1000$
- `s[i]` is either `'a'`, `'b'`, `'c'`, or `'d'`.

---

## 💡 Intuition & Approach

### 1. Why Naive Enumeration Fails

With $N = 1000$, there are up to $2^{1000}$ subsequences — far too many to enumerate. We need a way to count **distinct** palindromic subsequences without listing them.

### 2. Key Observation: Tiny Alphabet Enables Character-Anchored Decomposition

Since the alphabet is only `{a, b, c, d}`, every palindromic subsequence has one of these 4 characters as its outermost layer. This lets us **partition** all palindromes in an interval by their outermost character without double-counting.

### 3. Optimal Strategy: Interval DP

Define `dp[i][j]` = number of distinct non-empty palindromic subsequences in `s[i..j]`.

For each character $c \in \{a, b, c, d\}$, find:
- `lo` = **first** occurrence of $c$ in `s[i..j]`
- `hi` = **last** occurrence of $c$ in `s[i..j]`

Three cases arise:

| Case | Condition | Contribution |
| :--- | :--- | :--- |
| $c$ absent | `lo > j` | 0 |
| $c$ appears once | `lo == hi` | 1 (just `"c"`) |
| $c$ appears 2+ times | `lo < hi` | `dp[lo+1][hi-1] + 2` |

The `+2` in Case 3 accounts for `"c"` (single char) and `"cc"` (pair). The `dp[lo+1][hi-1]` term counts every palindromic subsequence in the interior, each of which produces a **new unique** palindrome when wrapped with $c$ on both sides.

$$dp[i][j] = \sum_{c \in \{a,b,c,d\}} \text{contribution}(c, i, j) \mod (10^9 + 7)$$

### 4. Why There's No Double-Counting

Two palindromes with **different outermost characters** are trivially distinct. Two palindromes with the **same outermost character** $c$ are anchored at `lo` and `hi` — the tightest possible wrapping — and their interiors come from `dp[lo+1][hi-1]`, which is already deduplicated. No palindrome is counted under two different characters.

### 5. Precomputing First/Last Occurrences in O(1)

We build two lookup tables:
- `nxt[i][c]` = first index $\ge i$ where `s[index] == c` (scan right-to-left)
- `prv[i][c]` = last index $\le i$ where `s[index] == c` (scan left-to-right)

Both are built in $\mathcal{O}(4N)$ time.

### 6. Step-by-step Execution

Given `s = "bccb"` (indices 0-3):

```
dp[0][0] = 1 (just "b")
dp[1][1] = 1 (just "c")
dp[2][2] = 1 (just "c")
dp[3][3] = 1 (just "b")

dp[1][2]: char 'c' → lo=1, hi=2, lo<hi → dp[2][1]=0 → 0+2=2
           Total: 2 ("c", "cc")

dp[0][3]: char 'a' → not present → 0
          char 'b' → lo=0, hi=3 → dp[1][2]+2 = 2+2 = 4
          char 'c' → lo=1, hi=2 → dp[2][1]+2 = 0+2 = 2
          char 'd' → not present → 0
          Total: 4 + 2 = 6 ✓
```

The 6 palindromes: `b, c, bb, cc, bcb, bccb`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$
  - $\mathcal{O}(N^2)$ intervals, each processed in $\mathcal{O}(4) = \mathcal{O}(1)$ (constant alphabet size).
  - Precomputation of `nxt` and `prv` tables: $\mathcal{O}(4N)$.
- **Space Complexity:** $\mathcal{O}(N^2)$
  - DP table: $N \times N$.
  - Lookup tables: $\mathcal{O}(4N)$.

---

## 🔍 Edge Cases Considered

- **Single character** (`"a"` → 1): One palindrome.
- **All identical characters** (`"aaa"` → 3): `"a"`, `"aa"`, `"aaa"`.
- **No repeated characters** (`"abcd"` → 4): Only single-char palindromes.
- **Maximum length** ($N = 1000$): $10^6$ DP states, well within time limits.
- **Modular arithmetic overflow**: All additions use `long long` before taking mod.

---

## 🔗 Related Problems

- [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/) — Standard interval DP on palindromes (length, not count)
- [647. Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/) — Counting contiguous palindromes (simpler variant)
- [1960. Maximum Product of the Length of Two Palindromic Substrings](../1960-maximum-product-of-the-length-of-two-palindromic-substrings/README.md) — Advanced palindrome decomposition

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
