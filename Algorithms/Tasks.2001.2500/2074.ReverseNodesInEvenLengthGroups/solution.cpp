#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* reverseEvenLengthGroups(ListNode* head) const
    {
        ListNode* prevGroupEnd = head;
        ListNode* currentGroupStart = head->next;
        size_t groupCount = 2;
        while (currentGroupStart != nullptr)
        {
            ListNode* current = currentGroupStart;
            ListNode* currentGroupEnd = current;
            size_t groupSize = 0;
            for (; groupSize < groupCount && current != nullptr; ++groupSize)
            {
                currentGroupEnd = current;
                current = current->next;
            }
            if (groupSize % 2 == 0)
            {
                reverseGroup(currentGroupStart, current);
                prevGroupEnd->next = currentGroupEnd;
                prevGroupEnd = currentGroupStart;
            }
            else
            {
                prevGroupEnd->next = currentGroupStart;
                prevGroupEnd = currentGroupEnd;
            }
            currentGroupStart = current;
            prevGroupEnd->next = nullptr;
            ++groupCount;
        }
        return head;
    }

private:
    void reverseGroup(ListNode* begin, ListNode* end) const
    {
        ListNode* prev = nullptr;
        while (begin != end)
        {
            ListNode* next = begin->next;
            begin->next = prev;
            prev = begin;
            begin = next;
        }
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace ReverseNodesInEvenLengthGroupsTask
{

TEST(ReverseNodesInEvenLengthGroupsTaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteLinkedList({5, 6, 2, 3, 9, 1, 4, 8, 3, 7}, solution.reverseEvenLengthGroups(createLinkedList({5, 2, 6, 3, 9, 1, 7, 3, 8, 4}, false).get()));
    checkAndDeleteLinkedList({1, 0, 1, 6}, solution.reverseEvenLengthGroups(createLinkedList({1, 1, 0, 6}, false).get()));
    checkAndDeleteLinkedList({1, 0, 1, 5, 6}, solution.reverseEvenLengthGroups(createLinkedList({1, 1, 0, 6, 5}, false).get()));
}

}