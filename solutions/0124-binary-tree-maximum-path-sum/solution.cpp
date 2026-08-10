/**
 * Problem: 124. Binary Tree Maximum Path Sum
 * Difficulty: Hard
 * Topics: Dynamic Programming, Tree, Depth-First Search, Binary Tree
 * LeetCode Link: https://leetcode.com/problems/binary-tree-maximum-path-sum/
 * 
 * Time Complexity:  O(N) single post-order traversal
 * Space Complexity: O(H) recursion stack where H is tree height
 */

#include <iostream>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

// Definition for a binary tree node (guarded for local testing)
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
    int globalMax = INT_MIN;

    int maxGain(TreeNode* node) {
        if (!node) {
            return 0;
        }

        // Maximum path sum on left and right subtrees (clamp to 0 if negative)
        int leftGain = max(0, maxGain(node->left));
        int rightGain = max(0, maxGain(node->right));

        // Price of the new path where `node` serves as the highest apex
        int currentPathSum = node->val + leftGain + rightGain;

        // Update global maximum path sum
        globalMax = max(globalMax, currentPathSum);

        // Return maximum branch gain contribution to parent
        return node->val + max(leftGain, rightGain);
    }

public:
    int maxPathSum(TreeNode* root) {
        globalMax = INT_MIN;
        maxGain(root);
        return globalMax;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: root = [1, 2, 3] -> 6
    {
        TreeNode* root = new TreeNode(1, new TreeNode(2), new TreeNode(3));
        assert(solver.maxPathSum(root) == 6);
        cout << "Test 1 Passed: [1, 2, 3] -> 6" << endl;
        delete root->left;
        delete root->right;
        delete root;
    }

    // Test Case 2: root = [-10, 9, 20, null, null, 15, 7] -> 42
    {
        TreeNode* root = new TreeNode(-10);
        root->left = new TreeNode(9);
        root->right = new TreeNode(20, new TreeNode(15), new TreeNode(7));
        assert(solver.maxPathSum(root) == 42);
        cout << "Test 2 Passed: [-10, 9, 20, null, null, 15, 7] -> 42" << endl;
        delete root->right->left;
        delete root->right->right;
        delete root->right;
        delete root->left;
        delete root;
    }

    // Test Case 3: Single negative node [-3] -> -3
    {
        TreeNode* root = new TreeNode(-3);
        assert(solver.maxPathSum(root) == -3);
        cout << "Test 3 Passed: [-3] -> -3" << endl;
        delete root;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
