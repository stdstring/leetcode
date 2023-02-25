#include <unordered_set>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool findTarget(TreeNode* root, int k) const
    {
        std::unordered_set<int> knownValues;
        return findTargetInSubtree(root, k, knownValues);
    }

private:
    bool findTargetInSubtree(TreeNode* root, int target, std::unordered_set<int> &knownValues) const
    {
        if (root == nullptr)
            return false;
        if (knownValues.count(target - root->val) == 1)
            return true;
        knownValues.insert(root->val);
        if (findTargetInSubtree(root->left, target, knownValues))
            return true;
        if (findTargetInSubtree(root->right, target, knownValues))
            return true;
        return false;
    }
};

}

using CommonLib::Codec;

namespace TwoSumIVInputIsBSTTask
{

TEST(TwoSumIVInputIsBSTTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.findTarget(Codec::createTree("[5,3,6,2,4,null,7]").get(), 9));
    ASSERT_EQ(false, solution.findTarget(Codec::createTree("[5,3,6,2,4,null,7]").get(), 28));
    ASSERT_EQ(true, solution.findTarget(Codec::createTree("[2,1,3]").get(), 4));
    ASSERT_EQ(false, solution.findTarget(Codec::createTree("[2,1,3]").get(), 1));
    ASSERT_EQ(true, solution.findTarget(Codec::createTree("[2,1,3]").get(), 3));
}

}