#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* reverseBetween(ListNode* head, int m, int n)
    {
        if (m == n)
            return head;
        ListNode* beforeCurrent = nullptr;
        // rewind to node with number m
        for (int position = 1; position < m; ++position)
            beforeCurrent = beforeCurrent == nullptr ? head : beforeCurrent->next;
        // reverse nodes with numbers from m to n
        ListNode* mNode = beforeCurrent == nullptr ? head : beforeCurrent->next;
        ListNode* prev = mNode;
        ListNode* current = mNode->next;
        for (int position = m + 1; position <= n; ++position)
        {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        mNode->next = current;
        if (beforeCurrent != nullptr)
            beforeCurrent->next = prev;
        return beforeCurrent != nullptr ? head : prev;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace ReverseLinkedListIITask
{

TEST(RemoveDuplicatesFromSortedListTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({1, 4, 3, 2, 5}, solution.reverseBetween(createLinkedList({1, 2, 3, 4, 5}, false).get(), 2, 4));
}

}