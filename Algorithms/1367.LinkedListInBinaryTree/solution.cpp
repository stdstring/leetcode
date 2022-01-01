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
    bool isSubPath(ListNode* head, TreeNode* root) const
    {
        if (root == nullptr)
            return false;
        return containsLinkedList(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }

private:
    bool containsLinkedList(ListNode* head, TreeNode* root) const
    {
        if (head == nullptr)
            return true;
        if (root == nullptr)
            return false;
        if (root->val != head->val)
            return false;
        if (containsLinkedList(head->next, root->left))
            return true;
        if (containsLinkedList(head->next, root->right))
            return true;
        return false;
    }
};

}

using CommonLib::Codec;
using CommonLib::createLinkedList;

namespace LinkedListInBinaryTreeTask
{

TEST(MaximumProductOfSplittedBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isSubPath(createLinkedList({4, 2, 8}, true).get(),
                                       Codec::createTree("[1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]").get()));
    ASSERT_EQ(true, solution.isSubPath(createLinkedList({1, 4, 2, 6}, true).get(),
                                       Codec::createTree("[1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]").get()));
    ASSERT_EQ(false, solution.isSubPath(createLinkedList({1, 4, 2, 6, 8}, true).get(),
                                        Codec::createTree("[1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]").get()));
}

}