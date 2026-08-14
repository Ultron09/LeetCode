# [878. Nth Magical Number](https://leetcode.com/problems/nth-magical-number/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [Binary Search](../../topics/binary-search.md)

---

## 📌 Problem Statement

A positive integer is magical if it is divisible by either `a` or `b`.

Given the three integers `n`, `a`, and `b`, return the `n`-th magical number. Since the answer may be very large, return it modulo `10^9 + 7`.

### Example 1:
```
Input: n = 1, a = 2, b = 3
Output: 2
```

### Example 2:
```
Input: n = 4, a = 2, b = 3
Output: 6
```

### Constraints:
- `1 <= n <= 10^9`
- `2 <= a, b <= 4 * 10^4`

---

## 💡 Intuition & Approach

1. **Monotonicity**: The number of magical numbers less than or equal to a given number $X$ is monotonically increasing as $X$ increases. This strongly implies we can use **Binary Search on Answer**.
2. **Counting Magical Numbers $\le X$**: By the Inclusion-Exclusion Principle, the number of integers in the range $[1, X]$ that are divisible by $a$ or $b$ is given by:
   $$ f(X) = \lfloor \frac{X}{a} \rfloor + \lfloor \frac{X}{b} \rfloor - \lfloor \frac{X}{\text{lcm}(a, b)} \rfloor $$
   where $\text{lcm}(a, b)$ is the least common multiple of $a$ and $b$.
3. **Binary Search Range**:
   - The smallest possible magical number is $\min(a, b)$.
   - The largest possible magical number for the $N$-th position occurs when we only consider the smaller of the two divisors. Therefore, the upper bound is $N \times \min(a, b)$.
   - Given $N \le 10^9$ and $\min(a, b) \le 40000$, the maximum value is $4 \times 10^{13}$, which fits perfectly within a 64-bit signed integer (`long long` in C++).
4. **Execution**: Perform binary search in the range $[L, R]$. For each `mid`, check if $f(mid) \ge n$. If it is, `mid` is a potential answer, so we record it and search the left half (`R = mid - 1`) to find the smallest valid $X$. Otherwise, we search the right half (`L = mid + 1`). Finally, we take the result modulo $10^9 + 7$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\log(N \cdot \min(a, b)))$ — Binary search over a range up to $4 \times 10^{13}$ takes at most around $46$ iterations. Each iteration involves simple $\mathcal{O}(1)$ arithmetic. Computing the LCM takes $\mathcal{O}(\log(\min(a, b)))$ time initially. Total time is essentially $\mathcal{O}(1)$ or extremely small constant time.
- **Space Complexity:** $\mathcal{O}(1)$ — No extra space is required, only a few variables for binary search.

---

## 🔍 Edge Cases Considered

- Extremely large values of $N$ up to $10^9$, handled by `long long` bounds without overflow.
- Modulo is only applied at the very end on the exact minimal $X$ found. Applying it during the binary search would break the monotonicity property of $f(X)$.
- Cases where $a = b$ or one is a multiple of the other are seamlessly handled by the inclusion-exclusion formula since their LCM effectively eliminates double counting properly.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
