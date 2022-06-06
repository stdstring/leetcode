#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) const
    {
        TreeNode* parent = nullptr;
        TreeNode* current = root;
        while ((current != nullptr) && (current->val > val))
        {
            parent = current;
            current = current->right;
        }
        TreeNode* insertedNode = new TreeNode(val);
        if (parent == nullptr)
        {
            insertedNode->left = root;
            root = insertedNode;
        }
        else
        {
            insertedNode->left = current;
            parent->right = insertedNode;
        }
        return root;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace MaximumBinaryTreeIITask
{

TEST(MaximumBinaryTreeIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("[5,4,null,1,3,null,null,2]", Codec::createData(createTreeHolder(solution.insertIntoMaxTree(Codec::createTreeRaw("[4,1,3,null,null,2]"), 5))));
    ASSERT_EQ("[5,2,4,null,1,null,3]", Codec::createData(createTreeHolder(solution.insertIntoMaxTree(Codec::createTreeRaw("[5,2,4,null,1]"), 3))));
    ASSERT_EQ("[5,2,4,null,1,3]", Codec::createData(createTreeHolder(solution.insertIntoMaxTree(Codec::createTreeRaw("[5,2,3,null,1]"), 4))));
}

}
