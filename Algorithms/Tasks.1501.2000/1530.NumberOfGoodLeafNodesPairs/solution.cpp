#include <unordered_map>
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
    int countPairs(TreeNode* root, int distance) const
    {
        std::vector<TreeNode*> leaves;
        std::unordered_map<TreeNode*, TreeNode*> parentNodes;
        prepareData(root, nullptr, parentNodes, leaves);
        size_t goodLeafPairs = 0;
        for (TreeNode* leaf : leaves)
            goodLeafPairs += calcGoodLeafPairs(leaf, nullptr, distance, parentNodes);
        return static_cast<int>(goodLeafPairs / 2);
    }

private:
    void prepareData(TreeNode* root, TreeNode* parent, std::unordered_map<TreeNode*, TreeNode*> &parentNodes, std::vector<TreeNode*> &leaves) const
    {
        parentNodes.emplace(root, parent);
        if ((root->left == nullptr) && (root->right == nullptr))
            leaves.push_back(root);
        if (root->left != nullptr)
            prepareData(root->left, root, parentNodes, leaves);
        if (root->right != nullptr)
            prepareData(root->right, root, parentNodes, leaves);
    }

    size_t calcGoodLeafPairs(TreeNode* current, TreeNode* previous, int distance, std::unordered_map<TreeNode*, TreeNode*> const &parentNodes) const
    {
        if ((previous != nullptr) && (current->left == nullptr) && (current->right == nullptr))
            return 1;
        if (distance == 0)
            return 0;
        size_t goodLeafPairs = 0;
        TreeNode* parent = parentNodes.at(current);
        if ((parent != nullptr) && (parent != previous))
            goodLeafPairs += calcGoodLeafPairs(parent, current, distance - 1, parentNodes);
        if ((current->left != nullptr) && (current->left != previous))
            goodLeafPairs += calcGoodLeafPairs(current->left, current, distance - 1, parentNodes);
        if ((current->right != nullptr) && (current->right != previous))
            goodLeafPairs += calcGoodLeafPairs(current->right, current, distance - 1, parentNodes);
        return goodLeafPairs;
    }
};

}

using CommonLib::Codec;

namespace NumberOfGoodLeafNodesPairsTask
{

TEST(NumberOfGoodLeafNodesPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.countPairs(Codec::createTree("[1,2,3,null,4]").get(), 3));
    ASSERT_EQ(2, solution.countPairs(Codec::createTree("[1,2,3,4,5,6,7]").get(), 3));
    ASSERT_EQ(1, solution.countPairs(Codec::createTree("[7,1,4,6,null,5,3,null,null,null,null,null,2]").get(), 3));
}

TEST(NumberOfGoodLeafNodesPairsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.countPairs(Codec::createTree("[11,99,88,77,null,null,66,55,null,null,44,33,null,null,22]").get(), 4));
}

}