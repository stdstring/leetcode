#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* convertBST(TreeNode* root) const
    {
        if (root == nullptr)
            return nullptr;
        int greaterKeysSum = 0;
        return createGreaterTree(root, greaterKeysSum);
    }

private:
    TreeNode* createGreaterTree(TreeNode* bstRoot, int &greaterKeysSum) const
    {
        if (bstRoot == nullptr)
            return nullptr;
        TreeNode* current = new TreeNode();
        current->right = createGreaterTree(bstRoot->right, greaterKeysSum);
        greaterKeysSum += bstRoot->val;
        current->val = greaterKeysSum;
        current->left = createGreaterTree(bstRoot->left, greaterKeysSum);
        return current;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace ConvertBSTToGreaterTreeTask
{

TEST(ConvertBSTToGreaterTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]",
              Codec::createData(createTreeHolder(solution.convertBST(Codec::createTree("[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]").get()))));
    ASSERT_EQ("[1,null,1]", Codec::createData(createTreeHolder(solution.convertBST(Codec::createTree("[0,null,1]").get()))));
    ASSERT_EQ("[3,3,2]", Codec::createData(createTreeHolder(solution.convertBST(Codec::createTree("[1,0,2]").get()))));
    ASSERT_EQ("[7,9,4,10]", Codec::createData(createTreeHolder(solution.convertBST(Codec::createTree("[3,2,4,1]").get()))));
}

}