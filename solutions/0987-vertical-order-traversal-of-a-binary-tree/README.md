# [987. Vertical Order Traversal of a Binary Tree](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/)

**Difficulty:** `Hard`  
**Topics:** [Trees](../../topics/trees.md), Hash Table, Sorting, Depth-First Search

---

## 📌 Problem Statement

Given the `root` of a binary tree, calculate the **vertical order traversal** of the binary tree.

For each node at position `(row, col)`, its left and right children will be at positions `(row + 1, col - 1)` and `(row + 1, col + 1)` respectively. The root of the tree is at `(0, 0)`.

The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, **sort these nodes by their values**.

### Example 1:
```
Input: root = [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]
Explanation:
Column -1: Only node 9 is in this column.
Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
Column 1: Only node 20 is in this column.
Column 2: Only node 7 is in this column.
```

### Constraints:
- The number of nodes in the tree is in the range `[1, 1000]`.
- `0 <= Node.val <= 1000`

---

## 💡 Intuition & Approach

To capture a vertical mapping, we must dynamically track coordinates `(row, col)` as we traverse down the tree. 
Unlike a standard top-down Level Order Traversal (BFS) which inherently preserves row order but ignores multi-node collisions within identical coordinate overlap, this problem demands strict sorting rules:
1. Ordered predominantly left-to-right by **column**.
2. Ordered secondly top-to-bottom by **row**.
3. Ordered tertiarily by **node value** (when two nodes share the exact same `(row, col)`).

**The Optimal Data Structure:**
We can use a deeply nested map structure in C++ to inherently maintain sorting constraints effortlessly:
```cpp
std::map<int, std::map<int, std::multiset<int>>>
```
- The outer `map` dictates the `column` (automatically sorting negative to positive).
- The inner `map` dictates the `row` (automatically sorting top down).
- The innermost `multiset` handles duplicate coordinates, inherently sorting their `val` payload.

**Execution Steps:**
1. Execute a pre-order Depth-First Search (`DFS`) injecting the `(row, col)` states.
2. Insert each visited node value into our deeply nested map structure.
3. Upon completion, iterate the structure linearly to compile and unpack the values into a clean 2D vector matrix for our final return.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$ — Every node is inserted into the map hierarchy, which performs binary tree balancing under the hood requiring $\log N$ cost per insertion. Building the vector from the structure takes strictly linear $\mathcal{O}(N)$ effort.
- **Space Complexity:** $\mathcal{O}(N)$ — The hash structures fully consume memory directly proportional to the node count.

---

## 🔍 Edge Cases Considered

- Complete overlaps: Two nodes mapping to the identical location `(row, col)` are reliably auto-sorted via the `std::multiset`.
- Skewed Trees: Narrow trees generating highly negative columns (e.g. consistently going left) organically fall into correct bounds because `std::map` handles unbounded, negative arbitrary indices natively.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
