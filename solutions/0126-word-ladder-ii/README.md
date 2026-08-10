# [126. Word Ladder II](https://leetcode.com/problems/word-ladder-ii/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), [Breadth-First Search](../../topics/graphs.md), [Backtracking](../../topics/backtracking.md), [Hash Table](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

A **transformation sequence** from word `beginWord` to word `endWord` using a dictionary `wordList` is a sequence of words `beginWord -> s1 -> s2 -> ... -> sk` such that:
- Every adjacent pair of words differs by a single letter.
- Every $s_i$ for $1 \le i \le k$ is in `wordList`. (`beginWord` does not need to be in `wordList`).
- $s_k == \text{endWord}$.

Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return *all the **shortest transformation sequences*** from `beginWord` to `endWord`, or an empty list if no such sequence exists.

### Example 1:
```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
Explanation: There are 2 shortest transformation sequences:
"hit" -> "hot" -> "dot" -> "dog" -> "cog"
"hit" -> "hot" -> "lot" -> "log" -> "cog"
```

### Example 2:
```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: []
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
```

### Constraints:
- $1 \le \text{beginWord.length} \le 5$
- $\text{endWord.length} == \text{beginWord.length}$
- $1 \le \text{wordList.length} \le 500$
- All the words in `wordList` are unique.
- The sum of all shortest transformation sequences does not exceed $10^5$.

---

## 💡 Intuition & Approach

### 1. Two-Phase Algorithm: BFS + DFS Backtracking
Finding the **shortest** paths in an unweighted graph naturally calls for Breadth-First Search (BFS), while finding **all** such paths requires backtracking along the shortest-path DAG.

1. **Phase 1: BFS Level-by-Level Shortest-Path Graph (DAG) Construction**:
   - Maintain `dist[word]` storing the shortest hop distance from `beginWord`.
   - Maintain `parents[neighbor]` tracking all predecessor nodes $u$ where $\text{dist}[\text{neighbor}] == \text{dist}[u] + 1$.
   - Generate neighbors by mutating each character across 'a' through 'z' ($\mathcal{O}(26 \times L)$).
   - Terminate BFS once the level containing `endWord` has finished processing.

2. **Phase 2: DFS Backtracking to Reconstruct Sequences**:
   - Starting at `endWord`, traverse backwards to `beginWord` along `parents`.
   - Reverse each completed sequence and collect in the output list.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot L \cdot 26 + K \cdot L)$ where $N = |wordList| \le 500$, $L = \text{word.length} \le 5$, and $K$ is the number of shortest paths.
- **Space Complexity:** $\mathcal{O}(N \cdot L)$ for the BFS queue, distance hash map, and predecessor DAG.

---

## 🔍 Edge Cases Considered

- **`endWord` not in `wordList`**: Fast-checked at the very beginning in $\mathcal{O}(1) \implies \text{returns } []$.
- **No path connecting `beginWord` and `endWord`**: BFS completes without reaching `endWord` $\implies \text{returns } []$.
- **Single step transformation**: e.g., `"a"` to `"c"`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
