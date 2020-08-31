#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* removeElements(ListNode* head, int val)
    {
        // remove from head
        while(head != nullptr && head->val == val)
        {
            ListNode* node = head;
            head = head->next;
            delete node;
        }
        if (head == nullptr)
            return head;
        // remove from body
        ListNode* prev = head;
        while (prev->next != nullptr)
        {
            ListNode* current = prev->next;
            if (current->val == val)
            {
                prev->next = current->next;
                delete current;
            }
            else
                prev = prev->next;
        }
        return head;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace RemoveLinkedListElementsTask
{

TEST(RemoveLinkedListElementsTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({1, 2, 3, 4, 5}, solution.removeElements(createLinkedList({1, 2, 6, 3, 4, 5, 6}, false).get(), 6));
}

}