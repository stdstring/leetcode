#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    void deleteNode(ListNode* node)
    {
        ListNode* next = node->next;
        node->val = next->val;
        node->next = next->next;
        delete next;
    }
};

ListNode* findNode(ListNode* node, int value)
{
    while (node->val != value)
        node = node->next;
    return node;
}

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace DeleteNodeInLinkedListTask
{

TEST(DeleteNodeInLinkedListTask, Examples)
{
    Solution solution;
    const std::shared_ptr<ListNode> list1 = createLinkedList({4, 5, 1, 9}, false);
    ASSERT_NO_THROW(solution.deleteNode(findNode(list1.get(), 5)));
    checkAndDeleteLinkedList({4, 1, 9}, list1.get());
    const std::shared_ptr<ListNode> list2 = createLinkedList({4, 5, 1, 9}, false);
    ASSERT_NO_THROW(solution.deleteNode(findNode(list2.get(), 1)));
    checkAndDeleteLinkedList({4, 5, 9}, list2.get());
}

}