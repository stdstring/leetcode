#include <vector>

#include "ListNode.h"
#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::ListNode;
using CommonDefs::TreeNode;

namespace
{

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) const
    {
        if (head == nullptr)
            return nullptr;
        std::vector<int> buffer;
        while (head != nullptr)
        {
            buffer.push_back(head->val);
            head = head->next;
        }
        return createBST(buffer, 0, buffer.size() - 1) ;
    }

private:
    TreeNode* createBST(std::vector<int> const &buffer, size_t from, size_t to) const
    {
        const size_t middle = (from + to) / 2;
        TreeNode *root = new TreeNode(buffer[middle]);
        root->left = from == middle ? nullptr : createBST(buffer, from, middle - 1);
        root->right = to == middle ? nullptr : createBST(buffer, middle + 1, to);
        return root;
    }
};

}

using CommonDefs::createLinkedList;
using CommonDefs::createTreeHolder;
using CommonDefs::checkAndDeleteTree;

namespace ConvertSortedListToBinarySearchTreeTask
{

TEST(ConvertSortedListToBinarySearchTreeTaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteTree(createTreeHolder(new TreeNode(0, new TreeNode(-10, nullptr, new TreeNode(-3)), new TreeNode(5, nullptr, new TreeNode(9)))).get(),
                       solution.sortedListToBST(createLinkedList({-10, -3, 0, 5, 9}, true).get()));
}

}