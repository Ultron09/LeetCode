# [600. Non-negative Integers without Consecutive Ones](https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Bit Manipulation](../../topics/bit-manipulation.md)

---

## 📌 Problem Statement

Given a positive integer `n`, return the number of integers in the range $[0, n]$ whose binary representations **do not contain consecutive ones**.

### Example 1:
```
Input: n = 5
Output: 5
Explanation:
Here are the non-negative integers <= 5 with their corresponding binary representations:
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule.
```

### Example 2:
```
Input: n = 1
Output: 2
```

### Example 3:
```
Input: n = 2
Output: 3
```

### Constraints:
- $1 \le n \le 10^9$

---

## 💡 Intuition & Approach

### 1. Fibonacci Recurrence on Binary Strings
Let $f[k]$ denote the number of valid binary strings of length $k$ containing no consecutive ones (`"11"`):
- A valid $k$-bit string starting with `0` can be followed by any valid $(k - 1)$-bit string $\implies f[k - 1]$ choices.
- A valid $k$-bit string starting with `1` must be followed by `0`, and then any valid $(k - 2)$-bit string $\implies f[k - 2]$ choices.
$$\therefore f[k] = f[k - 1] + f[k - 2]$$
Base cases: $f[0] = 1$ (empty string), $f[1] = 2$ (`"0"`, `"1"`).

### 2. MSB-to-LSB Digit DP
Since $n \le 10^9 < 2^{30}$, we examine bit positions $k$ from $30$ down to $0$:
1. **If bit $k$ of $n$ is `1`**:
   - **Branch `0`**: If we place a `0` at position $k$, all numbers formed by arbitrary valid choices of the remaining $k$ bits are strictly less than $n$. We add $f[k]$ to our answer.
   - **Branch `1`**: To match $n$'s prefix, we place `1` at position $k$.
     - If the previously placed bit `prevBit == 1`, placing another `1` creates `"11"`. Since all numbers strictly smaller than $n$ have already been accounted for, and no prefix extensions can be valid, we **terminate immediately** and return `ans`.
     - Otherwise, set `prevBit = 1`.
2. **If bit $k$ of $n$ is `0`**:
   - We must place `0` to match $n$'s prefix; set `prevBit = 0`.
3. **End of Loop**:
   - If the loop finishes without an early exit, $n$ itself contains no consecutive ones, so we add `1` for $n$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\log n) = \mathcal{O}(1)$
  - Fixed scan over 31 bit positions ($k = 30 \dots 0$).
- **Space Complexity:** $\mathcal{O}(1)$
  - 32-element precomputed Fibonacci lookup table.

---

## 🔍 Edge Cases Considered

- **$N = 1$**: Handled properly; returns $2$ ($0$ and $1$).
- **Consecutive Ones in $N$ (e.g. $N = 3 \to \text{"11"}_2$)**: Early exit prevents overcounting or illegal prefix derivations.
- **Powers of 2 ($N = 2^k$)**: Handled accurately; all numbers $< 2^k$ are summed directly via $f[k]$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
