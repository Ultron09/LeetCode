# [664. Strange Printer](https://leetcode.com/problems/strange-printer/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [String](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

There is a strange printer with the following two special properties:
1. The printer can only print a sequence of the same character each time.
2. At each turn, the printer can print new characters starting from and ending at any place and will cover the original existing characters.

Given a string `s`, return the **minimum number of turns** the printer needed to print it.

### Example 1:
```
Input: s = "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".
```

### Example 2:
```
Input: s = "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.
```

### Constraints:
- $1 \le \text{s.length} \le 100$
- `s` consists of lowercase English letters.

---

## 💡 Intuition & Approach

### 1. Preprocessing / String Compression
Consecutive identical characters require no additional turns since a printer turn prints a continuous span of the same letter. We compress runs of identical characters into a single representative character (e.g. `"aaabbb"` $\to$ `"ab"`), resulting in an effective length $N \le 100$.

### 2. Interval DP Formulation
Let $\text{dp}[i][j]$ be the minimum number of turns needed to print the compressed substring $s[i \dots j]$.

- **Base Case**: Single character substrings require 1 turn:
  $$\text{dp}[i][i] = 1 \quad (\forall i)$$

- **Baseline Transition**: We can always print $s[j]$ in a separate new turn after printing $s[i \dots j - 1]$:
  $$\text{dp}[i][j] = \text{dp}[i][j - 1] + 1$$

- **Overwrite Optimization**:
  If there exists an index $k \in [i, j - 1]$ such that $s[k] == s[j]$:
  - When the printer laid down character $s[k]$, it could have extended that print turn all the way to index $j$, covering $s[j]$ **for free**.
  - Any mismatched characters in the interval $[k + 1 \dots j - 1]$ can be printed over this background later.
  - Therefore, we can split at $k$:
    $$\text{dp}[i][j] = \min_{k=i}^{j-1} \left( \text{dp}[i][k] + (\text{dp}[k + 1][j - 1] \text{ if } k + 1 \le j - 1 \text{ else } 0) \right) \quad \text{where } s[k] == s[j]$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^3)$
  - There are $\mathcal{O}(N^2)$ intervals $[i, j]$.
  - Each interval explores $\mathcal{O}(N)$ split points $k$.
  - With $N \le 100$, operations $\approx \frac{100^3}{6} \approx 1.6 \times 10^5 \implies < 2\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(N^2)$
  - Table of size $N \times N$ to store subproblem answers.

---

## 🔍 Edge Cases Considered

- **Single Character ($N = 1$)**: Handled by base case $\text{dp}[0][0] = 1$.
- **All Identical Characters (`"aaaaa"`)**: Compressed to `"a"`, evaluates in 1 turn.
- **Palindromic Structures (`"abacaba"`)**: Multiple matching split points evaluated optimally via `min`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
