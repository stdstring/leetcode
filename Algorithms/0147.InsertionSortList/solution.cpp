#include <memory>

#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* insertionSortList(ListNode* head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* sortedHead = nullptr;
        while (head != nullptr)
        {
            ListNode* next = head->next;
            head->next = nullptr;
            if (sortedHead == nullptr)
                sortedHead = head;
            else if (sortedHead-> val >= head->val)
            {
                head->next = sortedHead;
                sortedHead = head;
            }
            else
            {
                ListNode* current = sortedHead;
                while (current->val < head->val && current->next != nullptr && current->next->val < head->val)
                    current = current->next;
                head->next = current->next;
                current->next = head;
            }
            head = next;
        }
        return sortedHead;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace InsertionSortListTask
{

TEST(InsertionSortListTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({1, 2, 3, 4}, solution.insertionSortList(createLinkedList({4, 2, 1, 3}, false).get()));
    checkAndDeleteLinkedList({-1, 0, 3, 4, 5}, solution.insertionSortList(createLinkedList({-1, 5, 3, 4, 0}, false).get()));
}

}