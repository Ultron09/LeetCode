# [793. Preimage Size of Factorial Zeroes Function](https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Binary Search](../../topics/binary-search.md)

---

## 📌 Problem Statement

Let `f(x)` be the number of zeroes at the end of `x!`. Recall that `x! = 1 * 2 * 3 * ... * x` and by convention, `0! = 1`.

For example, `f(3) = 0` because `3! = 6` has no zeroes at the end, while `f(11) = 2` because `11! = 39916800` has two zeroes at the end.
Given an integer `k`, return the number of non-negative integers `x` have the property that `f(x) = k`.

### Example 1:
```
Input: k = 0
Output: 5
Explanation: 0!, 1!, 2!, 3!, and 4! end with k = 0 zeroes.
```

### Example 2:
```
Input: k = 5
Output: 0
Explanation: There is no x such that x! ends in k = 5 zeroes.
```

### Constraints:
- `0 <= k <= 10^9`

---

## 💡 Intuition & Approach

The number of trailing zeroes in `x!` is determined by the number of times `10` divides `x!`. Since $10 = 2 \times 5$, and there are always more factors of $2$ than $5$ in factorials, we just need to count the factors of $5$.
By **Legendre's Formula**, the number of trailing zeroes is:
$f(x) = \lfloor x/5 \rfloor + \lfloor x/25 \rfloor + \lfloor x/125 \rfloor + \dots$

### Key Observations:
1. $f(x)$ is a **monotonically non-decreasing function**. As $x$ increases, $f(x)$ either stays the same or increases.
2. The factorial $x!$ only gains new factors of 5 when $x$ is a multiple of 5. Thus, for any $x$ that is a multiple of 5, the numbers $x, x+1, x+2, x+3, x+4$ will all have the exact same number of trailing zeroes.
3. This implies that if a target $k$ is reachable, it will always be reachable by exactly a block of **5** numbers.
4. However, when $x$ is a multiple of 25 (or 125, etc.), $x!$ gains *multiple* factors of 5 at once. This causes $f(x)$ to "jump" by more than 1. This jump means certain values of $k$ (like $k=5$) are skipped entirely.
5. Therefore, the answer for any $k$ will **always be either 5 or 0**.

### Algorithm: Binary Search
Since $f(x)$ is monotonic, we can use binary search to find if there is any $x$ such that $f(x) = k$.
- **Lower bound:** $0$
- **Upper bound:** $5(k + 1)$ (Since $f(x) \ge \lfloor x/5 \rfloor$, $x$ cannot be larger than $5k+5$).

If our binary search finds a match, we return `5`. Otherwise, we return `0`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\log^2 K)$ — The binary search space is up to $5 \times 10^9$, requiring about $\approx 33$ iterations. In each iteration, computing $f(x)$ takes $\mathcal{O}(\log_5 x) \approx 14$ iterations. Thus, it's extremely fast.
- **Space Complexity:** $\mathcal{O}(1)$ — No extra space is required.

---

## 🔍 Edge Cases Considered

- **$k=0$**: Properly handled. Searching in $[0, 5]$ will find $x=0$, $f(0)=0 \implies$ returns 5.
- **Skipped values (e.g., $k=5$)**: The binary search will miss 5 because $f(24) = 4$ and $f(25) = 6$. It correctly returns 0.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
