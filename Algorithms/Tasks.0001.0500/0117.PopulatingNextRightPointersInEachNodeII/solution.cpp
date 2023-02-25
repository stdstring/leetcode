#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

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

using CommonLib::Codec;
using CommonLib::checkTreeNextLinks;

namespace PopulatingNextRightPointersInEachNodeIITask
{

TEST(PopulatingNextRightPointersInEachNodeIITaskTests, Examples)
{
    Solution solution;
    checkTreeNextLinks({{1}, {2, 3}, {4, 5, 7}}, solution.connect(Codec::createTree("[1,2,3,4,5,null,7]").get()));
}

TEST(PopulatingNextRightPointersInEachNodeIITaskTests, FromWrongAnswers)
{
    Solution solution;
    checkTreeNextLinks({{1}, {2, 3}, {4, 5}}, solution.connect(Codec::createTree("[1,2,3,4,null,null,5]").get()));
    checkTreeNextLinks({{0}, {2, 4}, {1, 3, -1}, {5, 1, 6, 8}}, solution.connect(Codec::createTree("[0,2,4,1,null,3,-1,5,1,null,6,null,8]").get()));
    checkTreeNextLinks({{1}, {2, 3}, {4, 5, 6}, {7, 8}}, solution.connect(Codec::createTree("[1,2,3,4,5,null,6,7,null,null,null,null,8]").get()));
    checkTreeNextLinks({{2}, {1, 3}, {0, 7, 9, 1}, {2, 1, 0, 8, 8}, {7}}, solution.connect(Codec::createTree("[2,1,3,0,7,9,1,2,null,1,0,null,null,8,8,null,null,null,null,7]").get()));
}

}