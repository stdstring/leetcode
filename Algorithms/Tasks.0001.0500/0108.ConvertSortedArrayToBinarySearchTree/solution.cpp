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
    TreeNode* sortedArrayToBST(std::vector<int> const &nums) const
    {
        if (nums.empty())
            return nullptr;
        return createBST(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* createBST(std::vector<int> const &nums, size_t from, size_t to) const
    {
        const size_t middle = (from + to) / 2;
        TreeNode* root = new TreeNode(nums[middle]);
        root->left = from == middle ? nullptr : createBST(nums, from, middle - 1);
        root->right = to == middle ? nullptr : createBST(nums, middle + 1, to);
        return root;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace ConvertSortedArrayToBinarySearchTreeTask
{

TEST(ConvertSortedArrayToBinarySearchTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[0,-10,5,null,-3,null,9]", Codec::createData(createTreeHolder(solution.sortedArrayToBST({-10, -3, 0, 5, 9}))));
}

TEST(ConvertSortedArrayToBinarySearchTreeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("[0]", Codec::createData(createTreeHolder(solution.sortedArrayToBST({0}))));
    ASSERT_EQ("[2,0,4,null,1,3,5]", Codec::createData(createTreeHolder(solution.sortedArrayToBST({0, 1, 2, 3, 4, 5}))));
}

}