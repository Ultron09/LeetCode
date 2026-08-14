# [913. Cat and Mouse](https://leetcode.com/problems/cat-and-mouse/)

**Difficulty:** `Hard`  
**Topics:** [Graph](../../topics/graphs.md), [Dynamic Programming](../../topics/dynamic-programming.md), [Game Theory](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

A game on an undirected graph is played by two players, Mouse and Cat, who alternate turns.

The graph is given as follows: `graph[a]` is a list of all nodes `b` such that `ab` is an edge of the graph.

The mouse starts at node `1` and goes first, the cat starts at node `2` and goes second, and there is a hole at node `0`.

During each player's turn, they must travel along one edge of the graph that meets where they are. Additionally, it is not allowed for the Cat to travel to the Hole (node `0`).

Then, the game can end in three ways:
1. If ever the Cat occupies the same node as the Mouse, the Cat wins.
2. If ever the Mouse reaches the Hole, the Mouse wins.
3. If ever a position is repeated (i.e., the players are in the same position as a previous turn, and it is the same player's turn to move), the game is a draw.

Given a graph, and assuming both players play optimally, return:
- `1` if the mouse wins the game,
- `2` if the cat wins the game, or
- `0` if the game is a draw.

### Example 1:
```
Input: graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
Output: 0
```

### Example 2:
```
Input: graph = [[1,3],[0],[3],[0,2]]
Output: 1
```

### Constraints:
- `3 <= graph.length <= 50`
- `1 <= graph[i].length < graph.length`
- `0 <= graph[i][j] < graph.length`
- `graph[i][j] != i`
- `graph[i]` is unique.
- The mouse and the cat can always move.

---

## 💡 Intuition & Approach

This problem is a classic impartial game on a directed graph that can contain cycles, which implies the possibility of draws. Standard Mini-Max on trees doesn't immediately work because the state space can loop forever.

Instead of a standard Top-Down Depth First Search (which risks infinite loops for draws), we use a **Bottom-Up BFS (Topological Sort approach)** starting from known terminal states.

1. **State Definition**:
   A state is defined by a tuple `(m, c, t)`:
   - `m`: current position of the Mouse.
   - `c`: current position of the Cat.
   - `t`: turn identifier (`0` for Mouse's turn, `1` for Cat's turn).

2. **Base Cases (Terminal States)**:
   - If `m == 0`: Mouse wins (State Value = `1`).
   - If `c == m` and `m != 0`: Cat wins (State Value = `2`).

3. **Bottom-Up BFS**:
   - We initialize the out-degrees for every state. The out-degree is the number of possible valid moves from `(m, c, t)`. Remember the Cat cannot move to node `0`.
   - We push all terminal states into a queue.
   - For a state popped from the queue with a known winner `W`:
     - We look at all its valid predecessor states `(pm, pc, pt)`.
     - **If the predecessor belongs to the winner's turn** (e.g., `W == 1` and `pt == 0` for Mouse's turn), then the predecessor state is also a guaranteed win for `W`. (The player will obviously choose this move).
     - **If the predecessor belongs to the loser's turn** (e.g., `W == 1` and `pt == 1` for Cat's turn), we decrement the predecessor's out-degree. If the out-degree reaches `0`, it means *all* possible choices for that player inevitably lead to a loss. Thus, the predecessor state becomes a forced loss (a win for `W`).
   - We continue updating and pushing new resolved states into the queue until the queue is empty.

4. **Result Check**:
   Any state that wasn't resolved by the end of the BFS (remains untouched) involves cyclic dependencies where neither player can force a win. These remain `0` (Draw). We return the outcome for `(1, 2, 0)`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^3)$ where $N$ is the number of nodes. There are $2 \cdot N^2$ possible states. Each state is evaluated and pushed to the queue at most once. From each state, evaluating predecessors takes at most $\mathcal{O}(N)$ transitions.
- **Space Complexity:** $\mathcal{O}(N^2)$ to store the `color` grid, the `out_degree` grid, and the queue.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
