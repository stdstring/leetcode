#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int findTilt(TreeNode* root) const
    {
        if (root == nullptr)
            return 0;
        int tiltValue = 0;
        traverseTree(root, tiltValue);
        return tiltValue;
    }

private:
    int traverseTree(TreeNode* root, int &tiltValue) const
    {
        const int leftTreeSum = root->left == nullptr ? 0 : traverseTree(root->left, tiltValue);
        const int rightTreeSum = root->right == nullptr ? 0 : traverseTree(root->right, tiltValue);
        tiltValue += std::abs(leftTreeSum - rightTreeSum);
        return leftTreeSum + rightTreeSum + root->val;
    }
};

}

using CommonLib::Codec;

namespace BinaryTreeTiltTask
{

TEST(BinaryTreeTiltTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.findTilt(Codec::createTree("[1,2,3]").get()));
    ASSERT_EQ(15, solution.findTilt(Codec::createTree("[4,2,9,3,5,null,7]").get()));
    ASSERT_EQ(9, solution.findTilt(Codec::createTree("[21,7,14,1,1,2,2,3,3]").get()));
}

}