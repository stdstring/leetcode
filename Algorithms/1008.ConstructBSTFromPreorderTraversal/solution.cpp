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
    TreeNode* bstFromPreorder(std::vector<int> const &preorder) const
    {
        return constructTree(preorder, 0, preorder.size());
    }

private:
    TreeNode* constructTree(std::vector<int> const &preorder, size_t index, size_t size) const
    {
        if (size == 0)
            return nullptr;
        TreeNode* root = new TreeNode(preorder[index]);
        if (size == 1)
            return root;
        const size_t leftSubtreeSize = calcLeftSubtreeSize(preorder, index, size);
        const size_t rightSubtreeSize = size - 1 - leftSubtreeSize;
        root->left = constructTree(preorder, index + 1, leftSubtreeSize);
        root->right = constructTree(preorder, index + 1 + leftSubtreeSize, rightSubtreeSize);
        return root;
    }

    size_t calcLeftSubtreeSize(std::vector<int> const &preorder, size_t index, size_t size) const
    {
        const int value = preorder[index];
        ++index;
        --size;
        if (preorder[index] > value)
            return 0;
        if (preorder[index + size - 1] < value)
            return size;
        size_t left = index;
        size_t right = index + size - 1;
        while (right - left > 1)
        {
            const size_t middle = (right + left) / 2;
            if (preorder[middle] > value)
                right = middle;
            else
                left = middle;
        }
        return right - index;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace ConstructBSTFromPreorderTraversalTask
{
    TEST(ConstructBSTFromPreorderTraversalTaskTests, Examples)
    {
        const Solution solution;
        ASSERT_EQ("[8,5,10,1,7,null,12]", Codec::createData(createTreeHolder(solution.bstFromPreorder({8, 5, 1, 7, 10, 12}))));
        ASSERT_EQ("[1,null,3]", Codec::createData(createTreeHolder(solution.bstFromPreorder({1, 3}))));
    }

    TEST(ConstructBSTFromPreorderTraversalTaskTests, FromWrongAnswers)
    {
        const Solution solution;
        ASSERT_EQ("[15,13,18,12]", Codec::createData(createTreeHolder(solution.bstFromPreorder({15, 13, 12, 18}))));
        ASSERT_EQ("[3,2,8,null,null,4,19,null,null,15,null,13]", Codec::createData(createTreeHolder(solution.bstFromPreorder({3, 2, 8, 4, 19, 15, 13}))));
    }
}
