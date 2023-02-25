#include <numeric>
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
    int sumRootToLeaf(TreeNode* root) const
    {
        std::vector<int> dest;
        generateLeafNumbers(root, 0, dest);
        return std::accumulate(dest.cbegin(), dest.cend(), 0);
    }

private:
    void generateLeafNumbers(TreeNode* root, int prefixValue, std::vector<int> &dest) const
    {
        prefixValue = prefixValue * 2 + root->val;
        if (root->left == nullptr && root->right == nullptr)
            dest.push_back(prefixValue);
        else
        {
            if (root->left != nullptr)
                generateLeafNumbers(root->left, prefixValue, dest);
            if (root->right != nullptr)
                generateLeafNumbers(root->right, prefixValue, dest);
        }
    }
};

}

using CommonLib::Codec;

namespace SumOfRootToLeafBinNumbersTask
{

TEST(SumOfRootToLeafBinNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(22, solution.sumRootToLeaf(Codec::createTree("[1,0,1,0,1,0,1]").get()));
    ASSERT_EQ(0, solution.sumRootToLeaf(Codec::createTree("[0]").get()));
}

}