# [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

**Difficulty:** `Hard`  
**Topics:** [Sliding Window](../../topics/sliding-window.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md), [String](../../topics/sliding-window.md)

---

## 📌 Problem Statement

Given two strings `s` and `t` of lengths `m` and `n` respectively, return the **minimum window substring** of `s` such that every character in `t` (including duplicates) is included in the window. If there is no such substring, return the empty string `""`.

The testcases will be generated such that the answer is **unique**.

### Example 1:
```
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
```

### Example 2:
```
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
```

### Example 3:
```
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
```

### Constraints:
- $m == \text{s.length}$
- $n == \text{t.length}$
- $1 \le m, n \le 10^5$
- `s` and `t` consist of uppercase and lowercase English letters.

---

## 💡 Intuition & Approach

### 1. Dynamic Sliding Window with Character Matching Counter
- Build character frequency requirement map `targetFreq[128]` for $t$, noting `required = number of unique characters in t`.
- Maintain a sliding window $[left, right]$ over string $s$ with `windowFreq[128]`.
- As `right` expands:
  - Increment `windowFreq[s[right]]`.
  - When `windowFreq[c] == targetFreq[c]`, increment `formed`.
- While `formed == required` (window is valid and contains all needed characters from $t$):
  - Check and update $(minLen, minStart)$ if the current window is smaller.
  - Incrementally shrink the window by moving `left` rightward:
    - Decrement `windowFreq[s[left]]`.
    - If `windowFreq[s[left]] < targetFreq[s[left]]`, decrement `formed`.
    - Advance `left++`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M + N)$ where $M = |s|$ and $N = |t|$. Each character in $s$ is visited by $left$ and $right$ at most twice.
- **Space Complexity:** $\mathcal{O}(\Sigma) = \mathcal{O}(1)$ for fixed 128-byte ASCII frequency tables.

---

## 🔍 Edge Cases Considered

- **$|s| < |t|$**: Immediately impossible $\implies \text{""}$.
- **Duplicate target characters** ($t = \text{"aa"}$): Formed is only incremented when the full required count is satisfied.
- **No matching substring exists**: Returns `""`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
