# [968. Binary Tree Cameras](https://leetcode.com/problems/binary-tree-cameras/)

**Difficulty:** `Hard`  
**Topics:** [Tree](../../topics/trees.md), [Depth-First Search](../../topics/graphs.md), [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

You are given the `root` of a binary tree. We install cameras on the tree nodes where each camera at a node can monitor its parent, itself, and its immediate children.

Return the minimum number of cameras needed to monitor all nodes of the tree.

### Example 1:
```
Input: root = [0,0,null,0,0]
Output: 1
Explanation: One camera is enough to monitor all nodes if placed at the root's left child.
```

### Example 2:
```
Input: root = [0,0,null,0,null,0,null,null,0]
Output: 2
Explanation: At least two cameras are needed to monitor all nodes of the tree.
```

### Constraints:
- The number of nodes in the tree is in the range `[1, 1000]`.
- `Node.val == 0`

---

## 💡 Intuition & Approach

To minimize the number of cameras, we should strategically place cameras as high up the tree as possible to maximize their coverage (parent + self + children). 
Placing a camera at a leaf node is suboptimal because it only covers the leaf and its parent. If we instead place it at the leaf's parent, it covers the leaf, the parent itself, the parent's parent, and any other children the parent might have.

This leads to a **Greedy Depth-First Search (Bottom-Up)** approach. We process the tree from the leaves upwards, evaluating the state of each node based on the states of its children.

1. **Node States**:
   We can define three states for a node:
   - `0` (Uncovered): The node is not monitored and requires a camera to be placed at its parent.
   - `1` (Has Camera): A camera is placed at this node.
   - `2` (Covered): The node is monitored by a camera at one of its children (but doesn't have a camera itself).

2. **DFS Transitions**:
   When evaluating a node, we first fetch the states of its left and right children.
   - **Base Case**: A `null` child doesn't need to be covered, so we treat it as `Covered (2)`.
   - **Transition 1**: If **either** child is `Uncovered (0)`, we **must** place a camera at the current node to cover that child. We increment our camera count and return `Has Camera (1)`.
   - **Transition 2**: If **either** child `Has Camera (1)` (and the other isn't `Uncovered`), the current node is naturally monitored. We return `Covered (2)`.
   - **Transition 3**: If **both** children are `Covered (2)`, it means they are monitored but neither has a camera. This implies our current node is `Uncovered (0)` and relies on its parent to get covered.

3. **Root Check**:
   After the DFS traversal completes at the root, if the root itself is left `Uncovered (0)`, it has no parent to cover it! We must place one final camera at the root and increment our count.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N$ is the number of nodes in the tree. We perform a single post-order traversal, visiting each node exactly once.
- **Space Complexity:** $\mathcal{O}(H)$ where $H$ is the height of the tree. This accounts for the recursion stack space, which takes $\mathcal{O}(N)$ in the worst-case (skewed tree) and $\mathcal{O}(\log N)$ in the best-case (balanced tree).

---

## 🔍 Edge Cases Considered

- Single Node Tree: Root is evaluated as `Uncovered (0)` immediately, and the final check gracefully adds `1` camera.
- Skewed/Linked-List Trees: Correctly places cameras on alternating nodes to perfectly maximize parent+child coverage continuously up the chain.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
