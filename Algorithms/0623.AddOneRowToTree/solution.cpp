#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d)
    {
        if (d == 1)
            root = new TreeNode(v, root, nullptr);
        else
            traversalTree(root, v, d, 1);
        return root;
    }

private:
    void traversalTree(TreeNode* root, int value, int depth, int currentDepth)
    {
        if (root == nullptr)
            return;
        if ((currentDepth + 1) == depth)
        {
            root->left = new TreeNode(value, root->left, nullptr);
            root->right = new TreeNode(value, nullptr, root->right);
        }
        else
        {
            traversalTree(root->left, value, depth, currentDepth + 1);
            traversalTree(root->right, value, depth, currentDepth + 1);
        }
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace AddOneRowToTreeTask
{

TEST(AddOneRowToTreeTaskTests, Examples)
{
    Solution solution;
    ASSERT_EQ("[4,1,1,2,null,null,6,3,1,5]", Codec::createData(createTreeHolder(solution.addOneRow(Codec::createTreeRaw("[4,2,6,3,1,5]"), 1, 2))));
    ASSERT_EQ("[4,2,null,1,1,3,null,null,1]", Codec::createData(createTreeHolder(solution.addOneRow(Codec::createTreeRaw("[4,2,null,3,1]"), 1, 3))));
}

TEST(AddOneRowToTreeTaskTests, FromWrongAnswers)
{
    Solution solution;
    ASSERT_EQ("[1,2,3,4,null,null,null,5,5]", Codec::createData(createTreeHolder(solution.addOneRow(Codec::createTreeRaw("[1,2,3,4]"), 5, 4))));
}

}