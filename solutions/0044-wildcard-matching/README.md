# [44. Wildcard Matching](https://leetcode.com/problems/wildcard-matching/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Greedy](../../topics/greedy.md), [String](../../topics/sliding-window.md)

---

## 📌 Problem Statement

Given an input string `s` and a pattern `p`, implement wildcard pattern matching with support for `'?'` and `'*'` where:
- `'?'` Matches any single character.
- `'*'` Matches any sequence of characters (including the empty sequence).

The matching should cover the **entire** input string (not partial).

### Example 1:
```
Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
```

### Example 2:
```
Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.
```

### Example 3:
```
Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
```

### Constraints:
- $0 \le \text{s.length}, \text{p.length} \le 2000$
- `s` contains only lowercase English letters.
- `p` contains only lowercase English letters, `'?'` or `'*'`.

---

## 💡 Intuition & Approach

### 1. Dynamic Programming Formulation ($\mathcal{O}(M \cdot N)$ Time, $\mathcal{O}(N)$ Space)
Let `dp[i][j]` denote whether prefix `s[0..i-1]` matches pattern prefix `p[0..j-1]`:
- Base: `dp[0][0] = true`, `dp[0][j] = dp[0][j-1]` if `p[j-1] == '*'`.
- Transitions:
  - If `p[j-1] == '?' || p[j-1] == s[i-1]`: $\text{dp}[i][j] = \text{dp}[i-1][j-1]$
  - If `p[j-1] == '*'`: $\text{dp}[i][j] = \text{dp}[i-1][j] \lor \text{dp}[i][j-1]$

### 2. Greedy Two-Pointer Backtracking ($\mathcal{O}(1)$ Auxiliary Space)
Notice that because `'*'` matches **any arbitrary sequence**, when multiple `'*'` wildcards appear, only the **most recent** `'*'` needs to be backtracked to absorb extra characters in `s`:
1. Maintain `sIdx = 0, pIdx = 0`, and fallback pointers `starIdx = -1, sTmpIdx = -1`.
2. If `p[pIdx] == '?'` or `p[pIdx] == s[sIdx]`, step both `sIdx++, pIdx++`.
3. If `p[pIdx] == '*'`: record `starIdx = pIdx, sTmpIdx = sIdx, pIdx++` (tentatively match 0 characters).
4. If mismatch and `starIdx != -1`: restart from `pIdx = starIdx + 1`, expand the absorbed length in `s` by setting `sTmpIdx++`, and resume at `sIdx = sTmpIdx`.
5. If mismatch with no preceding `'*'`: return `false`.
6. Consume any trailing `'*'` characters in `p`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \cdot N)$ worst case (e.g. `s = "aaaa"`, `p = "*aaaa"`), $\mathcal{O}(M + N)$ average runtime (0 ms in C++).
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space.

---

## 🔍 Edge Cases Considered

- **Empty Strings**: Both empty $\implies$ `true`; pattern `*` with empty string $\implies$ `true`.
- **Multiple Consecutive Stars**: Handled in constant time per step.
- **Unmatched Tail**: Checked by verifying `pIdx == n` after skipping remaining stars.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
