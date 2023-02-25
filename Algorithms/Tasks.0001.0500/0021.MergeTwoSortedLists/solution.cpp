#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;
        ListNode* head = nullptr;
        ListNode* current = nullptr;
        if (l1->val <= l2->val)
        {
            head = current = l1;
            l1 = l1->next;
        }
        else
        {
            head = current = l2;
            l2 = l2->next;
        }
        while ((l1 != nullptr) && (l2 != nullptr))
        {
            if (l1->val < l2->val)
            {
                current->next = l1;
                current = current->next;
                l1 = l1->next;
            }
            else if (l1->val >= l2->val)
            {
                current->next = l2;
                current = current->next;
                l2 = l2->next;
            }
        }
        if (l1 != nullptr)
            current->next = l1;
        if (l2 != nullptr)
            current->next = l2;
        return head;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace MergeTwoSortedListsTask
{

TEST(MergeTwoSortedListsTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({1, 1, 2, 3, 4, 4}, solution.mergeTwoLists(createLinkedList({1, 2, 4}, false).get(), createLinkedList({1, 3, 4}, false).get()));
}

}