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
    TreeNode* constructMaximumBinaryTree(std::vector<int> const &nums) const
    {
        return createSubTree(nums, 0, nums.size());
    }

private:
    TreeNode* createSubTree(std::vector<int> const &nums, size_t start, size_t size) const
    {
        if (size == 0)
            return nullptr;
        const size_t maxIndex = findMaxIndex(nums, start, size);
        TreeNode* root = new TreeNode(nums[maxIndex]);
        const size_t leftSize = maxIndex - start;
        root->left = createSubTree(nums, start, leftSize);
        const size_t rightSize = size - leftSize - 1;
        root->right = createSubTree(nums, maxIndex + 1, rightSize);
        return root;
    }

    size_t findMaxIndex(std::vector<int> const &nums, size_t start, size_t size) const
    {
        size_t maxIndex = start;
        for (size_t index = 1; index < size; ++index)
        {
            if (nums[start + index] > nums[maxIndex])
                maxIndex = start + index;
        }
        return maxIndex;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace MaximumBinaryTreeTask
{

TEST(MaximumBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[6,3,5,null,2,0,null,null,1]", Codec::createData(createTreeHolder(solution.constructMaximumBinaryTree({3, 2, 1, 6, 0, 5}))));
    ASSERT_EQ("[3,null,2,null,1]", Codec::createData(createTreeHolder(solution.constructMaximumBinaryTree({3, 2, 1}))));
}

}
