# [3614. Process String with Special Operations II](https://leetcode.com/problems/process-string-with-special-operations-ii/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), [Math & Geometry](../../topics/math-and-geometry.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given a string `s` consisting of lowercase English letters and special characters `'*'`, `'#'`, and `'%'`, along with an integer `k`.

Build a new string `result` by processing `s` from left to right:
- **Lowercase letter**: Append it to `result`.
- **`'*'`**: Remove the last character from `result`, if it exists.
- **`'#'`**: Duplicate `result` and append it to itself (`result = result + result`).
- **`'%'`**: Reverse `result`.

Return the **$k$-th character** of the final string `result` (0-indexed). If $k$ is out of bounds, return `'.'`.

### Example 1:
```
Input: s = "a#b%*", k = 1
Output: "a"
Explanation:
- 'a' -> "a"
- '#' -> "aa"
- 'b' -> "aab"
- '%' -> "baa"
- '*' -> "ba"
Result is "ba". At index k = 1, char is 'a'.
```

### Example 2:
```
Input: s = "cd%#*#", k = 3
Output: "d"
Explanation:
- 'c' -> "c"
- 'd' -> "cd"
- '%' -> "dc"
- '#' -> "dcdc"
- '*' -> "dcd"
- '#' -> "dcddcd"
Result is "dcddcd". At index k = 3, char is 'd'.
```

### Example 3:
```
Input: s = "z*#", k = 0
Output: "."
Explanation:
- 'z' -> "z"
- '*' -> ""
- '#' -> ""
Result is "". Index 0 is out of bounds, return '.'.
```

### Constraints:
- $1 \le \text{s.length} \le 10^5$
- `s` consists of lowercase English letters and `'*'`, `'#'`, `'%'`.
- $0 \le k \le 10^{15}$
- The length of `result` after processing `s` will not exceed $10^{15}$.

---

## 💡 Intuition & Approach

### 1. The Challenge of Exponential Expansion
Due to repeated `'#'` duplications, `result` can grow up to length $10^{15}$. Constructing or storing the string explicitly is impossible ($\mathcal{O}(2^N)$ memory/time).

Instead, we use a **Two-Pass Coordinate Backtracking** approach:
1. **Forward Pass**: Compute and store the length of the string after each operation $i$.
2. **Backward Pass**: Start at the final target index $k$ and reverse the coordinate transformations back to find the exact character that generated index $k$.

### 2. Backward Coordinate Mapping Rules
Let $L[i]$ be the length after step $i$, and $\text{prev\_len} = L[i-1]$ (with $L[-1] = 0$).
Processing operations from $i = n - 1$ down to $0$:
- **`'*'` (Deletion)**: The deleted character was at index $\text{prev\_len} - 1$. Since $k < L[i]$, any index $k$ surviving after deletion was at the exact same index before deletion $\implies$ $k$ remains unchanged.
- **`'#'` (Duplication)**: The string consisted of two copies of length $\text{prev\_len}$. If $k \ge \text{prev\_len}$, it was in the second copy, so $k \leftarrow k - \text{prev\_len}$.
- **`'%'` (Reversal)**: The string of length $\text{prev\_len}$ was reversed. The previous index was $\text{prev\_len} - 1 - k \implies k \leftarrow \text{prev\_len} - 1 - k$.
- **Letter $c$ (Append)**: If $k == \text{prev\_len}$, then $c$ was precisely the character placed at index $k$! We immediately return $c$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - Forward pass: $\mathcal{O}(N)$ to compute length array $L$.
  - Backward pass: $\mathcal{O}(N)$ to trace index $k$.
  - Total operations $\le 2 \times 10^5$ ($< 2$ ms in C++).
- **Space Complexity:** $\mathcal{O}(N)$
  - Array $L$ of size $N$ storing `long long` lengths.

---

## 🔍 Edge Cases Considered

- **$k$ Out of Bounds ($k \ge \text{final\_len}$)**: Return `'.'`.
- **Empty Result ($L[N-1] = 0$)**: Handled by early check.
- **Consecutive Deletions on Empty String**: `curr = max(0LL, curr - 1)` ensures non-negative lengths.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
