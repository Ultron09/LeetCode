# [233. Number of Digit One](https://leetcode.com/problems/number-of-digit-one/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [Dynamic Programming (Digit DP)](../../topics/dynamic-programming.md), [Recursion](../../topics/backtracking.md)

---

## 📌 Problem Statement

Given an integer `n`, count the **total number of digit 1** appearing in all non-negative integers less than or equal to `n`.

### Example 1:
```
Input: n = 13
Output: 6
Explanation: Digit 1 occurred in the following numbers: 1, 10, 11, 12, 13 (note that 11 contains two 1s).
```

### Example 2:
```
Input: n = 0
Output: 0
```

### Constraints:
- $0 \le n \le 10^9$

---

## 💡 Intuition & Approach

### 1. Place-Value Positional Decomposition ($\mathcal{O}(\log_{10} n)$)
Rather than counting digit `1`s per integer, we count how many times digit `1` appears at **each decimal place value** $m \in \{1, 10, 100, 1000, \dots\}$.

For a fixed place value $m$ (e.g. $m=10$ for tens digit):
- $\text{higher} = \lfloor n / (10m) \rfloor$ (number of complete higher cycles)
- $\text{curr} = \lfloor n / m \rfloor \pmod{10}$ (digit at the current place)
- $\text{lower} = n \pmod m$ (trailing remainder)

### 2. Contribution Cases at Place $m$:
1. **$\text{curr} == 0$**:
   - The digit `1` occurs only in the fully completed higher cycles:
     $$\text{count} += \text{higher} \times m$$
2. **$\text{curr} == 1$**:
   - In addition to completed higher cycles, the current incomplete cycle contributes $(\text{lower} + 1)$ ones:
     $$\text{count} += \text{higher} \times m + (\text{lower} + 1)$$
3. **$\text{curr} > 1$**:
   - The current cycle has completely passed through all numbers containing `1` at place $m$:
     $$\text{count} += (\text{higher} + 1) \times m$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\log_{10} n)$ (at most $\approx 10$ loop iterations for $n \le 10^9$).
- **Space Complexity:** $\mathcal{O}(1)$ constant extra space.

---

## 🔍 Edge Cases Considered

- **$n = 0$**: Handled immediately $\implies \text{returns } 0$.
- **Single digit $n \in [1, 9]$**: Correctly yields $1$ if $n \ge 1$.
- **Upper Bound $n = 10^9$**: Handled with `long long` for $m$ to prevent 32-bit overflow when $m \times 10$ is computed.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
