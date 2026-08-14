# [864. Shortest Path to Get All Keys](https://leetcode.com/problems/shortest-path-to-get-all-keys/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), [Breadth-First Search](../../topics/graphs.md), [Bit Manipulation](../../topics/bit-manipulation.md)

---

## 📌 Problem Statement

You are given an `m x n` grid `grid` where:
- `'.'` is an empty cell.
- `'#'` is a wall.
- `'@'` is the starting point.
- Lowercase letters represent keys.
- Uppercase letters represent locks.

You start at the starting point and one move consists of walking one space in one of the four cardinal directions. You cannot walk outside the grid, or walk into a wall.

If you walk over a key, you can pick it up and you cannot walk over a lock unless you have its corresponding key.

For some `1 <= k <= 6`, there is exactly one lowercase and one uppercase letter of the first `k` letters of the English alphabet in the grid. This means that there is exactly one key for each lock, and one lock for each key; and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.

Return the lowest number of moves to acquire all keys. If it is impossible, return `-1`.

### Example 1:
```
Input: grid = ["@.a..","###.#","b.A.B"]
Output: 8
Explanation: Note that the goal is to obtain all the keys not to open all the locks.
```

### Example 2:
```
Input: grid = ["@..aA","..B#.","....b"]
Output: 6
```

### Example 3:
```
Input: grid = ["@Aa"]
Output: -1
```

### Constraints:
- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 30`
- `grid[i][j]` is either an English letter, `'.'`, `'#'`, or `'@'`. 
- There is exactly one `'@'` in the grid.
- The number of keys in the grid is in the range `[1, 6]`.
- Each key in the grid is unique.
- Each key in the grid has a matching lock.

---

## 💡 Intuition & Approach

1. **State Space Formulation**: 
   Since we can revisit the same physical cell $(r, c)$ in the grid after picking up a new key, the standard 2D visited array is insufficient. Our state must capture both our physical location and the set of keys we currently hold. 
   Thus, a state is uniquely identified by `(row, col, keys_mask)`.

2. **Bitmasking for Keys**: 
   Since there are at most 6 keys (`a` to `f`), we can use a bitmask (an integer) to represent the subset of keys collected. The $i$-th bit is 1 if we have collected the $(i+1)$-th key.
   For example, holding keys `a` and `c` gives a mask of `000101` in binary.

3. **Breadth-First Search (BFS)**:
   Since we are looking for the shortest path in an unweighted grid, BFS is the optimal choice.
   - We initialize our queue with the starting position `(start_r, start_c, 0, 0)` (row, col, mask, distance).
   - The goal is reached when `mask == (1 << K) - 1`, meaning all $K$ bits are set to 1.
   - For every adjacent cell:
     - If it's a wall (`#`), skip.
     - If it's a lock (`A`-`F`), skip unless we possess the corresponding key (check if the bit is set in the `mask`).
     - If it's a key (`a`-`f`), calculate the new `mask` by turning on the corresponding bit.
     - If the new state `(nr, nc, nmask)` hasn't been visited, mark it as visited and add it to the queue with `distance + 1`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \times N \times 2^K)$ — Where $M$ is the number of rows, $N$ is columns, and $K$ is the total number of keys. In the worst case, we visit every possible state exactly once. With bounds $M, N \le 30$ and $K \le 6$, the maximum number of states is $30 \times 30 \times 64 = 57,600$, which easily runs in time.
- **Space Complexity:** $\mathcal{O}(M \times N \times 2^K)$ — To store the 3D visited array and the BFS queue.

---

## 🔍 Edge Cases Considered

- Unreachable keys completely blocked by walls or their own lock (`@Aa` edge case).
- Re-visiting cells multiple times with different key masks, strictly regulated by the 3D visited array.
- Grids containing keys but no corresponding locks (though constrained to 1-to-1).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
