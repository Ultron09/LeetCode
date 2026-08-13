# [773. Sliding Puzzle](https://leetcode.com/problems/sliding-puzzle/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), Breadth-First Search

---

## 📌 Problem Statement

On a `2 x 3` board, there are five tiles labeled from `1` to `5`, and an empty square represented by `0`. A move consists of choosing `0` and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is `[[1,2,3],[4,5,0]]`.

Given the puzzle board `board`, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return `-1`.

### Example 1:
```
Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
```

### Example 2:
```
Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.
```

### Constraints:
- `board.length == 2`
- `board[i].length == 3`
- `0 <= board[i][j] <= 5`
- Each value `board[i][j]` is unique.

---

## 💡 Intuition & Approach

This problem is a classic shortest-path puzzle on an unweighted graph, making **Breadth-First Search (BFS)** the optimal choice.

1. **State Serialization**:
   - Instead of dealing with cumbersome `2x3` 2D arrays at every state, we can serialize the board into a 6-character string (e.g., `"123450"`).
   - The total number of valid permutations of 6 elements is $6! = 720$. Because the state space is remarkably small, memory and time limits are a non-issue.

2. **Graph Representation**:
   - In our serialized 1D string, we map the 2D adjacency rules. The valid swap targets for the `'0'` tile at index `i` are:
     - `0` (top-left) $\rightarrow$ `1` (right), `3` (down)
     - `1` (top-mid) $\rightarrow$ `0` (left), `2` (right), `4` (down)
     - `2` (top-right) $\rightarrow$ `1` (left), `5` (down)
     - `3` (bot-left) $\rightarrow$ `0` (up), `4` (right)
     - `4` (bot-mid) $\rightarrow$ `1` (up), `3` (left), `5` (right)
     - `5` (bot-right) $\rightarrow$ `2` (up), `4` (left)

3. **BFS Execution**:
   - Start with the serialized initial board. 
   - Add it to a queue and a visited `unordered_set`.
   - Pop a state, generate all valid swaps for the `'0'` tile using the precomputed map, and enqueue any unvisited resulting states with `moves + 1`.
   - Terminate and return `moves` if the target state `"123450"` is reached.
   - If the queue empties without reaching the target, return `-1`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(6!) = \mathcal{O}(720)$ which is effectively $\mathcal{O}(1)$. Generating and checking 720 states is practically instantaneous.
- **Space Complexity:** $\mathcal{O}(6!) = \mathcal{O}(720)$ which is $\mathcal{O}(1)$ for storing the queue and visited set.

---

## 🔍 Edge Cases Considered

- **Already Solved**: If the input `board` equals `[[1,2,3],[4,5,0]]`, the serialized string immediately matches the target and returns `0`.
- **Unsolvable States**: Half of the possible permutations (360) are unreachable due to the mathematical properties of the sliding puzzle (parity of inversions). The BFS elegantly exhausts all reachable states and safely returns `-1`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
