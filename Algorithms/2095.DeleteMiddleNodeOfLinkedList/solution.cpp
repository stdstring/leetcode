#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* deleteMiddle(ListNode* head) const
    {
        if (head->next == nullptr)
            return nullptr;
        ListNode* current = head;
        ListNode* doubleCurrent = head;
        ListNode* changedListHead = nullptr;
        ListNode* changedListCurrent = nullptr;
        while (doubleCurrent != nullptr && doubleCurrent->next != nullptr)
        {
            ListNode* changedListNext = new ListNode(current->val);
            if (changedListHead == nullptr)
                changedListHead = changedListCurrent = changedListNext;
            else
            {
                changedListCurrent->next = changedListNext;
                changedListCurrent = changedListNext;
            }
            current = current->next;
            doubleCurrent = doubleCurrent->next->next;
        }
        current = current->next;
        while (current != nullptr)
        {
            ListNode* changedListNext = new ListNode(current->val);
            changedListCurrent->next = changedListNext;
            changedListCurrent = changedListNext;
            current = current->next;
        }
        return changedListHead;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace DeleteMiddleNodeOfLinkedListTask
{

TEST(DeleteMiddleNodeOfLinkedListTaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteLinkedList({1, 3, 4, 1, 2, 6}, solution.deleteMiddle(createLinkedList({1, 3, 4, 7, 1, 2, 6}, true).get()));
    checkAndDeleteLinkedList({1, 2, 4}, solution.deleteMiddle(createLinkedList({1, 2, 3, 4}, true).get()));
    checkAndDeleteLinkedList({2}, solution.deleteMiddle(createLinkedList({2, 1}, true).get()));
}

}