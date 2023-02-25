#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) const
    {
        if (root == nullptr)
            return new TreeNode(val);
        insertIntoBSTImpl(root, val);
        return root;
    }

private:
    void insertIntoBSTImpl(TreeNode* root, int val) const
    {
        if (root->val > val)
        {
            if (root->left == nullptr)
                root->left = new TreeNode(val);
            else
                insertIntoBST(root->left, val);
        }
        else
        {
            if (root->right == nullptr)
                root->right = new TreeNode(val);
            else
                insertIntoBST(root->right, val);
        }
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace InsertIntoBSTTask
{

TEST(InsertIntoBSTTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[4,2,7,1,3,5]", Codec::createData(createTreeHolder(solution.insertIntoBST(Codec::createTreeRaw("[4,2,7,1,3]"), 5))));
    ASSERT_EQ("[40,20,60,10,30,50,70,null,null,25]", Codec::createData(createTreeHolder(solution.insertIntoBST(Codec::createTreeRaw("[40,20,60,10,30,50,70]"), 25))));
    ASSERT_EQ("[4,2,7,1,3,5]", Codec::createData(createTreeHolder(solution.insertIntoBST(Codec::createTreeRaw("[4,2,7,1,3,null,null,null,null,null,null]"), 5))));
}


}