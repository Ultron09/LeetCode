# 🌲 Trees & Binary Search Trees

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Binary Trees, Binary Search Trees (BST), and Tree Traversals.

---

## 📖 1. Core Theory & Fundamentals

A Tree is a hierarchical non-linear data structure consisting of nodes connected by edges, with no cycles.

### Standard Binary Tree Node
```cpp
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
```

### Traversals
- **Pre-order (Root -> Left -> Right)**: Used for serialization/cloning.
- **In-order (Left -> Root -> Right)**: Yields sorted order in a Binary Search Tree (BST).
- **Post-order (Left -> Right -> Root)**: Bottom-up evaluation (e.g., maximum depth, diameter, deleting a tree).
- **Level-order (Breadth-First Search)**: Uses a `std::queue` to traverse layer by layer.

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Level Order Traversal (BFS)
```cpp
#include <queue>

vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();
            currentLevel.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(currentLevel);
    }
    return result;
}
```

### Pattern B: Tree Depth / Diameter / Post-Order Recursion
```cpp
// Maximum Depth of Binary Tree
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// Diameter of Binary Tree
int calculateDiameter(TreeNode* root, int& maxDiameter) {
    if (!root) return 0;
    int leftHeight = calculateDiameter(root->left, maxDiameter);
    int rightHeight = calculateDiameter(root->right, maxDiameter);
    maxDiameter = max(maxDiameter, leftHeight + rightHeight);
    return 1 + max(leftHeight, rightHeight);
}
```

### Pattern C: Lowest Common Ancestor (LCA) in Binary Tree
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    
    if (left && right) return root; // p and q are on separate subtrees
    return left ? left : right;
}
```

### Pattern D: Binary Lifting for LCA & Tree Path Distances
When answering many path queries on a general tree of size $N$:
1. Precompute depths and $2^k$-th ancestors with BFS/DFS: $\text{up}[k][u] = \text{up}[k - 1][\text{up}[k - 1][u]]$.
2. For query $(u, v)$, equalize depths, lift simultaneously to find $\text{LCA}(u, v)$ in $\mathcal{O}(\log N)$.
3. Path length $d = \text{depth}[u] + \text{depth}[v] - 2 \cdot \text{depth}[\text{LCA}(u, v)]$.

### Pattern E: Trie / Suffix Tree with Node-Augmented Metadata
When matching longest common suffixes/prefixes with multi-criterion tiebreaking:
1. Reverse strings to transform suffix matching into prefix matching on a Trie.
2. Augment each `TrieNode` with optimal subtree properties (e.g. `minLen`, `bestIdx`).
3. During insertion in natural index order, update node metadata with strict comparison (`len < node->minLen`) to automatically break ties toward earlier indices.
### Pattern F: Post-Order Tree DP (Max Branch Gain & Apex Path)
When finding the maximum path sum across any simple path in a binary tree:
1. **Branch Gain ($\text{gain}(u)$)**: Maximum gain from $u$ extending downward: $u.\text{val} + \max(0, \max(\text{leftGain}, \text{rightGain}))$.
2. **Apex Path Sum**: Path turning at $u$: $u.\text{val} + \max(0, \text{leftGain}) + \max(0, \text{rightGain})$.
3. Update global maximum across all nodes in $\mathcal{O}(N)$ post-order traversal.

### Pattern G: 10-ary Trie Traversal & Subtree Skip Counting (Lexicographical Number Search)
When finding the $k$-th lexicographically ordered integer in $[1, n]$:
1. **Denary Tree Abstraction**: Numbers $1 \dots n$ form a 10-ary tree where node $x$ has children $[10x, 10x+9]$. Pre-order traversal corresponds to lexicographical order.
2. **Subtree Size Counting**: Count numbers sharing prefix `curr` by expanding intervals $[first, last)$ with $\times 10$, summing $\min(n + 1, last) - first$.
3. **Branching**:
   - If $\text{steps} \le k$: target lies outside subtree $\to$ skip subtree ($k \gets k - \text{steps}, curr \gets curr + 1$).
   - If $\text{steps} > k$: target lies inside subtree $\to$ descend down ($k \gets k - 1, curr \gets curr \times 10$).
4. **Complexity**: $\mathcal{O}((\log_{10} n)^2)$ time and $\mathcal{O}(1)$ space.

### Pattern H: Preorder DFS Serialization with Null Sentinels (Serialize and Deserialize Binary Tree)
When serializing and reconstructing arbitrary binary tree structures:
1. **Preorder DFS Encoding**: Traverse `Root -> Left -> Right`. Append `"# "` for null pointers and `to_string(val) + " "` for real nodes.
2. **Deterministic Deserialization**: Wrap serialized tokens in an `istringstream`. Each recursive call extracts a token: if `"#"` return `nullptr`, else construct `TreeNode(val)`, assign `left = deserializeHelper(in)`, `right = deserializeHelper(in)`, and return the root.
3. **Complexity**: $\mathcal{O}(N)$ time and $\mathcal{O}(N)$ space.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Skewed Trees & Recursion Depth**: For degenerate linked-list trees, recursive DFS uses $\mathcal{O}(N)$ stack space and can cause stack overflow.
2. **BST Validation**: Validating BST cannot just check if `root->left->val < root->val`. The left subtree must be strictly less than `root->val` for ALL nodes. Always pass valid interval ranges `(low, high)` using `long long`.
3. **Empty Trees**: Always handle `root == nullptr` as the first base case.
4. **Log Table Size**: For $N \le 10^5$, $\lceil \log_2(10^5) \rceil = 17$, use table size $18$.
5. **All-Negative Node Trees**: Initialize global maxima to `INT_MIN` so single least-negative node values are picked correctly.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 124 | [Binary Tree Maximum Path Sum](../solutions/0124-binary-tree-maximum-path-sum/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(H)$ | [C++](../solutions/0124-binary-tree-maximum-path-sum/solution.cpp) |
| 297 | [Serialize and Deserialize Binary Tree](../solutions/0297-serialize-and-deserialize-binary-tree/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0297-serialize-and-deserialize-binary-tree/solution.cpp) |
| 440 | [K-th Smallest in Lexicographical Order](../solutions/0440-k-th-smallest-in-lexicographical-order/README.md) | `Hard` | $\mathcal{O}((\log_{10} N)^2)$ | $\mathcal{O}(1)$ | [C++](../solutions/0440-k-th-smallest-in-lexicographical-order/solution.cpp) |
| 745 | [Prefix and Suffix Search](../solutions/0745-prefix-and-suffix-search/README.md) | `Hard` | $\mathcal{O}(L)$ query | $\mathcal{O}(N \cdot L^2)$ | [C++](../solutions/0745-prefix-and-suffix-search/solution.cpp) |
| 834 | [Sum of Distances in Tree](../solutions/0834-sum-of-distances-in-tree/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0834-sum-of-distances-in-tree/solution.cpp) |
| 968 | [Binary Tree Cameras](../solutions/0968-binary-tree-cameras/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(H)$ | [C++](../solutions/0968-binary-tree-cameras/solution.cpp) |
| 987 | [Vertical Order Traversal of a Binary Tree](../solutions/0987-vertical-order-traversal-of-a-binary-tree/README.md) | `Hard` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0987-vertical-order-traversal-of-a-binary-tree/solution.cpp) |
| 3093 | [Longest Common Suffix Queries](../solutions/3093-longest-common-suffix-queries/README.md) | `Hard` | $\mathcal{O}(\sum |W_c| + \sum |W_q|)$ | $\mathcal{O}(\sum |W_c| \cdot \Sigma)$ | [C++](../solutions/3093-longest-common-suffix-queries/solution.cpp) |
| 3559 | [Number of Ways to Assign Edge Weights II](../solutions/3559-number-of-ways-to-assign-edge-weights-ii/README.md) | `Hard` | $\mathcal{O}((N + Q) \log N)$ | $\mathcal{O}(N \log N)$ | [C++](../solutions/3559-number-of-ways-to-assign-edge-weights-ii/solution.cpp) |



