# [479. Largest Palindrome Product](https://leetcode.com/problems/largest-palindrome-product/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

Given an integer `n`, return the largest palindromic integer that can be represented as the product of two `n`-digits integers. Since the answer can be very large, return it **modulo 1337**.

### Example 1:
```
Input: n = 2
Output: 987
Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
```

### Example 2:
```
Input: n = 1
Output: 9
Explanation: 9 = 9 x 1 or 3 x 3
```

### Constraints:
- $1 \le n \le 8$

---

## 💡 Intuition & Approach

### 1. Palindrome Generation via Upper-Half Mirroring
For $n = 1$, the largest single-digit product is $9$.

For $n \ge 2$, the product of two $n$-digit integers (in range $[10^{n-1}, 10^n - 1]$) has at most $2n$ digits. There always exists a $2n$-digit palindrome that factorizes into two $n$-digit numbers.

Rather than multiplying every pair of $n$-digit numbers $(\mathcal{O}(10^{2n}))$ and testing for palindromes:
1. Generate candidate $2n$-digit palindromes in **strictly decreasing order** by taking an $n$-digit upper half $H \in [10^n - 1, 10^{n-1}]$ and appending its reverse:
   $$P = H \times 10^n + \text{reverse}(H)$$
2. For each candidate palindrome $P$, check whether it can be factored as $P = x \times y$, where both $x$ and $y$ are $n$-digit integers.

### 2. Efficient Factor Search with Early Pruning
To find if $P = x \cdot y$:
- Iterate $x$ downwards from $\text{upper} = 10^n - 1$ down to $\lceil \sqrt{P} \rceil$:
- **Early Exit Criterion**: If $x \times x < P$, any further decrease in $x$ would require $y = P / x > x$, which would have already been considered in an earlier iteration. We can break immediately.
- If $P \pmod x == 0$:
  - $y = P / x$.
  - Because $x \ge \sqrt{P}$, $y \le \sqrt{P} \le 10^n - 1$.
  - Because $P > 10^{2n-1}$ and $x < 10^n$, $y > 10^{n-1}$.
  - Thus $y$ is guaranteed to be an $n$-digit number.
  - The first such palindrome $P$ found is guaranteed to be the largest possible. Return $P \pmod{1337}$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(10^n)$ worst case, but practically near $\mathcal{O}(1)$
  - For each $n \in [1, 8]$, the largest palindromic product lies very close to $(10^n - 1)^2$.
  - Only a few candidate upper halves $H$ and a small number of divisors $x$ are examined before a valid pair is found.
  - Entire function executes in $< 1\text{ ms}$ across all $n \le 8$.
- **Space Complexity:** $\mathcal{O}(1)$
  - Generates mirrored numbers using standard 64-bit integers (`long long`). Max value for $n = 8$ is $< 10^{16} < 2^{63} - 1$.

---

## 🔍 Edge Cases Considered

- **$n = 1$**: Handled as a base case returning $9$ (since $9$ is odd-length).
- **64-bit Integer Precision**: Palindromes for $n = 8$ reach $\approx 10^{16}$, fitting within standard 64-bit signed integers without overflow.
- **Divisibility Modulo 1337**: Modulo arithmetic is applied only at the very end on the final verified palindrome $P$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
