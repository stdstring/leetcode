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
    TreeNode* balanceBST(TreeNode* root) const
    {
        std::vector<int> values;
        collectValues(root, values);
        return generateTree(values, 0, values.size() - 1);
    }

private:
    void collectValues(TreeNode* root, std::vector<int> &values) const
    {
        if (root->left != nullptr)
            collectValues(root->left, values);
        values.push_back(root->val);
        if (root->right != nullptr)
            collectValues(root->right, values);
    }

    [[nodiscard]] TreeNode* generateTree(std::vector<int> const &values, size_t fromIndex, size_t toIndex) const
    {
        const size_t size = toIndex - fromIndex + 1;
        switch (size)
        {
            case 1:
                return new TreeNode(values[fromIndex]);
            case 2:
                return new TreeNode(values[fromIndex + 1], new TreeNode(values[fromIndex]), nullptr);
            case 3:
                return new TreeNode(values[fromIndex + 1], new TreeNode(values[fromIndex]), new TreeNode(values[fromIndex + 2]));
            default:
                const size_t middleIndex = fromIndex + size / 2;
                return new TreeNode(values[middleIndex], generateTree(values, fromIndex, middleIndex - 1), generateTree(values, middleIndex + 1, toIndex));
        }
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace BalanceBinarySearchTreeTask
{

TEST(BalanceBinarySearchTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("[3,2,4,1]", Codec::createData(createTreeHolder(solution.balanceBST(Codec::createTree("[1,null,2,null,3,null,4,null,null]").get()))));
    ASSERT_EQ("[2,1,3]", Codec::createData(createTreeHolder(solution.balanceBST(Codec::createTree("[2,1,3]").get()))));
}

}