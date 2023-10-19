/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
#include <queue>
using namespace std;
class BSTIterator {
typedef struct linked_p
{
    TreeNode* next;
    int val;
}linked_p_t;
public:
    BSTIterator(TreeNode* root) {
        if(!root)
            return;
        //construct linked list
        link(root);
    }
    void link(TreeNode* root) {
        if(!root->left && !root->right)
        {
            nodes_.push(root);
            return;
        }
        if(root->left)
            link(root->left);
        nodes_.push(root);
        if(root->right)
            link(root->right);
    }
    
    int next() {
        TreeNode* node = nodes_.front();
        nodes_.pop();
        return node->val;
    }
    
    bool hasNext() {
        return !nodes_.empty();
    }
    queue<TreeNode*> nodes_;
    
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */