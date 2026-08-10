# [2573. Find the String with LCP](https://leetcode.com/problems/find-the-string-with-lcp/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Greedy](../../topics/greedy.md), [String](../../topics/arrays-and-hashing.md), [Matrix](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

We define the **LCP (Longest Common Prefix) matrix** of any 0-indexed string `word` of $n$ lowercase English letters as an $n \times n$ grid where:
- `lcp[i][j]` is equal to the length of the longest common prefix between the suffixes `word[i..n-1]` and `word[j..n-1]`.

Given an $n \times n$ matrix `lcp`, return the **alphabetically smallest** string `word` that corresponds to `lcp`. If no such string exists, return `""`.

### Example 1:
```
Input: lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
Output: "abab"
Explanation: "abab" produces the exact LCP matrix given and is the lexicographically smallest.
```

### Example 2:
```
Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]
Output: "aaaa"
```

### Example 3:
```
Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]
Output: ""
Explanation: lcp[3][3] = 3 is invalid since the suffix word[3..3] has length 1.
```

### Constraints:
- $1 \le n == \text{lcp.length} == \text{lcp}[i]\text{.length} \le 1000$
- $0 \le \text{lcp}[i][j] \le n$

---

## 💡 Intuition & Approach

### 1. Structural Properties of an LCP Matrix
- If `lcp[i][j] > 0`, the first characters of suffixes `word[i..n-1]` and `word[j..n-1]` must match: `word[i] == word[j]`.
- Suffix DP relation:
  $$\text{LCP}(i, j) = \begin{cases} 1 + \text{LCP}(i + 1, j + 1) & \text{if } \text{word}[i] == \text{word}[j] \\ 0 & \text{otherwise} \end{cases}$$

### 2. Greedy Alphabetical Construction
- Iterate $i$ from $0$ to $n - 1$:
  - If `word[i]` is not yet assigned:
    - Assign the next available character from `'a'` to `'z'`.
    - If more than 26 distinct characters are required, return `""`.
    - For all $j > i$ where `lcp[i][j] > 0`, assign `word[j] = word[i]`.

### 3. Suffix DP Validation
- Recompute the true LCP matrix of `word` using bottom-up 2D DP in $\mathcal{O}(n^2)$ time:
  $$\text{dp}[i][j] = (\text{word}[i] == \text{word}[j]) \, ? \, (1 + \text{dp}[i+1][j+1]) : 0$$
- If `dp[i][j] != lcp[i][j]` at any position, the input matrix is structurally invalid or inconsistent with a 26-character alphabet $\implies$ return `""`.
- Otherwise, `word` is guaranteed to be the unique, lexicographically smallest string.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$ where $N \le 1000$
  - Greedy construction: $\mathcal{O}(N^2)$.
  - DP validation: $\mathcal{O}(N^2)$ iterations with $\mathcal{O}(1)$ work per cell.
  - Total operations $\approx 10^6$ ($< 5$ ms in C++).
- **Space Complexity:** $\mathcal{O}(N^2)$ for the DP validation grid.

---

## 🔍 Edge Cases Considered

- **$N = 1$**: Single character string; validates `lcp[0][0] == 1`.
- **Alphabet exhaustion ($> 26$ disjoint components)**: Cleanly returns `""`.
- **Invalid matrix entries**: Asymmetry (`lcp[i][j] != lcp[j][i]`), impossible diagonal values (`lcp[i][i] != n - i`), or false transitive matches are caught by the full $\mathcal{O}(N^2)$ validation pass.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
