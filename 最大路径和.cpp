// 二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

// 路径和 是路径中各节点值的总和。

// 给你一个二叉树的根节点 root ，返回其 最大路径和 。

 

// 示例 1：
//   1
//  / \
// 2   3
// 输入：root = [1,2,3]
// 输出：6
// 解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
// 示例 2：
//   -10
//  /  \
// 9   20
//     /\
//    15 7
// 输入：root = [-10,9,20,null,null,15,7]
// 输出：42
// 解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
 

// 提示：

// 树中节点数目范围是 [1, 3 * 104]
// -1000 <= Node.val <= 1000
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
#include <algorithm>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    int maxGain(TreeNode* root, int* max_path_sum)
    {
        int left_max_gain = INT_MIN, right_max_gain = INT_MIN;
        if(root->left)
            left_max_gain = maxGain(root->left, max_path_sum);
        if(root->right)
            right_max_gain = maxGain(root->right, max_path_sum);
        int root_max_gain = max(max(right_max_gain, 0),max(left_max_gain, 0)) + root->val;
        *max_path_sum = max(*max_path_sum, max(0,left_max_gain)+max(0,right_max_gain)+root->val);
        return root_max_gain;
    }
    int maxPathSum(TreeNode* root) {
        int max_path_sum = root->val;
        int a = maxGain(root, &max_path_sum);
        return max_path_sum;
    }
};