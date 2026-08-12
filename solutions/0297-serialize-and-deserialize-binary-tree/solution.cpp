/**
 * Problem: 297. Serialize and Deserialize Binary Tree
 * Difficulty: Hard
 * Topics: Tree, Depth-First Search, Breadth-First Search, Design, String, Binary Tree
 * LeetCode Link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
 * 
 * Time Complexity:  O(N) for both serialize and deserialize (where N is the number of nodes)
 * Space Complexity: O(N) for recursion stack and serialized string representation
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
private:
    void serializeHelper(TreeNode* root, ostringstream& out) {
        if (!root) {
            out << "# ";
            return;
        }
        out << root->val << " ";
        serializeHelper(root->left, out);
        serializeHelper(root->right, out);
    }

    TreeNode* deserializeHelper(istringstream& in) {
        string val;
        if (!(in >> val)) return nullptr;

        if (val == "#") {
            return nullptr;
        }

        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserializeHelper(in);
        root->right = deserializeHelper(in);
        return root;
    }

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serializeHelper(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserializeHelper(in);
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

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Codec codec;

    // Test Case 1: Standard Tree [1, 2, 3, null, null, 4, 5]
    {
        TreeNode* root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->right->left = new TreeNode(4);
        root->right->right = new TreeNode(5);

        string serialized = codec.serialize(root);
        cout << "Test 1 - Serialized: " << serialized << endl;

        TreeNode* deserialized = codec.deserialize(serialized);
        assert(isSameTree(root, deserialized));
        cout << "Test 1 Passed: Tree deserialized accurately!" << endl;

        deleteTree(root);
        deleteTree(deserialized);
    }

    // Test Case 2: Empty Tree []
    {
        TreeNode* root = nullptr;
        string serialized = codec.serialize(root);
        cout << "Test 2 - Empty tree serialized: " << serialized << endl;

        TreeNode* deserialized = codec.deserialize(serialized);
        assert(deserialized == nullptr);
        cout << "Test 2 Passed: Empty tree correctly reconstructed as nullptr!" << endl;
    }

    // Test Case 3: Single Node [42]
    {
        TreeNode* root = new TreeNode(42);
        string serialized = codec.serialize(root);
        TreeNode* deserialized = codec.deserialize(serialized);
        assert(isSameTree(root, deserialized));
        cout << "Test 3 Passed: Single node tree reconstructed!" << endl;

        deleteTree(root);
        deleteTree(deserialized);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
