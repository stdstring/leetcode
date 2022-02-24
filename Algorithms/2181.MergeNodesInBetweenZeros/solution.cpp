#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* mergeNodes(ListNode* head) const
    {
        ListNode* resultHead = nullptr;
        ListNode* resultCurrent = nullptr;
        while (head->next != nullptr)
        {
            if (head->val == 0)
            {
                ListNode* resultNext = new ListNode(0);
                if (resultHead == nullptr)
                    resultHead = resultCurrent = resultNext;
                else
                {
                    resultCurrent->next = resultNext;
                    resultCurrent = resultNext;
                }
            }
            else
                resultCurrent->val += head->val;
            head = head->next;
        }
        return resultHead;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace MergeNodesInBetweenZerosTask
{

TEST(MergeNodesInBetweenZerosTaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteLinkedList({4, 11}, solution.mergeNodes(createLinkedList({0, 3, 1, 0, 4, 5, 2, 0}, true).get()));
    checkAndDeleteLinkedList({1, 3, 4}, solution.mergeNodes(createLinkedList({0, 1, 0, 3, 0, 2, 2, 0}, true).get()));
}

}