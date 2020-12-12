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
    TreeNode* buildTree(std::vector<int> const &inorder, std::vector<int> const &postorder) const
    {
        size_t postorderRIndex = 0;
        return buildTree(inorder, postorder, postorderRIndex, 0, inorder.size());
    }

private:
    TreeNode* buildTree(std::vector<int> const &inorder, std::vector<int> const &postorder, size_t &postorderRIndex, size_t inorderRangeStart, size_t inorderRangeSize) const
    {
        if (inorderRangeSize == 0)
            return nullptr;
        const int currentValue = postorder[postorder.size() - 1 - postorderRIndex];
        ++postorderRIndex;
        if (inorderRangeSize == 1)
            return new TreeNode(currentValue);
        const size_t currentValueIndex = findValueInorderIndex(inorder, inorderRangeStart, inorderRangeSize, currentValue);
        const size_t leftSize = currentValueIndex - inorderRangeStart;
        const size_t rightSize = inorderRangeSize - leftSize - 1;
        TreeNode* rightSubtree = buildTree(inorder, postorder, postorderRIndex, currentValueIndex + 1, rightSize);
        TreeNode* leftSubtree = buildTree(inorder, postorder, postorderRIndex, inorderRangeStart, leftSize);
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

namespace ConstructBinaryTreeFromInorderPostorderTraversalTask
{

TEST(ConstructBinaryTreeFromPreorderInorderTraversalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[3,9,20,null,null,15,7]", Codec::createData(createTreeHolder(solution.buildTree({9, 3, 15, 20, 7}, {9, 15, 7, 20, 3}))));
}

}