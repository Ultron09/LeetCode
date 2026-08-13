# [749. Contain Virus](https://leetcode.com/problems/contain-virus/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), Simulation, DFS/BFS

---

## 📌 Problem Statement

A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.

The world is modeled as an `m x n` binary grid `isInfected`, where `isInfected[i][j] == 0` represents uninfected cells, and `isInfected[i][j] == 1` represents cells contaminated with the virus. A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.

Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall. Resources are limited. Each day, you can install walls around only one region (i.e., the affected area (continuous block of infected cells) that threatens the most uninfected cells the following night). There will never be a tie.

Return the number of walls used to quarantine all the infected regions. If the world will become fully infected, return the number of walls used.

### Example 1:
```
Input: isInfected = [[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]]
Output: 10
Explanation: There are 2 contaminated regions.
On the first day, add 5 walls to quarantine the viral region on the left.
On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
```

### Constraints:
- `m == isInfected.length`
- `n == isInfected[i].length`
- `1 <= m, n <= 50`
- `isInfected[i][j]` is either `0` or `1`.
- There is always a contiguous viral region throughout the described process that will infect strictly more uncontaminated squares in the next round.

---

## 💡 Intuition & Approach

1. **Simulation**: The problem is a straight simulation problem. We need to simulate the day-by-day progress until all virus regions are either contained or no uninfected cells are left to be threatened.
2. **Identifying Regions**: We can use BFS or DFS to find all connected components of `1`s.
3. **Calculating Threats and Walls**: For each region, we explore its neighbors.
   - Uninfected neighbors (`0`s) represent the threatened cells. The number of *unique* uninfected neighbors is the threat level. We can use a `set` or a secondary visited array to count unique threatened cells.
   - The number of walls needed is exactly the number of boundaries between a cell in the region (`1`) and an uninfected cell (`0`). Notice that if multiple `1`s touch the same `0`, multiple walls are needed, so the wall count can be greater than the unique threatened cells.
4. **Quarantine and Spread**: 
   - Pick the region with the highest threat level. Add its required walls to our total. Mark its cells as contained (e.g., set to `2`).
   - For all other uncontained regions, let them spread by turning their threatened `0`s into `1`s.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}((M \cdot N)^2)$ — In the worst-case scenario, we might only contain one cell per day, and the simulation could run $\mathcal{O}(M \cdot N)$ times. Each day's BFS/DFS scans the entire grid, taking $\mathcal{O}(M \cdot N)$.
- **Space Complexity:** $\mathcal{O}(M \cdot N)$ — We use auxiliary data structures like `visited` arrays, sets for frontiers, and queues for BFS, all of which are bounded by the grid size.

---

## 🔍 Edge Cases Considered

- **Fully Enclosed Uninfected Cell**: A single `0` surrounded by `1`s. It requires 4 walls to protect. The code correctly counts the boundaries rather than just unique `0`s for the wall count.
- **Multiple Regions Merging**: When uncontained regions spread, they might merge into a single larger region. The daily re-evaluation using BFS correctly identifies these merged regions as a single new component.
- **No Uninfected Cells Left**: The loop terminates gracefully when the maximum threat size is 0.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
