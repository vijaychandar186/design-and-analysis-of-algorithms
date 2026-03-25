// Lab 08 – Various Tree Traversals
// Description: Build a binary search tree from input and perform
//              in-order, pre-order, and post-order traversals.
//              Time complexity: O(n) per traversal.

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left  = insert(root->left,  val);
    else                 root->right = insert(root->right, val);
    return root;
}

void inOrder(TreeNode* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

void preOrder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(TreeNode* root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << " ";
}

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter node values:\n";

    TreeNode* root = nullptr;
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        root = insert(root, v);
    }

    cout << "In-order   (sorted): "; inOrder(root);   cout << "\n";
    cout << "Pre-order  (root first): "; preOrder(root);  cout << "\n";
    cout << "Post-order (root last):  "; postOrder(root); cout << "\n";
    return 0;
}
