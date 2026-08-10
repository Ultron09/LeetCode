# [132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [String](../../topics/sliding-window.md)

---

## 📌 Problem Statement

Given a string `s`, partition `s` such that every substring of the partition is a palindrome.

Return the **minimum cuts** needed for a palindrome partitioning of `s`.

### Example 1:
```
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
```

### Example 2:
```
Input: s = "a"
Output: 0
```

### Example 3:
```
Input: s = "ab"
Output: 1
```

### Constraints:
- $1 \le \text{s.length} \le 2000$
- `s` consists of lowercase English letters only.

---

## 💡 Intuition & Approach

### 1. 1D DP State Definition
Let $dp[i]$ denote the minimum number of cuts needed to partition prefix $s[0 \dots i]$ into palindromic substrings.
- **Worst-case Initialization**: $dp[i] = i$ (cutting after each single character).

### 2. Dual Center Expansion ($\mathcal{O}(N^2)$ Time, $\mathcal{O}(N)$ Space)
Instead of allocating an $\mathcal{O}(N^2)$ 2D table `isPalindrome[i][j]`, we can expand around all $2N - 1$ centers directly:
- **Odd Centers**: $(i, i)$
- **Even Centers**: $(i, i + 1)$

While expanding outwards with pointers $l$ and $r$ ($s[l] == s[r]$):
- If $l == 0$: The entire prefix $s[0 \dots r]$ is a palindrome, so $dp[r] = 0$ (0 cuts needed).
- If $l > 0$: The substring $s[l \dots r]$ is a palindrome, so we can transition from prefix $s[0 \dots l - 1]$:
  $$dp[r] = \min(dp[r], dp[l - 1] + 1)$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$ where $N = |s| \le 2000$ (expanding each center takes $\mathcal{O}(N)$).
- **Space Complexity:** $\mathcal{O}(N)$ auxiliary space for the DP cuts vector (no 2D matrix overhead).

---

## 🔍 Edge Cases Considered

- **Single Character String** (`"a"`): Returns `0`.
- **Entire String is Palindrome** (`"abacaba"`): Returns `0`.
- **All Distinct Characters** (`"abcde"`): Returns $N - 1 = 4$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
