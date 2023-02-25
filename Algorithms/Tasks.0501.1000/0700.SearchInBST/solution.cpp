#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* searchBST(TreeNode* root, int val) const
    {
        if (root == nullptr)
            return nullptr;
        if (root->val == val)
            return root;
        return searchBST(val < root->val ? root->left : root->right, val);
    }
};

}

using CommonLib::Codec;

namespace SearchInBSTTask
{

TEST(SearchInBSTTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[2,1,3]", Codec::createDataRaw(solution.searchBST(Codec::createTree("[4,2,7,1,3]").get(), 2)));
    ASSERT_EQ("[]", Codec::createDataRaw(solution.searchBST(Codec::createTree("[4,2,7,1,3]").get(), 5)));
}

}