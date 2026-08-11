# [488. Zuma Game](https://leetcode.com/problems/zuma-game/)

**Difficulty:** `Hard`  
**Topics:** [Backtracking](../../topics/backtracking.md), [Graphs](../../topics/graphs.md), [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

You are playing a variation of the game Zuma.

In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red `'R'`, yellow `'Y'`, blue `'B'`, green `'G'`, or white `'W'`. You also have several colored balls in your hand.

Your goal is to clear all of the balls from the board. On each turn:
1. Pick any ball from your hand and insert it in between two balls in the row or on either end of the row.
2. If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.
3. If this removal causes more groups of three or more of the same color to form, continue removing each group until there are none left.
4. If there are no more balls on the board, you win the game.

Given a string `board` representing the row of balls, and a string `hand` representing the balls in your hand, return the **minimum number of balls** you have to insert to clear all the balls from the board. If you cannot clear all the balls, return `-1`.

### Example 1:
```
Input: board = "WRRBBW", hand = "RB"
Output: -1
Explanation: It is impossible to clear all the balls.
- Insert 'R' -> WRRRBBW -> WBBW.
- Insert 'B' -> WBBBW -> WW.
There are balls remaining and no more balls in hand.
```

### Example 2:
```
Input: board = "WWRRBBWW", hand = "WRBRW"
Output: 2
Explanation:
- Insert 'R' -> WWRRRBBWW -> WWBBWW.
- Insert 'B' -> WWBBBWW -> WWWW -> empty.
2 balls from your hand were needed to clear the board.
```

### Example 3:
```
Input: board = "G", hand = "GGGGG"
Output: 2
```

### Constraints:
- $1 \le \text{board.length} \le 16$
- $1 \le \text{hand.length} \le 5$
- `board` and `hand` consist of `'R'`, `'Y'`, `'B'`, `'G'`, and `'W'`.
- The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.

---

## 💡 Intuition & Approach

### 1. BFS Shortest-Path in Game State Space
Because we seek the **minimum number of insertions**, Breadth-First Search (BFS) is the optimal traversal strategy:
- Each state is defined as `(board, hand)`.
- To avoid duplicate state explorations, we sort `hand` canonically so identical hands with different permutations map to the same key.
- The first time we reach an empty `board` (`""`), the number of BFS steps taken is guaranteed to be minimal.

### 2. Recursive Chain Reaction Collapsing
Whenever a ball is inserted:
- Scan the board for any contiguous sequence of $\ge 3$ matching colors.
- Erase the sequence and restart scanning from index $0$ to process subsequent chain reactions.
- Repeat until no $\ge 3$ runs exist.

### 3. Critical Branch-Pruning Heuristics
Arbitrary insertion at all $N + 1$ positions for all $|hand|$ balls creates an enormous search tree ($17 \times 5 \times 18 \times 4 \dots \approx 10^7$ branches). We apply selective pruning:
1. **Cluster Duplicate Hand Balls**: Only try one instance of identical consecutive hand balls per state.
2. **Targeted Insertion Positions**:
   - Insert ball $c$ directly adjacent to an existing ball of color $c$ (`board[i-1] == c` or `board[i] == c`).
   - **Split Combinations**: Insert ball $c$ between two identical adjacent balls (`board[i-1] == board[i] && board[i] != c`) to split them and enable future cascading chain collapses (e.g. `RRWWRRBBRR`).
   - Skip all other arbitrary placements that cannot trigger or setup matches.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(V \cdot B \cdot H \cdot (B + H))$
  - $B \le 16$ is the maximum board size, $H \le 5$ is hand size.
  - $V \le 2 \times 10^4$ is the total number of reachable pruned game states.
  - Collapsing takes $\mathcal{O}(B^2)$ per transition.
  - Execution completes within $< 25\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(V \cdot (B + H))$
  - Visited hash table and queue entries for exploring the state space graph.

---

## 🔍 Edge Cases Considered

- **Single Ball Board ($|board| = 1$)**: Requires inserting two matching balls.
- **Empty Hand Before Board Cleared**: Discarded from queue without infinite looping.
- **Cascading Chain Reactions**: Multiple consecutive 3+ blocks collapsing across separated segments handled via restart in `collapse()`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
