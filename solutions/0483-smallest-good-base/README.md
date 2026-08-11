# [483. Smallest Good Base](https://leetcode.com/problems/smallest-good-base/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Binary Search](../../topics/binary-search.md)

---

## 📌 Problem Statement

Given an integer `n` represented as a string, return the **smallest good base** of `n`.

We call $k \ge 2$ a **good base** of $n$, if all digits of $n$ in base $k$ are `1`'s.

### Example 1:
```
Input: n = "13"
Output: "3"
Explanation: 13 base 3 is 111 (1 + 3 + 9 = 13).
```

### Example 2:
```
Input: n = "4681"
Output: "8"
Explanation: 4681 base 8 is 11111 (1 + 8 + 64 + 512 + 4096 = 4681).
```

### Example 3:
```
Input: n = "1000000000000000000"
Output: "999999999999999999"
Explanation: 1000000000000000000 base 999999999999999999 is 11 (1 + 999999999999999999 = 1000000000000000000).
```

### Constraints:
- $n$ is an integer in the range $[3, 10^{18}]$.
- $n$ does not contain any leading zeros.

---

## 💡 Intuition & Approach

### 1. Geometric Series Formulation
An integer $n$ in base $k \ge 2$ has all $1$'s of length $m$ if:
$$n = 1 + k + k^2 + \dots + k^{m-1} = \frac{k^m - 1}{k - 1}$$
where $m$ is the number of digits in base $k$ ($m \ge 2$).

- For a fixed $n$, the base $k$ and the length $m$ are **inversely related**: maximizing $m$ minimizes $k$.
- Therefore, to find the **smallest base $k$**, we iterate the length $m$ in **strictly descending order** from $\lfloor \log_2(n) \rfloor + 1$ down to $2$.

### 2. Search Range & Candidate Root
- **Maximum $m$**: When $k = 2$, $n \ge 2^m - 1 \implies m \le \lfloor \log_2(n) \rfloor + 1 \le 60$.
- **Minimum $m$**: $m = 2 \implies n = 1 + k \implies k = n - 1$. This is always a valid base ("11"), serving as the guaranteed fallback.
- **Direct Root Approximation**: By binomial expansion:
  $$k^{m-1} < 1 + k + \dots + k^{m-1} = n < (k + 1)^{m-1}$$
  Taking $(m-1)$-th roots yields $k < \sqrt[m-1]{n} < k + 1 \implies k = \lfloor n^{1/(m-1)} \rfloor$.
  Testing $k - 1, k, k + 1$ with Horner's evaluation rigorously checks if $\sum_{i=0}^{m-1} k^i = n$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}((\log_2 n)^2)$
  - $m$ ranges from $\approx 60$ down to $3$ (at most $60$ outer iterations).
  - For each $m$, evaluating the polynomial of degree $m$ using Horner's method takes $\mathcal{O}(m)$ operations.
  - Total operations $\le 60 \times 3 \times 60 \approx 10^4$ (executes in $< 1\text{ ms}$).
- **Space Complexity:** $\mathcal{O}(1)$
  - Constant auxiliary space using 64-bit unsigned integer arithmetic.

---

## 🔍 Edge Cases Considered

- **$n = 3$**: Minimum boundary input, correctly resolves to base $2$ ("11").
- **Mersenne Numbers ($n = 2^p - 1$)**: Immediately identifies base $k = 2$.
- **Large Prime Numbers / Non-decomposable**: Gracefully falls back to $m = 2$, returning $n - 1$.
- **64-bit Integer Overflow**: Guarded during Horner's accumulation using `sum > (n - 1) / candK`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
