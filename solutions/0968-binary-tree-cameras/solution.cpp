/**
 * Problem: 968. Binary Tree Cameras
 * Difficulty: Hard
 * Topics: Tree, Depth-First Search, Dynamic Programming
 * LeetCode Link: https://leetcode.com/problems/binary-tree-cameras/
 * 
 * Time Complexity:  O(N) where N is the number of nodes in the binary tree. We visit each node exactly once.
 * Space Complexity: O(H) where H is the height of the tree, representing the recursion stack depth.
 */

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

// Definition for a binary tree node.
#ifdef LOCAL_TEST
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#endif

class Solution {
private:
    int cameras = 0;
    
    // States:
    // 0: Uncovered (needs a camera at parent)
    // 1: Has a camera
    // 2: Covered (but no camera at this node)
    int dfs(TreeNode* node) {
        if (!node) return 2; // Null nodes are inherently covered
        
        int left = dfs(node->left);
        int right = dfs(node->right);
        
        // If either child is uncovered, we MUST place a camera here
        if (left == 0 || right == 0) {
            cameras++;
            return 1;
        }
        
        // If either child has a camera, this node is covered by it
        if (left == 1 || right == 1) {
            return 2;
        }
        
        // Otherwise, both children are covered but don't have cameras.
        // Thus, this node is currently uncovered.
        return 0;
    }

public:
    int minCameraCover(TreeNode* root) {
        cameras = 0;
        // If the root is uncovered after DFS, we need one last camera for the root itself
        if (dfs(root) == 0) {
            cameras++;
        }
        return cameras;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: [0,0,null,0,0]
    TreeNode* root1 = new TreeNode(0);
    root1->left = new TreeNode(0);
    root1->left->left = new TreeNode(0);
    root1->left->right = new TreeNode(0);
    assert(solver.minCameraCover(root1) == 1);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2: [0,0,null,0,null,0,null,null,0]
    TreeNode* root2 = new TreeNode(0);
    root2->left = new TreeNode(0);
    root2->left->left = new TreeNode(0);
    root2->left->left->left = new TreeNode(0);
    root2->left->left->left->right = new TreeNode(0);
    assert(solver.minCameraCover(root2) == 2);
    cout << "Test 2 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
