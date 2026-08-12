# [679. 24 Game](https://leetcode.com/problems/24-game/)

**Difficulty:** `Hard`  
**Topics:** [Backtracking](../../topics/backtracking.md), [Math & Geometry](../../topics/math-and-geometry.md), [Array](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an integer array `cards` of length 4. You have four cards, each containing a number in the range `[1, 9]`. You should arrange the numbers on these cards in a mathematical expression using the operators `['+', '-', '*', '/']` and the parentheses `'('` and `')'` to get the value `24`.

You are restricted with the following rules:
- The division operator `/` represents **real division**, not integer division (e.g., $4 / (1 - 2 / 3) = 4 / (1/3) = 12$).
- Every operation is done between two numbers. Unary minus is not allowed.
- You cannot concatenate numbers together (e.g., `12 + 12` is invalid).

Return `true` if you can get such expression that evaluates to `24`, and `false` otherwise.

### Example 1:
```
Input: cards = [4,1,8,7]
Output: true
Explanation: (8-4) * (7-1) = 24
```

### Example 2:
```
Input: cards = [1,2,1,2]
Output: false
```

### Constraints:
- `cards.length == 4`
- $1 \le \text{cards}[i] \le 9$

---

## 💡 Intuition & Approach

### 1. Recursive Pairwise Reduction
Every valid mathematical expression on 4 numbers corresponds to a full binary expression tree with 3 operator nodes. At each stage:
1. Select any two distinct numbers $a$ and $b$ from the current pool of operands.
2. Form all valid binary operations between them:
   $$a + b, \quad a - b, \quad a \times b, \quad \frac{a}{b} \ (b \neq 0)$$
3. Replace the pair $(a, b)$ with the computed result, reducing the pool size by $1$ ($4 \to 3 \to 2 \to 1$).
4. Recursively repeat the reduction until only $1$ scalar value remains.

### 2. Floating-Point Tolerance ($\epsilon$)
Because intermediate division generates real numbers (e.g. $8 / (3 - 8/3) = 24$), operations must be performed using `double`. To avoid floating-point rounding errors when checking if the final result equals $24$, we use an epsilon threshold:
$$|\text{result} - 24.0| < 10^{-6}$$

### 3. Exhaustive State Space Bounding
- Stage 1 (4 numbers): $\binom{4}{2} = 6$ pairs $\times 6$ operations $= 36$ branches.
- Stage 2 (3 numbers): $\binom{3}{2} = 3$ pairs $\times 6$ operations $= 18$ branches.
- Stage 3 (2 numbers): $\binom{2}{2} = 1$ pair $\times 6$ operations $= 6$ branches.
- Total maximum function calls $\le 36 \times 18 \times 6 = 3888 \implies \mathcal{O}(1)$ execution time.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(1)$
  - Bounded by at most $\approx 3888$ recursive evaluations, completing in $< 1\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(1)$
  - Maximum recursion call stack depth of 4.

---

## 🔍 Edge Cases Considered

- **Fractional Intermediate Values**: Cases like `[3, 3, 8, 8]` $\to 8 / (3 - 8/3) = 24$ and `[1, 3, 4, 6]` $\to 6 / (1 - 3/4) = 24$ correctly handled via floating-point division.
- **Division by Zero**: Guarded by `fabs(b) > 1e-6` before division.
- **Precision Guard**: Epsilon tolerance `1e-6` ensures exact matching despite floating-point drift.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
