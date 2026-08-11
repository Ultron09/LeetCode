# [214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/)

**Difficulty:** `Hard`  
**Topics:** [String](../../topics/sliding-window.md), [String Matching (KMP)](../../topics/sliding-window.md), [Rolling Hash](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

You are given a string `s`. You can convert `s` to a palindrome by adding characters **in front of it**.

Return the **shortest palindrome** you can find by performing this transformation.

### Example 1:
```
Input: s = "aacecaaa"
Output: "aaacecaaa"
```

### Example 2:
```
Input: s = "abcd"
Output: "dcbabcd"
```

### Constraints:
- $0 \le \text{s.length} \le 5 \times 10^4$
- `s` consists of lowercase English letters only.

---

## 💡 Intuition & Approach

### 1. Problem Equivalence: Longest Palindromic Prefix
Adding the minimum number of characters to the front of $s$ is equivalent to finding the **longest prefix of $s$ that is already a palindrome**.
- If the longest palindromic prefix has length $L$, then the remaining suffix $s[L \dots |s|-1]$ is the only part that lacks a symmetric mirror.
- Reversing this suffix and prepending it to $s$ yields the shortest possible palindrome:
  $$\text{result} = \text{reverse}(s[L \dots |s|-1]) + s$$

### 2. Linear Identification via KMP $\pi$ Table
To find $L$ in $\mathcal{O}(N)$ deterministic time:
1. Form the combined string $T = s + '\#' + \text{reverse}(s)$ where `'#'` is a unique delimiter not present in $s$.
2. Compute the KMP Prefix Function ($\pi$ array / LPS table) for $T$:
   - $\pi[i]$ denotes the length of the longest proper prefix of $T$ that matches a suffix of $T[0 \dots i]$.
3. Since $T$ ends with $\text{reverse}(s)$, the final entry $\pi[|T|-1]$ directly gives the length of the longest prefix of $s$ that matches a suffix of $\text{reverse}(s)$ (i.e. is identical to its own reverse).
4. Hence, $L = \pi[|T|-1]$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N = |s| \le 5 \times 10^4$ (linear KMP preprocessing of string of length $2N + 1$).
- **Space Complexity:** $\mathcal{O}(N)$ auxiliary memory for the combined string and $\pi$ table.

---

## 🔍 Edge Cases Considered

- **Empty String** (`""`): Handled $\implies \text{returns } ""$.
- **Already a Palindrome** (e.g. `"abacaba"`): $L = |s|$, zero characters prepended $\implies \text{returns } s$.
- **No Symmetric Characters** (e.g. `"abcd"`): $L = 1$, prepends `"dcb"` $\implies \text{returns "dcbabcd"}$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
