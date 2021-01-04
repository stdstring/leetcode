#include <stack>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) const
    {
        std::stack<TreeNode*> pathToPNode;
        buildPathToNode(root, p, pathToPNode);
        std::stack<TreeNode*> pathToQNode;
        buildPathToNode(root, q, pathToQNode);
        TreeNode* lcaNode = nullptr;
        while (!pathToPNode.empty() && !pathToQNode.empty() && pathToPNode.top() == pathToQNode.top())
        {
            lcaNode = pathToPNode.top();
            pathToPNode.pop();
            pathToQNode.pop();
        }
        return lcaNode;
    }

private:
    void buildPathToNode(TreeNode* root, TreeNode* dest, std::stack<TreeNode*> &path) const
    {
        if (root == dest)
        {
            path.push(root);
            return;
        }
        if (root->left != nullptr)
            buildPathToNode(root->left, dest, path);
        if (!path.empty())
        {
            path.push(root);
            return;
        }
        if (root->right != nullptr)
            buildPathToNode(root->right, dest, path);
        if (!path.empty())
            path.push(root);
    }
};

}


using CommonLib::Codec;
using CommonLib::findNodeByValue;

namespace LowestCommonAncestorOfBinaryTreeTask
{

TEST(LowestCommonAncestorOfBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    const std::shared_ptr<TreeNode> tree1 = Codec::createTree("[3,5,1,6,2,0,8,null,null,7,4]");
    ASSERT_EQ(3, solution.lowestCommonAncestor(tree1.get(), findNodeByValue(tree1.get(), 5), findNodeByValue(tree1.get(), 1))->val);
    ASSERT_EQ(5, solution.lowestCommonAncestor(tree1.get(), findNodeByValue(tree1.get(), 5), findNodeByValue(tree1.get(), 4))->val);
    const std::shared_ptr<TreeNode> tree2 = Codec::createTree("[1,2]");
    ASSERT_EQ(1, solution.lowestCommonAncestor(tree2.get(), findNodeByValue(tree2.get(), 1), findNodeByValue(tree2.get(), 2))->val);
}

}