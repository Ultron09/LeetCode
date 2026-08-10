# [3518. Smallest Palindromic Rearrangement II](https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Greedy](../../topics/greedy.md), [Backtracking](../../topics/backtracking.md)

---

## 📌 Problem Statement

You are given a palindromic string `s` and an integer `k`.

Return the **$k$-th lexicographically smallest palindromic permutation** of `s`. If fewer than `k` distinct palindromic permutations exist, return an empty string `""`.

### Example 1:
```
Input: s = "aba", k = 1
Output: "aba"
Explanation: The only palindromic permutation is "aba".
```

### Example 2:
```
Input: s = "aba", k = 2
Output: ""
Explanation: There is only 1 palindromic permutation, so for k = 2 we return "".
```

### Example 3:
```
Input: s = "ababbab", k = 2
Output: "bababab"
Explanation: 
The distinct palindromic permutations in lexicographical order are:
1. "abbabba"
2. "bababab"
3. "bbaaabb"
For k = 2, the answer is "bababab".
```

### Constraints:
- $1 \le \text{s.length} \le 10^4$
- `s` consists only of lowercase English letters.
- `s` is a palindrome.
- $1 \le k \le 10^6$

---

## 💡 Intuition & Approach

### 1. Halving the Problem via Symmetry
A palindrome of length $N$ is uniquely determined by its **left half** of length $m = \lfloor N / 2 \rfloor$ (and a middle character if $N$ is odd).
- The right half is simply the mirror image (reversed left half).
- Therefore, finding the $k$-th smallest palindromic permutation of $s$ is equivalent to finding the **$k$-th lexicographically smallest permutation of the multiset of characters in the left half**.

### 2. Trial-and-Error Greedy Construction (Inverse Cantor Expansion)
We construct the left half character-by-character from index $0$ to $m-1$:
1. At position `pos`, try candidate characters $c \in ['a', 'z']$ in increasing alphabetical order.
2. For each candidate $c$ that has at least 1 remaining count:
   - Temporarily place $c$ (decrement count of $c$).
   - Calculate $P$, the number of unique permutations that can be formed with the remaining characters:
     $$P = \frac{\text{rem}!}{\prod_{i=1}^{\sigma} \text{cnt}[c_i]!} = \prod_{i=1}^{\sigma} \binom{\text{rem} - \sum_{j=1}^{i-1} \text{cnt}[c_j]}{\text{cnt}[c_i]}$$
   - **Case 1 ($P \ge k$)**: The $k$-th permutation falls within this branch! Fix character $c$ at position `pos`, leave its count decremented, and proceed to `pos + 1`.
   - **Case 2 ($P < k$)**: All $P$ permutations starting with $c$ precede the $k$-th permutation. Subtract $P$ from $k$ ($k \leftarrow k - P$), restore the count of $c$, and test the next candidate character.
3. If all candidates are exhausted and no character could be placed, then fewer than $k$ permutations exist $\implies$ return `""`.

### 3. Avoiding Factorial Overflow via Multiplicative Combinations
Directly computing factorials is impossible due to overflow ($N \le 10^4$). We compute combinations iteratively using:
$$\binom{n}{m} = \prod_{j=1}^m \frac{n - j + 1}{j}, \quad \text{where } m = \min(m, n - m)$$
We cap the product at $k + 1$ during intermediate multiplications. Because each step at least doubles when $n \ge 2m$, the inner combination loop runs in at most $\mathcal{O}(\min(\text{cnt}[c_i], \log k))$ operations.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot \sigma \cdot (\sigma + \min(N, \log k)))$
  - With alphabet size $\sigma = 26$ and $k \le 10^6 \implies \log_2 k \approx 20$.
  - At each of the $N / 2$ positions, we test up to 26 characters.
  - Computing permutations runs in $\mathcal{O}(\sigma + \log k) \le 50$ operations.
  - Total operations $\approx 10^4 \times 26 \times 50 \approx 1.3 \times 10^7$, executing well within 25 ms.
- **Space Complexity:** $\mathcal{O}(N)$ for the resulting string and $\mathcal{O}(\sigma)$ for character frequency arrays.

---

## 🔍 Edge Cases Considered

- **$k$ exceeds total permutations**: Handled gracefully by returning `""`.
- **Odd vs Even length $N$**: Center character is uniquely identified and restored in the middle.
- **Single-character strings / duplicate characters**: Fully handled by the combination multiplicative formula.
- **Overflow protection**: Intermediate products capped at $k+1$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
