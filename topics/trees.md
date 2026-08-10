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

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Skewed Trees & Recursion Depth**: For degenerate linked-list trees, recursive DFS uses $\mathcal{O}(N)$ stack space and can cause stack overflow.
2. **BST Validation**: Validating BST cannot just check if `root->left->val < root->val`. The left subtree must be strictly less than `root->val` for ALL nodes. Always pass valid interval ranges `(low, high)` using `long long`.
3. **Empty Trees**: Always handle `root == nullptr` as the first base case.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :--- | :--- |
<!-- Problems will be added here -->
