#include <utility>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

struct SubtreeData
{
    SubtreeData(int maxDiffValue, int minValue, int maxValue) : MaxDiffValue(maxDiffValue), MinValue(minValue), MaxValue(maxValue)
    {
    }

    void merge(SubtreeData const &other)
    {
        MaxDiffValue = std::max(MaxDiffValue, other.MaxDiffValue);
        MinValue = std::min(MinValue, other.MinValue);
        MaxValue = std::max(MaxValue, other.MaxValue);
    }

    int MaxDiffValue;
    int MinValue;
    int MaxValue;
};

class Solution
{
public:
    int maxAncestorDiff(TreeNode* root) const
    {
        return calcMaxDiff(root).MaxDiffValue;
    }

private:
    SubtreeData calcMaxDiff(TreeNode* root) const
    {
        SubtreeData data(0, root->val, root->val);
        if (root->left != nullptr)
            data.merge(calcMaxDiff(root->left));
        if (root->right != nullptr)
            data.merge(calcMaxDiff(root->right));
        data.MaxDiffValue = std::max(data.MaxDiffValue, std::abs(root->val - data.MinValue));
        data.MaxDiffValue = std::max(data.MaxDiffValue, std::abs(root->val - data.MaxValue));
        return data;
    }
};

}

using CommonLib::Codec;

namespace MaxDiffBetweenNodeAndAncestorTask
{

TEST(MaxDiffBetweenNodeAndAncestorTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(7, solution.maxAncestorDiff(Codec::createTree("[8,3,10,1,6,null,14,null,null,4,7,13]").get()));
    ASSERT_EQ(3, solution.maxAncestorDiff(Codec::createTree("[1,null,2,null,0,3]").get()));
}

TEST(MaxDiffBetweenNodeAndAncestorTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(4, solution.maxAncestorDiff(Codec::createTree("[2,null,0,null,4,null,3,null,1]").get()));
}

}