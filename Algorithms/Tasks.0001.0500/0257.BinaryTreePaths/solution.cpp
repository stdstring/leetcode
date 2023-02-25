#include <string>
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
    std::vector<std::string> binaryTreePaths(TreeNode* root) const
    {
        if (root == nullptr)
            return {};
        std::vector<std::string> dest;
        generatePaths(root, dest, "");
        return dest;
    }

private:
    void generatePaths(TreeNode* root, std::vector<std::string> &dest, std::string currentPath) const
    {
        if (!currentPath.empty())
            currentPath.append("->");
        currentPath.append(std::to_string(root->val));
        if (root->left == nullptr && root->right == nullptr)
        {
            dest.push_back(currentPath);
            return;
        }
        if (root->left != nullptr)
            generatePaths(root->left, dest, currentPath);
        if (root->right != nullptr)
            generatePaths(root->right, dest, currentPath);
    }
};

}


using CommonLib::Codec;

namespace BinaryTreePathsTask
{

TEST(BinaryTreePathsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"1->2->5", "1->3"}), solution.binaryTreePaths(Codec::createTree("[1,2,3,null,5]").get()));
}

}