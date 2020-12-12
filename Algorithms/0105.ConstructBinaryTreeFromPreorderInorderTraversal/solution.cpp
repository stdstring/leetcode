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
    TreeNode* buildTree(std::vector<int> const &preorder, std::vector<int> const &inorder) const
    {
        size_t preorderIndex = 0;
        return buildTree(preorder, inorder, preorderIndex, 0, inorder.size());
    }

private:
    TreeNode* buildTree(std::vector<int> const &preorder, std::vector<int> const &inorder, size_t &preorderIndex, size_t inorderRangeStart, size_t inorderRangeSize) const
    {
        if (inorderRangeSize == 0)
            return nullptr;
        const int currentValue = preorder[preorderIndex++];
        if (inorderRangeSize == 1)
            return new TreeNode(currentValue);
        const size_t inorderValueIndex = findValueInorderIndex(inorder, inorderRangeStart, inorderRangeSize, currentValue);
        const size_t leftSize = inorderValueIndex - inorderRangeStart;
        TreeNode* leftSubtree = buildTree(preorder, inorder, preorderIndex, inorderRangeStart, leftSize);
        const size_t rightSize = inorderRangeSize - leftSize - 1;
        TreeNode* rightSubtree = buildTree(preorder, inorder, preorderIndex, inorderValueIndex + 1, rightSize);
        return new TreeNode(currentValue, leftSubtree, rightSubtree);
    }

    size_t findValueInorderIndex(std::vector<int> const &inorder, size_t inorderStart, size_t inorderRangeSize, int value) const
    {
        for (size_t shift = 0; shift < inorderRangeSize; ++shift)
        {
            if (inorder[inorderStart + shift] == value)
                return inorderStart + shift;
        }
        throw std::out_of_range("value");
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace ConstructBinaryTreeFromPreorderInorderTraversalTask
{

TEST(ConstructBinaryTreeFromPreorderInorderTraversalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[3,9,20,null,null,15,7]", Codec::createData(createTreeHolder(solution.buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7}))));
}

}