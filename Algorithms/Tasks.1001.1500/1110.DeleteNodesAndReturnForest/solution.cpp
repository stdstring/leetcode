#include <algorithm>
#include <queue>
#include <unordered_set>
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
    std::vector<TreeNode*> delNodes(TreeNode* root, std::vector<int> const &toDelete) const
    {
        const std::unordered_set toDeleteValues(toDelete.cbegin(), toDelete.cend());
        std::vector<TreeNode*> forest;
        if (toDeleteValues.count(root->val) == 0)
            forest.push_back(root);
        std::queue<TreeNode*> nodes;
        nodes.push(root);
        while (!nodes.empty())
        {
            TreeNode* current = nodes.front();
            nodes.pop();
            if (current->left != nullptr)
            {
                nodes.push(current->left);
                if (toDeleteValues.count(current->left->val) == 1)
                    current->left = nullptr;
            }
            if (current->right != nullptr)
            {
                nodes.push(current->right);
                if (toDeleteValues.count(current->right->val) == 1)
                    current->right = nullptr;
            }
            if (toDeleteValues.count(current->val) == 1)
            {
                if (current->left != nullptr)
                    forest.push_back(current->left);
                if (current->right != nullptr)
                    forest.push_back(current->right);
                delete current;
            }
        }
        return forest;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace
{

void checkDelNodes(std::string const &treeSource, std::vector<int> const &toDelete, std::vector<std::string> const &expectedForest)
{
    constexpr Solution solution;
    TreeNode* tree = Codec::createTreeRaw(treeSource);
    const std::vector<TreeNode*> forest(solution.delNodes(tree, toDelete));
    std::vector<std::shared_ptr<TreeNode>> actualForest;
    std::transform(forest.cbegin(), forest.cend(), std::back_inserter(actualForest), [](TreeNode* node){ return createTreeHolder(node); });
    ASSERT_EQ(expectedForest.size(), actualForest.size());
    for (size_t index = 0; index < expectedForest.size(); ++index)
        ASSERT_EQ(expectedForest[index], Codec::createData(actualForest[index]));
}

}

namespace DeleteNodesAndReturnForestTask
{

TEST(DeleteNodesAndReturnForestTaskTests, Examples)
{
    checkDelNodes("[1,2,3,4,5,6,7]", {3, 5}, {"[1,2,null,4]", "[6]", "[7]"});
    checkDelNodes("[1,2,4,null,3]", {3}, {"[1,2,4]"});
}

}