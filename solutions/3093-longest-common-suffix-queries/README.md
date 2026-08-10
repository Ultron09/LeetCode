# [3093. Longest Common Suffix Queries](https://leetcode.com/problems/longest-common-suffix-queries/)

**Difficulty:** `Hard`  
**Topics:** [Trees & BST / Trie](../../topics/trees.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given two arrays of strings, `wordsContainer` and `wordsQuery`.

For each `wordsQuery[i]`, find a string from `wordsContainer` that:
1. Shares the **longest common suffix** with `wordsQuery[i]`.
2. If there are ties, chooses the string with the **smallest length**.
3. If there are still ties, chooses the string that **appeared earliest** (smallest index) in `wordsContainer`.

Return an array `ans` where `ans[i]` is the index of the best matching string for `wordsQuery[i]`.

### Example 1:
```
Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]
Output: [1,1,1]
Explanation:
- "cd": Candidates sharing suffix "cd" are indices 0, 1, 2. Index 1 has the shortest length (3) -> 1.
- "bcd": Candidates sharing suffix "bcd" are indices 0, 1, 2. Index 1 has the shortest length (3) -> 1.
- "xyz": No common suffix (empty suffix ""). Shortest word in wordsContainer is index 1 -> 1.
```

### Example 2:
```
Input: wordsContainer = ["abcdefgh","poiuygh","ghghgh"], wordsQuery = ["gh","acbfgh","acbfegh"]
Output: [2,0,2]
```

### Constraints:
- $1 \le \text{wordsContainer.length}, \text{wordsQuery.length} \le 10^4$
- $1 \le \text{wordsContainer}[i].\text{length}, \text{wordsQuery}[i].\text{length} \le 5 \times 10^3$
- Sum of `wordsContainer[i].length` $\le 5 \times 10^5$
- Sum of `wordsQuery[i].length` $\le 5 \times 10^5$

---

## 💡 Intuition & Approach

### 1. Suffix Matching $\to$ Reversed Prefix Trie
Finding the longest common suffix of two strings is equivalent to reversing both strings and finding the **longest common prefix** using a **Trie**.

### 2. Node-Augmented Optimization
Instead of doing a DFS on the Trie for each query, each `TrieNode` maintains:
- `minLen`: the minimum length among all container words that pass through this node.
- `bestIdx`: the index of that best word in `wordsContainer`.

When inserting words in sequential index order ($i = 0 \dots N - 1$):
- We update `node->bestIdx` whenever `word.length() < node->minLen`.
- Because indices $i$ are strictly increasing, strictly smaller length (`<`) automatically breaks ties in favor of the **earliest occurring word**!

### 3. Querying
For each query string $Q$:
- Traverse the Trie backwards from $Q[\text{len} - 1]$ down to $Q[0]$.
- At each matched character, record `best = curr->bestIdx`.
- If a character transition does not exist, terminate traversal and return the recorded `best` index.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\sum |\text{wordsContainer}[i]| + \sum |\text{wordsQuery}[i]|)$
  - Building the Trie: Linear in the total length of all container words ($\le 5 \times 10^5$ operations).
  - Processing queries: Linear in the total length of all query words ($\le 5 \times 10^5$ operations).
  - Total runtime $< 40$ ms in C++.
- **Space Complexity:** $\mathcal{O}(\sum |\text{wordsContainer}[i]| \times \Sigma)$
  - At most $\sum |\text{wordsContainer}[i]|$ Trie nodes with alphabet size $\Sigma = 26$.

---

## 🔍 Edge Cases Considered

- **No Common Suffix (Empty Suffix)**: Handled at the root node, which stores the shortest and earliest word in `wordsContainer`.
- **Identical Words**: Strict inequality (`<`) guarantees the earlier index is retained.
- **Query Longer/Shorter than Container Word**: Traversal stops safely when nodes run out.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
