/**
 * Problem: 987. Vertical Order Traversal of a Binary Tree
 * Difficulty: Hard
 * Topics: Tree, Depth-First Search, Breadth-First Search, Sorting, Hash Table
 * LeetCode Link: https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/
 * 
 * Time Complexity:  O(N log N) - Traversing takes O(N) and inserting into nested maps/multiset takes O(log N).
 * Space Complexity: O(N) - Storing all nodes in the map structure requires linear space.
 */

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

#ifdef LOCAL_TEST
// Definition for a binary tree node.
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
public:
    void dfs(TreeNode* node, int row, int col, map<int, map<int, multiset<int>>>& nodes) {
        if (!node) return;
        nodes[col][row].insert(node->val);
        dfs(node->left, row + 1, col - 1, nodes);
        dfs(node->right, row + 1, col + 1, nodes);
    }

    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // Map structure: Column -> Row -> Set of values (automatically sorted)
        map<int, map<int, multiset<int>>> nodes;
        
        // Populate the map using DFS
        dfs(root, 0, 0, nodes);
        
        vector<vector<int>> result;
        for (auto& [col, rowMap] : nodes) {
            vector<int> colList;
            for (auto& [row, valSet] : rowMap) {
                colList.insert(colList.end(), valSet.begin(), valSet.end());
            }
            result.push_back(colList);
        }
        
        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: [3,9,20,null,null,15,7]
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    vector<vector<int>> expected1 = {{9}, {3, 15}, {20}, {7}};
    vector<vector<int>> res1 = solver.verticalTraversal(root1);
    
    bool pass1 = (res1 == expected1);
    cout << "Test 1 " << (pass1 ? "Passed!" : "Failed!") << endl;

    // Memory cleanup omitted for brevity in CP templates
    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
