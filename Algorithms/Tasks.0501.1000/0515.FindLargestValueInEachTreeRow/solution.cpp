#include <algorithm>
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
    std::vector<int> largestValues(TreeNode* root) const
    {
        if (root == nullptr)
            return {};
        std::vector<int> largestValues;
        traverseTree(root, 0, largestValues);
        return largestValues;
    }

private:
    void traverseTree(TreeNode* root, size_t level, std::vector<int> &largestValues) const
    {
        if (level < largestValues.size())
            largestValues[level] = std::max(largestValues[level], root->val);
        else
            largestValues.push_back(root->val);
        if (root->left != nullptr)
            traverseTree(root->left, level + 1, largestValues);
        if (root->right != nullptr)
            traverseTree(root->right, level + 1, largestValues);
    }
};

}

using CommonLib::Codec;

namespace FindLargestValueInEachTreeRowTask
{

TEST(FindLargestValueInEachTreeRowTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 9}), solution.largestValues(Codec::createTree("[1,3,2,5,3,null,9]").get()));
    ASSERT_EQ(std::vector<int>({1, 3}), solution.largestValues(Codec::createTree("[1,2,3]").get()));
    ASSERT_EQ(std::vector<int>({1}), solution.largestValues(Codec::createTree("[1]").get()));
    ASSERT_EQ(std::vector<int>({1, 2}), solution.largestValues(Codec::createTree("[1,null,2]").get()));
    ASSERT_EQ(std::vector<int>({}), solution.largestValues(Codec::createTree("[]").get()));
}

}