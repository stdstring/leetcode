#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

struct RobData
{
    RobData(int sumWithRoot, int sumWithoutRoot) : SumWithRoot(sumWithRoot), SumWithoutRoot(sumWithoutRoot)
    {
    }

    int SumWithRoot;
    int SumWithoutRoot;
};

class Solution
{
public:
    int rob(TreeNode* root) const
    {
        const RobData treeRobSums(calcRobSums(root));
        return std::max(treeRobSums.SumWithRoot, treeRobSums.SumWithoutRoot);
    }

private:
    RobData calcRobSums(TreeNode* root) const
    {
        if (root == nullptr)
            return {0, 0};
        const RobData leftRobData(calcRobSums(root->left));
        const RobData rightRobData(calcRobSums(root->right));
        const int sumWithoutRoot = std::max({leftRobData.SumWithRoot + rightRobData.SumWithRoot,
                                             leftRobData.SumWithRoot + rightRobData.SumWithoutRoot,
                                             leftRobData.SumWithoutRoot + rightRobData.SumWithRoot,
                                             leftRobData.SumWithoutRoot + rightRobData.SumWithoutRoot});
        return {root->val + leftRobData.SumWithoutRoot + rightRobData.SumWithoutRoot, sumWithoutRoot};
    }
};

}

using CommonLib::Codec;

namespace HouseRobberIIITask
{

TEST(HouseRobberIIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(7, solution.rob(Codec::createTree("[3,2,3,null,3,null,1]").get()));
    ASSERT_EQ(9, solution.rob(Codec::createTree("[3,4,5,1,3,null,1]").get()));
}

TEST(HouseRobberIIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(7, solution.rob(Codec::createTree("[4,1,null,2,null,3]").get()));
}

}