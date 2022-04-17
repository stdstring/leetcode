#include <utility>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* increasingBST(TreeNode* root) const
    {
        return convertToChain(root).first;
    }

private:
    std::pair<TreeNode*, TreeNode*> convertToChain(TreeNode* root) const
    {
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        TreeNode* newRoot = root;
        TreeNode* newFoot = root;
        if (left != nullptr)
        {
            const std::pair<TreeNode*, TreeNode*> leftChain(convertToChain(left));
            newRoot = leftChain.first;
            leftChain.second->right = root;
        }
        root->left = nullptr;
        if (right != nullptr)
        {
            const std::pair<TreeNode*, TreeNode*> rightChain(convertToChain(right));
            root->right = rightChain.first;
            newFoot = rightChain.second;
        }
        return {newRoot, newFoot};
    }
};

}

using CommonLib::createTreeHolder;
using CommonLib::Codec;

namespace IncreasingOrderSearchTreeTask
{

TEST(IncreasingOrderSearchTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]",
              Codec::createData(createTreeHolder(solution.increasingBST(Codec::createTreeRaw("[5,3,6,2,4,null,8,1,null,null,null,7,9]")))));
    ASSERT_EQ("[1,null,5,null,7]",
              Codec::createData(createTreeHolder(solution.increasingBST(Codec::createTreeRaw("[5,1,7]")))));
}

}