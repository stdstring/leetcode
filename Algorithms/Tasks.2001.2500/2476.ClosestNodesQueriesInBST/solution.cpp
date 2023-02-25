#include <algorithm>
#include <numeric>
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
    std::vector<std::vector<int>> closestNodes(TreeNode* root, std::vector<int> const &queries) const
    {
        std::vector<int> tree;
        flattenTree(root, tree);
        std::vector<size_t> indices(queries.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&queries](size_t left, size_t right){ return queries[left] < queries[right]; });
        std::vector<std::vector<int>> result(queries.size(), std::vector<int>());
        for (size_t index = 0, treeIndex = 0; index < indices.size(); ++index)
        {
            int query = queries[indices[index]];
            while ((treeIndex < tree.size()) && (tree[treeIndex] < query))
                ++treeIndex;
            if ((treeIndex < tree.size()) && (tree[treeIndex] == query))
            {
                result[indices[index]].emplace_back(query);
                result[indices[index]].emplace_back(query);
            }
            else
            {
                result[indices[index]].emplace_back(treeIndex == 0 ? -1 : tree[treeIndex - 1]);
                result[indices[index]].emplace_back(treeIndex == tree.size() ? -1 : tree[treeIndex]);
            }
        }
        return result;
    }

private:
    void flattenTree(TreeNode* root, std::vector<int> &dest) const
    {
        if (root->left != nullptr)
            flattenTree(root->left, dest);
        dest.emplace_back(root->val);
        if (root->right != nullptr)
            flattenTree(root->right, dest);
    }
};

}

using CommonLib::Codec;

namespace ClosestNodesQueriesInBSTTask
{

TEST(ClosestNodesQueriesInBSTTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{2, 2}, {4, 6}, {15, -1}}),
              solution.closestNodes(Codec::createTree("[6,2,13,1,4,9,15,null,null,null,null,null,null,14]").get(), {2, 5, 16}));
    ASSERT_EQ(std::vector<std::vector<int>>({{-1, 4}}), solution.closestNodes(Codec::createTree("[4,null,9]").get(), {3}));
}

}