# [30. Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)

**Difficulty:** `Hard`  
**Topics:** [Hash Table](../../topics/arrays-and-hashing.md), [String](../../topics/sliding-window.md), [Sliding Window](../../topics/sliding-window.md)

---

## 📌 Problem Statement

You are given a string `s` and an array of strings `words`. All the strings of `words` are of the **same length**.

A **concatenated string** is a string that exactly contains all the strings of any permutation of `words` concatenated.

For example, if `words = ["ab","cd","ef"]`, then `"abcdef"`, `"abefcd"`, `"cdabef"`, `"cdefab"`, `"efabcd"`, and `"efcdab"` are all concatenated strings. `"acdbef"` is not a concatenated string because it is not the concatenation of any permutation of `words`.

Return an array of the starting indices of all the concatenated substrings in `s`. You can return the answer in any order.

### Example 1:
```
Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation:
The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"].
The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"].
```

### Example 2:
```
Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
Explanation: There is no concatenated substring.
```

### Example 3:
```
Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
```

### Constraints:
- $1 \le \text{s.length} \le 10^4$
- $1 \le \text{words.length} \le 5000$
- $1 \le \text{words}[i]\text{.length} \le 30$
- `s` and `words[i]` consist of lowercase English letters.

---

## 💡 Intuition & Approach

### 1. Phased Multi-Offset Sliding Window
Let $L = \text{words}[0]\text{.length}$ and $K = \text{words.length}$.
Since all words share identical length $L$, valid concatenated substrings must start at some index $i$. Any such sequence can be decomposed into contiguous chunks of length $L$.
By running $L$ independent sliding windows starting at offsets $i \in [0, L - 1]$, every token boundary in $s$ is partitioned into disjoint sequences of length-$L$ word tokens.

### 2. Window State Maintenance
For a fixed offset $i$:
1. Step `right` forward by $L$ chunks.
2. Extract slice `sub = s.substr(right, L)`.
3. If `sub` exists in `wordCount`:
   - Increment `windowCount[sub]` and increment total matched count.
   - If `windowCount[sub] > wordCount[sub]`, contract the window from `left` by chunks of size $L$ until the excess occurrence of `sub` is removed.
   - If `count == K`, append `left` to the output list.
4. If `sub` is not a word in `words`:
   - Reset the window (`windowCount.clear()`, `count = 0`), and jump `left = right + L`.

### 3. String View Optimization
Using `std::string_view` allows slicing substrings without heap allocations or buffer copying, giving blazing performance.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot L)$
  - $N = |s| \le 10^4$, $L \le 30$.
  - Across all $L$ phase offsets, every character in $s$ is visited $\mathcal{O}(1)$ times.
  - Overall runtime $\approx 8$ ms in C++.
- **Space Complexity:** $\mathcal{O}(K \cdot L)$ auxiliary space for the target word frequency hash map.

---

## 🔍 Edge Cases Considered

- **$|s| < K \cdot L$**: String too short to contain all words $\implies$ returns `[]`.
- **Duplicate words in `words`**: Properly tracked via exact frequency counting.
- **Overlapping concatenations**: Captured accurately as the window shifts forward by step $L$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
