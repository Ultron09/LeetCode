# [60. Permutation Sequence](https://leetcode.com/problems/permutation-sequence/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Backtracking](../../topics/backtracking.md), [Combinatorics](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

The set `[1, 2, 3, ..., n]` contains a total of `n!` unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for `n = 3`:
1. `"123"`
2. `"132"`
3. `"213"`
4. `"231"`
5. `"312"`
6. `"321"`

Given `n` and `k`, return the $k^{\text{th}}$ permutation sequence.

### Example 1:
```
Input: n = 3, k = 3
Output: "213"
```

### Example 2:
```
Input: n = 4, k = 9
Output: "2314"
```

### Example 3:
```
Input: n = 3, k = 1
Output: "123"
```

### Constraints:
- $1 \le n \le 9$
- $1 \le k \le n!$

---

## 💡 Intuition & Approach

### 1. Factorial Number System (Lehmer Code / Factoradic Decomposition)
Instead of generating all $n!$ permutations via backtracking ($\mathcal{O}(n!)$), we directly compute each digit in $\mathcal{O}(1)$:
- The list of $n!$ permutations is grouped into $n$ blocks of size $(n - 1)!$, each starting with a different digit in $\{1, 2, \dots, n\}$.
- By zero-indexing $k \leftarrow k - 1$:
  - The first digit is chosen at index `idx = k / (n - 1)!` from the available sorted digits.
  - Append `numbers[idx]` and remove it from `numbers`.
  - Update $k \leftarrow k \bmod (n - 1)!$.
- Repeat the process for $(n - 2)!, (n - 3)!, \dots, 1!$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$ where $N \le 9$ ($N$ steps, with array deletion taking $\mathcal{O}(N) \implies \le 81$ operations, 0 ms in C++).
- **Space Complexity:** $\mathcal{O}(N)$ auxiliary space for tracking available digits.

---

## 🔍 Edge Cases Considered

- **$N = 1$**: Handled immediately $\implies \text{"1"}$.
- **$k = 1$ (First permutation)**: Outputs `"123...n"`.
- **$k = n!$ (Last permutation)**: Correctly computes descending sequence.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
