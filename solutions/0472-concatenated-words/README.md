# [472. Concatenated Words](https://leetcode.com/problems/concatenated-words/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an array of strings `words` (without duplicates), return all the **concatenated words** in the given list of words.

A **concatenated word** is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.

### Example 1:
```
Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
Explanation: 
- "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
- "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
- "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
```

### Example 2:
```
Input: words = ["cat","dog","catdog"]
Output: ["catdog"]
```

### Constraints:
- $1 \le \text{words.length} \le 10^4$
- $1 \le \text{words}[i]\text{.length} \le 30$
- `words[i]` consists of only lowercase English letters.
- All the strings of `words` are **unique**.
- $1 \le \sum \text{words}[i]\text{.length} \le 10^5$

---

## 💡 Intuition & Approach

### 1. Incremental Vocabulary Building by Length
A concatenated word can only be composed of **strictly shorter** words.
- If we sort `words` in ascending order of string length, whenever we evaluate a word $W$, all possible candidate building blocks are already present in our dictionary `wordSet`.
- After evaluating word $W$, we insert $W$ into `wordSet` so it can serve as a component for longer words.

### 2. Word Break DP Verification
For each word $W$ of length $L$:
- Define `dp[i]` as a boolean indicating whether the prefix $W[0 \dots i-1]$ can be completely segmented into words contained in `wordSet`.
- **Base Case:** `dp[0] = true` (empty prefix).
- **Transition:** For each $i \in [1, L]$ and each partition point $j \in [0, i-1]$:
  $$\text{dp}[i] = \text{true} \quad \text{if } \text{dp}[j] == \text{true} \land W[j \dots i-1] \in \text{wordSet}$$
- If `dp[L] == true`, $W$ can be formed by at least two shorter words already in `wordSet`, so we add $W$ to `result`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N + N \cdot L^3)$
  - Sorting $N$ words takes $\mathcal{O}(N \log N)$ where $N \le 10^4$.
  - For each word of length $L \le 30$, the double loop performs at most $\frac{L(L+1)}{2}$ substring extractions and hash lookups, costing $\mathcal{O}(L^3)$.
  - Total time is dominated by $N \cdot L^3 \le 10^4 \times 30^3 \approx 2.7 \times 10^5$ operations (executes in $< 25\text{ ms}$).
- **Space Complexity:** $\mathcal{O}\left(\sum |W_i|\right)$
  - Storing all strings in `wordSet`. The DP array for each word requires $\mathcal{O}(L)$ auxiliary space.

---

## 🔍 Edge Cases Considered

- **Empty Words**: Ignored safely without corrupting `dp[0]`.
- **Duplicate Elements**: Problem guarantees all strings are unique.
- **Word Composed of Itself**: Length-based sorting ensures the word itself is not in `wordSet` during its own evaluation.
- **Deeply Nested Compositions**: e.g., `"catsdogcats"` composed of 3 words, verified seamlessly via dynamic programming.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
