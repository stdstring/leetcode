#include <algorithm>
#include <map>
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
    std::vector<std::vector<int>> verticalTraversal(TreeNode* root) const
    {
        std::map<int, std::vector<std::pair<int, int>>> columnMap;
        FillColumnMap(root, 0, 0, columnMap);
        auto comparer = [](std::pair<int, int> const &l, std::pair<int, int> const &r){ return (l.first < r.first) || ((l.first == r.first) && (l.second < r.second)); };
        std::vector<std::vector<int>> result;
        for (auto &entry : columnMap)
        {
            std::sort(entry.second.begin(), entry.second.end(), comparer);
            result.emplace_back();
            for (std::pair<int, int> const &nodeData : entry.second)
                result.back().push_back(nodeData.second);
        }
        return result;
    }

private:
    void FillColumnMap(TreeNode* root, int row, int column, std::map<int, std::vector<std::pair<int, int>>> &columnMap) const
    {
        if (root == nullptr)
            return;
        columnMap[column].push_back({row, root->val});
        FillColumnMap(root->left, row + 1, column - 1, columnMap);
        FillColumnMap(root->right, row + 1, column + 1, columnMap);
    }
};

}

using CommonLib::Codec;

namespace VerticalOrderTraversalOfBinaryTreeTask
{

TEST(VerticalOrderTraversalOfBinaryTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{9}, {3, 15}, {20}, {7}}), solution.verticalTraversal(Codec::createTree("[3,9,20,null,null,15,7]").get()));
    ASSERT_EQ(std::vector<std::vector<int>>({{4}, {2}, {1, 5, 6}, {3}, {7}}), solution.verticalTraversal(Codec::createTree("[1,2,3,4,5,6,7]").get()));
    ASSERT_EQ(std::vector<std::vector<int>>({{4}, {2}, {1, 5, 6}, {3}, {7}}), solution.verticalTraversal(Codec::createTree("[1,2,3,4,6,5,7]").get()));
}

}