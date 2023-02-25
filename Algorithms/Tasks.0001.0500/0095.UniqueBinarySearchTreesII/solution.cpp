#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
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
    std::vector<TreeNode*> generateTrees(int n) const
    {
        return generateTrees(1, n);
    }

private:
    std::vector<TreeNode*> generate1Trees(int value) const
    {
        return {new TreeNode(value)};
    }

    std::vector<TreeNode*> generate2Trees(int value1, int value2) const
    {
        return {new TreeNode(value1, nullptr, new TreeNode(value2)), new TreeNode(value2, new TreeNode(value1), nullptr)};
    }

    std::vector<TreeNode*> generateTrees(int valueFrom, int size) const
    {
        if (size == 0)
            return {nullptr};
        if (size == 1)
            return generate1Trees(valueFrom);
        if (size == 2)
            return generate2Trees(valueFrom, valueFrom + 1);
        std::vector<TreeNode*> result;
        for (int leftSize = 0; leftSize < size ; ++leftSize)
        {
            const int value = valueFrom + leftSize;
            std::vector<TreeNode*> leftSubtrees(generateTrees(valueFrom, leftSize));
            std::vector<TreeNode*> rightSubtrees(generateTrees(value + 1, size - leftSize - 1));
            for (TreeNode* leftSubtree : leftSubtrees)
            {
                for (TreeNode* rightSubtree : rightSubtrees)
                {
                    result.push_back(new TreeNode(value, leftSubtree, rightSubtree));
                }
            }
        }
        return result;
    }
};

}

using CommonLib::Codec;

namespace
{

void enumerateUniqueNodes(TreeNode* root, std::unordered_set<TreeNode*> &uniqueNodes)
{
    if (uniqueNodes.count(root) != 0)
        return;
    uniqueNodes.insert(root);
    if (root->left != nullptr)
        enumerateUniqueNodes(root->left, uniqueNodes);
    if (root->right != nullptr)
        enumerateUniqueNodes(root->right, uniqueNodes);
}

std::shared_ptr<std::vector<TreeNode*>> createTreesHolder(std::vector<TreeNode*> &treesRaw)
{
    auto deleter = [](std::vector<TreeNode*>* trees)
    {
        std::unordered_set<TreeNode*> uniqueNodes;
        for (TreeNode* tree : *trees)
            enumerateUniqueNodes(tree, uniqueNodes);
        for (TreeNode* node : uniqueNodes)
            delete node;
    };
    return std::shared_ptr<std::vector<TreeNode*>>(&treesRaw, deleter);
}

void checkGenerateTrees(std::vector<std::string> const &expected, int n)
{
    const Solution solution;
    std::vector<TreeNode*> trees(solution.generateTrees(n));
    std::shared_ptr<std::vector<TreeNode*>> treesHolder(createTreesHolder(trees));
    std::vector<std::string> actual;
    std::transform(trees.cbegin(), trees.cend(), std::back_inserter(actual), [](TreeNode* root) { return Codec::createDataRaw(root); });
    ASSERT_EQ(expected, actual);
}

}

namespace UniqueBinarySearchTreesIITask
{

TEST(UniqueBinarySearchTreesIITaskTests, Examples)
{
    checkGenerateTrees({"[1,null,2,null,3]", "[1,null,3,2]", "[2,1,3]", "[3,1,null,null,2]", "[3,2,null,1]"}, 3);
    checkGenerateTrees({"[1]"}, 1);
}

}
