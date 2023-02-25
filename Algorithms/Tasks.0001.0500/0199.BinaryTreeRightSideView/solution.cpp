#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    std::vector<int> rightSideView(TreeNode* root) const
    {
        if (root == nullptr)
            return {};
        std::vector<int> result;
        traverseTree(root, 1, result);
        return result;
    }

private:
    void traverseTree(TreeNode* root, size_t level, std::vector<int> &data) const
    {
        if (level > data.size())
            data.push_back(root->val);
        if (root->right != nullptr)
            traverseTree(root->right, level + 1, data);
        if (root->left != nullptr)
            traverseTree(root->left, level + 1, data);
    }
};

}

using CommonLib::Codec;

namespace BinaryTreeRightSideViewTask
{

TEST(BinaryTreeRightSideViewTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 4}), solution.rightSideView(Codec::createTree("[1,2,3,null,5,null,4]").get()));
}

}