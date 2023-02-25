#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) const
    {
        ListNode* resultHead = nullptr;
        ListNode* resultCurrent = nullptr;
        ListNode* firstCurrent = list1;
        size_t firstIndex = 0;
        // copy list1 before a
        for (;firstIndex < static_cast<size_t>(a); ++firstIndex, firstCurrent = firstCurrent->next)
        {
            if (resultHead == nullptr)
                resultHead = resultCurrent = new ListNode(firstCurrent->val);
            else
            {
                ListNode* next = new ListNode(firstCurrent->val);
                resultCurrent->next = next;
                resultCurrent = next;
            }
        }
        // skip list1 after a before b
        for (;firstIndex <= static_cast<size_t>(b); ++firstIndex, firstCurrent = firstCurrent->next)
        {}
        // copy list2
        resultCurrent = appendList(list2, resultCurrent);
        // copy list1 after b
        appendList(firstCurrent, resultCurrent);
        return resultHead;
    }

private:
    ListNode* appendList(ListNode* source, ListNode* dest) const
    {
        while (source != nullptr)
        {
            ListNode* next = new ListNode(source->val);
            dest->next = next;
            dest = next;
            source = source->next;
        }
        return dest;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace MergeInBetweenLinkedListsTask
{

TEST(MergeInBetweenLinkedListsTaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteLinkedList({0, 1, 2, 1000000, 1000001, 1000002, 5},
                             solution.mergeInBetween(createLinkedList({0, 1, 2, 3, 4, 5}, true).get(), 3, 4, createLinkedList({1000000, 1000001, 1000002}, true).get()));
    checkAndDeleteLinkedList({0, 1, 1000000, 1000001, 1000002, 1000003, 1000004, 6},
                             solution.mergeInBetween(createLinkedList({0, 1, 2, 3, 4, 5, 6}, true).get(), 2, 5, createLinkedList({1000000, 1000001, 1000002, 1000003, 1000004}, true).get()));
}

}