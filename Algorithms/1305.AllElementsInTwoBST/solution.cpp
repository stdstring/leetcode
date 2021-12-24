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
    std::vector<int> getAllElements(TreeNode* root1, TreeNode* root2) const
    {
        std::vector<int> dest;
        traverseTree(root1, dest);
        traverseTree(root2, dest);
        std::sort(dest.begin(), dest.end());
        return dest;
    }

private:
    void traverseTree(TreeNode* root, std::vector<int> &dest) const
    {
        if (root == nullptr)
            return;
        dest.push_back(root->val);
        traverseTree(root->left, dest);
        traverseTree(root->right, dest);
    }
};

}

using CommonLib::Codec;

namespace AllElementsInTwoBSTTask
{

TEST(BinarySearchTreeToGreaterSumTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 1, 2, 3, 4}), solution.getAllElements(Codec::createTree("[2,1,4]").get(), Codec::createTree("[1,0,3]").get()));
    ASSERT_EQ(std::vector<int>({1, 1, 8, 8}), solution.getAllElements(Codec::createTree("[1,null,8]").get(), Codec::createTree("[8,1]").get()));
}

}