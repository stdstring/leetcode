#include "ListNode.h"

#include "gtest/gtest.h"

using CommonDefs::ListNode;

namespace
{

class Solution
{
public:
    ListNode* oddEvenList(ListNode* head)
    {
        if (head == nullptr)
            return nullptr;
        ListNode* oddHead = head;
        ListNode* oddCurrent = oddHead;
        ListNode* evenHead = head->next;
        ListNode* evenCurrent = evenHead;
        while (evenCurrent != nullptr)
        {
            ListNode* oddNext = evenCurrent->next == nullptr ? nullptr : evenCurrent->next;
            ListNode* evenNext = oddNext == nullptr ? nullptr: oddNext->next;
            oddCurrent->next = oddNext;
            evenCurrent->next = evenNext;
            if (oddNext != nullptr)
                oddCurrent = oddNext;
            evenCurrent = evenNext;
        }
        oddCurrent->next = evenHead;
        return oddHead;
    }
};

}

using CommonDefs::createLinkedList;
using CommonDefs::checkAndDeleteLinkedList;

namespace OddEvenLinkedListTask
{

TEST(DeleteNodeInLinkedListTask, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({1, 3, 5, 2, 4}, solution.oddEvenList(createLinkedList({1, 2, 3, 4, 5}, false).get()));
    checkAndDeleteLinkedList({2, 3, 6, 7, 1, 5, 4}, solution.oddEvenList(createLinkedList({2, 1, 3, 5, 6, 4, 7}, false).get()));
}

}