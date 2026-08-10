# [3348. Smallest Divisible Digit Product II](https://leetcode.com/problems/smallest-divisible-digit-product-ii/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Dynamic Programming](../../topics/dynamic-programming.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

You are given a string `num` which represents a positive integer, and an integer `t`.

A number is called **zero-free** if none of its digits are `0`.

Return a string representing the **smallest zero-free number greater than or equal to `num`** such that the product of its digits is divisible by `t`. If no such number exists, return `"-1"`.

### Example 1:
```
Input: num = "1234", t = 256
Output: "1488"
Explanation:
The smallest zero-free number that is >= 1234 and has digit product divisible by 256 is 1488 (1 * 4 * 8 * 8 = 256).
```

### Example 2:
```
Input: num = "12355", t = 50
Output: "12355"
Explanation:
12355 is already zero-free and has digit product divisible by 50 (1 * 2 * 3 * 5 * 5 = 150 = 3 * 50).
```

### Example 3:
```
Input: num = "11111", t = 26
Output: "-1"
Explanation:
26 has prime factor 13. Since single digits 1-9 have prime factors in {2, 3, 5, 7}, no product of non-zero digits can be divisible by 26.
```

### Constraints:
- $2 \le \text{num.length} \le 2 \times 10^5$
- `num` consists only of digits in the range `['0', '9']`.
- `num` does not contain leading zeros.
- $1 \le t \le 10^{14}$

---

## 💡 Intuition & Approach

### 1. Prime Factorization Feasibility Check
Non-zero single digits $d \in [1, 9]$ only decompose into prime factors $\{2, 3, 5, 7\}$:
- $2 = 2^1$
- $3 = 3^1$
- $4 = 2^2$
- $5 = 5^1$
- $6 = 2^1 \cdot 3^1$
- $7 = 7^1$
- $8 = 2^3$
- $9 = 3^2$

If $t$ has any prime factor $> 7$ (e.g. 11, 13, 17, 19, ...), it is impossible to form any product divisible by $t$. In this case, immediately return `"-1"`.

Otherwise, we factorize $t = 2^a \cdot 3^b \cdot 5^c \cdot 7^d$. Since $t \le 10^{14}$, the prime powers are small ($a \le 47, b \le 30, c \le 20, d \le 17$).

### 2. Precomputing Minimum Digits (`DP`)
- Powers of $5$ and $7$ are independent and can only be satisfied by digits `'5'` and `'7'` respectively. Thus, they require $c$ and $d$ digits.
- For powers of $2$ and $3$, we precompute $DP[i][j]$: the minimum number of digits from $\{2, 3, 4, 6, 8, 9\}$ required to contribute at least $i$ factors of $2$ and $j$ factors of $3$.
$$\text{minDigits}(a, b, c, d) = DP[\max(0, a)][\max(0, b)] + \max(0, c) + \max(0, d)$$

### 3. Prefix Matching & Greedy Suffix Construction
Let $N = \text{num.length}$.
1. **Zero-Free Prefix Check**: If `num` contains `'0'`, any valid number matching a prefix of `num` cannot extend past the first `'0'`. Let `first_zero` be the index of the first `'0'`.
2. **Check if `num` is directly valid**: If `num` has no zeros and its digit product satisfies the required prime powers, return `num`.
3. **Try Prefix of Length $i$ ($first\_zero \ge i \ge 0$)**:
   - At index $i$, pick a replacement digit $D > \text{num}[i]$ (or $D \ge 1$ if `num[i] == '0'`).
   - The remaining suffix length is $L = N - 1 - i$.
   - Calculate remaining required prime powers $(rem_a, rem_b, rem_c, rem_d)$.
   - If $L \ge \text{minDigits}(rem_a, rem_b, rem_c, rem_d)$, we found the optimal length-$N$ answer!
4. **Lexicographically Smallest Suffix Construction**:
   - Fill excess length $L - \text{minDigits}$ with `'1'`s.
   - For the remaining positions, greedily try digits $d \in [1, 9]$ in increasing order and select the first digit that leaves enough remaining length to fulfill the rest of the prime powers.
5. **Length Expansion ($> N$)**: If no length-$N$ candidate exists, the answer has length $L_{ans} = \max(N + 1, \text{minDigits}(a, b, c, d))$ filled via the same suffix builder.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N + \log t + \text{MAX\_A} \times \text{MAX\_B})$
  - Factoring $t$: $\mathcal{O}(\log t) \approx 47$ operations.
  - DP precomputation: $60 \times 40 \times 6 \approx 1.4 \times 10^4$ operations ($< 1$ ms).
  - Prefix scans & greedy suffix reconstruction: $\mathcal{O}(N)$.
  - Total time is $\mathcal{O}(N)$, completing well within 15 ms for $N = 2 \times 10^5$.
- **Space Complexity:** $\mathcal{O}(N)$ to store prefix prime counts and the constructed output string.

---

## 🔍 Edge Cases Considered

- **Prime factors $> 7$ in $t$**: Correctly returns `"-1"`.
- **`t = 1`**: Requires no prime factors; simply returns the smallest zero-free number $\ge \text{num}$.
- **Zeros in `num`**: Cannot match prefixes past the first zero; smoothly replaces the zero with $\ge 1$.
- **Number of digits expands ($> N$)**: Handled by length expansion to $N+1$ or $\text{minDigits}$.
- **Large $N$ ($2 \times 10^5$)**: Suffix building pads `'1'`s in $\mathcal{O}(1)$ without per-digit loops for high performance.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
