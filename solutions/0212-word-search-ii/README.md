# [212. Word Search II](https://leetcode.com/problems/word-search-ii/)

**Difficulty:** `Hard`  
**Topics:** [Backtracking](../../topics/backtracking.md), [Trie](../../topics/trees.md), [Matrix](../../topics/backtracking.md), [Array](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an `m x n` `board` of characters and a list of strings `words`, return **all words on the board**.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

### Example 1:
```
Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], 
       words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
```

### Example 2:
```
Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
```

### Constraints:
- $m == \text{board.length}$
- $n == \text{board}[i]\text{.length}$
- $1 \le m, n \le 12$
- `board[i][j]` is a lowercase English letter.
- $1 \le \text{words.length} \le 3 \times 10^4$
- $1 \le \text{words}[i]\text{.length} \le 10$
- `words[i]` consists of lowercase English letters.
- All the strings of `words` are unique.

---

## 💡 Intuition & Approach

### 1. Multi-Prefix Search via Trie
Searching each word individually across the board would cost $\mathcal{O}(W \cdot M \cdot N \cdot 4^L)$, resulting in a Time Limit Exceeded (TLE). 

Instead, we insert all target words into a single **Prefix Tree (Trie)**:
- We execute a single unified Depth-First Search from every cell on the board, traversing both the grid and the Trie simultaneously.
- As soon as the grid path forms a prefix not present in the Trie, exploration terminates immediately.

### 2. In-Flight Trie Pruning (Leaf Removal)
Once a word is matched at `currNode`:
1. Record `currNode->word` into the results.
2. Clear `currNode->word = ""` to eliminate duplicate entries.
3. If `currNode` has zero active children and no other terminating words, delete/unlink it from its parent. This aggressively shrinks the Trie and prevents future redundant traversals.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(W \cdot L + M \cdot N \cdot 3^{L})$ where $M, N \le 12$, $L \le 10$ is the max word length, and $W = |\text{words}| \le 3 \times 10^4$.
- **Space Complexity:** $\mathcal{O}(W \cdot L)$ auxiliary memory for Trie storage.

---

## 🔍 Edge Cases Considered

- **Overlapping / Shared Prefixes** (e.g. `"oa"`, `"oath"`, `"oaths"`): Correctly detected as individual words without mutual interference.
- **Cycles / Re-visiting Same Cell**: Blocked by temporarily setting `board[r][c] = '#'`.
- **Words Not in Grid**: Pruned at the shallowest unmatched prefix.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
