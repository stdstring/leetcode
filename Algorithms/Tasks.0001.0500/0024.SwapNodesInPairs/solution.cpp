#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* swapPairs(ListNode* head)
    {
        if (head == nullptr)
            return head;
        if (head->next == nullptr)
            return head;
        ListNode* current = head;
        head = current->next;
        swapNodes(nullptr, current);
        ListNode* prev = current;
        current = current->next;
        while (current != nullptr && current->next != nullptr)
        {
            swapNodes(prev, current);
            prev = current;
            current = current->next;
        }
        return head;
    }

private:
    void swapNodes(ListNode* prev, ListNode* current)
    {
        ListNode* next = current->next;
        current->next = next->next;
        next->next = current;
        if (prev != nullptr)
            prev->next = next;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace SwapNodesInPairsTask
{

TEST(SwapNodesInPairsTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({2, 1, 4, 3}, solution.swapPairs(createLinkedList({1, 2, 3, 4}, false).get()));
}

}