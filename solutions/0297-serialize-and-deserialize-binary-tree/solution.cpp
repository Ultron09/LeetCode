/**
 * Problem: 297. Serialize and Deserialize Binary Tree
 * Difficulty: Hard
 * Topics: String, Tree, Depth-First Search, Breadth-First Search, Design, Binary Tree
 * LeetCode Link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
 * 
 * Time Complexity:
 *   - serialize():   O(N) - visits each node once
 *   - deserialize(): O(N) - reconstructs each node once
 * Space Complexity:  O(N) - string representation and recursion call stack
 */

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

#ifdef LOCAL_TEST
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};
#endif

class Codec {
private:
    void serializeDfs(TreeNode* node, ostringstream& out) {
        if (!node) {
            out << "# ";
            return;
        }
        out << node->val << " ";
        serializeDfs(node->left, out);
        serializeDfs(node->right, out);
    }

    TreeNode* deserializeDfs(istringstream& in) {
        string val;
        if (!(in >> val) || val == "#") {
            return nullptr;
        }
        TreeNode* node = new TreeNode(stoi(val));
        node->left = deserializeDfs(in);
        node->right = deserializeDfs(in);
        return node;
    }

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serializeDfs(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserializeDfs(in);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

int main() {
    Codec codec;

    // Test Case 1: [1,2,3,null,null,4,5]
    {
        TreeNode* root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->right->left = new TreeNode(4);
        root->right->right = new TreeNode(5);

        string serialized = codec.serialize(root);
        TreeNode* deserialized = codec.deserialize(serialized);

        assert(isSameTree(root, deserialized));
        cout << "Test 1 Passed: [1,2,3,null,null,4,5] serialized to: " << serialized << endl;
    }

    // Test Case 2: Empty Tree
    {
        TreeNode* root = nullptr;
        string serialized = codec.serialize(root);
        TreeNode* deserialized = codec.deserialize(serialized);

        assert(isSameTree(root, deserialized));
        cout << "Test 2 Passed: Empty tree serialized to: \"" << serialized << "\"" << endl;
    }

    // Test Case 3: Single Node with Negative Value
    {
        TreeNode* root = new TreeNode(-42);
        string serialized = codec.serialize(root);
        TreeNode* deserialized = codec.deserialize(serialized);

        assert(isSameTree(root, deserialized));
        cout << "Test 3 Passed: Single negative node [-42]" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
