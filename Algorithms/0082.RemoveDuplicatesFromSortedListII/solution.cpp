#include "ListNode.h"

#include "gtest/gtest.h"

using CommonDefs::ListNode;

namespace
{

class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        while ((head != nullptr) && hasDuplicates(head))
        {
            head = removeDuplicates(head);
        }
        if (head == nullptr)
            return head;
        ListNode* prev = head;
        ListNode* current = head->next;
        while (current != nullptr)
        {
            if (hasDuplicates(current))
                prev->next = current = removeDuplicates(current);
            else
            {
                prev = prev->next;
                current = current->next;
            }
        }
        return head;
    }

private:
    bool hasDuplicates(ListNode* current)
    {
        return (current->next != nullptr) && (current->val == current->next->val);
    }

    ListNode* removeDuplicates(ListNode* current)
    {
        const int val = current->val;
        while (current != nullptr && current->val == val)
        {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
        return current;
    }
};

}

using CommonDefs::createLinkedList;
using CommonDefs::checkAndDeleteLinkedList;

namespace RemoveDuplicatesFromSortedListIITask
{

TEST(RemoveDuplicatesFromSortedListIITaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({1, 2, 5}, solution.deleteDuplicates(createLinkedList({1, 2, 3, 3, 4, 4, 5}, false).get()));
    checkAndDeleteLinkedList({2, 3}, solution.deleteDuplicates(createLinkedList({1, 1, 1, 2, 3}, false).get()));
}

TEST(RemoveDuplicatesFromSortedListIITaskTests, FromWrongAnswers)
{
    Solution solution;
    checkAndDeleteLinkedList({}, solution.deleteDuplicates(createLinkedList({1, 1}, false).get()));
}

}