#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* connect(TreeNode* root)
    {
        if (root != nullptr)
            connectImpl(root);
        return root;
    }

private:
    void connectImpl(TreeNode* current)
    {
        if (current->left != nullptr)
            current->left->next = current->right != nullptr ? current->right : findNextRightNode(current);
        if (current->right != nullptr)
            current->right->next = findNextRightNode(current);
        if (current->right != nullptr)
            connectImpl(current->right);
        if (current->left != nullptr)
            connectImpl(current->left);
    }

    TreeNode* findNextRightNode(TreeNode* parent)
    {
        if (parent == nullptr)
            return nullptr;
        if (parent->next == nullptr)
            return nullptr;
        TreeNode* next = parent->next;
        while (next != nullptr)
        {
            if (next->left != nullptr || next->right != nullptr)
                return next->left != nullptr ? next->left : next->right;
            next = next->next;
        }
        return nullptr;
    }
};

}

using CommonDefs::createTreeHolder;
using CommonDefs::checkTreeNextLinks;

namespace PopulatingNextRightPointersInEachNodeIITask
{

TEST(PopulatingNextRightPointersInEachNodeIITaskTests, Examples)
{
    Solution solution;
    checkTreeNextLinks({{1}, {2, 3}, {4, 5, 7}}, solution.connect(createTreeHolder(new TreeNode(1, new TreeNode(2, 4, 5), new TreeNode(3, nullptr, 7))).get()));
}

TEST(PopulatingNextRightPointersInEachNodeIITaskTests, FromWrongAnswers)
{
    Solution solution;
    checkTreeNextLinks({{1}, {2, 3}, {4, 5}}, solution.connect(createTreeHolder(new TreeNode(1, new TreeNode(2, 4, nullptr), new TreeNode(3, nullptr, 5))).get()));
    checkTreeNextLinks({{0}, {2, 4}, {1, 3, -1}, {5, 1, 6, 8}},
                       solution.connect(createTreeHolder(new TreeNode(0, new TreeNode(2, new TreeNode(1, 5, 1), nullptr), new TreeNode(4, new TreeNode(3, nullptr, 6), new TreeNode(-1, nullptr, 8)))).get()));
    checkTreeNextLinks({{1}, {2, 3}, {4, 5, 6}, {7, 8}},
                       solution.connect(createTreeHolder(new TreeNode(1, new TreeNode(2, new TreeNode(4, 7, nullptr), 5), new TreeNode(3, nullptr, new TreeNode(6, nullptr, 8)))).get()));
    checkTreeNextLinks({{2}, {1, 3}, {0, 7, 9, 1}, {2, 1, 0, 8, 8}, {7}},
                       solution.connect(createTreeHolder(new TreeNode(2, new TreeNode(1, new TreeNode(0, 2, nullptr), new TreeNode(7, 1, new TreeNode(0, 7, nullptr))), new TreeNode(3, 9, new TreeNode(1, 8, 8)))).get()));
}

}