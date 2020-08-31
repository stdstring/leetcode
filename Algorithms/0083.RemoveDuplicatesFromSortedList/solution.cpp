#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (head == nullptr)
            return head;
        ListNode* prev = head;
        ListNode* current = head->next;
        while (current != nullptr)
        {
            if (current->val == prev->val)
            {
                prev->next = current->next;
                delete current;
            }
            else
                prev = current;
            current = prev->next;
        }
        return head;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace RemoveDuplicatesFromSortedListTask
{

TEST(RemoveDuplicatesFromSortedListTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({1, 2}, solution.deleteDuplicates(createLinkedList({1, 1, 2}, false).get()));
    checkAndDeleteLinkedList({1, 2, 3}, solution.deleteDuplicates(createLinkedList({1, 1, 2, 3, 3}, false).get()));
}

TEST(RemoveDuplicatesFromSortedListTaskTests, FromWrongAnswers)
{
    Solution solution;
    checkAndDeleteLinkedList({}, solution.deleteDuplicates(nullptr));
}

}