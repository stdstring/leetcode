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

using CommonLib::createTreeHolder;
using CommonLib::checkAndDeleteTree;

namespace ConvertSortedArrayToBinarySearchTreeTask
{

TEST(ConvertSortedArrayToBinarySearchTreeTaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteTree(createTreeHolder(new TreeNode(0, new TreeNode(-10, nullptr, -3), new TreeNode(5, nullptr, 9))).get(), solution.sortedArrayToBST({-10, -3, 0, 5, 9}));
}

TEST(ConvertSortedArrayToBinarySearchTreeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    checkAndDeleteTree(createTreeHolder(new TreeNode(0)).get(), solution.sortedArrayToBST({0}));
    checkAndDeleteTree(createTreeHolder(new TreeNode(2, new TreeNode(0, nullptr, 1), new TreeNode(4, 3, 5))).get(), solution.sortedArrayToBST({0, 1, 2, 3, 4, 5}));
}

}