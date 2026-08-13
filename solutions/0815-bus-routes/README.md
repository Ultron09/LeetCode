# [815. Bus Routes](https://leetcode.com/problems/bus-routes/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), Arrays, Hash Table, Breadth-First Search

---

## 📌 Problem Statement

You are given an array `routes` representing bus routes where `routes[i]` is a bus route that the $i$-th bus repeats forever.

For example, if `routes[0] = [1, 5, 7]`, this means that the 0th bus travels in the sequence `1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ...` forever.

You will start at the bus stop `source` (You are not on any bus initially), and you want to go to the bus stop `target`. You can travel between bus stops by buses only.

Return the least number of buses you must take to travel from `source` to `target`. Return `-1` if it is not possible.

### Example 1:
```
Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
Output: 2
Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
```

### Example 2:
```
Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
Output: -1
```

### Constraints:
- `1 <= routes.length <= 500`
- `1 <= routes[i].length <= 10^5`
- All the values of `routes[i]` are **unique**.
- `sum(routes[i].length) <= 10^5`
- `0 <= routes[i][j] < 10^6`
- `0 <= source, target < 10^6`

---

## 💡 Intuition & Approach

The naive approach is to build a graph where each node is a **bus stop**, and edges connect stops on the same bus route. However, since a route can have up to $10^5$ stops, constructing a highly connected graph will result in an excessive number of edges (up to $\mathcal{O}(K^2)$ where $K$ is route length), leading to Memory Limit Exceeded or Time Limit Exceeded.

### Optimal Approach: BFS on Buses
Instead of hopping from stop to stop, we should think about **transferring from bus to bus**.
Each **bus** is a node in our implicit graph.
Two buses share an edge if they intersect at a common bus stop.

1. **Precomputation**: First, map every `stop` to a list of `bus_ids` that service it. This allows us to rapidly query which buses we can board from any given stop.
2. **BFS Initialization**: Find all buses that visit the `source` stop. Push them onto a BFS queue and mark them as visited. We also start counting our `num_buses = 1`.
3. **Queue Processing**: 
   - Pop a `bus`. Check all the stops along its route.
   - If any `stop == target`, we return `num_buses`.
   - Otherwise, for each `stop`, we can board new unvisited buses (`next_bus`) from our mapping and push them to the queue.
4. **Key Pruning Step**: After adding all connected buses from a `stop`, we **clear** the buses associated with that `stop` in our hash map (`stop_to_buses[stop].clear()`). This prevents us from re-evaluating the same intersection when another bus reaches the same stop, keeping the traversal strictly linear.

---

## ⚡ Complexity Analysis

Let $S$ be the total number of stops across all routes (i.e., `sum(routes[i].length)`).

- **Time Complexity:** $\mathcal{O}(S)$ — We build the hash map in $\mathcal{O}(S)$ time. During the BFS, each bus is popped exactly once, and its route is scanned exactly once. Furthermore, due to clearing the hash map lists, we iterate over the connections from a stop exactly once. Thus, the total work is proportional to the size of the input.
- **Space Complexity:** $\mathcal{O}(S)$ — The hash map `stop_to_buses` stores exactly $S$ pairs. The BFS queue and `visited_buses` boolean array take up to $\mathcal{O}(\text{number of buses})$ space, which is bound by $\mathcal{O}(S)$.

---

## 🔍 Edge Cases Considered

- `source == target`: We don't need to take any buses. Evaluated early and returns `0`.
- The `source` or `target` doesn't exist in any route: Queue won't populate, loop finishes safely and returns `-1`.
- Disconnected route clusters: Naturally returns `-1` once the reachable connected component is exhausted.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
