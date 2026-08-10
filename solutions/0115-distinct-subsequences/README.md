# [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [String](../../topics/sliding-window.md)

---

## 📌 Problem Statement

Given two strings `s` and `t`, return the number of distinct subsequences of `s` which equals `t`.

The test cases are generated so that the answer fits on a 32-bit signed integer.

### Example 1:
```
Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
There are 3 ways to form "rabbit" from "rabbbit":
- rabb[b]it (omit 3rd 'b')
- rab[b]bit (omit 2nd 'b')
- ra[b]bbit (omit 1st 'b')
```

### Example 2:
```
Input: s = "babgbag", t = "bag"
Output: 5
```

### Constraints:
- $1 \le \text{s.length}, \text{t.length} \le 1000$
- `s` and `t` consist of English letters.

---

## 💡 Intuition & Approach

### 1. 2D DP Recurrence
Let $dp[i][j]$ denote the number of distinct subsequences of prefix $s[0 \dots i - 1]$ that equal prefix $t[0 \dots j - 1]$:
- **Base Case**: $dp[i][0] = 1$ for all $i \ge 0$ (the empty string can always be formed by deleting all characters).
- **Transitions**:
  - We can always choose *not* to include $s[i - 1]$: $dp[i][j] = dp[i - 1][j]$.
  - If $s[i - 1] == t[j - 1]$, we can also choose to match $s[i - 1]$ with $t[j - 1]$:
    $$dp[i][j] += dp[i - 1][j - 1]$$

### 2. Space Optimization ($\mathcal{O}(N)$ Space)
Since state $dp[i][j]$ depends only on row $i - 1$ at positions $j$ and $j - 1$, we can compress the DP table to a 1D array $dp[j]$ updated in reverse ($j = n \dots 1$):
```cpp
if (s[i - 1] == t[j - 1]) {
    dp[j] += dp[j - 1];
}
```

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \times N)$ where $M = |s|$ and $N = |t|$.
- **Space Complexity:** $\mathcal{O}(N)$ space-optimized 1D DP table.

---

## 🔍 Edge Cases Considered

- **$|s| < |t|$**: Impossible to form $t \implies \text{return 0}$.
- **Identical strings**: $s == t \implies \text{return 1}$.
- **No common characters**: Returns 0.
- **Intermediate Integer Overflow**: Avoided using `unsigned long long` buffers.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
