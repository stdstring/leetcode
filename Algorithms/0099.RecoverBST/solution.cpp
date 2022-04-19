#include <memory>
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
    void recoverTree(TreeNode* root)
    {
        std::vector<TreeNode*> nodes;
        collectNodes(nodes, root);
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        for (size_t index = 0; index < nodes.size(); ++index)
        {
            TreeNode* current = nodes[index];
            TreeNode* prev = index > 0 ? nodes[index - 1] : nullptr;
            if ((prev != nullptr) && (prev->val > current->val))
            {
                if (first == nullptr)
                    first = prev;
                if (first != nullptr)
                    second = current;
            }
        }
        std::swap(first->val, second->val);
    }

private:
    void collectNodes(std::vector<TreeNode*> &nodes, TreeNode* current)
    {
        if (current->left != nullptr)
            collectNodes(nodes, current->left);
        nodes.push_back(current);
        if (current->right != nullptr)
            collectNodes(nodes, current->right);
    }
};

using CommonLib::Codec;

namespace
{

void checkRecoverTree(std::string const &source, std::string const &expected)
{
    const std::shared_ptr<TreeNode> tree(Codec::createTree(source));
    Solution solution;
    ASSERT_NO_THROW(solution.recoverTree(tree.get()));
    ASSERT_EQ(expected, Codec::createData(tree));
}

}

}

namespace RecoverBSTTask
{

TEST(RecoverBSTTaskTests, Examples)
{
    checkRecoverTree("[1,3,null,null,2]", "[3,1,null,null,2]");
    checkRecoverTree("[3,1,4,null,null,2]", "[2,1,4,null,null,3]");
}

}