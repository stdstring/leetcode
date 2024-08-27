#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::NTreeNode;

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> postorder(NTreeNode* root) const
    {
        if (root == nullptr)
            return {};
        std::vector<int> dest;
        postorder(root, dest);
        return dest;
    }

private:
    void postorder(NTreeNode* root, std::vector<int> &dest) const
    {
        for (NTreeNode* child : root->children)
            postorder(child, dest);
        dest.emplace_back(root->val);
    }
};

}

using CommonLib::Codec;

namespace NaryTreePostorderTraversalTask
{

TEST(NaryTreePostorderTraversalTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({5, 6, 3, 2, 4, 1}), solution.postorder(Codec::createNTree("[1,null,3,2,4,null,5,6]").get()));
    ASSERT_EQ(std::vector<int>({2, 6, 14, 11, 7, 3, 12, 8, 4, 13, 9, 10, 5, 1}),
              solution.postorder(Codec::createNTree("[1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]").get()));
}

}