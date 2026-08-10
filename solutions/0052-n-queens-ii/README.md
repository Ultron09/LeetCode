# [52. N-Queens II](https://leetcode.com/problems/n-queens-ii/)

**Difficulty:** `Hard`  
**Topics:** [Backtracking](../../topics/backtracking.md), [Bit Manipulation](../../topics/bit-manipulation.md)

---

## 📌 Problem Statement

The **n-queens** puzzle is the problem of placing `n` queens on an `n x n` chessboard such that no two queens attack each other.

Given an integer `n`, return the **number of distinct solutions** to the n-queens puzzle.

### Example 1:
```
Input: n = 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle.
```

### Example 2:
```
Input: n = 1
Output: 1
```

### Constraints:
- $1 \le n \le 9$

---

## 💡 Intuition & Approach

### 1. Shift-Register Bitmask DFS
Since we only need to count valid configurations rather than formatting string boards, we can use an ultra-fast bitwise DFS where the state across rows is propagated via bit-shifts:
- `cols`: Bitmask of occupied columns.
- `diag1`: Bitmask of main diagonal attack paths, shifted left by 1 for the next row: `(diag1 | p) << 1`.
- `diag2`: Bitmask of anti-diagonal attack paths, shifted right by 1 for the next row: `(diag2 | p) >> 1`.

### 2. Available Positions in $\mathcal{O}(1)$
At each row:
$$\text{available} = ((1 \ll n) - 1) \ \& \ \sim(\text{cols} \mid \text{diag1} \mid \text{diag2})$$
Iterate available bits by extracting least significant bit $p = \text{available} \ \& \ -\text{available}$ until $\text{available} = 0$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N!)$ (for $N \le 9$, computes solution counts in 0 ms in C++).
- **Space Complexity:** $\mathcal{O}(N)$ recursion stack depth.

---

## 🔍 Edge Cases Considered

- **$N = 1$**: Exactly 1 solution.
- **$N = 2, 3$**: Exactly 0 solutions.
- **$N = 4 \dots 9$**: Benchmark values 2, 10, 4, 40, 92, 352 verified.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
