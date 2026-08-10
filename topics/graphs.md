# 🕸️ Graphs & Graph Algorithms

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Graphs, BFS, DFS, Topological Sort, Union-Find, and Shortest Paths.

---

## 📖 1. Core Theory & Fundamentals

A Graph $G = (V, E)$ consists of vertices $V$ and edges $E$.
- **Representations**:
  - **Adjacency List**: `vector<vector<int>> adj;` (Space: $\mathcal{O}(V + E)$, optimal for sparse graphs).
  - **Adjacency Matrix**: `vector<vector<int>> matrix;` (Space: $\mathcal{O}(V^2)$, fast $\mathcal{O}(1)$ edge lookup).

### Key Algorithms & Complexities
- **BFS (Breadth-First Search)**: $\mathcal{O}(V + E)$ - Shortest path in unweighted graphs.
- **DFS (Depth-First Search)**: $\mathcal{O}(V + E)$ - Connected components, cycle detection, pathfinding.
- **Dijkstra's Algorithm**: $\mathcal{O}((V + E) \log V)$ - Single-source shortest path with non-negative weights.
- **Topological Sort (Kahn's / DFS)**: $\mathcal{O}(V + E)$ - Dependency resolution in Directed Acyclic Graphs (DAG).
- **Disjoint Set Union (Union-Find)**: $\mathcal{O}(\alpha(N))$ nearly $\mathcal{O}(1)$ per operation with path compression and rank optimization.

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Disjoint Set Union (DSU / Union-Find)
```cpp
class DisjointSet {
public:
    vector<int> parent, rank;
    int components;

    DisjointSet(int n) : parent(n), rank(n, 0), components(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]); // Path compression
    }

    bool unite(int u, int v) {
        int rootU = find(u), rootV = find(v);
        if (rootU == rootV) return false; // Already connected

        if (rank[rootU] < rank[rootV]) swap(rootU, rootV);
        parent[rootV] = rootU;
        if (rank[rootU] == rank[rootV]) rank[rootU]++;
        components--;
        return true;
    }
};
```

### Pattern B: Topological Sort (Kahn's BFS with In-Degrees)
```cpp
// Course Schedule II: Return topological ordering
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> inDegree(numCourses, 0);

    for (const auto& pre : prerequisites) {
        adj[pre[1]].push_back(pre[0]);
        inDegree[pre[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (inDegree[i] == 0) q.push(i);
    }

    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : adj[u]) {
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }
    return (order.size() == static_cast<size_t>(numCourses)) ? order : vector<int>{};
}
```

### Pattern C: Dijkstra's Algorithm (Shortest Path)
```cpp
#include <queue>

vector<int> dijkstra(int n, vector<vector<pair<int, int>>>& adj, int start) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start}); // {distance, node}

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue; // Stale queue entry

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

### Pattern D: Binary Lifting for Interval / Graph Shortest Path Queries
When edges are defined by value proximity $|nums[i] - nums[j]| \le \text{maxDiff}$, sort nodes by value:
1. Each node connects to a contiguous window of sorted nodes $[i, R_i]$, where $R_i$ is computed via Two Pointers.
2. Build binary lifting table $\text{jump}[i][k] = \text{jump}[\text{jump}[i][k-1]][k-1]$ representing furthest index reached in $2^k$ hops.
3. For query $(u, v)$, greedily take largest powers of $2$ hops to find the exact shortest path distance in $\mathcal{O}(\log N)$ per query.

### Pattern E: Bottleneck Shortest Path / Max-Min Path Score (Binary Search + Dijkstra)
To maximize the minimum edge-cost along a path from source to target subject to a total path weight $\le k$:
1. Binary search the bottleneck threshold $X$ over sorted unique edge costs.
2. In the `check(X)` predicate, filter edges to only include $\text{cost} \ge X$ and enforce vertex validity (e.g. `online[v] == true`).
3. Run Dijkstra's algorithm to find the minimum path sum from source to target. If $\text{dist}[\text{target}] \le k$, search higher; else search lower.

### Pattern F: BFS Shortest Path with Equivalence Class Clearing
When nodes can jump to any other node with an identical attribute (teleport / clique edges):
1. Index all nodes by attribute into a hash map `valToIndices`.
2. Run standard layer-by-layer BFS for unweighted shortest paths.
3. Upon expanding the neighbors of value $V$, immediately erase $V$ from the map (`valToIndices.erase(it)`) to prevent quadratic edge re-traversals, ensuring strict $\mathcal{O}(V + E)$ linear time.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Cycles in Unweighted BFS/DFS**: Always maintain a `visited` set or array to prevent infinite recursion.
2. **0-indexed vs 1-indexed Vertices**: Check if node labels are from $1 \dots N$ or $0 \dots N - 1$ to avoid out-of-bounds indexing.
3. **Negative Cycles**: Dijkstra fails with negative edge weights; use Bellman-Ford or Floyd-Warshall instead.
4. **Disconnected Graph Queries**: In binary lifting queries, if $\text{jump}[\text{start}][\text{maxLevel} - 1] < \text{target}$, return $-1$.
5. **Path Weight Overflow**: Accumulating path weights up to $5 \times 10^{13}$ requires `long long` for distance tables and priority queues.
6. **Clique Edge Reprocessing**: Forgetting to clear equivalence class adjacency lists causes TLE ($\mathcal{O}(N^2)$).

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 1345 | [Jump Game IV](../solutions/1345-jump-game-iv/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/1345-jump-game-iv/solution.cpp) |
| 3534 | [Path Existence Queries in a Graph II](../solutions/3534-path-existence-queries-in-a-graph-ii/README.md) | `Hard` | $\mathcal{O}(N \log N + Q \log N)$ | $\mathcal{O}(N \log N)$ | [C++](../solutions/3534-path-existence-queries-in-a-graph-ii/solution.cpp) |
| 3620 | [Network Recovery Pathways](../solutions/3620-network-recovery-pathways/README.md) | `Hard` | $\mathcal{O}((N + M) \log N \log M)$ | $\mathcal{O}(N + M)$ | [C++](../solutions/3620-network-recovery-pathways/solution.cpp) |



