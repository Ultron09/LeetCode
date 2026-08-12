# [639. Decode Ways II](https://leetcode.com/problems/decode-ways-ii/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [String](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

A message containing letters from `A-Z` can be encoded into numbers using the following mapping:

```
'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
```

To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above.

In addition to the mapping above, an encoded message may contain the `'*'` character, which can represent any digit from `'1'` to `'9'` (`'0'` is excluded).

Given a string `s` consisting of digits and `'*'` characters, return the **number of ways to decode it**.

Since the answer may be very large, return it **modulo $10^9 + 7$**.

### Example 1:
```
Input: s = "*"
Output: 9
Explanation: The encoded message can represent any of the encoded messages "1", "2", "3", "4", "5", "6", "7", "8", or "9".
Each of these can be decoded to the strings "A", "B", "C", "D", "E", "F", "G", "H", and "I" respectively.
Hence, there are a total of 9 ways to decode "*".
```

### Example 2:
```
Input: s = "1*"
Output: 18
Explanation: The encoded message can represent any of "11", "12", "13", "14", "15", "16", "17", "18", or "19".
Each of these messages has 2 ways to decode (e.g., "11" -> "AA" or "K"). Total = 9 * 2 = 18.
```

### Example 3:
```
Input: s = "2*"
Output: 15
Explanation: "21"-"26" have 2 ways, "27"-"29" have 1 way. Total = 6*2 + 3*1 = 15.
```

### Constraints:
- $1 \le \text{s.length} \le 10^5$
- `s[i]` is a digit or `'*'`.

---

## 💡 Intuition & Approach

### 1. Second-Order Linear DP Formulation
Let $\text{dp}[i]$ be the number of ways to decode the prefix $s[0 \dots i - 1]$.
Each step $i$ can be formed either by:
1. Decoding $s[i - 1]$ as a **single character**: contributes $w_1 \times \text{dp}[i - 1]$ ways.
2. Decoding the two-character pair $s[i - 2 \dots i - 1]$ as a **two-digit number**: contributes $w_2 \times \text{dp}[i - 2]$ ways.

$$\text{dp}[i] = (w_1 \times \text{dp}[i - 1] + w_2 \times \text{dp}[i - 2]) \pmod{10^9 + 7}$$

### 2. Comprehensive Wildcard Branching Breakdown

#### A. Single-Digit Multiplier $w_1(c)$
- If $c = \text{'*'}$: Can be `'1'` through `'9'` $\implies w_1 = 9$.
- If $c \in [\text{'1'} \dots \text{'9'}]$: Exactly 1 mapping $\implies w_1 = 1$.
- If $c = \text{'0'}$: Cannot decode individually $\implies w_1 = 0$.

#### B. Two-Digit Multiplier $w_2(c_1, c_2)$
- **Both Wildcards (`**`)**:
  - `11` to `19` (9 valid numbers) + `21` to `26` (6 valid numbers) $\implies w_2 = 15$.
- **First Wildcard (`*d`)**:
  - If $d \in [\text{'0'} \dots \text{'6'}]$: Can form `1d` and `2d` (e.g. `10, 20` or `16, 26`) $\implies w_2 = 2$.
  - If $d \in [\text{'7'} \dots \text{'9'}]$: Can only form `1d` (`17, 18, 19`) $\implies w_2 = 1$.
- **Second Wildcard (`d*`)**:
  - If $d = \text{'1'}$: Can form `11` to `19` $\implies w_2 = 9$.
  - If $d = \text{'2'}$: Can form `21` to `26` $\implies w_2 = 6$.
  - Other digits: Cannot form any number in $[10, 26]$ $\implies w_2 = 0$.
- **Both Digits (`d1 d2`)**:
  - Value $\text{val} = 10 \times d_1 + d_2 \in [10, 26] \implies w_2 = 1$; otherwise $w_2 = 0$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - Single pass through string of length $N \le 10^5$, with $\mathcal{O}(1)$ branch evaluations per character.
- **Space Complexity:** $\mathcal{O}(1)$
  - Constant memory tracking only `dp0` ($\text{dp}[i - 2]$) and `dp1` ($\text{dp}[i - 1]$).

---

## 🔍 Edge Cases Considered

- **Leading `'0'`**: `s[0] == '0'` immediately produces 0 ways.
- **Un-decodable Sequences**: Sequences like `"30"` or `"70"` correctly evaluate to 0 ways.
- **Max Modulo Arithmetic**: All multiplications and additions use `long long` with modulo $10^9 + 7$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
