# [902. Numbers At Most N Given Digit Set](https://leetcode.com/problems/numbers-at-most-n-given-digit-set/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

Given an array of `digits` which is sorted in non-decreasing order. You can write numbers using each `digits[i]` as many times as we want.

Return the number of positive integers that can be generated that are less than or equal to a given integer `n`.

### Example 1:
```
Input: digits = ["1","3","5","7"], n = 100
Output: 20
Explanation: 
The 20 numbers that can be written are:
1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
```

### Example 2:
```
Input: digits = ["1","4","9"], n = 1000000000
Output: 29523
Explanation: 
We can write 3 one digit numbers, 9 two digit numbers, 27 three digit numbers,
81 four digit numbers, 243 five digit numbers, 729 six digit numbers,
2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine digit numbers.
In total, this is 29523 integers that can be written using the digits array.
```

### Constraints:
- `1 <= digits.length <= 9`
- `digits[i].length == 1`
- `digits[i]` is a digit from `'1'` to `'9'`.
- All the values in `digits` are unique.
- `digits` is sorted in non-decreasing order.
- `1 <= n <= 10^9`

---

## 💡 Intuition & Approach

This problem is a classic Digit DP / Combinatorics problem. We can break it into two distinct parts. Let $K$ be the number of digits in $N$, and $D$ be the number of allowed digits.

1. **Numbers with fewer than $K$ digits:**
   - Any number formed using the given digits with a length strictly less than $K$ will be strictly smaller than $N$.
   - For length $i$, since we have $D$ choices for each position, we can form $D^i$ numbers.
   - We simply sum $D^i$ for all $1 \le i < K$.

2. **Numbers with exactly $K$ digits:**
   - We compare digit by digit from left to right with the string representation of $N$, let's call it $S$.
   - For a digit $d$ in `digits`:
     - If $d < S[i]$, we can place $d$ at index $i$, and all remaining $K - 1 - i$ positions can be any of the $D$ digits. So we add $D^{K - 1 - i}$ to our answer.
     - If $d == S[i]$, we can potentially place $d$ at index $i$, but we are restricted by the subsequent digits of $N$. We record this possibility (`hasSameNum = true`) and continue to the next position $i+1$.
     - If no $d$ equals $S[i]$, it means we cannot match the prefix of $N$ perfectly. Any number formed must deviate and be smaller at some earlier index. We stop searching further.
   - If we successfully match all $K$ digits of $N$ (the loop finishes completely), it means $N$ itself is a valid number, so we add $1$ to the final answer.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\log_{10} N \cdot D)$. Let $K = \log_{10} N$ (the number of digits in $N$). We iterate through the $K$ digits of $N$, and for each digit we iterate through the $D$ allowed digits. Since $D \le 9$, this simplifies to $\mathcal{O}(\log_{10} N)$.
- **Space Complexity:** $\mathcal{O}(\log_{10} N)$ to store the string representation of $N$.

---

## 🔍 Edge Cases Considered

- $N$ contains digits that are not in the given `digits` set.
- All numbers formed are strictly shorter than $N$.
- The number $N$ itself is formed completely by the `digits` set.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
