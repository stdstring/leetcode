#include <unordered_set>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) const
    {
        std::unordered_set<TreeNode*> insufficientNodes;
        findInsufficientNodes(root, limit, 0, insufficientNodes);
        return createTree(root, insufficientNodes);
    }

private:
    bool findInsufficientNodes(TreeNode* root, int limit, int parentSum, std::unordered_set<TreeNode*> &insufficientNodes) const
    {
        bool result;
        const int currentSum = parentSum + root->val;
        if ((root->left == nullptr) && (root->right == nullptr))
            result = currentSum >= limit;
        else
        {
            const bool leftResult = root->left == nullptr ? false : findInsufficientNodes(root->left, limit, currentSum, insufficientNodes);
            const bool rightResult = root->right == nullptr ? false : findInsufficientNodes(root->right, limit, currentSum, insufficientNodes);
            result = leftResult || rightResult;
        }
        if (!result)
            insufficientNodes.insert(root);
        return result;
    }

    TreeNode* createTree(TreeNode* root, std::unordered_set<TreeNode*> const &insufficientNodes) const
    {
        if (root == nullptr)
            return nullptr;
        if (insufficientNodes.count(root) == 1)
            return nullptr;
        TreeNode* left = createTree(root->left, insufficientNodes);
        TreeNode* right = createTree(root->right, insufficientNodes);
        return new TreeNode(root->val, left, right);
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace InsufficientNodesInRootToLeafPathTask
{

TEST(InsufficientNodesInRootToLeafPathTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[1,2,3,4,null,null,7,8,9,null,14]",
              Codec::createData(createTreeHolder(solution.sufficientSubset(Codec::createTree("[1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14]").get(), 1))));
    ASSERT_EQ("[5,4,8,11,null,17,4,7,null,null,null,5]",
              Codec::createData(createTreeHolder(solution.sufficientSubset(Codec::createTree("[5,4,8,11,null,17,4,7,1,null,null,5,3]").get(), 22))));
    ASSERT_EQ("[1,null,-3,4]", Codec::createData(createTreeHolder(solution.sufficientSubset(Codec::createTree("[1,2,-3,-5,null,4,null]").get(), -1))));
}

}