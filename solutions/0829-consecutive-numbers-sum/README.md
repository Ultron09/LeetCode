# [829. Consecutive Numbers Sum](https://leetcode.com/problems/consecutive-numbers-sum/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

Given an integer `n`, return the number of ways you can write `n` as the sum of consecutive positive integers.

### Example 1:
```
Input: n = 5
Output: 2
Explanation: 5 = 2 + 3
```

### Example 2:
```
Input: n = 9
Output: 3
Explanation: 9 = 4 + 5 = 2 + 3 + 4
```

### Example 3:
```
Input: n = 15
Output: 4
Explanation: 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
```

### Constraints:
- `1 <= n <= 10^9`

---

## 💡 Intuition & Approach

We are looking for a sequence of $k$ consecutive positive integers starting from an integer $x$ (where $x \ge 1$) that sum up to $n$.

The sum of $k$ consecutive integers starting from $x$ is:
$x + (x + 1) + (x + 2) + \dots + (x + k - 1)$

Using the arithmetic progression sum formula, this equals:
$$k \cdot x + \frac{k(k - 1)}{2} = n$$

We can isolate $x$:
$$k \cdot x = n - \frac{k(k - 1)}{2}$$

For $x$ to be a valid positive integer, two conditions must be strictly satisfied:
1. $n - \frac{k(k - 1)}{2} > 0$ (so that $x \ge 1$)
2. $\left(n - \frac{k(k - 1)}{2}\right) \pmod k == 0$ (so that $x$ is an integer)

We can iterate through possible lengths $k$ starting from $1$. We stop the iteration when $k \cdot (k - 1) / 2 \ge n$, meaning the sequence is too long and the required starting integer $x$ would be zero or negative.

### Alternative Approach (Prime Factorization):
A known number theory theorem states that the number of ways to write $n$ as a sum of consecutive positive integers is exactly equal to the number of **odd divisors** of $n$. While factoring $n$ also takes $\mathcal{O}(\sqrt{n})$ time, the arithmetic progression check is much simpler to implement and doesn't require prime factorization logic.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\sqrt{N})$ — The loop terminates when $\frac{k(k-1)}{2} \ge n$, which means $k^2 \approx 2n$, so $k$ goes up to $\approx \sqrt{2n}$. For $n = 10^9$, the loop runs at most $\approx 44,721$ times.
- **Space Complexity:** $\mathcal{O}(1)$ — Only a few primitive variables are used.

---

## 🔍 Edge Cases Considered

- **$n$ is a power of 2:** Will have only 1 way (itself) because it has no odd divisors $> 1$. Handled correctly by the equation.
- **Integer overflow:** The term $k \cdot (k-1)$ can reach $\approx 2 \times 10^9$, which flirts dangerously with the 32-bit signed integer limit ($2.14 \times 10^9$). We cast $k$ to `long long` to guarantee safety across all platforms.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
