# [332. Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), [Stack & Queue](../../topics/stack-and-queue.md), [Greedy](../../topics/greedy.md)

---

## 📌 Problem Statement

You are given a list of airline tickets where `tickets[i] = [fromi, toi]` represent the departure and the arrival airports of one flight. Reconstruct the itinerary in order and return it.

All of the tickets belong to a man who departs from `"JFK"`, thus, the itinerary must begin with `"JFK"`. If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.

For example, the itinerary `["JFK", "LGA"]` has a smaller lexical order than `["JFK", "LGB"]`.

You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.

### Example 1:
```
Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
Output: ["JFK","MUC","LHR","SFO","SJC"]
```

### Example 2:
```
Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"] but it is larger in lexical order.
```

### Constraints:
- $1 \le \text{tickets.length} \le 300$
- $\text{tickets}[i].\text{length} == 2$
- $\text{from}_i.\text{length} == 3$
- $\text{to}_i.\text{length} == 3$
- $\text{from}_i$ and $\text{to}_i$ consist of uppercase English letters.
- $\text{from}_i \ne \text{to}_i$

---

## 💡 Intuition & Approach

### 1. Eulerian Path Formulation
- Finding an itinerary that uses every ticket (directed edge) exactly once starting from `"JFK"` is the textbook definition of finding an **Eulerian Path** in a directed multigraph.
- A standard naive DFS backtracking algorithm might get stuck in a "dead end" prematurely (a node with no remaining outgoing edges before all tickets are consumed), requiring expensive state resets and backtracking.

### 2. Hierholzer's Algorithm (Post-Order DFS)
**Hierholzer's Algorithm** finds an Eulerian path in $\mathcal{O}(E \log E)$ time:
1. **Min-Heap Adjacency List**:
   Store outgoing edges for each airport in a priority queue (`std::priority_queue<string, vector<string>, greater<string>>`) so that we always visit lexicographically smaller destinations first.
2. **Post-Order DFS**:
   - Start from `"JFK"`.
   - While airport $u$ has available outgoing flights $(u, v)$, pop the smallest destination $v$, delete the ticket, and recurse `dfs(v)`.
   - When a node $u$ runs out of outgoing edges (it reaches a dead-end or completes its cycle), append $u$ to the `itinerary` array.
3. **Reversal**:
   - The first node to get stuck at a dead-end must be the absolute final destination of the Eulerian path.
   - Any subcycles traversed along the way are naturally spliced into the path when unwinding the recursion.
   - Reversing the post-order sequence gives the complete, correct Eulerian path from `"JFK"` with minimum lexical order.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(E \log E)$
  - Building the min-heap adjacency list takes $\mathcal{O}(E \log (\text{deg}(u))) \le \mathcal{O}(E \log E)$.
  - Each of the $E$ directed edges is popped and traversed exactly once during the DFS ($\mathcal{O}(E)$).
  - String reversals and array operations take $\mathcal{O}(E \cdot L)$ with $L = 3$.
  - Total runtime is $\mathcal{O}(E \log E)$, executing in $< 5\text{ ms}$ for $E \le 300$.
- **Space Complexity:** $\mathcal{O}(V + E) = \mathcal{O}(E)$
  - Adjacency map stores $E$ tickets across at most $2E$ airports.
  - Recursion call stack depth is at most $E + 1$.

---

## 🔍 Edge Cases Considered

- **Premature Dead Ends (e.g. `JFK -> KUL`, `JFK -> NRT -> JFK`)**:
  - Greedily flying to `"KUL"` first creates a dead end because `"KUL"` has 0 outgoing tickets.
  - Hierholzer's algorithm pushes `"KUL"` into `itinerary` first (at the end of post-order), unwinds back to `"JFK"`, traverses the `"JFK" -> "NRT" -> "JFK"` cycle, and reverses the sequence to produce `["JFK", "NRT", "JFK", "KUL"]`.
- **Parallel Edges / Duplicate Flights**: Handled seamlessly since multigraph edge frequencies are stored as separate items in the priority queue.
- **Multiple Disjoint Subcycles**: Automatically spliced together in the correct sequence.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
