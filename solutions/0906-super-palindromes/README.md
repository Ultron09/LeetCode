# [906. Super Palindromes](https://leetcode.com/problems/super-palindromes/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [String](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Let's say a positive integer is a **super-palindrome** if it is a palindrome, and it is also the square of a palindrome.

Given two positive integers `left` and `right` represented as strings, return the number of super-palindromes integers in the inclusive range `[left, right]`.

### Example 1:
```
Input: left = "4", right = "1000"
Output: 4
Explanation: 4, 9, 121, and 484 are superpalindromes.
Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a palindrome.
```

### Example 2:
```
Input: left = "1", right = "2"
Output: 1
```

### Constraints:
- `1 <= left.length, right.length <= 18`
- `left` and `right` consist of only digits.
- `left` and `right` cannot have leading zeros.
- `left` and `right` represent integers in the range `[1, 10^18 - 1]`.
- `left` is less than or equal to `right`.

---

## 💡 Intuition & Approach

This problem requires identifying numbers that are both palindromes themselves, and the square of a palindrome. Since `right` can be up to $10^{18}$, the square roots of these super-palindromes will be at most $\sqrt{10^{18}} = 10^9$.

If we tried to check every number up to $10^{18}$ to see if it's a super-palindrome, it would be impossible. Even checking every palindrome up to $10^9$ and squaring it is slow. 

However, we only need to construct palindromes up to $10^9$. A palindrome of length at most 9 can be fully determined by its first half (its prefix). The length of this prefix will be at most $\lceil 9 / 2 \rceil = 5$.
This means the prefixes range from $1$ to $10^5 - 1$ (around $100,000$).

### Approach
1. We can construct all possible palindromes $v$ up to $10^9$ by generating prefixes from $1$ up to $10^5$.
2. For each prefix, we construct two types of palindromes:
   - **Odd length palindromes**: The last digit of the prefix is the center. (e.g., prefix `123` $\to 12321$).
   - **Even length palindromes**: The entire prefix is mirrored. (e.g., prefix `123` $\to 123321$).
3. For each generated palindrome $v$:
   - Calculate its square $v^2$.
   - Check if $v^2$ falls within the range `[left, right]`.
   - Check if $v^2$ is also a palindrome by converting it to a string and comparing it with its reverse.
4. Count and return the number of such valid super-palindromes.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(W^{0.25} \cdot \log W)$ where $W$ is the maximum value of `right` ($10^{18}$). The square root limits palindromes to $\le 10^9$, and generating palindromes up to $10^9$ requires exploring prefixes up to $10^5 = (10^{18})^{0.25}$. For each of the $\approx 200,000$ generated numbers, we convert $v^2$ to a string of max length 18 to verify palindromicity, which takes $\mathcal{O}(\log W)$ time.
- **Space Complexity:** $\mathcal{O}(\log W)$ to store the string representations during palindrome checks.

---

## 🔍 Edge Cases Considered

- Avoiding integer overflow: Max $v$ is $10^9$, so $v^2 = 10^{18}$, which safely fits in a signed 64-bit integer (`long long` in C++).
- Values where $v^2$ exceeds `right` can simply be ignored or used to terminate the loop early.
- Very small ranges (e.g., `left = "1", right = "2"`).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
