#include <vector>

#include "ListNode.h"
#include "ListNodeUtils.h"
#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;
using CommonLib::TreeNode;

namespace
{

class Solution
{
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
        TreeNode* root = new TreeNode(buffer[middle]);
        root->left = from == middle ? nullptr : createBST(buffer, from, middle - 1);
        root->right = to == middle ? nullptr : createBST(buffer, middle + 1, to);
        return root;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace ConvertSortedListToBinarySearchTreeTask
{

TEST(ConvertSortedListToBinarySearchTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[0,-10,5,null,-3,null,9]", Codec::createData(createTreeHolder(solution.sortedListToBST(createLinkedList({-10, -3, 0, 5, 9}, true).get()))));
}

}