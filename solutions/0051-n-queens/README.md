# [51. N-Queens](https://leetcode.com/problems/n-queens/)

**Difficulty:** `Hard`  
**Topics:** [Backtracking](../../topics/backtracking.md), [Bit Manipulation](../../topics/bit-manipulation.md), [Array](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

The **n-queens** puzzle is the problem of placing `n` queens on an `n x n` chessboard such that no two queens attack each other.

Given an integer `n`, return all distinct solutions to the **n-queens puzzle**. You may return the answer in any order.

Each solution contains a distinct board configuration of the n-queens' placement, where `'Q'` and `'.'` both indicate a queen and an empty space, respectively.

### Example 1:
```
Input: n = 4
Output: [
  [".Q..","...Q","Q...","..Q."],
  ["..Q.","Q...","...Q",".Q.."]
]
```

### Example 2:
```
Input: n = 1
Output: [["Q"]]
```

### Constraints:
- $1 \le n \le 9$

---

## 💡 Intuition & Approach

### 1. Row-by-Row Search Space Construction
Because each row must contain exactly one queen, we can recursively place a queen in row $r$ from $0$ to $n - 1$:
- For row $r$, try placing a queen in column $c \in [0, n - 1]$.
- A position $(r, c)$ is safe if and only if no existing queen shares the same column $c$, main diagonal, or anti-diagonal.

### 2. Fast $\mathcal{O}(1)$ Diagonal & Column Bitmasks
- **Column**: Identified by column index $c$.
- **Main Diagonal ($\backslash$)**: All cells on the same top-left to bottom-right diagonal share the same value of $r - c$. To map to non-negative indices:
  $$d_1 = r - c + (n - 1) \in [0, 2n - 2]$$
- **Anti-Diagonal ($/$)**: All cells on the same top-right to bottom-left diagonal share the same value of:
  $$d_2 = r + c \in [0, 2n - 2]$$
- Use integer bitmasks (`cols`, `diag1`, `diag2`) to test and set attack lines in $\mathcal{O}(1)$ time.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N!)$ (Row 0 has $N$ choices, row 1 at most $N-1$ choices, ..., upper bounded by $N!$). For $N \le 9$, runs in $< 1$ ms in C++.
- **Space Complexity:** $\mathcal{O}(N^2)$ for recursion stack and board state representation.

---

## 🔍 Edge Cases Considered

- **$N = 1$**: Handled directly $\implies [[\text{"Q"}]]$.
- **$N = 2, 3$**: No valid placements exist $\implies []$.
- **$N = 4$**: Generates 2 solutions.
- **$N = 8$**: Standard 92 valid configurations.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
