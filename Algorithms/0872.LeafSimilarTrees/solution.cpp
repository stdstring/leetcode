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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) const
    {
        std::vector<int> leaves1;
        collectLeaves(root1, leaves1);
        std::vector<int> leaves2;
        collectLeaves(root2, leaves2);
        if (leaves1.size() != leaves2.size())
            return false;
        for (size_t index = 0; index < leaves1.size(); ++index)
        {
            if (leaves1[index] != leaves2[index])
                return false;
        }
        return true;
    }

private:
    void collectLeaves(TreeNode* root, std::vector<int> &leaves) const
    {
        if ((root->left == nullptr) && (root->right == nullptr))
            leaves.emplace_back(root->val);
        else
        {
            if (root->left != nullptr)
                collectLeaves(root->left, leaves);
            if (root->right != nullptr)
                collectLeaves(root->right, leaves);
        }
    }
};

}

using CommonLib::Codec;

namespace LeafSimilarTreesTask
{

TEST(BinaryTreeLevelOrderTraversalIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.leafSimilar(Codec::createTree("[3,5,1,6,2,9,8,null,null,7,4]").get(),
                                         Codec::createTree("[3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]").get()));
    ASSERT_EQ(false, solution.leafSimilar(Codec::createTree("[1,2,3]").get(), Codec::createTree("[1,3,2]").get()));
}

}