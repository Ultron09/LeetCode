# [10. Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [String](../../topics/arrays-and-hashing.md), [Recursion](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

Given an input string `s` and a pattern `p`, implement regular expression matching with support for `'.'` and `'*'` where:
- `'.'` Matches any single character.
- `'*'` Matches zero or more of the preceding element.

Return a boolean indicating whether the matching covers the **entire** input string (not partial).

### Example 1:
```
Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
```

### Example 2:
```
Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
```

### Example 3:
```
Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
```

### Constraints:
- $1 \le s\text{.length} \le 20$
- $1 \le p\text{.length} \le 20$
- `s` contains only lowercase English letters.
- `p` contains only lowercase English letters, `'.'`, and `'*'`.
- Guaranteed that for each `'*'`, there is a preceding valid character.

---

## 💡 Intuition & Approach

### 1. State Formulation
Let $\text{dp}[i][j]$ be `true` if the prefix $s[0..i-1]$ matches the pattern prefix $p[0..j-1]$.

### 2. Base Cases
- $\text{dp}[0][0] = \text{true}$ (empty string matches empty pattern).
- For $i = 0$ (empty string $s$ against non-empty pattern $p$):
  - If $p[j - 1] == '*' $, the `'*'` can match 0 occurrences of $p[j - 2]$, so:
    $$\text{dp}[0][j] = \text{dp}[0][j - 2]$$

### 3. State Transitions
For each $i \in [1, m]$ and $j \in [1, n]$:
1. **Direct Character / Wildcard Dot (`p[j - 1] != '*'`)**:
   $$\text{dp}[i][j] = \text{dp}[i - 1][j - 1] \quad \text{if } (p[j - 1] == s[i - 1] \lor p[j - 1] == '.')$$
2. **Wildcard Multiplier (`p[j - 1] == '*'`)**:
   - **Zero Occurrences**: Drop the preceding character and `'*'` token:
     $$\text{dp}[i][j] = \text{dp}[i][j - 2]$$
   - **One or More Occurrences**: If $p[j - 2]$ matches $s[i - 1]$ (or is `'.'`), we can consume $s[i - 1]$ while keeping the pattern token $p[j - 1]$ active:
     $$\text{dp}[i][j] = \text{dp}[i][j] \lor \text{dp}[i - 1][j]$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \cdot N)$ where $M, N \le 20 \implies \le 400$ state transitions ($< 1$ ms).
- **Space Complexity:** $\mathcal{O}(M \cdot N)$ for the DP lookup table.

---

## 🔍 Edge Cases Considered

- **Empty matches via `*`**: Patterns like `"a*b*c*"` matching `""` or `"c"`.
- **Universal Wildcard `".*"`**: Capable of consuming any sequence of arbitrary length.
- **Multiple preceding duplicates**: Correctly propagates greedy non-deterministic matches via OR transitions.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
