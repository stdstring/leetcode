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
    std::string tree2str(TreeNode* root) const
    {
        std::string dest;
        tree2strImpl(root, dest);
        return dest;
    }

private:
    void tree2strImpl(TreeNode* root, std::string &dest) const
    {
        dest.append(std::to_string(root->val));
        if ((root->left != nullptr) || (root->right != nullptr))
        {
            dest.push_back('(');
            if (root->left != nullptr)
                tree2strImpl(root->left, dest);
            dest.push_back(')');
        }
        if (root->right != nullptr)
        {
            dest.push_back('(');
            tree2strImpl(root->right, dest);
            dest.push_back(')');
        }
    }
};

}

using CommonLib::Codec;

namespace ConstructStringFromBinaryTreeTask
{

TEST(InvertBinaryTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("1(2(4))(3)", solution.tree2str(Codec::createTree("[1,2,3,4]").get()));
    ASSERT_EQ("1(2()(4))(3)", solution.tree2str(Codec::createTree("[1,2,3,null,4]").get()));
}

}