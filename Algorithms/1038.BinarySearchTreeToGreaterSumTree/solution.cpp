#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* bstToGst(TreeNode* root) const
    {
        int greaterKeysSum = 0;
        return createGst(root, greaterKeysSum);
    }

private:
    TreeNode* createGst(TreeNode* bstRoot, int &greaterKeysSum) const
    {
        if (bstRoot == nullptr)
            return nullptr;
        TreeNode* current = new TreeNode();
        current->right = createGst(bstRoot->right, greaterKeysSum);
        greaterKeysSum += bstRoot->val;
        current->val = greaterKeysSum;
        current->left = createGst(bstRoot->left, greaterKeysSum);
        return current;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace BinarySearchTreeToGreaterSumTreeTask
{

TEST(BinarySearchTreeToGreaterSumTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]",
              Codec::createData(createTreeHolder(solution.bstToGst(Codec::createTree("[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]").get()))));
    ASSERT_EQ("[1,null,1]", Codec::createData(createTreeHolder(solution.bstToGst(Codec::createTree("[0,null,1]").get()))));
    ASSERT_EQ("[3,3,2]", Codec::createData(createTreeHolder(solution.bstToGst(Codec::createTree("[1,0,2]").get()))));
    ASSERT_EQ("[7,9,4,10]", Codec::createData(createTreeHolder(solution.bstToGst(Codec::createTree("[3,2,4,1]").get()))));
}

}