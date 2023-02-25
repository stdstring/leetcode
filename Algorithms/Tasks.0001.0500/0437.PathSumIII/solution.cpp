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
    int pathSum(TreeNode* root, int sum) const
    {
        return root == nullptr ? 0 : pathSum(root, sum, {});
    }

private:
    int pathSum(TreeNode* root, int sum, std::vector<int> const &sums) const
    {
        int pathCount = 0;
        std::vector<int> current(sums.cbegin(), sums.cend());
        for (size_t index = 0; index < current.size(); ++index)
        {
            current[index] += root->val;
            if (current[index] == sum)
                ++pathCount;
        }
        current.push_back(root->val);
        if (root->val == sum)
            ++pathCount;
        if (root->left != nullptr)
            pathCount += pathSum(root->left, sum, current);
        if (root->right != nullptr)
            pathCount += pathSum(root->right, sum, current);
        return pathCount;
    }
};

}

using CommonLib::Codec;

namespace PathSumIIITask
{

TEST(PathSumIIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.pathSum(Codec::createTree("[10,5,-3,3,2,null,11,3,-2,null,1]").get(), 8));
    ASSERT_EQ(3, solution.pathSum(Codec::createTree("[5,4,8,11,null,13,4,7,2,null,null,5,1]").get(), 22));
}

}
