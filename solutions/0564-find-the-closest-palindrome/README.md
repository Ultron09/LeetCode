# [564. Find the Closest Palindrome](https://leetcode.com/problems/find-the-closest-palindrome/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [String](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

Given a string `n` representing an integer, return the **closest integer (not including itself)**, which is a palindrome. If there is a tie, return the **smaller one**.

The closest is defined as the absolute difference minimized between two integers.

### Example 1:
```
Input: n = "123"
Output: "121"
```

### Example 2:
```
Input: n = "1"
Output: "0"
Explanation: 0 and 2 are the closest palindromes but we return the smallest which is 0.
```

### Constraints:
- $1 \le n.\text{length} \le 18$
- `n` consists of only digits.
- `n` does not have leading zeros.
- `n` represents an integer in the range $[1, 10^{18} - 1]$.

---

## 💡 Intuition & Approach

### 1. The 5-Candidate Family Theorem
For any decimal integer $N$ of length $L$, the closest palindrome to $N$ (excluding $N$ itself) is guaranteed to belong to one of 5 canonical candidates:

1. **Prefix Reflection ($\text{prefix}$)**:
   Extract the left half prefix of length $\lceil L / 2 \rceil = (L + 1) / 2$, and mirror it to form a palindrome of length $L$.
2. **Prefix Decrement ($\text{prefix} - 1$)**:
   Decrement the prefix by 1 and mirror it (capturing cases where rounding down yields the closest palindrome).
3. **Prefix Increment ($\text{prefix} + 1$)**:
   Increment the prefix by 1 and mirror it (capturing cases where rounding up yields the closest palindrome).
4. **Lower Boundary Transition ($10^{L-1} - 1$)**:
   The largest palindrome with $L - 1$ digits (e.g. `99...9`). Essential when $N$ is of the form $100\dots0$ or $100\dots1$.
5. **Upper Boundary Transition ($10^L + 1$)**:
   The smallest palindrome with $L + 1$ digits (e.g. `100...001`). Essential when $N$ is of the form $999\dots9$.

### 2. Selection & Tie-Breaking
1. Exclude the candidate identical to $N$.
2. Compute the absolute distance $|C - N|$ for each valid candidate $C$.
3. Choose the candidate with minimal $|C - N|$.
4. If multiple candidates achieve the same minimal distance, pick the smaller numerical value.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(L)$
  - Generating and mirroring 5 strings of length $L \le 18$ takes $\mathcal{O}(L)$ time.
  - Overall execution time is $< 1\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(L)$
  - Space to store candidate integers and prefix substrings.

---

## 🔍 Edge Cases Considered

- **Single Digit ($N = 1 \dots 9$)**: Correctly returns $N - 1$.
- **Powers of 10 (`"10" -> "9"`, `"100" -> "99"`, `"1000" -> "999"`)**: Evaluated accurately via boundary candidate $10^{L-1} - 1$.
- **All 9s (`"99" -> "101"`, `"999" -> "1001"`)**: Evaluated accurately via boundary candidate $10^L + 1$.
- **Large 18-digit Integers ($\le 10^{18} - 1$)**: Full arithmetic fits safely in 64-bit `long long`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
