#include <vector>

#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> pathSum(TreeNode* root, int sum) const
    {
        if (root == nullptr)
            return {};
        std::vector<std::vector<int>> dest;
        std::vector<int> current;
        pathSumImpl(root, sum, current, dest);
        return dest;
    }

private:
    void pathSumImpl(TreeNode* root, int sum, std::vector<int> &current, std::vector<std::vector<int>> &dest) const
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            if (sum == root->val)
            {
                current.push_back(root->val);
                dest.push_back(current);
                current.pop_back();
            }
            return;
        }
        if (root->left != nullptr)
        {
            current.push_back(root->val);
            pathSumImpl(root->left, sum - root->val, current, dest);
            current.pop_back();
        }
        if (root->right != nullptr)
        {
            current.push_back(root->val);
            pathSumImpl(root->right, sum - root->val, current, dest);
            current.pop_back();
        }
    }
};

}

namespace PathSumIITask
{

TEST(PathSumIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{5 ,4, 11, 2}, {5, 8, 4, 5}}),
              solution.pathSum(createTreeHolder(new TreeNode(5, new TreeNode(4, new TreeNode(11, 7, 2), nullptr), new TreeNode(8, 13, new TreeNode(4, 5, 1)))).get(), 22));
}

}