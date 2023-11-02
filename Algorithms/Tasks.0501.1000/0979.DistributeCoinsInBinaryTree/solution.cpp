#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    [[nodiscard]] int distributeCoins(TreeNode* root) const
    {
        return traverseTree(root).Cost;
    }

private:
    struct TraverseData
    {
        TraverseData(int cost, int balance) : Cost(cost), Balance(balance)
        {
        }
        int Cost;
        int Balance;
    };

    [[nodiscard]] TraverseData traverseTree(TreeNode* root) const
    {
        if (root == nullptr)
            return TraverseData(0, 0);
        const TraverseData leftData = traverseTree(root->left);
        const TraverseData rightData = traverseTree(root->right);
        const int cost = leftData.Cost + rightData.Cost + std::abs(leftData.Balance) + std::abs(rightData.Balance);
        const int balance = leftData.Balance + rightData.Balance + (root->val - 1);
        return TraverseData(cost, balance);
    }
};

}

using CommonLib::Codec;

namespace DistributeCoinsInBinaryTreeTask
{

TEST(DistributeCoinsInBinaryTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.distributeCoins(Codec::createTree("[3,0,0]").get()));
    ASSERT_EQ(3, solution.distributeCoins(Codec::createTree("[0,3,0]").get()));
}

}