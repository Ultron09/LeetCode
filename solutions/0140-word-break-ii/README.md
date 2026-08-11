# [140. Word Break II](https://leetcode.com/problems/word-break-ii/)

**Difficulty:** `Hard`  
**Topics:** [Backtracking](../../topics/backtracking.md), [Dynamic Programming](../../topics/dynamic-programming.md), [Hash Table](../../topics/arrays-and-hashing.md), [String](../../topics/sliding-window.md)

---

## 📌 Problem Statement

Given a string `s` and a dictionary of strings `wordDict`, add spaces in `s` to construct a sentence where each word is a valid dictionary word. Return **all such possible sentences** in any order.

**Note** that the same word in the dictionary may be reused multiple times in the segmentation.

### Example 1:
```
Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]
```

### Example 2:
```
Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.
```

### Example 3:
```
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
```

### Constraints:
- $1 \le \text{s.length} \le 20$
- $1 \le \text{wordDict.length} \le 1000$
- $1 \le \text{wordDict}[i]\text{.length} \le 10$
- `s` and `wordDict[i]` consist of only lowercase English letters.
- All the strings of `wordDict` are unique.
- Input is generated in a way that the length of the answer doesn't exceed $10^5$.

---

## 💡 Intuition & Approach

### 1. Suffix-Memoized Depth-First Search (DFS)
To find all valid space-separated segmentations without redundant recalculation of identical suffixes:
- Let $\text{dfs}(\text{start})$ return the list of all valid sentences that can be formed from suffix $s[\text{start} \dots |s|-1]$.
- **Base Case**: If $\text{start} == |s|$, return `{""}`.
- **Memoization**: Cache results in `unordered_map<int, vector<string>> memo` keyed by the starting index.
- **Transitions**: For every candidate endpoint $\text{end} \in [\text{start} + 1, |s|]$:
  - Extract substring $w = s[\text{start} \dots \text{end} - 1]$.
  - If $w \in \text{wordDict}$, recursively call $\text{dfs}(\text{end})$.
  - For each sub-sentence $sub$ returned, form $w + (\text{if empty } "" \text{ else } " " + sub)$ and append to current results.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(2^N + N^2 + W)$ where $N = |s| \le 20$ and $W = \sum |wordDict[i]|$ (each suffix state is computed once and combined).
- **Space Complexity:** $\mathcal{O}(2^N \cdot N + W)$ for storing memoized suffix sentences and the recursion stack.

---

## 🔍 Edge Cases Considered

- **No Valid Segmentation** (e.g. `"catsandog"`): Returns empty list `[]`.
- **Entire String is a Single Word** (e.g. `"cat"` in `["cat"]`): Returns `["cat"]`.
- **Multiple Overlapping Valid Segmentations**: Properly extracted and formatted.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
