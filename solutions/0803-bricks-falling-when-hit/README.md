# [803. Bricks Falling When Hit](https://leetcode.com/problems/bricks-falling-when-hit/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), Array, Matrix, Union Find

---

## 📌 Problem Statement

You are given an `m x n` binary `grid`, where each `1` represents a brick and `0` represents an empty space. A brick is stable if:

- It is directly connected to the top of the grid, or
- At least one other brick in its four adjacent cells is stable.

You are also given an array `hits`, which is a sequence of erasures we want to apply. Each time we want to erase the brick at the location `hits[i] = (rowi, coli)`. The brick on that location (if it exists) will disappear. Some other bricks may no longer be stable because of that erasure and will fall. Once a brick falls, it is immediately erased from the grid (i.e., it does not land on other stable bricks).

Return an array `result`, where each `result[i]` is the number of bricks that will fall after the `i`th erasure is applied.

Note that an erasure may refer to a location with no brick, and if it does, no bricks drop.

### Example 1:
```
Input: grid = [[1,0,0,0],[1,1,1,0]], hits = [[1,0]]
Output: [2]
Explanation: Starting with the grid:
[[1,0,0,0],
 [1,1,1,0]]
We erase the underlined brick at (1,0), resulting in the grid:
[[1,0,0,0],
 [0,1,1,0]]
The two underlined bricks are no longer stable as they are no longer connected to the top nor adjacent to another stable brick, so they will fall. The resulting grid is:
[[1,0,0,0],
 [0,0,0,0]]
Hence the result is [2].
```

### Constraints:
- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 200`
- `grid[i][j]` is `0` or `1`.
- `1 <= hits.length <= 4 * 10^4`
- `hits[i].length == 2`
- `0 <= xi <= m - 1`
- `0 <= yi <= n - 1`
- All `(xi, yi)` are unique.

---

## 💡 Intuition & Approach

Simulating the breaking of connections over time and identifying components that get disconnected from the "roof" is computationally expensive. Splitting a connected component takes $\mathcal{O}(V + E)$ time per operation. 

However, **adding** connections and merging components is extremely fast using a **Disjoint Set Union (DSU)** data structure. This suggests a classic **"Reverse Time"** technique.

### Step-by-Step Approach

1. **Simulate All Hits First (End State):**
   Remove all bricks from the grid at the locations specified in `hits`. Keep track of which bricks were actually there.
   
2. **Build Initial DSU:**
   Initialize a DSU where each grid cell is a node. Introduce a special "roof" node (e.g., node `M * N`).
   Connect all remaining bricks to their 4-way neighbors. Any brick in the top row (`row == 0`) is also connected directly to the roof node. The DSU will track the size of the connected components.
   
3. **Reverse Time Process:**
   Iterate through `hits` backwards. For each hit:
   - If the cell was originally empty (`0`), ignore it (`0` bricks drop).
   - Otherwise, we "add" this brick back to the grid.
   - Note the size of the component connected to the roof *before* adding the brick (`pre_roof_size`).
   - Connect the brick to its stable 4-way neighbors and to the roof (if it is on row `0`).
   - Note the size of the component connected to the roof *after* adding the brick (`post_roof_size`).
   - If the newly added brick is now connected to the roof, then it "saved" `post_roof_size - pre_roof_size - 1` bricks from falling. We subtract `1` because the added brick itself doesn't count as a fallen brick.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \cdot N + H \cdot \alpha(M \cdot N))$ — Building the initial grid state takes $\mathcal{O}(M \cdot N)$. Processing each of the $H$ hits involves at most 4 union operations. The Inverse Ackermann function $\alpha$ guarantees nearly constant time per operation.
- **Space Complexity:** $\mathcal{O}(M \cdot N)$ — For the DSU data arrays (`parent` and `size`), and the copy of the `grid`.

---

## 🔍 Edge Cases Considered

- **Hitting an Empty Space:** Pre-verify if the hit was originally a brick. If it wasn't, `result[i] = 0`.
- **Hit Brick doesn't connect to roof:** Even if adding a brick back merges multiple disconnected components, if none of them attach to the roof, then no bricks were "saved" (prevented from falling) by this hit. Handled by checking if the current brick ends up in the same set as the roof.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
