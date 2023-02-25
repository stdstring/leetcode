#include <memory>
#include <string>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* pruneTree(TreeNode* root) const
    {
        const bool containsOne = pruneTreeImpl(root);
        return containsOne ? root : nullptr;
    }

private:
    bool pruneTreeImpl(TreeNode* root) const
    {
        if (root == nullptr)
            return false;
        const bool containsOneLeft = pruneTreeImpl(root->left);
        if (!containsOneLeft)
        {
            delete root->left;
            root->left = nullptr;
        }
        const bool containsOneRight = pruneTreeImpl(root->right);
        if (!containsOneRight)
        {
            delete root->right;
            root->right = nullptr;
        }
        return (root->val == 1) || containsOneLeft || containsOneRight;
    }
};

}

using CommonLib::Codec;

namespace
{

void checkPruneTree(std::string const &source, std::string const &expected)
{
    const std::shared_ptr<TreeNode> tree = Codec::createTree(source);
    const Solution solution;
    ASSERT_EQ(expected, Codec::createDataRaw(solution.pruneTree(tree.get())));
}

}

namespace BinaryTreePruningTask
{

TEST(BinaryTreePruningTaskTests, Examples)
{
    checkPruneTree("[1,null,0,0,1]", "[1,null,0,null,1]");
    checkPruneTree("[1,0,1,0,0,0,1]", "[1,null,1,null,1]");
    checkPruneTree("[1,1,0,1,1,0,1,0]", "[1,1,0,1,1,null,1]");
}

}