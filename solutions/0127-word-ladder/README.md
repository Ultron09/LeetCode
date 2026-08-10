# [127. Word Ladder](https://leetcode.com/problems/word-ladder/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), [Breadth-First Search](../../topics/graphs.md), [Hash Table](../../topics/arrays-and-hashing.md), [String](../../topics/sliding-window.md)

---

## 📌 Problem Statement

A **transformation sequence** from word `beginWord` to word `endWord` using a dictionary `wordList` is a sequence of words `beginWord -> s1 -> s2 -> ... -> sk` such that:
- Every adjacent pair of words differs by a single letter.
- Every $s_i$ for $1 \le i \le k$ is in `wordList`. (`beginWord` does not need to be in `wordList`).
- $s_k == \text{endWord}$.

Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return the **number of words in the shortest transformation sequence** from `beginWord` to `endWord`, or `0` if no such sequence exists.

### Example 1:
```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> "cog", which is 5 words long.
```

### Example 2:
```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
```

### Constraints:
- $1 \le \text{beginWord.length} \le 10$
- $\text{endWord.length} == \text{beginWord.length}$
- $1 \le \text{wordList.length} \le 5000$
- All the words in `wordList` are unique.
- `beginWord != endWord`

---

## 💡 Intuition & Approach

### 1. Bidirectional BFS (Frontier Swapping)
In a standard unidirectional BFS, the search tree expands outward with branching factor $b$ and depth $d$, leading to $\mathcal{O}(b^d)$ nodes visited.
With **Bidirectional BFS**:
- We maintain two frontiers: `beginSet` rooted at `beginWord` and `endSet` rooted at `endWord`.
- At each iteration, we always expand from the smaller frontier:
  ```cpp
  if (beginSet.size() > endSet.size()) swap(beginSet, endSet);
  ```
- This reduces the search volume from $\mathcal{O}(b^d)$ down to $\mathcal{O}(b^{d/2})$, executing in under $10$ ms.

### 2. Immediate Dictionary Clearing
To avoid redundant re-expansions and avoid needing a separate visited set, words are erased from `dict` immediately when they are enqueued into `nextLevel`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot L \cdot 26)$ where $N = |wordList| \le 5000$, $L = \text{word.length} \le 10$.
- **Space Complexity:** $\mathcal{O}(N \cdot L)$ for dictionary and frontier sets.

---

## 🔍 Edge Cases Considered

- **`endWord` not in `wordList`**: Returns `0` instantly.
- **Disconnected Search**: Returns `0` when frontiers cannot connect.
- **Direct 1-hop Transformation**: Returns `2`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
