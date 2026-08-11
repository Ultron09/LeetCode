# [336. Palindrome Pairs](https://leetcode.com/problems/palindrome-pairs/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Trees & BST](../../topics/trees.md), [Sliding Window](../../topics/sliding-window.md)

---

## 📌 Problem Statement

You are given a 0-indexed array of unique strings `words`.

A palindrome pair is a pair of integers `(i, j)` such that:
- $0 \le i, j < \text{words.length}$
- $i \ne j$, and
- $\text{words}[i] + \text{words}[j]$ (the concatenation of the two strings) is a palindrome.

Return an array of all the palindrome pairs of words.

You must write an algorithm with $\mathcal{O}(\sum \text{words}[i].\text{length}^2)$ runtime complexity.

### Example 1:
```
Input: words = ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]]
Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]
```

### Example 2:
```
Input: words = ["bat","tab","cat"]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["battab","tabbat"]
```

### Example 3:
```
Input: words = ["a",""]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["a","a"]
```

### Constraints:
- $1 \le \text{words.length} \le 5000$
- $0 \le \text{words}[i].\text{length} \le 300$
- `words[i]` consists of lowercase English letters.
- All strings in `words` are unique.

---

## 💡 Intuition & Approach

### 1. Palindromic Concatenation Structure
For two strings $A$ and $B$ to concatenate into a palindrome $A + B$:
- **Case 1 ($|A| = |B|$)**: $B$ must be the exact reverse of $A$ ($\text{reversed}(A) = B$).
- **Case 2 ($|A| > |B|$)**: $A$ can be decomposed into $A = \text{prefix} + \text{suffix}$ where $\text{prefix} = \text{reversed}(B)$ and $\text{suffix}$ is itself a palindrome. Then $A + B = \text{prefix} + \text{suffix} + B$ is palindromic.
- **Case 3 ($|A| < |B|$)**: $B$ can be decomposed into $B = \text{prefix} + \text{suffix}$ where $\text{prefix}$ is a palindrome and $\text{suffix} = \text{reversed}(A)$. Then $A + B = A + \text{prefix} + \text{suffix}$ is palindromic.

### 2. Prefix & Suffix Decomposition with Hash Table
Instead of comparing all $\mathcal{O}(N^2)$ pairs:
1. Store all words in a hash map: $\text{wordMap}[w] = \text{index}$.
2. For each word $w = \text{words}[i]$ of length $L$, test all $L + 1$ split points $k \in [0, L]$ where $w = w[0\dots k-1] + w[k\dots L-1]$:
   - **Right Append ($i, j$)**: If the suffix $w[k\dots L-1]$ is a palindrome, look up $\text{reversed}(w[0\dots k-1])$ in `wordMap`. If found at index $j$ ($j \ne i$), then $\text{words}[i] + \text{words}[j]$ forms a valid palindrome pair $(i, j)$.
   - **Left Prepend ($j, i$)**: If the prefix $w[0\dots k-1]$ is a palindrome (with $k > 0$), look up $\text{reversed}(w[k\dots L-1])$ in `wordMap`. If found at index $j$ ($j \ne i$), then $\text{words}[j] + \text{words}[i]$ forms a valid palindrome pair $(j, i)$.
3. **Preventing Duplicates**:
   Requiring $k > 0$ for the left-prepend branch avoids duplicating pairs when $k = 0$ (which corresponds to treating the entire string as the suffix).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\sum L_i^2)$
  - For each word of length $L_i$, there are $L_i + 1$ split points.
  - Palindrome verification and substring slicing take $\mathcal{O}(L_i)$ time per split.
  - Average hash table lookup is $\mathcal{O}(L_i)$.
  - Total time is $\sum_{i=1}^N \mathcal{O}(L_i^2)$, taking $< 35\text{ ms}$ for $N = 5000, L \le 300$.
- **Space Complexity:** $\mathcal{O}(N \cdot L)$
  - $\mathcal{O}(N \cdot L)$ space to store the hash map and string keys.

---

## 🔍 Edge Cases Considered

- **Empty String (`""`)**: Handled correctly. An empty string paired with any palindrome word $w$ produces both $(i, j)$ and $(j, i)$.
- **Self-Pairing ($i == j$)**: Guard condition `it->second != i` prevents a single palindrome word from pairing with itself.
- **Single-Letter Words (`"s"`)**: Evaluates $k = 0$ and $k = 1$ correctly without duplicate insertion.
- **Mutual Reverses (`"abcd"`, `"dcba"`)**: Exactly one direction $(0, 1)$ generated from $w = \text{"abcd"}$ at $k = 4$, and $(1, 0)$ generated from $w = \text{"dcba"}$ at $k = 4$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
