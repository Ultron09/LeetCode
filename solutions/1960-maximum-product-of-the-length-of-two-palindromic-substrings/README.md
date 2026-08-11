# [1960. Maximum Product of the Length of Two Palindromic Substrings](https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/)

**Difficulty:** `Hard`  
**Topics:** [Sliding Window](../../topics/sliding-window.md), [Two Pointers](../../topics/two-pointers.md), [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

You are given a 0-indexed string `s` and are tasked with finding two **non-intersecting palindromic substrings of odd length** such that the product of their lengths is maximized.

More formally, you want to choose four integers $i, j, k, l$ such that:
- $0 \le i \le j < k \le l < s.\text{length}$
- Both substrings $s[i \dots j]$ and $s[k \dots l]$ are palindromes and have **odd lengths**.

Return the **maximum possible product** of the lengths of the two non-intersecting palindromic substrings.

### Example 1:
```
Input: s = "ababbb"
Output: 9
Explanation: Substrings "aba" and "bbb" are palindromes with odd length. product = 3 * 3 = 9.
```

### Example 2:
```
Input: s = "zaaaxbbby"
Output: 9
Explanation: Substrings "aaa" and "bbb" are palindromes with odd length. product = 3 * 3 = 9.
```

### Constraints:
- $2 \le s.\text{length} \le 10^5$
- `s` consists of lowercase English letters.

---

## 💡 Intuition & Approach

### 1. Problem Decomposition via Prefix and Suffix Max
To maximize $(j - i + 1) \times (l - k + 1)$ with non-intersecting constraint $j < k$, we can define a partition boundary $t \in [0, N-2]$:
- $\text{leftMax}[t]$: maximum length of an odd-length palindrome contained entirely within prefix $s[0 \dots t]$.
- $\text{rightMax}[t+1]$: maximum length of an odd-length palindrome contained entirely within suffix $s[t+1 \dots N-1]$.
- Overall Answer:
  $$\max_{0 \le t < N-1} \left(\text{leftMax}[t] \times \text{rightMax}[t+1]\right)$$

### 2. Linear Palindrome Radii via Manacher's Algorithm
Using standard Manacher's algorithm for odd palindromes, compute $P[i]$ = radius of the longest odd-length palindrome centered at index $i$ in $\mathcal{O}(N)$ time:
- Substring $s[i - P[i] \dots i + P[i]]$ is a palindrome of length $2P[i] + 1$.

### 3. Monotonic Queue for Prefix/Suffix Extension
To compute $\text{leftMax}[e]$ (max odd palindrome ending at or before $e$):
- Any odd palindrome ending at $e$ with center $c$ has length $2(e - c) + 1$, where $c \le e \le c + P[c]$.
- To maximize $2(e - c) + 1$, we must find the **smallest center $c$** that can reach $e$ ($c + P[c] \ge e$).
- As $e$ increases from $0$ to $N-1$:
  - Push centers $c \le e$ into a FIFO queue `q`.
  - Pop expired centers from the front of `q` where $c + P[c] < e$.
  - The front of `q` gives the minimal valid center $c$, yielding maximum length ending at $e$: $2(e - q.\text{front}()) + 1$.
  - Propagate prefix maximum: $\text{leftMax}[e] = \max(\text{leftMax}[e-1], \text{length ending at } e)$.

A symmetric scan from $N-1$ down to $0$ computes $\text{rightMax}[start]$ in identical $\mathcal{O}(N)$ time.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - Manacher's algorithm runs in $\mathcal{O}(N)$.
  - Each center is pushed into and popped from the monotonic deque at most once across the prefix and suffix scans ($\mathcal{O}(N)$ total queue operations).
  - With $N \le 10^5$, total execution time is $< 20\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(N)$
  - Storing array $P$, $\text{leftMax}$, $\text{rightMax}$, and the deque.

---

## 🔍 Edge Cases Considered

- **Minimum Length $N = 2$**: e.g., `"bb"` produces answer $1 \times 1 = 1$.
- **64-Bit Product Overflow**: Max product can reach $\approx (10^5 / 2)^2 = 2.5 \times 10^9 > 2^{31} - 1$. Evaluated using `long long` (`1LL * leftMax[t] * rightMax[t+1]`).
- **Overlapping Substrings**: Strictly separated by $t$ and $t+1$ partition index.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
