#include "ListNode.h"

#include "gtest/gtest.h"

using CommonDefs::ListNode;

namespace
{

class Solution
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode *tail = head;
        for (int index = 0; index < n; ++index)
            tail = tail->next;
        if (tail == nullptr)
        {
            ListNode *current = head->next;
            delete head;
            return current;
        }
        tail = tail->next;
        ListNode *prev = head;
        while (tail != nullptr)
        {
            tail = tail->next;
            prev = prev->next;
        }
        ListNode *current = prev->next;
        prev->next = current->next;
        delete current;
        return head;
    }
};

}

using CommonDefs::createLinkedList;
using CommonDefs::checkAndDeleteLinkedList;

namespace RemoveNthNodeFromEndOfListTask
{

TEST(RemoveNthNodeFromEndOfListTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({1, 2, 3, 5}, solution.removeNthFromEnd(createLinkedList({1, 2, 3, 4, 5}, false).get(), 2));
}

}